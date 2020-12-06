#!/bin/bash

### WFR
visualize.py bsmtautau_lephad/config-WjetsFakeRegion/applyFF/master/master_os.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_os_wfr_applyff/summary.tex

### TCR
#visualize.py bsmtautau_lephad/config-WjetsFakeRegion/applyFF/master/master_os_tcr.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_os_tcr_applyff/summary.tex
