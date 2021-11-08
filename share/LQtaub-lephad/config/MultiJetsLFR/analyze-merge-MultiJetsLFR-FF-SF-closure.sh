#!/bin/bash

TASK="MultiJetsLFR-FF-SF-closure"
tqmerge -o sampleFolders/analyzed/samples-analyzed-LQtaub-lephad-${TASK}.root -t analyze \
    batchOutput/unmerged_${TASK}/*.root \
    sampleFolders/analyzed/samples-analyzed-LQtaub-lephad-MultiJetsLFR-FF.root 
