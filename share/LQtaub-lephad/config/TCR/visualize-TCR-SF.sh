#!/bin/bash

TASK="TCR-SF"
visualize.py LQtaub-lephad/config/TCR/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}/summary.tex
