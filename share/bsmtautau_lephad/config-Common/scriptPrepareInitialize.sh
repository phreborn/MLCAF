#!/bin/bash

if [ "${GITLAB_CI}" == "true" ]; then IS_GITLAB_CI="true"; else IS_GITLAB_CI="false"; fi

CI_OPTS=()
if [ "${IS_GITLAB_CI}" == "true" ]; then
    echo "Applying CI exceptions..."
    CI_OPTS=(--options "lineUpdates=false" "consoleWidth=80")
fi

echo "Preparing..."
prepare.py "bsmtautau_lephad/config-Common/master/master.cfg" "${CI_OPTS[@]}"
echo "Finished preparing!"

echo "Initializing..."
initialize.py "bsmtautau_lephad/config-Common/master/master.cfg" "${CI_OPTS[@]}"
echo "Finished initializing!"
