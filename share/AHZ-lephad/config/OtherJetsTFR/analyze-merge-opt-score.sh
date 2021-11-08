#!/bin/bash

REGION="OtherJetsTFR"
TASK="opt-score"

tqmerge -o sampleFolders/analyzed/samples-analyzed-AHZ-lephad-${REGION}-${TASK}.root -t analyze batchOutput/unmerged_${REGION}-${TASK}/*.root
