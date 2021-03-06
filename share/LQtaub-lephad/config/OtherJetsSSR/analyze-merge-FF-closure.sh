#!/bin/bash

REGION="OtherJetsSSR"
TASK="FF-closure"

tqmerge -o sampleFolders/analyzed/samples-analyzed-LQtaub-lephad-${REGION}-${TASK}.root -t analyze batchOutput/unmerged_${REGION}-${TASK}/*.root \
    `find ./batchOutput/unmerged_OtherJetsSSR-FF -name "*.root" | grep -v mcFakeCorrected`
