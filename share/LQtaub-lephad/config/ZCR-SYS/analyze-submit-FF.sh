#!/bin/bash

REGION="SYS"

# handle arguments
if [ -z "$*" ]; then
    echo "No arguments provided!"
    return
fi
echo "Accepting arguments: $*"


# loop execute
for ARG in "$@"; do
    echo ""
    echo "Submitting systematic: ${ARG}"

    # config
    CONFIG="LQtaub-lephad/config/ZCR-${REGION}/master/analyze-systematics-${ARG}.cfg"
    IDENTIFIER="ZCR-FF-${REGION}-${ARG}"
    JOBLIST="jobs_SYS-ZCR-FF-NOMINAL_c16a.txt jobs_SYS-ZCR-FF-NOMINAL_c16d.txt jobs_SYS-ZCR-FF-NOMINAL_c16e.txt"

    # execute
    source "${CAFANALYSISSHARE:?}/LQtaub-lephad/config/common/submit.sh" "${CONFIG}" "${IDENTIFIER}" "${JOBLIST}"
done



