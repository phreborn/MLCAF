#!/bin/bash

REGION="SYS"

JOBLIST="jobs_SYS-SR-FF-Theory_Top_c16a.txt jobs_SYS-SR-FF-Theory_Top_c16d.txt jobs_SYS-SR-FF-Theory_Top_c16e.txt"

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
    CONFIG="LQtaub-lephad/config/${REGION}/master/analyze-systematics-${ARG}.cfg"
    IDENTIFIER="SR-FF-${REGION}-${ARG}"

    # execute
    source "${CAFANALYSISSHARE:?}/LQtaub-lephad/config/common/submit.sh" "${CONFIG}" "${IDENTIFIER}" "${JOBLIST}"
done



