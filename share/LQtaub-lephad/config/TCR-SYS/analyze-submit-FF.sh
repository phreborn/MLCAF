#!/bin/bash

REGION="SYS"

#JOBLIST="jobs_SYS-SR-FF_c16a.txt jobs_SYS-SR-FF_c16d.txt jobs_SYS-SR-FF_c16e.txt"

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
    CONFIG="LQtaub-lephad/config/TCR-${REGION}/master/analyze-systematics-${ARG}.cfg"
    IDENTIFIER="TCR-FF-${REGION}-${ARG}"
    JOBLIST="jobs_SYS-SR-FF-${ARG}_c16a.txt jobs_SYS-SR-FF-${ARG}_c16d.txt jobs_SYS-SR-FF-${ARG}_c16e.txt"

    # execute
    source "${CAFANALYSISSHARE:?}/LQtaub-lephad/config/common/submit.sh" "${CONFIG}" "${IDENTIFIER}" "${JOBLIST}"
done



