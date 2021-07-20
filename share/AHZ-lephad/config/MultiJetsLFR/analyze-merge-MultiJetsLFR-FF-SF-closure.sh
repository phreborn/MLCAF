#!/bin/bash

TASK="MultiJetsLFR-FF-SF-closure"
tqmerge -o sampleFolders/analyzed/samples-analyzed-AHZ-lephad-${TASK}.root -t analyze \
    batchOutput/unmerged_${TASK}/*.root \
    sampleFolders/analyzed/samples-analyzed-AHZ-lephad-MultiJetsLFR-FF.root 
