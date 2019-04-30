#!/bin/bash

REGION="$1"
CONFIG="$2"
JOBS="$3"
IDENT="$4"

SUBMIT=""
if [[ "${HOSTNAME}" == *".shef.ac.uk" ]]; then
  SUBMIT="--submit condor"
elif [ "$USER" == "yehf" ]; then
  SUBMIT="--submit hep_sub --account atlas"
fi

submit.py ${REGION}/${CONFIG}.cfg --jobs ${REGION}/${JOBS} --identifier ${IDENT} --allowArgChanges ${SUBMIT}

# use either --merge option (the script will wait for all jobs to finish)
# or merge yourself with
echo "tqmerge -o sampleFolders/analyzed/samples-analyzed-${CONFIG}.root -t analyze batchOutput/unmerged_${IDENT}/*.root"
