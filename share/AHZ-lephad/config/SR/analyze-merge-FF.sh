#!/bin/bash

REGION="SR"
TASK="FF"
tqmerge -o sampleFolders/analyzed/samples-analyzed-AHZ-lephad-${REGION}-${TASK}-NOMINAL.root -t analyze batchOutput/unmerged_${REGION}-${TASK}/*.root --downmerge generalize --patch AHZ-lephad/config/common/patches/downmerge.txt --patch AHZ-lephad/config/common/patches/trimmingAfterPooling.txt


