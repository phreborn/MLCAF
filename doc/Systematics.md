Systematic uncertainty estimation
=================================

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
