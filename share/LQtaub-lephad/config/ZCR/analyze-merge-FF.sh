#!/bin/bash

REGION="ZCR"
TASK="FF"
tqmerge -o sampleFolders/analyzed/samples-analyzed-LQtaub-lephad-${REGION}-${TASK}-NOMINAL.root -t analyze batchOutput/unmerged_${REGION}-${TASK}/*.root


