#!/bin/bash

TASK="TCR-FSRdo-SF-closure"

# Configuration of the analyze stage
CONFIG="LQtaub-lephad/config/TCR/master/analyze-${TASK}.cfg"

# Job identifier
IDENTIFIER=${TASK}

# Job list
JOBLIST="jobs_${TASK}_c16a.txt jobs_${TASK}_c16d.txt jobs_${TASK}_c16e.txt"

source "${CAFANALYSISSHARE:?}/LQtaub-lephad/config/common/submit.sh" "${CONFIG}" "${IDENTIFIER}" "${JOBLIST}"
