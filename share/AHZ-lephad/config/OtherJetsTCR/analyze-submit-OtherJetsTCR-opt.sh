#!/bin/bash

TASK="OtherJetsTCR-opt"

# Configuration of the analyze stage
CONFIG="AHZ-lephad/config/OtherJetsTCR/master/analyze-${TASK}.cfg"

# Job identifier
IDENTIFIER=${TASK}

# Job list
JOBLIST="jobs_${TASK}_c16a.txt jobs_${TASK}_c16d.txt jobs_${TASK}_c16e.txt"

source "${CAFANALYSISSHARE:?}/AHZ-lephad/config/common/submit.sh" 
