BSMtautau CAFCore Analysis
=========================

This repository is meant to construct an analysis for the BSMtautau LepHad channel using the [CAFCore](https://gitlab.cern.ch/atlas-caf/CAFCore) framework.  
Further help about the Common Analysis Framework can be found [here](http://atlas-caf.web.cern.ch).  
If there are any problems, please refer to the [FAQ](https://gitlab.cern.ch/atlas-phys-hdbs-htautau/BSMtautauCAF/blob/master/doc/FAQ.md) first.  
If the problem is not listed there, then please feel free to contact the project maintainers:  
- Xiaozhong Huang (xiaozhong.huang@cern.ch)
- Theodore Zorbas (t.zorbas@cern.ch)

Cloning the project
--------------------

First ensure you have [forked](https://gitlab.cern.ch/atlas-phys-hdbs-htautau/BSMtautauCAF/forks/new) the repository, then

```bash
setupATLAS
lsetup git
# Set up your work area with any name you want
mkdir myWorkDir
cd myWorkDir

# There are a few different protocol options for cloning the project, which are all provided at the top of the main page of the repository.
# Kerberos is typically recommended if it is available (e.g. lxplus) since it does not require a username or password when interacting with remote repositories.
# ssh acts similarly, but requires a password and a bit of initial setup
# https is usually the most robust, but always requres a username and password

# Kerberos
git clone --recursive https://:@gitlab.cern.ch:8443/${USER}/BSMtautauCAF.git
# ssh
#git clone --recursive ssh://git@gitlab.cern.ch:7999/${USER}/BSMtautauCAF.git
# https
#git clone --recursive https://gitlab.cern.ch/${USER}/BSMtautauCAF.git

# While your 'origin' would be set to your fork, you can also set the 'upstream' to the main repository.
# This way, you are able to pull in the latest updates from the main upstream repository to your fork

cd BSMtautauCAF

# Kerberos
git remote add upstream https://:@gitlab.cern.ch:8443/atlas-phys-hdbs-htautau/BSMtautauCAF.git
# ssh
#git remote add upstream ssh://git@gitlab.cern.ch:7999/atlas-phys-hdbs-htautau/BSMtautauCAF.git
# https
#git remote add upstream https://gitlab.cern.ch/atlas-phys-hdbs-htautau/BSMtautauCAF.git

# You should also avoid working on your master, and instead work from a development branch.
# This way, you can keep your master synced with the main upstream repository

git checkout myDevBranch

cd -
```

Building the project
---------------------

```bash
mkdir build
cd build
asetup AnalysisBase,21.2.102
cmake ../BSMtautauCAF
asetup source setupAnalysis.sh # this configures asetup to automatically call setupAnalysis.sh next time
cafbuild # build the code (check details by typing "type cafbuild")
export PYTHONPATH="${CAFANALYSISBASE:?}/tools:${PYTHONPATH}"
cd -
```

On Every Login
--------------

Navigate to the working directory and

```bash
setupATLAS
lsetup git
cd build
asetup
export PYTHONPATH="${CAFANALYSISBASE:?}/tools:${PYTHONPATH}"
cd -
```

Recompiling the project
-----------------------

If you have edited any `C++` files such as observables, you can quickly recompile the project from any directory using

```bash
cafcompile
```

Updating your fork
------------------

Further help can be found at the [ATLAS Git Workflow tutorial](https://atlassoftwaredocs.web.cern.ch/gittutorial/).

```bash
cd BSMtautauCAF
git fetch upstream
git pull upstream master
cd -
```

Running the analysis
--------------------

Navigate to the execution directory
```bash
cd BSMtautauCAF/share
```

### Preparing and initializing inputs for the nominal analysis
First you need to collect the list of input sample ROOT files you will be running over in the nominal analysis.  
Our framework is currently designed to run over flat ntuples produced by the [xTauFramework](https://gitlab.cern.ch/atlas-phys-hdbs-htautau/xTauFramework).  
Unless you change these samples, this step will only need to be run once.
```bash
# Define the remote locations of your input samples by pinging them on EOS through XRootD
source configCommon/collectSamples.sh eosatlas "/eos/atlas/path/to/my/ntuples/YYMMDD"
# Alternatively, this can be switched to access the EOS user area instead
#source configCommon/collectSamples.sh eosuser "/eos/user/path/to/my/ntuples/YYMMDD"
# Or, you could set the input path to your samples by pointing to any other local directory
#source configCommon/collectSamples.sh local "/any/other/path/to/my/ntuples/YYMMDD"
```

Then prepare a `TQSampleFolder` representation of your input samples, with their weights initialized.  
Unless you change the cross-section values, this step will also only need to be run once.
```bash
# Prepare and initialize your samples
source configCommon/scriptPrepareInitialize.sh
```

### Fake background estimation
For the LepHad channel, the fakes (lepton/jet fake tau) are estimated using a data-driven fake-factor method.  
All these fake-factors and their systematic uncertaintiees are avaiable in the repository.  
In case you want to produce them yourself, please refer to the instructions [here](https://gitlab.cern.ch/atlas-phys-hdbs-htautau/BSMtautauCAF/blob/master/doc/Fakes.md).

### Running the SR/VR/TCR in the nominal analysis
```bash
# Debug test before sending the jobs to a cluster
source configSignalControlRegion/scriptDebug.sh

# Submit the analysis to a cluster
source configSignalControlRegion/scriptSubmit.sh

# Merge the output after all jobs are finished successfully
source configSignalControlRegion/scriptMerge.sh

# Visualize plots
source configSignalControlRegion/scriptVisualize.sh 
```

### Prepare the inputs for the systematic analysis
If there is no change to the input files or the cross-section files, this step is only needed to be run one time.
```bash
# Initialize the samples with 10 subprocesses to speed up
source configSignalControlRegion/syst/scriptPrepareInitialize.sh 10
```

### Running the SR/VR/TCR in the systematic analysis
The systematic uncertainties are classified into two types:
- SYS: need to run over different trees in the systematic samples
- NOM: need to run over NOMINAL tree in the systematic/nominal samples, need the output from SYS.

```bash
# First, run SYS
# Submit the anslysis into a cluster
souce configSignalControlRegion/syst/scriptSubmit SYS 10

# Merge the output after all jobs are finished successfully
source configSignalControlRegion/syst/scriptMerge.sh SYS 10

# Then, run NOM
# Submit the anslysis into a cluster
souce configSignalControlRegion/syst/scriptSubmit NOM 10

# Merge the output after all jobs are finished successfully
source configSignalControlRegion/syst/scriptMerge.sh NOM 10
```

### Produce the workspace inputs (SR, TCR)

```bash
# Dump systematic outputs to standard ROOT files
python configSignalControlRegion/syst/scriptDumpHist.py

# Merge the systematic outputs for each region
python configSignalControlRegion/syst/scriptMergeHist.py

# Produce the workspace inputs
hadd -f -j 10 LimitHistograms.13teV.Attlh.mc16ade.YYMMDDD.v1.root dumpHist/c16ade_sr*.root dumpHist/c16ade_tcr*.root
```

### Generate the worksapce
For Att analysis, workspace are generated using [WSMaker](https://gitlab.cern.ch/atlas-phys-hdbs-htautau/WSMaker_Htautau).
