#!/bin/bash

visualize.py bsmtautau_lephad/config-QCDLeptonFakeRegion/master/master-os.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_os_qcdlfr/summary.tex

visualize.py bsmtautau_lephad/config-QCDLeptonFakeRegion/master/master-ss.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_ss_qcdlfr/summary.tex
