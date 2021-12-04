#!/bin/bash

REGION="AntiID"
TASK="FF"
tqmerge -o sampleFolders/analyzed/samples-analyzed-LQtaub-lephad-${REGION}-${TASK}-NOMINAL.root -t analyze batchOutput/unmerged_${REGION}-${TASK}/*.root --downmerge generalize --patch LQtaub-lephad/config/common/patches/downmerge.txt --patch LQtaub-lephad/config/common/patches/trimmingAfterPooling.txt


