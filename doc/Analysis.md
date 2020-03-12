Running the analysis
====================

Navigate to the execution directory to begin
```bash
cd BSMtautauCAF/share
```

Preparing and initializing inputs for the nominal analysis
----------------------------------------------------------

First you need to collect the list of input sample ROOT files you will be running over in the nominal analysis.  
Our framework is currently designed to run over flat ntuples produced by the [xTauFramework](https://gitlab.cern.ch/atlas-phys-hdbs-htautau/xTauFramework).  
It may be preferable to use pre-slimmed/skimmed samples where possible, in order to gain an improvement in performance.  
Unless you change these samples, this step will only need to be run once.
```bash
# Define the remote locations of your input samples by pinging them on EOS through XRootD
source bsmtautau_lephad/config-Common/samples/inputFileLists/collectSamples.sh eosatlas "/eos/atlas/path/to/my/ntuples/YYMMDD"
# Alternatively, this can be switched to access the EOS user area instead
#source bsmtautau_lephad/config-Common/samples/inputFileLists/collectSamples.sh eosuser "/eos/user/path/to/my/ntuples/YYMMDD"
# Or, you could set the input path to your samples by pointing to any other local directory
#source bsmtautau_lephad/config-Common/samples/inputFileLists/collectSamples.sh local "/any/other/path/to/my/ntuples/YYMMDD"
```

Then prepare a `TQSampleFolder` representation of your input samples, with their weights initialized.  
Unless you change the cross-section values, this step will also only need to be run once.
```bash
# Prepare and initialize your samples
source bsmtautau_lephad/config-Common/scriptPrepareInitialize.sh
```

Fake background estimation
--------------------------

For the lephad channel, the fakes (lepton/jet fake tau) are estimated using a data-driven fake-factor method. 
All these fake-factors and their systematic uncertaintiees can be found in `/eos/atlas/atlascerngroupdisk/phys-higgs/HSG6/Htautau/lephad/CAFInput/Run2`. 
In case you want to produce them yourself, please refer to the instructions [here](doc/Fakes.md).

Running the SR/VR/TCR in the nominal analysis
---------------------------------------------

```bash
# Copy the fake factors and scale factors
cp -r /eos/atlas/atlascerngroupdisk/phys-higgs/HSG6/Htautau/lephad/CAFInput/Run2/* .

# Debug test before sending the jobs to a cluster
source configSignalControlRegion/scriptDebug.sh

# Submit the analysis to a cluster
source configSignalControlRegion/scriptSubmit.sh

# Merge the output after all jobs are finished successfully
source configSignalControlRegion/scriptMerge.sh

# Visualize plots
source configSignalControlRegion/scriptVisualize.sh 

# Obtain the extrapolation systematic uncertainty of jet fake factors
python scripts/calculateScaleFactor.py VR

# Put the systematic uncertainties into one root file
hadd ScaleFactors/VR_SF.root ScaleFactors/VR*SF.root
```

Prepare the inputs for the systematic analysis
----------------------------------------------

If there is no change to the input files or the cross-section files, this step is only needed to be run one time.
```bash
# Initialize the samples with 10 subprocesses to speed up
source configSignalControlRegion/syst/scriptInitialize.sh 10
```

Running the SR/VR/TCR in the systematic analysis
------------------------------------------------

The systematic uncertainties are classified into two types:
- SYS: need to run over different trees in the systematic samples
- NOM: need to run over NOMINAL tree in the systematic/nominal samples, need the output from SYS.

```bash
# First, run SYS
# Submit the anslysis into a cluster
source configSignalControlRegion/syst/scriptSubmit.sh SYS 10

# Merge the output after all jobs are finished successfully
source configSignalControlRegion/syst/scriptMerge.sh SYS 10

# Then, run NOM
# Submit the anslysis into a cluster
source configSignalControlRegion/syst/scriptSubmit.sh NOM 10

# Merge the output after all jobs are finished successfully
source configSignalControlRegion/syst/scriptMerge.sh NOM 10
```

Produce the workspace inputs (SR, TCR)
--------------------------------------

```bash
# Dump systematic outputs to standard ROOT files
python configSignalControlRegion/syst/scriptDumpHist.py

# Merge the systematic outputs for each region
python configSignalControlRegion/syst/scriptMergeHist.py

# Produce the workspace inputs
hadd -f -j 10 LimitHistograms.13teV.Attlh.mc16ade.YYMMDDD.v1.root dumpHist/c16ade_sr*.root dumpHist/c16ade_tcr*.root
```

Generate the workspace
----------------------
For Att analysis, workspace are generated using [WSMaker](https://gitlab.cern.ch/atlas-phys-hdbs-htautau/WSMaker_Htautau).
