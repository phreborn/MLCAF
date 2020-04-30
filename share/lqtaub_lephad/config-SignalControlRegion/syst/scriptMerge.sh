#!/bin/bash

# common config
SAMPLEBASE="sampleFolders/analyzed/samples-analyzed-lqtaub_lephad_sr"

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
            batchOutput/unmerged_SRsys"${ARG}"/*.root \
            -o "${SAMPLEBASE}"_sys_"${ARG}".root
    fi
done
