#!/bin/bash

REGION="OtherJetsTFR"
TASK="MC-os"
visualize.py AHZ-lephad/config/${REGION}/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/AHZ-lephad-${REGION}-${TASK}/summary.tex

REGION="OtherJetsTFR"
TASK="MC-ss"
visualize.py AHZ-lephad/config/${REGION}/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/AHZ-lephad-${REGION}-${TASK}/summary.tex
