#!/bin/bash

REGION="SR"
TASK="FF"
analyze.py AHZ-lephad/config/${REGION}/master/analyze-${TASK}.cfg --debug \
      --restrict /data/?/c16a \
