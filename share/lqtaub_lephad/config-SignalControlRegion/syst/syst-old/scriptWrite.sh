#!/bin/bash

if [ -z $1 ]; then
    echo "No type specified."
    return 1
fi

echo "Running over $1 set..."
if [ "$1" == "NOM" ]; then
    SYSTYPE=$1
elif [ "$1" == "SYS" ]; then
    SYSTYPE=$1
else
    echo "Systematic set not recognised."
    return 1
fi

for campaign in "[c16a+c16d+c16e]" "c16a" "c16d" "c16e"; do
    for channel in "ehad" "muhad"; do
        python configSignalControlRegion/syst/temp_systematics_code.py --channel ${channel} --campaign ${campaign} --systype ${SYSTYPE}
    done
done
