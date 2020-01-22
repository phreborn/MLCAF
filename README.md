BSMtautau CAFCore Analysis
=========================

This repository is meant to construct an analysis for the BSMtautau LepHad channel using the [CAFCore](https://gitlab.cern.ch/atlas-caf/CAFCore) framework.

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
mkdir build run
cd build
asetup AnalysisBase,21.2.78
cmake ../BSMtautauCAF
source setupAnalysis.sh
export PYTHONPATH="${CAFANALYSISBASE:?}/tools:${PYTHONPATH}"
make -j4
cd -
```

On Every Login
--------------

Navigate to the working directory and

```bash
setupATLAS
lsetup git
cd build
asetup --restore
source setupAnalysis.sh
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

### Initialization
```bash
# First define the remote locations of your input samples by pinging them on EOS through XRootD
MY_SAMPLE_DIR="/eos/atlas/atlascerngroupdisk/phys-higgs/HSG6/Htautau/lephad/ntuples/190530"
source configCommon/collectSamples.sh remote "${MY_SAMPLE_DIR:?}"
# Alternatively, you could set the input path to your samples by pointing to any local directory
#source configCommon/collectSamples.sh local "${MY_SAMPLE_DIR:?}"

# Prepare and initialize your samples
source configCommon/scriptPrepareInitialize.sh
```

### Lepton/QCD Fake Region (L/QFR)
```bash
# Debug test the analysis
source configLeptonFakeRegion/scriptDebug.sh
# Submit the full analysis to a cluster
source configLeptonFakeRegion/scriptSubmit.sh
# After all cluster jobs have finished, merge the output
source configLeptonFakeRegion/scriptMerge.sh
# Visualize plots
source configLeptonFakeRegion/scriptVisualize.sh
# Calculate lepton fake factors
python scripts/calculateFakeFactor.py LFR

# To check back the L/QFF modelling in the L/QFR
# Debug test the analysis with fakes
source configLeptonFakeRegion/applyFF/scriptDebug.sh
# Submit the fake analysis to a cluster
source configLeptonFakeRegion/applyFF/scriptSubmit.sh
# After all cluster jobs have finished, merge the output with the existing file
source configLeptonFakeRegion/applyFF/scriptMerge.sh
# Visualize plots with fakes
source configLeptonFakeRegion/applyFF/scriptVisualize.sh
# Calculate lepton correction scale factors
python scripts/calculateScaleFactor.py LFR

# To check back the L/QSF modelling in the L/QFR
# Debug test the analysis with corrected fakes
source configLeptonFakeRegion/applyFF/applySF/scriptDebug.sh
# Submit the corrected fake analysis to a cluster
source configLeptonFakeRegion/applyFF/applySF/scriptSubmit.sh
# After all cluster jobs have finished, merge the output with the existing file
source configLeptonFakeRegion/applyFF/applySF/scriptMerge.sh
# Visualize plots with corrected fakes
source configLeptonFakeRegion/applyFF/applySF/scriptVisualize.sh
```

### W+jets/Top Fake Region (WFR/TFR)
```bash
# Debug test the analysis
source configWjetsFakeRegion/scriptDebug.sh
# Submit the full analysis to a cluster
source configWjetsFakeRegion/scriptSubmit.sh
# After all cluster jobs have finished, merge the output
source configWjetsFakeRegion/scriptMerge.sh
# Visualize plots          
source configWjetsFakeRegion/scriptVisualize.sh
# Calculate W+jets/Top fake factors
python scripts/calculateFakeFactor.py WFR

# To check back the WFF/TFF modelling in the WFR/TFR
# Debug test the analysis with fakes
source configWjetsFakeRegion/applyFF/scriptDebug.sh
# Submit the fake analysis to a cluster
source configWjetsFakeRegion/applyFF/scriptSubmit.sh
# After all cluster jobs have finished, merge the output with the existing file
source configWjetsFakeRegion/applyFF/scriptMerge.sh
# Visualize plots with fakes
source configWjetsFakeRegion/applyFF/scriptVisualize.sh
```

### Signal Region (SR), Validation Region (VR), W+jets/Top Control Regions (WCR/TCR)
```bash
# Debug test the analysis
source configSignalControlRegion/scriptDebug.sh
# Submit the full analysis to a cluster
source configSignalControlRegion/scriptSubmit.sh
# After all cluster jobs have finished, merge the output
source configSignalControlRegion/scriptMerge.sh
# Visualize plots
source configSignalControlRegion/scriptVisualize.sh
```

### Systematics (SR, VR, TCR)
```bash
# Calculate top correction scale factors
python scripts/calculateScaleFactor.py TCR
# Calculate validation correction scale factors
python scripts/calculateScaleFactor.py VR

# To prepare the T/VSF modelling for the NOMINAL SR/VR/TCR
# Debug test the analysis with corrected scale factors
source configSignalControlRegion/applySF/scriptDebug.sh
# Submit the corrected scale factor analysis to a cluster
source configSignalControlRegion/applySF/scriptSubmit.sh
# After all cluster jobs have finished, merge the output
source configSignalControlRegion/applySF/scriptMerge.sh

# Debug test the NOM-based systematic analysis
source configSignalControlRegion/syst/scriptDebug.sh NOM
# Submit the NOM-based systematic analysis to a cluster
source configSignalControlRegion/syst/scriptSubmit.sh NOM 1
# After all cluster jobs have finished, merge the output
source configSignalControlRegion/syst/scriptMerge.sh NOM 1
# Write the systematics to band files and tables
source configSignalControlRegion/syst/scriptWrite.sh NOM
# Visualize plots with systematics
source configSignalControlRegion/syst/scriptVisualize.sh

# Initialize your SYS-based samples
source configSignalControlRegion/syst/scriptInitialize.sh
# Debug test the SYS-based systematic analysis
source configSignalControlRegion/syst/scriptDebug.sh SYS
# Submit the SYS-based systematic analysis to a cluster
source configSignalControlRegion/syst/scriptSubmit.sh SYS 1
# After all cluster jobs have finished, merge the output
source configSignalControlRegion/syst/scriptMerge.sh SYS 1
# Re-write the full systematics to band files and tables
source configSignalControlRegion/syst/scriptWrite.sh SYS
# Re-visualize plots with full systematics
source configSignalControlRegion/syst/scriptVisualize.sh
```

### Workspace inputs (SR, TCR)
```bash
# Dump systematic outputs to standard ROOT files and merge
python configSignalControlRegion/syst/scriptDumpHist.py
```

Old README content
------------------
TODO: Decide how to calculate FF:
    - proposed function in the calculateFakeFactor.py script works well;
        -- calcJetFakeFactorFinal(identifier, dataPath, bkgPath, nominator, denominator, histogram, channel, region, uncertainty)
        ---- make cosmetic improvements for FF plots.

IMPORTANT: Top samples with dilepton filter contains more statistics because we use truth matching anyway.
        Be careful to use allhad/nonallhad top samples for QCD regions.
