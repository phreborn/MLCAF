#!/bin/bash

CI_OPTS=()
if [ "${GITLAB_CI}" == "true" ]; then
    echo "Applying CI exceptions..."
    CI_OPTS=(--options "lineUpdates=false" "consoleWidth=80" --snowflakeThresh 0)
fi

CONFIG="AHZ-lephad/config/common/master/prepare-common.cfg"

echo "Preparing..."
prepare.py "${CONFIG:?}" "${CI_OPTS[@]}"
echo "Finished preparing!"
