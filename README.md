[![pipeline status](https://gitlab.cern.ch/atlas-caf/CAFExample/badges/master/pipeline.svg)](https://gitlab.cern.ch/atlas-caf/CAFExample/commits/master)

Example CAFCore Analysis
=========================

This repository is meant as an example for how to construct an analysis using the [CAFCore](https://gitlab.cern.ch/atlas-caf/CAFCore) framework. In order to begin a new analysis, simply fork this project and modify the scripts and configs which are available here.

Cloning the project
--------------------

```bash
setupATLAS
lsetup git
mkdir BSMtautauCAF
cd BSMtautauCAF

# There are a few different protocol options for cloning the project, which are all provided at the top of the main page of the repository.
# Kerberos is typically recommended if it is available (e.g. lxplus) since it does not require a username or password when interacting with remote repositories.
# ssh acts similarly, but requires a password and a bit of initial setup
# https is usually the most robust, but always requres a username and password

# Kerberos
git clone --recursive https://:@gitlab.cern.ch:8443/${USER}/BSMtautauCAF.git
# ssh
#git clone --recursive ssh://git@gitlab.cern.ch:7999/atlas-caf/CAFExample.git
# https
#git clone --recursive https://gitlab.cern.ch/atlas-caf/CAFExample.git
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
```

Running the analysis
--------------------

TBA


On Every Login
--------------

Navigate to the working directory and

```bash
setupATLAS
lsetup git
cd build
asetup --restore
source ../BSMtautauCAF/setup/setupAnalysis.sh
```
