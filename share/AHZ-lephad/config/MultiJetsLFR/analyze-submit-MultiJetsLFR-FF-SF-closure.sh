#!/bin/bash

TASK="MultiJetsLFR-FF-SF-closure"

# Configuration of the analyze stage
CONFIG="AHZ-lephad/config/MultiJetsLFR/master/analyze-${TASK}.cfg"

# Job identifier
IDENTIFIER=${TASK}

# Job list
JOBLIST="jobs_MultiJetsLFR-FF-closure_c16a.txt jobs_MultiJetsLFR-FF-closure_c16d.txt jobs_MultiJetsLFR-FF-closure_c16e.txt"

source "${CAFANALYSISSHARE:?}/AHZ-lephad/config/common/submit.sh" 
