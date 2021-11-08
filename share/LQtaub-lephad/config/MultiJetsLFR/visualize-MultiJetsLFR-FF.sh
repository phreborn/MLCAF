#!/bin/bash

TASK="MultiJetsLFR-FF"

visualize.py LQtaub-lephad/config/MultiJetsLFR/master/visualize-${TASK}-os.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}-os/summary.tex

visualize.py LQtaub-lephad/config/MultiJetsLFR/master/visualize-${TASK}-ss.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}-ss/summary.tex
