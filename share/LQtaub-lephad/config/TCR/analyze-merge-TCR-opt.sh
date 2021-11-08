#!/bin/bash

TASK="TCR-opt"
tqmerge -o sampleFolders/analyzed/samples-analyzed-LQtaub-lephad-${TASK}.root -t analyze batchOutput/unmerged_${TASK}/*.root
