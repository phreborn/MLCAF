#!/bin/bash

REGION="OtherJetsTFR"
TASK="FF-closure"

tqmerge -o sampleFolders/analyzed/samples-analyzed-LQtaub-lephad-${REGION}-${TASK}.root -t analyze \
    batchOutput/unmerged_${REGION}-${TASK}/*.root \
    `find ./batchOutput/unmerged_OtherJetsTFR-FF -name "*.root" | grep MultiJets` \
    `find ./batchOutput/unmerged_OtherJetsTFR-FF -name "*.root" | grep -v MultiJets | grep -v mcFake` \
