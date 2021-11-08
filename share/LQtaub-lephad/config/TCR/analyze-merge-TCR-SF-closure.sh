#!/bin/bash

TASK="TCR-SF-closure"
tqmerge -o sampleFolders/analyzed/samples-analyzed-LQtaub-lephad-${TASK}.root -t analyze \
    batchOutput/unmerged_${TASK}/*.root \
    `find ./batchOutput/unmerged_TCR-SF -name "*.root" | grep Top | grep MultiJets` \
    `find ./batchOutput/unmerged_TCR-SF -name "*.root" | grep -v Top`
