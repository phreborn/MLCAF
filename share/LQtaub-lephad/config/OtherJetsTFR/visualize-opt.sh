#!/bin/bash

REGION="OtherJetsTFR"

TASK="opt-os"
visualize.py LQtaub-lephad/config/${REGION}/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${REGION}-${TASK}/summary.tex

TASK="opt-ss"
visualize.py LQtaub-lephad/config/${REGION}/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${REGION}-${TASK}/summary.tex
