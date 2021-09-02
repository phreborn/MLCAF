#!/bin/bash

# common config
SAMPLEBASE="sampleFolders/analyzed/samples-analyzed-AHZ-lephad-SR-FF"

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
            batchOutput/unmerged_SYS-"${ARG}"-FF/*.root \
            -o "${SAMPLEBASE}"-SYS-"${ARG}".root \
            --downmerge generalize \
            --patch AHZ-lephad/config/common/patches/downmerge.txt \
            --patch AHZ-lephad/config/common/patches/trimmingAfterPooling.txt
    fi
done
