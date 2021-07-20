#!/bin/bash

TASK="MultiJetsLFR-opt"

visualize.py AHZ-lephad/config/MultiJetsLFR/master/visualize-${TASK}-os.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/AHZ-lephad-${TASK}-os/summary.tex

visualize.py AHZ-lephad/config/MultiJetsLFR/master/visualize-${TASK}-ss.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/AHZ-lephad-${TASK}-ss/summary.tex
