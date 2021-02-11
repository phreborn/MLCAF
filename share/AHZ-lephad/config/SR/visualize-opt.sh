#!/bin/bash

REGION="SR"
TASK="opt-bveto"
visualize.py AHZ-lephad/config/${REGION}/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/AHZ-lephad-${REGION}-${TASK}/summary.tex

REGION="SR"
TASK="opt-btag"
visualize.py AHZ-lephad/config/${REGION}/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/AHZ-lephad-${REGION}-${TASK}/summary.tex
