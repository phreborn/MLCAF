#!/bin/bash

visualize.py bsmtautau_lephad/config-QCDLeptonFakeRegion/applyFF/master/master-os.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_os_qcdlfr_applyff/summary.tex

visualize.py bsmtautau_lephad/config-QCDLeptonFakeRegion/applyFF/master/master-ss.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_ss_qcdlfr_applyff/summary.tex
