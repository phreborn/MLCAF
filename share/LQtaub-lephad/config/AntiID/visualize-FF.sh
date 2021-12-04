#!/bin/bash

REGION="AntiID"
TASK="FF"
visualize.py LQtaub-lephad/config/${REGION}/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${REGION}-${TASK}/summary.tex
