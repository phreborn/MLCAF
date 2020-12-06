#!/bin/bash

# receive arguments
REGION="$1"
CONFIG="$2"
IDENT="$3"
JOBSLIST="$4"

# additional institute-specific submission commands
OPTIONS=()
if [[ "${HOSTNAME}" == *".shef.ac.uk" ]]; then
  # Sheffield
  OPTIONS=(--submit condor --maxSampleSize 20000)
elif [[ "${HOSTNAME}" == *".ihep.ac.cn" ]]; then
  # IHEP
  OPTIONS=(--submit condor --account atlas --maxSampleSize 10000)
fi

# create temp jobs file
JOBSFILE="${CAFANALYSISSHARE:?}/bsmtautau_lephad/${REGION}/jobs-${IDENT}.tmp"
rm -f "${JOBSFILE:?}"

for LIST in "${JOBSLIST[@]}"; do
    cat "${CAFANALYSISSHARE:?}/bsmtautau_lephad/config-Common/jobLists/jobs_${LIST}_c16"*".txt" >> "${JOBSFILE}"
done

cat ${JOBSFILE}

# submission
echo "Submitting..."
submit.py "bsmtautau_lephad/${REGION}/master/${CONFIG}.cfg" \
    --jobs "${JOBSFILE}" --identifier "${IDENT}" --allowArgChanges \
    --time 4320 --memory 1024 --maxSampleSize 7000 \
    --mergeConfig "bsmtautau_lephad/submission/merge.cfg" "${OPTIONS[@]}"
echo "Finished submitting!"

# cleanup temp jobs file
rm -f "${JOBSFILE:?}"
