#!/bin/bash

REGION="OtherJetsSSR"
TASK="FF-closure"

analyze.py LQtaub-lephad/config/${REGION}/master/analyze-${TASK}.cfg --debug \
      --restrict /bkg/?/c16d/mcFakeCorrected/Top/single \
