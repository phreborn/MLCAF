#!/bin/bash

REGION="SR"
TASK="alternateFR"
analyze.py AHZ-lephad/config/${REGION}/master/analyze-${TASK}.cfg --debug \
      --restrict /sig/?/c16a/bbH \
