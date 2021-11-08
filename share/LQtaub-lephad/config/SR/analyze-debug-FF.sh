#!/bin/bash

REGION="SR"
TASK="FF"
analyze.py LQtaub-lephad/config/${REGION}/master/analyze-${TASK}.cfg --debug \
      --restrict /data/?/c16a \
