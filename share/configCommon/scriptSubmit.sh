#!/bin/bash

REGION="$1"
CONFIG="$2"
JOBS="$3"
IDENT="$4"
#GROUP="$5"

SUBMIT=""
if [ "$USER" == "yehf" ]; then
   SUBMIT="--submit hep_sub"
fi

#submit.py ${REGION}/${CONFIG}.cfg --jobs ${REGION}/${JOBS} --identifier ${IDENT} --allowArgChanges ${SUBMIT} --account ${GROUP}
submit.py ${REGION}/${CONFIG}.cfg --jobs ${REGION}/${JOBS} --identifier ${IDENT} --allowArgChanges ${SUBMIT}

# use either --merge option (the script will wait for all jobs to finish)
# or merge yourself with
echo "tqmerge -o sampleFolders/analyzed/samples-analyzed-${CONFIG}-nominal.root -t analyze batchOutput/unmerged_${IDENT}/*.root"
