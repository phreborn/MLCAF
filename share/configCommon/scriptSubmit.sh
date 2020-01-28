#!/bin/bash

REGION="$1"
CONFIG="$2"
JOBS="$3"
IDENT="$4"

# additional institute/user-specific submission commands
SUBMIT=""
if [[ "${HOSTNAME}" == *".shef.ac.uk" ]]; then
  SUBMIT="--submit condor --maxSampleSize 20000"
elif [ "$USER" == "yehf" ]; then
  SUBMIT="--submit condor --account atlas"
elif [ "$USER" == "xiaozhong" ]; then
  SUBMIT="--submit condor --account atlas"
fi

submit.py ${REGION}/${CONFIG}.cfg --jobs ${REGION}/${JOBS} --identifier ${IDENT} --allowArgChanges --time 4320 --memory 1024 --maxSampleSize 7000 ${SUBMIT}

# use either --merge option (the script will wait for all jobs to finish)
# or merge yourself with
# echo "tqmerge -o sampleFolders/analyzed/samples-analyzed-${CONFIG}.root -t analyze batchOutput/unmerged_${IDENT}/*.root"
