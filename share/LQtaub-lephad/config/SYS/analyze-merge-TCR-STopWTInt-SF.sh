#!/bin/bash

TASK="SR-FF-SYS-Theory_Top_STopWTInt"
tqmerge -o sampleFolders/analyzed/samples-analyzed-LQtaub-lephad-SR-FF-SYS-Theory_Top_STopWTInt.root -t analyze \
    batchOutput/unmerged_${TASK}/*.root \
    `find ./batchOutput/unmerged_SR-FF -name "*.root" | grep -v Top_single_nominal_tW`
