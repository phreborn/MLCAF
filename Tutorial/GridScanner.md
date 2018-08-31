WORK IN PROGRESS

This document is intended to provide instructions on how to utilize the GridScanner feature provided by [CAF](https://gitlab.cern.ch/atlas-caf/CAFCore).
Currently, the branch GridScanner-rewrite of CAF needs to be checked out to run the following (assuming you are in the CAFExample/share directory):

```bash
# Step 1: Prepare multidimensional histogram (grid)
./prepare.py xAOD/config/master/prepare-GridScanner-Example.cfg
./initialize.py xAOD/config/master/initialize-GridScanner-Example.cfg
./analyze.py xAOD/config/master/analyze-GridScanner-Example.cfg
(takes a while ~10min)

# Step 2: Run Gridscanner
../tools/runGridScanner.py common/config/gridscanner/GridScanner-Example.cfg --plotInputs
../tools/runGridScanner.py common/config/gridscanner/GridScanner-Example.cfg --plotResults
```
