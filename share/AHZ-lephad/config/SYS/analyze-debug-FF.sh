#!/bin/bash

OPTION="indexLow=1 indexHigh=2"
REGION=$1

analyze.py AHZ-lephad/config/SYS/master/analyze-systematics-${REGION}.cfg \
    --restrict /bkg/?/c16a/mcReal/Diboson/ \
    --debug \
    --options ${OPTION}
