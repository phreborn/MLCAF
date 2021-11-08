#!/bin/bash

REGION="OtherJetsTFR"
TASK="MC"

analyze.py AHZ-lephad/config/${REGION}/master/analyze-${TASK}.cfg --debug \
      --restrict /bkg/?/c16a/mcFake/Top/single \
