#!/bin/bash

NCORES=1
if [ ! -z $1 ]; then
    NCORES=$1
fi
echo "Setting NCORES = ${NCORES}"

#declare -a SYSTYPES=("isovar" "fakevar" "weightvar" "lpxvar" "topvar" "treevar")
declare -a SYSTYPES=("treevar")

for systype in "${SYSTYPES[@]}"; do
    python bsmtautau_lephad/config-SignalControlRegion/syst-old/scriptSubmit.py --systype ${systype} --stage analyze --ncores ${NCORES}
done
