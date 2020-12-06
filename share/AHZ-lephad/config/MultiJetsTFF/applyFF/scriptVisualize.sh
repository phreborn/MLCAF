#!/bin/bash

### QCDTFR
visualize.py bsmtautau_lephad/config-QCDTauFakeRegion/applyFF/master/master_os.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_os_qcdtfr_applyff/summary.tex
