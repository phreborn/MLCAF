#!/bin/bash

visualize.py bsmtautau_lephad/config-LeptonFakeRegion/applyFF/applySF/master/master.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_lfr_applyffsf/summary.tex

#visualize.py bsmtautau_lephad/config-LeptonFakeRegion/applyFF/applySF/master/master_qcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_lfr_applyffsf_qcd/summary.tex
