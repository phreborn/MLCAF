#!/bin/bash

TASK="ZCR-FF-closure"
tqmerge -o sampleFolders/analyzed/samples-analyzed-LQtaub-lephad-${TASK}-NOMINAL.root -t analyze \
    batchOutput/unmerged_${TASK}/*.root \
    `find ./batchOutput/unmerged_ZCR-FF -name "*.root" | grep Zjets | grep MultiJets` \
    `find ./batchOutput/unmerged_ZCR-FF -name "*.root" | grep -v Zjets`
