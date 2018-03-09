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
./prepare.py example/config/master/run2-prepare-ZjetsFF-Example.cfg
./initialize.py example/config/master/run2-initialize-ZjetsFF-Example.cfg
./analyze.py example/config/master/run2-analyze-ZjetsFF-Example.cfg
./visualize.py example/config/master/run2-visualize-ZjetsFF-Example.cfg
```