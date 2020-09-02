#!/bin/bash

### QCDTFR
visualize.py bsmtautau_lephad/config-QCDTauFakeRegion/applyFF/applySF/master/master.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_qcdtfr_applyffsf/summary.tex

#visualize.py bsmtautau_lephad/config-QCDTauFakeRegion/applyFF/applySF/master/master_qcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_qcdtfr_applyffsf_qcd/summary.tex

#visualize.py bsmtautau_lephad/config-QCDTauFakeRegion/applyFF/applySF/master/master_wjets.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_qcdtfr_applyffsf_wjets/summary.tex

#visualize.py bsmtautau_lephad/config-QCDTauFakeRegion/applyFF/applySF/master/master_wjetsqcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_qcdtfr_applyffsf_wjetsqcd/summary.tex

### TCR
visualize.py bsmtautau_lephad/config-QCDTauFakeRegion/applyFF/applySF/master/master_tcr.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_tcr_applyffsf/summary.tex
