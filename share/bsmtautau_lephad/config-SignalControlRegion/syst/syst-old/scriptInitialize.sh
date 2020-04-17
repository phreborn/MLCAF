#!/bin/bash

NCORES=1
if [ ! -z $1 ]; then
    NCORES=$1
fi
echo "Setting NCORES = ${NCORES}"

python configSignalControlRegion/syst/submit_systematics.py --systype treevar --stage initialize --ncores ${NCORES}
