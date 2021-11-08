#!/bin/bash

TASK="TCR-opt"
visualize.py AHZ-lephad/config/TCR/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/AHZ-lephad-${TASK}/summary.tex

TASK="1bTCR-opt"
visualize.py AHZ-lephad/config/TCR/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/AHZ-lephad-${TASK}/summary.tex

TASK="2bTCR-opt"
visualize.py AHZ-lephad/config/TCR/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/AHZ-lephad-${TASK}/summary.tex
