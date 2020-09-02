#!/bin/bash

NCORES=1
if [ ! -z $1 ]; then
    NCORES=$1
fi
echo "Setting NCORES = ${NCORES}"

python bsmtautau_lephad/config-SignalControlRegion/syst-old/scriptSubmit.py --systype treevar --stage initialize --ncores ${NCORES}
