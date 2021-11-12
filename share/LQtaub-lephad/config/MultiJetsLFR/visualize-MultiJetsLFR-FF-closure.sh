#!/bin/bash

TASK="MultiJetsLFR-FF-closure"

visualize.py LQtaub-lephad/config/MultiJetsLFR/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}/summary.tex
