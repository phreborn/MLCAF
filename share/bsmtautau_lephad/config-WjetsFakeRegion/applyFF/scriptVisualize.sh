#!/bin/bash

### WFR
visualize.py bsmtautau_lephad/config-WjetsFakeRegion/applyFF/master.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_wfr_applyff/summary.tex

#visualize.py bsmtautau_lephad/config-WjetsFakeRegion/applyFF/master_qcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_wfr_applyff_qcd/summary.tex

#visualize.py bsmtautau_lephad/config-WjetsFakeRegion/applyFF/master_wjets.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_wfr_applyff_wjets/summary.tex

#visualize.py bsmtautau_lephad/config-WjetsFakeRegion/applyFF/master_wjetsqcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_wfr_applyff_wjetsqcd/summary.tex

### TCR
visualize.py bsmtautau_lephad/config-WjetsFakeRegion/applyFF/master_tcr.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_tcr_applyff/summary.tex
