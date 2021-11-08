#!/bin/bash

REGION="OtherJetsTFR"
TASK="FF-SF-closure"

analyze.py LQtaub-lephad/config/${REGION}/master/analyze-${TASK}.cfg --debug \
      --restrict /bkg/?/c16a/ddOtherJetsFake/mcReal/Top/ttbar/nominal \
