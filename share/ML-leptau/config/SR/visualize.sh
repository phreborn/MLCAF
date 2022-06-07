#!/bin/bash

REGION="SR"
TASK="FF-os"
visualize.py ML-leptau/config/${REGION}/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/ML-leptau-${REGION}-${TASK}/summary.tex

#REGION="VR"
#TASK="FF-os"
#visualize.py ML-leptau/config/SR/master/visualize-${REGION}-${TASK}.cfg 
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/ML-leptau-${REGION}-${TASK}/summary.tex
