#!/bin/bash

REGION="OtherJetsTFR"
TASK="FF-closure-os"
visualize.py AHZ-lephad/config/${REGION}/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/AHZ-lephad-${REGION}-${TASK}/summary.tex

REGION="OtherJetsTFR"
TASK="FF-closure-ss"
visualize.py AHZ-lephad/config/${REGION}/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/AHZ-lephad-${REGION}-${TASK}/summary.tex
