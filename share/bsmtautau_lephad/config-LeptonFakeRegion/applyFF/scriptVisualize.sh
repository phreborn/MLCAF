#!/bin/bash

visualize.py bsmtautau_lephad/config-LeptonFakeRegion/applyFF/master/master.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_lfr_applyff/summary.tex

#visualize.py bsmtautau_lephad/config-LeptonFakeRegion/applyFF/master/master_qcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_lfr_applyff_qcd/summary.tex
