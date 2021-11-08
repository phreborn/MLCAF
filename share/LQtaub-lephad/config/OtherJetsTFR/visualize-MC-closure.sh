#!/bin/bash

REGION="OtherJetsTFR"
TASK="MC-closure-os"
visualize.py LQtaub-lephad/config/${REGION}/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${REGION}-${TASK}/summary.tex

REGION="OtherJetsTFR"
TASK="MC-closure-ss"
visualize.py LQtaub-lephad/config/${REGION}/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${REGION}-${TASK}/summary.tex
