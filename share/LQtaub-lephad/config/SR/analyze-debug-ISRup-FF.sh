#!/bin/bash

REGION="SR"
TASK="ISRup-FF"
analyze.py LQtaub-lephad/config/${REGION}/master/analyze-${TASK}.cfg --debug \
      --restrict /bkg/?/c16d/mcFakeCorrected/Top/ttbar/ISRup \
