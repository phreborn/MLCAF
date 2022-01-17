#!/bin/bash

OPTION="indexLow=1 indexHigh=2"
REGION=$1

analyze.py LQtaub-lephad/config/OtherJetsTFR-SYS/master/analyze-systematics-${REGION}.cfg \
    --restrict /bkg/?/c16a/mcReal/Diboson/ \
    --debug \
    --options ${OPTION}
