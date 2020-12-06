#!/bin/bash

CI_OPTS=()
if [ "${GITLAB_CI}" == "true" ]; then
    echo "Applying CI exceptions..."
    CI_OPTS=(--options "lineUpdates=false" "consoleWidth=80" --snowflakeThresh 1)
fi

analyze.py AHZ-lephad/config/MultiJetsLFF/master/analyze-MultiJetsLFF.cfg --debug --restrict /bkg/?/c16a/mcReal/Top/single "${CI_OPTS[@]}" 
