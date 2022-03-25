#!/bin/bash

REGION="ZCR"
TASK="FF-closure"

# Configuration of the analyze stage
CONFIG="LQtaub-lephad/config/${REGION}/master/analyze-${TASK}.cfg"

# Job identifier
IDENTIFIER="${REGION}-${TASK}"

# Job list
JOBLIST="jobs_ZCR-${TASK}_c16a.txt jobs_ZCR-${TASK}_c16d.txt jobs_ZCR-${TASK}_c16e.txt"


source "${CAFANALYSISSHARE:?}/LQtaub-lephad/config/common/submit.sh" "${CONFIG}" "${IDENTIFIER}" "${JOBLIST}"

