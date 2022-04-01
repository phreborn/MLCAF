#!/bin/bash

REGION="ZCR"
TASK="FF-closure"
analyze.py LQtaub-lephad/config/${REGION}/master/analyze-${TASK}.cfg --debug \
      --restrict /bkg/?/c16d/mcReal/Zjets/LF \
