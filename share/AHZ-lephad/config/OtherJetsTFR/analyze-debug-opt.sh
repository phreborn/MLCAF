#!/bin/bash

REGION="OtherJetsTFR"
TASK="opt"

analyze.py AHZ-lephad/config/${REGION}/master/analyze-${TASK}.cfg --debug \
      --restrict /bkg/?/c16a/mcReal/Top/single \
