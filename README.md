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

git checkout -b myDevBranch

cd -
```

Building the project
---------------------

```bash
mkdir build run
cd build
asetup AnalysisBase,21.2.34
cmake ../BSMtautauCAF
source ../BSMtautauCAF/setup/setupAnalysis.sh
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
source ../BSMtautauCAF/setup/setupAnalysis.sh
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

```bash
cd BSMtautauCAF/share

# First edit without committing the 'dataPaths' and 'mcPaths' for NOM/SYS in
configCommon/htautau_lephad_common_campaigns_input*.cfg
# relevant for your setup (don't let them be too long or you could see errors)
```

### Lepton Fake Region
```bash
# Prepare and initialize your samples
source configLeptonFakeRegion/scriptPrepareInitialize.sh
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

# To check back the LFF modelling in the LFR
# Prepare and initialize your samples with fakes
source configLeptonFakeRegion/applyFF/scriptPrepareInitialize.sh
# Debug test the analysis with fakes
source configLeptonFakeRegion/applyFF/scriptDebug.sh
# Submit the fake analysis to a cluster
source configLeptonFakeRegion/applyFF/scriptSubmit.sh
# After all cluster jobs have finished, merge the output with the existing file
source configLeptonFakeRegion/applyFF/scriptMerge.sh
# Visualize plots with fakes
source configLeptonFakeRegion/applyFF/scriptVisualize.sh
```

### W+jets Fake Region
```bash
# Prepare and initialize your samples
source configWjetsFakeRegion/scriptPrepareInitialize.sh
# Debug test the analysis
source configWjetsFakeRegion/scriptDebug.sh
# Submit the full analysis to a cluster
source configWjetsFakeRegion/scriptSubmit.sh
# After all cluster jobs have finished, merge the output
source configWjetsFakeRegion/scriptMerge.sh
# Visualize plots          
source configWjetsFakeRegion/scriptVisualize.sh
# Calculate W+jets fake factors
python scripts/calculateFakeFactor.py WFR

# To check back the WFF modelling in the WFR
# Prepare and initialize your samples with fakes
source configWjetsFakeRegion/applyFF/scriptPrepareInitialize.sh
# Debug test the analysis with fakes
source configWjetsFakeRegion/applyFF/scriptDebug.sh
# Submit the fake analysis to a cluster
source configWjetsFakeRegion/applyFF/scriptSubmit.sh
# After all cluster jobs have finished, merge the output with the existing file
source configWjetsFakeRegion/applyFF/scriptMerge.sh
# Visualize plots with fakes
source configWjetsFakeRegion/applyFF/scriptVisualize.sh
```

### Signal Region, Validation Region, W+jets/Top Control Regions
```bash
# Prepare and initialize your samples
source configSignalControlRegion/scriptPrepareInitialize.sh
# Debug test the analysis
source configSignalControlRegion/scriptDebug.sh
# Submit the full analysis to a cluster
source configSignalControlRegion/scriptSubmit.sh
# After all cluster jobs have finished, merge the output
source configSignalControlRegion/scriptMerge.sh
# Visualize plots
source configSignalControlRegion/scriptVisualize.sh
```

### Systematics (Signal Region, Validation Region, W+jets/Top Control Regions)
```bash
# Prepare and initialize your systematic variation samples
source configSignalControlRegion/syst/scriptPrepareInitializeSystematics.sh
# Submit the full systematic analysis to a cluster
source configSignalControlRegion/syst/scriptSubmitSystematics.sh
# After all cluster jobs have finished, merge the output
source configSignalControlRegion/syst/scriptMergeSystematics.sh
# Write the systematics to band files and tables
source configSignalControlRegion/syst/scriptWriteSystematics.sh
# Re-visualize plots
source configSignalControlRegion/scriptVisualize.sh
```

### Workspace inputs (Signal Region, Top Control Region)
```bash
# Dump systematic outputs to standard ROOT files and merge
source configSignalControlRegion/syst/scriptDumpHist.sh
```

Old README content
------------------
TODO: Decide how to calculate FF:
    - proposed function in the calculateFakeFactor.py script works well;
        -- calcJetFakeFactorFinal(identifier, dataPath, bkgPath, nominator, denominator, histogram, channel, region, uncertainty)
        ---- make cosmetic improvements for FF plots.

IMPORTANT: Top samples with dilepton filter contains more statistics because we use truth matching anyway.
        Be careful to use allhad/nonallhad top samples for QCD regions.

####################
### WCR stuff:
####################

In WCR the sample folder structure is made that truth labels are separate and there are lephad, muhad and ehad channels which are
executed separately so in config file under runAnalysis.channel write which ones to run over. This takes more time but is more flexible
and requires less hardcoding in cuts and histos config files.

## for nominal plotting, cutflow, study use:
    # config:
    config/htautau_lephad_wfr.cfg

    because we want to plot all truth labels but they are not needed for ff calculation,
    so we save time and make things more clear.

## for ff measurement:
    # config:
    config/htautau_lephad_wfr_ff.cfg

    this is only to make Pt histos with proper binning and Pass and Fail cuts.

## for applying ff to wcr:
    # config:
    config/htautau_lephad_wfr_applyff.cfg

    atm this doesn't include QCD, but studies could be made to show that QCD changes nothing to ff,
    or at least not significantly.
