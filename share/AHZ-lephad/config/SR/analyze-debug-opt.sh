#!/bin/bash

REGION="SR"
TASK="opt"
analyze.py AHZ-lephad/config/${REGION}/master/analyze-${TASK}.cfg --debug \
      --restrict /sig/?/c16a/bbH \
