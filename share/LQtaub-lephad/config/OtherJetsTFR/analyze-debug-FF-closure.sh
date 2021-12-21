#!/bin/bash

REGION="OtherJetsTFR"
TASK="FF-closure"

analyze.py LQtaub-lephad/config/${REGION}/master/analyze-${TASK}.cfg --debug \
      --restrict /bkg/?/c16a/mcFakeCorrected/Top/ttbar/nominal \
