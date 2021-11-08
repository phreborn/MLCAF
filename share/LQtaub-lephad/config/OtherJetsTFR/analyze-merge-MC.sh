#!/bin/bash

REGION="OtherJetsTFR"
TASK="MC"

tqmerge -o sampleFolders/analyzed/samples-analyzed-LQtaub-lephad-${REGION}-${TASK}.root -t analyze batchOutput/unmerged_${REGION}-${TASK}/*.root
