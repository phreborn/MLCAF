#!/bin/bash

REGION="SR"
TASK="FF-os"
visualize.py AHZ-lephad/config/${REGION}/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/AHZ-lephad-${REGION}-${TASK}/summary.tex

REGION="SR"
TASK="FF-ss"
visualize.py AHZ-lephad/config/${REGION}/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/AHZ-lephad-${REGION}-${TASK}/summary.tex
