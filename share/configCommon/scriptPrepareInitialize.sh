#!/bin/bash

if [ "${GITLAB_CI}" == "true" ]; then IS_GITLAB_CI="true"; else IS_GITLAB_CI="false"; fi

CI_OPTS=""
if [ "${IS_GITLAB_CI}" == "true" ]; then
    echo "Applying CI exceptions..."
    CI_OPTS="--options lineUpdates=false consoleWidth=80"
fi

prepare.py configCommon/htautau_lephad_common.cfg ${CI_OPTS}
initialize.py configCommon/htautau_lephad_common.cfg ${CI_OPTS}
