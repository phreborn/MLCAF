#!/bin/bash

TASK="TCR-SF"
tqmerge -o sampleFolders/analyzed/samples-analyzed-AHZ-lephad-${TASK}.root -t analyze batchOutput/unmerged_${TASK}/*.root
