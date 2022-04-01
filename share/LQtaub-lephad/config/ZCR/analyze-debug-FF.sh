#!/bin/bash

REGION="ZCR"
TASK="FF"
analyze.py LQtaub-lephad/config/${REGION}/master/analyze-${TASK}.cfg --debug \
      --restrict /bkg/?/c16e/mcReal/Zjets/HF/ \
