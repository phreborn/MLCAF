#!/bin/bash

CI_OPTS=()
if [ "${GITLAB_CI}" == "true" ]; then
    echo "Applying CI exceptions..."
    CI_OPTS=(--options "lineUpdates=false" "consoleWidth=80" --snowflakeThresh 1)
fi

analyze.py LQtaub-lephad/config/MultiJetsLFR/master/analyze-MultiJetsLFR-FF.cfg --debug \
      --restrict /bkg/?/c16a/mcReal/Top/single \
      "${CI_OPTS[@]}"
