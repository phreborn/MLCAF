#!/bin/bash

JOBNAME=${1:-*}
BASEMEM="1024"
MULTMEM="2"

echo "$(date) : Checking jobs..."

for file in $(find ./logs -name "${JOBNAME}_*.condorlog" ); do
    MEMVAL=$(grep "MemoryUsage" $file | tail -n 1 | cut -f 2 | cut -d ' ' -f 1)
    if [[ ${MEMVAL:-0} -gt $(echo "${BASEMEM} * ${MULTMEM}" | bc | cut -d '.' -f 1) ]]; then
        BADFILE=$(basename $file | rev | cut -c15- | rev)
        unset CONDORID
        CONDORID=$(condor_q -wide | grep $BADFILE | tr -s ' ' | cut -d ' ' -f 9)
        if [ ! -z "$CONDORID" ]; then
            echo "Killing ${MEMVAL}MB = $BADFILE = $CONDORID"
            condor_rm $CONDORID
        fi
    fi
done
