#!/bin/bash

REGION="OtherJetsTFR"
TASK="FF-SF-closure"

tqmerge -o sampleFolders/analyzed/samples-analyzed-AHZ-lephad-${REGION}-${TASK}.root -t analyze batchOutput/unmerged_${REGION}-${TASK}/*.root \
    sampleFolders/analyzed/samples-analyzed-AHZ-lephad-OtherJetsTFR-FF.root
