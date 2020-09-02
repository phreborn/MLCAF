#!/bin/bash

visualize.py bsmtautau_lephad/config-QCDTauFakeRegion/master/master_os.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_os_qcdtfr/summary.tex

#visualize.py bsmtautau_lephad/config-QCDTauFakeRegion/master/master_ss.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_ss_qcdtfr/summary.tex
