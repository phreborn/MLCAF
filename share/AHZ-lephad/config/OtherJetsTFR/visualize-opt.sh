#!/bin/bash

REGION="OtherJetsTFR"

TASK="opt-os"
visualize.py AHZ-lephad/config/${REGION}/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/AHZ-lephad-${REGION}-${TASK}/summary.tex

TASK="opt-ss"
visualize.py AHZ-lephad/config/${REGION}/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/AHZ-lephad-${REGION}-${TASK}/summary.tex
