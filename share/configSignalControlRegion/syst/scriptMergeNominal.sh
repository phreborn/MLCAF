#!/bin/bash

tqmerge -o sampleFolders/analyzed/samples-analyzed-htautau_lephad_sr-NOMINAL.root -t analyze batchOutput/unmerged_SRsys/*.root batchOutput/unmerged_SR/*_SR_data_*.root
