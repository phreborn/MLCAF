#!/bin/bash

REGION="OtherJetsSSR"
TASK="FF-closure"

# Configuration of the analyze stage
CONFIG="LQtaub-lephad/config/${REGION}/master/analyze-${TASK}.cfg"

# Job identifier
IDENTIFIER=${REGION}-${TASK}

# Job list
#JOBLIST="jobs_${REGION}-${TASK}_c16a.txt jobs_${REGION}-${TASK}_c16d.txt jobs_${REGION}-${TASK}_c16e.txt"
JOBLIST="jobs_${REGION}-FF_c16a.txt jobs_${REGION}-FF_c16d.txt jobs_${REGION}-FF_c16e.txt"

source "${CAFANALYSISSHARE:?}/LQtaub-lephad/config/common/submit.sh" "${CONFIG}" "${IDENTIFIER}" "${JOBLIST}"
