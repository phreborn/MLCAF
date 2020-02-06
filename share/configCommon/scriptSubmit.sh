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
  OPTIONS=(--submit condor --account atlas)
fi

# create temp jobs file
JOBSFILE="jobs-${IDENT}.tmp"
rm -f "${REGION}/${JOBSFILE}"

for LIST in "${JOBSLIST[@]}"; do
    cat "configCommon/jobLists/jobs_${LIST}_c16"*".txt" >> "${REGION}/${JOBSFILE}"
done

# submission
echo "Submitting..."
submit.py "${REGION}/${CONFIG}.cfg" --jobs "${REGION}/${JOBSFILE}" --identifier "${IDENT}" --allowArgChanges --time 4320 --memory 1024 --maxSampleSize 7000 --mergeConfig "configCommon/merge.cfg" "${OPTIONS[@]}"
echo "Finished submitting!"

# cleanup temp jobs file
rm -f "${REGION}/${JOBSFILE}"

# use either --merge option (the script will wait for all jobs to finish)
# or merge yourself with
# echo "tqmerge -o sampleFolders/analyzed/samples-analyzed-${CONFIG}.root -t analyze batchOutput/unmerged_${IDENT}/*.root"
