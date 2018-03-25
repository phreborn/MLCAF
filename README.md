[![pipeline status](https://gitlab.cern.ch/atlas-caf/CAFExample/badges/master/pipeline.svg)](https://gitlab.cern.ch/atlas-caf/CAFExample/commits/master)

Example CAFCore Analysis
=========================

This repository is meant as an example for how to construct an analysis using the [CAFCore](https://gitlab.cern.ch/atlas-caf/CAFCore) framework. In order to begin a new analysis, simply fork this project and modify the scripts and configs which are available here.

Cloning the project
--------------------

```bash
setupATLAS
lsetup git # needed for 'git submodule update --remote'
mkdir AnalysisExample
cd AnalysisExample
git clone --recursive ssh://git@gitlab.cern.ch:7999/atlas-caf/CAFExample.git
cd CAFExample
git submodule update --remote
cd ..
```

Building the project
---------------------

```bash
mkdir build
cd build
asetup 21.2.4,AnalysisBase
cmake ../CAFExample
source ../CAFExample/CAFCore/cafsetup.sh
make -j4
```

Running an example analysis
----------------------------

```bash
cd ../CAFExample/share
./prepare.py nTuple/config/master/prepare-ZjetsFF-Example.cfg
./initialize.py nTuple/config/master/initialize-ZjetsFF-Example.cfg
./analyze.py nTuple/config/master/analyze-ZjetsFF-Example.cfg
./visualize.py nTuple/config/master/visualize-ZjetsFF-Example.cfg
```