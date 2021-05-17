#!/bin/bash

REGION="OtherJetsTFR"
TASK="FF"

# Configuration of the analyze stage
CONFIG="AHZ-lephad/config/${REGION}/master/analyze-${TASK}.cfg"

# Job identifier
IDENTIFIER=${REGION}-${TASK}

# Job list
JOBLIST="jobs_${REGION}-${TASK}_c16a.txt jobs_${REGION}-${TASK}_c16d.txt jobs_${REGION}-${TASK}_c16e.txt"

source "${CAFANALYSISSHARE:?}/AHZ-lephad/config/common/submit.sh" 
