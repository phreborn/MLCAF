Example CAFCore Analysis
=========================

This repository is meant as an example for how to construct an analysis using the [CAFCore](https://gitlab.cern.ch/atlas-caf/CAFCore) framework. In order to begin a new analysis, simply fork this project and modify the scripts and configs which are available here.

Cloning the project
--------------------

```bash
mkdir AnalysisExample
cd AnalysisExample
git clone --recursive https://:@gitlab.cern.ch:8443/atlas-caf/CAFExample.git
cd CAFExample
git submodule update --remote
cd ..
```

Building the project
---------------------

```bash
mkdir build
cd build
setupATLAS
asetup 21.2.4,AnalysisBase
cmake ../CAFExample
make
```

Running a test
--------------

```bash
cd ../CAFExample
source CAFCore/cafsetup.sh
cd share
./prepare.py config/test/run2-ZjetsTest.cfg
./initialize.py config/test/run2-ZjetsTest.cfg