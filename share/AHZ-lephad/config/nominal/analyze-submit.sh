#!/bin/bash

# Configuration of the analyze stage
CONFIG="analyze-nominal.cfg"

# Job identifier
IDENTIFIER="nominal"

# Job list
JOBLIST="jobs_nominal_c16d.txt jobs_nominal_c16e.txt"

# Job submission
OPTIONS=()
if [[ "${HOSTNAME}" == *".shef.ac.uk" ]]; then
  # Sheffield
  OPTIONS=(--submit condor --maxSampleSize 20000)
elif [[ "${HOSTNAME}" == *".ihep.ac.cn" ]]; then
  # IHEP
  OPTIONS=(--submit condor --account atlas --maxSampleSize 10000)
fi


JOBFILE="/tmp/${USER}/${IDENTIFIER}.list"
rm -f "${JOBFILE:?}"
for job in ${JOBLIST}
do
  cat AHZ-lephad/config/common/jobLists/${job} >> ${JOBFILE}
done

submit.py AHZ-lephad/config/nominal/master/${CONFIG} \
    --jobs ${JOBFILE} \
    --identifier ${IDENTIFIER} \
    --allowArgChanges \
    --time 4320 --memory 1024 \
    --mergeConfig AHZ-lephad/common/submission/merge.cfg \
    "${OPTIONS[@]}"
