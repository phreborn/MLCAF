#!/bin/bash

if [ -z $1 ]; then
    echo "No type specified."
    return 1
fi

NCORES=1
if [ ! -z $2 ]; then
    NCORES=$2
fi
echo "Setting NCORES = ${NCORES}"

echo "Running over $1 set..."
if [ "$1" == "NOM" ]; then
    declare -a SYSTYPES=("isovar" "fakevar" "topvar")
elif [ "$1" == "SYS" ]; then
    declare -a SYSTYPES=("weightvar" "treevar")
else
    echo "Systematic set not recognised.
    return 1
fi

for systype in "${SYSTYPES[@]}"; do
    python configSignalControlRegion/syst/submit_systematics.py --systype ${systype} --stage analyze --ncores ${NCORES}
done
