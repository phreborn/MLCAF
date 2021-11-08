#!/bin/bash

TASK="MultiJetsLFR-FF-closure"

# Configuration of the analyze stage
CONFIG="LQtaub-lephad/config/MultiJetsLFR/master/analyze-${TASK}.cfg"

# Job identifier
IDENTIFIER=${TASK}

# Job list
JOBLIST="jobs_${TASK}_c16a.txt jobs_${TASK}_c16d.txt jobs_${TASK}_c16e.txt"

source "${CAFANALYSISSHARE:?}/LQtaub-lephad/config/common/submit.sh" "${CONFIG}" "${IDENTIFIER}" "${JOBLIST}"
