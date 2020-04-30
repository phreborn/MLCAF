#!/bin/bash

visualize.py lqtaub_lephad/config-LeptonFakeRegion/applyFF/master/master.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_lfr_applyff/summary.tex

#visualize.py lqtaub_lephad/config-LeptonFakeRegion/applyFF/master/master_qcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_lfr_applyff_qcd/summary.tex
