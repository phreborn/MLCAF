#!/bin/bash

#TASK="TCR-SF"
#visualize.py LQtaub-lephad/config/TCR/master/visualize-${TASK}.cfg 
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}/summary.tex

#TASK="TCR-PS-SF"
#visualize.py LQtaub-lephad/config/TCR/master/visualize-${TASK}.cfg 
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}/summary.tex

#TASK="TCR-ME-SF"
#visualize.py LQtaub-lephad/config/TCR/master/visualize-${TASK}.cfg 
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}/summary.tex

TASK="TCR-ISRup-SF"
visualize.py LQtaub-lephad/config/TCR/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}/summary.tex

#TASK="TCR-ISRdo-SF"
#visualize.py LQtaub-lephad/config/TCR/master/visualize-${TASK}.cfg 
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}/summary.tex

#TASK="TCR-FSRup-SF"
#visualize.py LQtaub-lephad/config/TCR/master/visualize-${TASK}.cfg 
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}/summary.tex

#TASK="TCR-FSRdo-SF"
#visualize.py LQtaub-lephad/config/TCR/master/visualize-${TASK}.cfg 
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}/summary.tex
