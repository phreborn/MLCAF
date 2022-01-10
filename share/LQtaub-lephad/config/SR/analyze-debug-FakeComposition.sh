#!/bin/bash

REGION="SR"
TASK="FakeComposition"
analyze.py LQtaub-lephad/config/${REGION}/master/analyze-${TASK}.cfg --debug \
      --restrict /bkg/?/c16a/Gluon/Top/single \
