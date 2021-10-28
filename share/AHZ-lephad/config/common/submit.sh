#!/bin/bash

# receive arguments
CONFIG=$1
IDENTIFIER=$2
JOBSLIST=$3

# Job submission
OPTIONS=()
if [[ "${HOSTNAME}" == *".shef.ac.uk" ]]; then
  # Sheffield
  OPTIONS=(--submit condor --maxSampleSize 20000)
elif [[ "${HOSTNAME}" == *".ihep.ac.cn" ]]; then
  # IHEP
  OPTIONS=(--submit condor --account atlas --maxSampleSize 10000)
else
  OPTIONS=(--maxSampleSize 7000)
fi


JOBSFILE="/tmp/${USER}/${IDENTIFIER}.list"
rm -f "${JOBSFILE:?}"

for LIST in ${JOBSLIST}; do
    cat "${CAFANALYSISSHARE:?}/AHZ-lephad/config/common/jobLists/${LIST}" >> "${JOBSFILE}"
done


    #--mergeConfig AHZ-lephad/common/submission/merge.cfg 
submit.py "${CONFIG}" \
    --jobs "${JOBSFILE}" \
    --identifier "${IDENTIFIER}" \
    --allowArgChanges \
    --time 4320 --memory 1024 \
#    --mergeConfig "AHZ-lephad/common/submission/merge.cfg" "${OPTIONS[@]}"
#    --maxSampleSize 3000 \

rm -f "${JOBSFILE:?}"
