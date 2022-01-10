#!/bin/bash

REGION="OtherJetsSSR"
TASK="FakeComposition"

# Configuration of the analyze stage
CONFIG="LQtaub-lephad/config/${REGION}/master/analyze-${TASK}.cfg"

# Job identifier
IDENTIFIER=${REGION}-${TASK}

# Job list
JOBLIST="jobs_SR-FakeComposition_c16a.txt jobs_SR-FakeComposition_c16d.txt jobs_SR-FakeComposition_c16e.txt"

source "${CAFANALYSISSHARE:?}/LQtaub-lephad/config/common/submit.sh" "${CONFIG}" "${IDENTIFIER}" "${JOBLIST}"
