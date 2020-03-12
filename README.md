BSMtautau CAFCore Analysis
==========================

This repository is meant to construct an analysis for $`\textrm{BSM} \rightarrow \tau^{+}\tau^{-}`$ using the [CAFCore](https://gitlab.cern.ch/atlas-caf/CAFCore) framework.  

In order to begin this analysis, the repository is a fork of the [CAFExample](https://gitlab.cern.ch/atlas-caf/CAFExample) project.  
Further help about the Common Analysis Framework (CAF) can be found [here](http://atlas-caf.web.cern.ch).  

If there are any problems with the analysis, please refer to the [FAQ](doc/FAQ.md) first.  
If the problem is not listed there, then please feel free to contact the project maintainers:  
- Xiaozhong Huang (xiaozhong.huang@cern.ch)
- Theodore Zorbas (t.zorbas@cern.ch)

Cloning the project
--------------------

First ensure you have [forked](https://gitlab.cern.ch/atlas-phys-hdbs-htautau/BSMtautauCAF/forks/new) this repository, then

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

# obtain updates from upstream
git fetch upstream

# You should also avoid working on your master, and instead work from a development branch.
# This way, you can keep your master mirrored with the main upstream repository
git checkout -b myDevBranch upstream/master --no-track

cd ..
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
export CAFOUTPUTDIR="${CAFANALYSISSHARE}"
cd ..
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
export CAFOUTPUTDIR="${CAFANALYSISSHARE}"
cd ..
```

Updating your fork
------------------

Further help can be found at the [ATLAS Git Workflow tutorial](https://atlassoftwaredocs.web.cern.ch/gittutorial/).

```bash
cd BSMtautauCAF
git fetch upstream
git pull upstream master
cd ..
```

Recompiling the project
-----------------------

If you have edited any `C++` files such as observables, you can quickly recompile the project from any directory using

```bash
cafbuild
```

If you have added new `C++` files or made any other changes that also need to be registered to the library by CMake, then use

```bash
cafcompile
```

Running the analysis
--------------------

To begin processing the analysis, please refer to the [documentation](doc/Analysis.md).
