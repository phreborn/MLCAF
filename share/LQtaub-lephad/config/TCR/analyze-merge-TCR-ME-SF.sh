#!/bin/bash

TASK="TCR-ME-SF"
tqmerge -o sampleFolders/analyzed/samples-analyzed-LQtaub-lephad-${TASK}.root -t analyze \
    batchOutput/unmerged_${TASK}/*.root \
    `find ./batchOutput/unmerged_TCR-SF -name "*.root" | grep Top | grep MultiJets` \
    `find ./batchOutput/unmerged_TCR-SF -name "*.root" | grep -v Top_ttbar | grep -v MultiJetsFake_mc_Top_single`
