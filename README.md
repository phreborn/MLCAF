[![pipeline status](https://gitlab.cern.ch/atlas-caf/CAFExample/badges/master/pipeline.svg)](https://gitlab.cern.ch/atlas-caf/CAFExample/commits/master)

Example CAFCore Analysis
=========================

This repository is meant as an example for how to construct an analysis using the [CAFCore](https://gitlab.cern.ch/atlas-caf/CAFCore) framework. In order to begin a new analysis, simply fork this project and modify the scripts and configs which are available here.

Cloning the project
--------------------

```bash
setupATLAS
lsetup git
mkdir AnalysisExample
cd AnalysisExample

# There are a few different protocol options for cloning the project, which are all provided at the top of the main page of the repository.
# Kerberos is typically recommended if it is available (e.g. lxplus) since it does not require a username or password when interacting with remote repositories.
# ssh acts similarly, but requires a bit of initial setup
# https is usually the most robust, but always requres a username and password

# Kerberos
git clone --recursive https://:@gitlab.cern.ch:8443/atlas-caf/CAFExample.git
# ssh
#git clone --recursive ssh://git@gitlab.cern.ch:7999/atlas-caf/CAFExample.git
# https
#git clone --recursive https://gitlab.cern.ch/atlas-caf/CAFExample.git

cd CAFExample
git submodule update --remote
cd ..
```

Building the project
---------------------

```bash
mkdir build output
cd build
asetup AnalysisBase,21.2.23
cmake ../CAFExample
source ../CAFExample/setup/setupAnalysis.sh
make -j4
```

Running an example analysis on flat nTuples
-------------------------------------------

The following scripts will (very quickly) run over a selection of flat nTuples to reproduce the cutflow and some visualized results for a Zjets Fake Factor estimate. It is not meant to describe the bare minimum configuration needed for producing results (that's what the dummy example provided in the near future will be for).
Similarly, a full-blown analysis is likely to include a host of custom observables which are calculated on-the-fly during runtime and for many more events (all quantities in this case have been pre-computed).
Rather, it is simply meant to showcase how fast results can be obtained once the uninteresting events have been skimmed away and the necessary quantities are already available directly in the TTree.

```bash
cd ../CAFExample/share
./prepare.py flatNTuple/config/master/prepare-ZjetsFF-Example.cfg
./initialize.py flatNTuple/config/master/initialize-ZjetsFF-Example.cfg
./analyze.py flatNTuple/config/master/analyze-ZjetsFF-Example.cfg
./visualize.py flatNTuple/config/master/visualize-ZjetsFF-Example.cfg
```

Alternatively, the analysis scripts above can also be run from an arbitrary directory. The config files still have to be specified relative to the share folder:
```bash
cd any/location/
prepare.py flatNTuple/config/master/prepare-ZjetsFF-Example.cfg
initialize.py flatNTuple/config/master/initialize-ZjetsFF-Example.cfg
analyze.py flatNTuple/config/master/analyze-ZjetsFF-Example.cfg
visualize.py flatNTuple/config/master/visualize-ZjetsFF-Example.cfg
```

On Every Login
--------------

Navigate to the working directory and

```bash
setupATLAS
cd build
asetup --restore
source ../CAFExample/setup/setupAnalysis.sh
```
