#!/bin/bash

### individual sys
for SYS in "lff" "lsf" "wff" "wsf" "vsf" "lpx" "top" "weight" "p4"; do
    # "material"
    tqmerge -o sampleFolders/analyzed/samples-analyzed-bsmtautau_lephad_sr_sys_"${SYS}".root -t analyze batchOutput/unmerged_SRsys"${SYS}"/*.root
done

### all sys + nominal
tqmerge -o sampleFolders/analyzed/samples-analyzed-bsmtautau_lephad_sr_sys.root -t analyze sampleFolders/analyzed/samples-analyzed-bsmtautau_lephad_sr_sys_*.root sampleFolders/analyzed/samples-analyzed-bsmtautau_lephad_sr.root
