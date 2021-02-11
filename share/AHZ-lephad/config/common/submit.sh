#!/bin/bash

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


JOBFILE="/tmp/${USER}/${IDENTIFIER}.list"
rm -f "${JOBFILE:?}"
for job in ${JOBLIST}
do
  cat AHZ-lephad/config/common/jobLists/${job} >> ${JOBFILE}
done

    #--mergeConfig AHZ-lephad/common/submission/merge.cfg \
submit.py ${CONFIG} \
    --jobs ${JOBFILE} \
    --identifier ${IDENTIFIER} \
    --allowArgChanges \
    --time 4320 --memory 1024 \
    "${OPTIONS[@]}"

rm -f "${JOBFILE:?}"
