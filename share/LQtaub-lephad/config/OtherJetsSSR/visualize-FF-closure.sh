#!/bin/bash

#REGION="OtherJetsSSR"
#TASK="FF-closure-os"
#visualize.py LQtaub-lephad/config/${REGION}/master/visualize-${TASK}.cfg 
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${REGION}-${TASK}/summary.tex

REGION="OtherJetsSSR"
TASK="FF-closure-ss"
visualize.py LQtaub-lephad/config/${REGION}/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${REGION}-${TASK}/summary.tex
