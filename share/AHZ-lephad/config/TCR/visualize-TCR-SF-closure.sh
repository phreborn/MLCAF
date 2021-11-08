#!/bin/bash

TASK="TCR-SF-closure"
visualize.py AHZ-lephad/config/TCR/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/AHZ-lephad-${TASK}/summary.tex

#TASK="2bTVR-SF-closure"
#visualize.py AHZ-lephad/config/TCR/master/visualize-${TASK}.cfg 
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/AHZ-lephad-${TASK}/summary.tex
