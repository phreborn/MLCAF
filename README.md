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
# ssh acts similarly, but requires a password and a bit of initial setup
# https is usually the most robust, but always requres a username and password

# Kerberos
git clone --recursive https://:@gitlab.cern.ch:8443/atlas-caf/CAFExample.git
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
asetup AnalysisBase,21.2.102
cmake ../CAFExample
source CAFExample/setupAnalysis.sh
make -j4
```

Running a minimal example
-------------------------

The following commands will reproduce (in seconds) a minimal example, showcasing the least amount of configuration necessary to produce results by taking a VBF signal MC sample and passing it through a single cut on Mjj while producing one histogram.

```bash
cd ../CAFExample/share
./prepare.py minimal/config/master/prepare-Minimal-Example.cfg
./initialize.py minimal/config/master/initialize-Minimal-Example.cfg
./analyze.py minimal/config/master/analyze-Minimal-Example.cfg
./visualize.py minimal/config/master/visualize-Minimal-Example.cfg
```

Running an example analysis on flat nTuples
-------------------------------------------

The following commands will (very quickly) run over a selection of flat nTuples to reproduce the cutflow and some visualized results for a Zjets Fake Factor analysis. It is not meant to describe the bare minimum configuration needed for producing results (that's what the minimal example above is for).
Similarly, a full-blown analysis is likely to include a host of custom observables which are calculated on-the-fly during runtime and for many more events (all quantities in this case have been pre-computed).
Rather, it is simply meant to showcase how fast results can be obtained once the uninteresting events have been skimmed away and the necessary quantities are already available directly in the TTree.

```bash
cd ../CAFExample/share
./prepare.py flatNTuple/config/master/prepare-flatNTuple-Example.cfg
./initialize.py flatNTuple/config/master/initialize-flatNTuple-Example.cfg
./analyze.py flatNTuple/config/master/analyze-flatNTuple-Example.cfg
./visualize.py flatNTuple/config/master/visualize-flatNTuple-Example.cfg
```

Running an example analysis on xAOD inputs
------------------------------------------

The following commands will (on order of minutes) run over a selection of xAOD inputs to reproduce the same Zjets Fake Factor analysis as in the flat nTuple example above. A couple of important differences exist between the two variants. First, while the xAODs have been skimmed to cut down on runtime, their events haven't been removed quite as aggressively as in the flat nTuple case - there are still about an order of magnitude more. Secondly, the xAOD analysis showcases in addition the use of a number of custom observables to calculate quantities for on-the-fly use, which again contributes to a slightly longer runtime.

```bash
cd ../CAFExample/share
./prepare.py xAOD/config/master/prepare-xAOD-Example.cfg
./initialize.py xAOD/config/master/initialize-xAOD-Example.cfg
./analyze.py xAOD/config/master/analyze-xAOD-Example.cfg
./visualize.py xAOD/config/master/visualize-xAOD-Example.cfg
```

Running from an arbitrary location
----------------------------------

Alternatively, each of the analysis scripts above can also be run from an arbitrary directory. The master config files still have to be specified relative to the share folder, although they can be discovered via tab completion:

e.g.

```bash
cd run/or/any/other/location/
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
lsetup git
cd build
asetup --restore
source CAFExample/setupAnalysis.sh
```
