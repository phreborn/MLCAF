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
    #declare -a SYSTYPES=("isovar" "fakevar" "weightvar" "lpxvar" "topvar")
    ## running with NOMINAL branch of standard samples
    #declare -a SYSTYPES=("isovar" "fakevar")
    #declare -a SYSTYPES=("fakevar")
    #declare -a SYSTYPES=("isovar")
    ## running with NOMINAL branch of sys samples
    #declare -a SYSTYPES=("weightvar" "lpxvar" "topvar")
    declare -a SYSTYPES=("topvar")
elif [ "$1" == "SYS" ]; then
    # running with specific branch of sys samples
    declare -a SYSTYPES=("treevar")
else
    echo "Systematic set not recognised."
    return 1
fi

for systype in "${SYSTYPES[@]}"; do
    python configSignalControlRegion/syst/submit_systematics.py --systype ${systype} --stage analyze --ncores ${NCORES}
done
