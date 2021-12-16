#!/bin/bash

TASK="TCR-SF-closure"
visualize.py LQtaub-lephad/config/TCR/master/visualize-${TASK}.cfg 
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}/summary.tex

#TASK="TCR-PS-SF-closure"
#visualize.py LQtaub-lephad/config/TCR/master/visualize-${TASK}.cfg 
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}/summary.tex

#TASK="TCR-ME-SF-closure"
#visualize.py LQtaub-lephad/config/TCR/master/visualize-${TASK}.cfg 
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}/summary.tex

#TASK="TCR-ISRup-SF-closure"
#visualize.py LQtaub-lephad/config/TCR/master/visualize-${TASK}.cfg 
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}/summary.tex

#TASK="TCR-ISRdo-SF-closure"
#visualize.py LQtaub-lephad/config/TCR/master/visualize-${TASK}.cfg 
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}/summary.tex

#TASK="TCR-FSRup-SF-closure"
#visualize.py LQtaub-lephad/config/TCR/master/visualize-${TASK}.cfg 
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}/summary.tex

#TASK="TCR-FSRdo-SF-closure"
#visualize.py LQtaub-lephad/config/TCR/master/visualize-${TASK}.cfg 
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/LQtaub-lephad-${TASK}/summary.tex
