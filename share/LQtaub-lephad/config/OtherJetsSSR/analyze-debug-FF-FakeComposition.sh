#!/bin/bash

REGION="OtherJetsSSR"
TASK="FF-FakeComposition"

analyze.py LQtaub-lephad/config/${REGION}/master/analyze-${TASK}.cfg --debug \
      --restrict /bkg/?/c16d/bottom/Top/ttbar/nominal \
