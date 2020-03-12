#!/bin/bash

if [ "${GITLAB_CI}" == "true" ]; then IS_GITLAB_CI="true"; else IS_GITLAB_CI="false"; fi

CI_OPTS=()
if [ "${IS_GITLAB_CI}" == "true" ]; then
    echo "Applying CI exceptions..."
    CI_OPTS=(--options "lineUpdates=false" "consoleWidth=80" --snowflakeThresh 3)
fi

analyze.py bsmtautau_lephad/config-LeptonFakeRegion/master/master.cfg --debug --restrict /bkg/?/c16a/Top/single "${CI_OPTS[@]}"
