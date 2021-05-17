#!/bin/bash

REGION="OtherJetsTFR"
TASK="MC-closure"

analyze.py AHZ-lephad/config/${REGION}/master/analyze-${TASK}.cfg --debug \
      --restrict /bkg/?/c16a/mcFakeCorrected/Top/single \
