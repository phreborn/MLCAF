#!/bin/bash

TASK="MultiJetsLFR-opt"
tqmerge -o sampleFolders/analyzed/samples-analyzed-AHZ-lephad-${TASK}.root -t analyze batchOutput/unmerged_${TASK}/*.root
