#!/bin/bash

NCORES=1
if [ ! -z $1 ]; then
    NCORES=$1
fi
echo "Setting NCORES = ${NCORES}"

#declare -a SYSTYPES=("fakevar" "isovar" "weightvar" "topvar" "lpxvar" "weightvar")
declare -a SYSTYPES=("treevar")

for systype in "${SYSTYPES[@]}"; do
    python bsmtautau_lephad/config-SignalControlRegion/syst-old/scriptSubmit.py --systype ${systype} --stage merge --ncores ${NCORES}
done
