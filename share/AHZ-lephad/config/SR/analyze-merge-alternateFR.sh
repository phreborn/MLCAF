#!/bin/bash

REGION="SR"
TASK="alternateFR"
tqmerge -o sampleFolders/analyzed/samples-analyzed-AHZ-lephad-${REGION}-${TASK}.root -t analyze batchOutput/unmerged_${REGION}-${TASK}/*.root
