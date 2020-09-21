#!/bin/bash

visualize.py bsmtautau_lephad/config-QCDLeptonFakeRegion/applyFF/applySF/master/master-os.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_os_qcdlfr_applyffsf/summary.tex

visualize.py bsmtautau_lephad/config-QCDLeptonFakeRegion/applyFF/applySF/master/master-ss.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_ss_qcdlfr_applyffsf/summary.tex
