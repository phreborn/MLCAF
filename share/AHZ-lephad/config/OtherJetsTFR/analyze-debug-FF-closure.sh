#!/bin/bash

REGION="OtherJetsTFR"
TASK="FF-closure"

analyze.py AHZ-lephad/config/${REGION}/master/analyze-${TASK}.cfg --debug \
      --restrict /bkg/?/c16a/ddOtherJetsFake/mcReal/Top/ttbar/nominal \
