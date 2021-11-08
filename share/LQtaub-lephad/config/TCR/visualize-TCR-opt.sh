#!/bin/bash

TASK="TCR-opt"
visualize.py LQtaub-lephad/config/TCR/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}/summary.tex

TASK="1bTCR-opt"
visualize.py LQtaub-lephad/config/TCR/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}/summary.tex

TASK="2bTCR-opt"
visualize.py LQtaub-lephad/config/TCR/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}/summary.tex
