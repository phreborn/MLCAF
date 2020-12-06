#!/bin/bash
IDENTIFIER="nominal"

tqmerge -o sampleFolders/analyzed/samples-analyzed-AHZ-lephad-${IDENTIFIER}.root -t analyze batchOutput/unmerged_${IDENTIFIER}/*.root
