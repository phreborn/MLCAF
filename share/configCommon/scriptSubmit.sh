#!/bin/bash

DATE=`date '+%Y%m%dT%H%M%S'`

REGION="$1"
CONFIG="$2"
JOBS="$3"
IDENT="$4"

SUBMIT=""
if [ "$USER" == "zorbas" ]; then
   SUBMIT="--submit condor"
fi

submit.py ${REGION}/${CONFIG}.cfg --jobs ${REGION}/${JOBS} --identifier ${IDENT}_${DATE} --allowArgChanges ${SUBMIT}

# use either --merge option (the script will wait for all jobs to finish)
# or merge yourself with
echo "tqmerge -o sampleFolders/analyzed/samples-analyzed-${CONFIG}-nominal.root -t analyze batchOutput/unmerged_${IDENT}_${DATE}/*.root"
