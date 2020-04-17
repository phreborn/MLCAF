#!/bin/bash

CI_OPTS=()
if [ "${GITLAB_CI}" == "true" ]; then
    echo "Applying CI exceptions..."
    CI_OPTS=(--options "lineUpdates=false" "consoleWidth=80" --snowflakeThresh 1)
fi

analyze.py bsmtautau_lephad/config-LeptonFakeRegion/master/master.cfg --debug --restrict /bkg/?/c16a/Top/single "${CI_OPTS[@]}"
