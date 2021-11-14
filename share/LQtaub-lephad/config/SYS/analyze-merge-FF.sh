#!/bin/bash

# common config
SAMPLEBASE="sampleFolders/analyzed/samples-analyzed-LQtaub-lephad-SR-FF"

# handle arguments
if [ -z "$*" ]; then
    echo "No arguments provided!"
    return
fi
echo "Accepting arguments: $*"

# loop execute
for ARG in "$@"; do
    echo ""
    if [ "${ARG}" == "ALL" ]; then
        # merge all individual sys together with nominal
        echo "Merging ALL systematics!"
        tqmerge -t analyze \
            "${SAMPLEBASE}"_sys_*.root "${SAMPLEBASE}".root \
            -o "${SAMPLEBASE}"_sys.root
    else
        # merge individual sys
        echo "Merging systematic: ${ARG}"
        tqmerge -t analyze \
            batchOutput/unmerged_SR-FF-SYS-"${ARG}"/*.root \
            batchOutput/unmerged_SR-FF/unmerged_SR-FF_data*.root \
            -o "${SAMPLEBASE}"-SYS-"${ARG}".root \
            --downmerge generalize \
            --patch LQtaub-lephad/config/common/patches/downmerge.txt \
            --patch LQtaub-lephad/config/common/patches/trimmingAfterPooling.txt
    fi
done
