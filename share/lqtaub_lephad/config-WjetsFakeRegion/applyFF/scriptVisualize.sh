#!/bin/bash

### WFR
visualize.py lqtaub_lephad/config-WjetsFakeRegion/applyFF/master/master.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_wfr_applyff/summary.tex

#visualize.py lqtaub_lephad/config-WjetsFakeRegion/applyFF/master/master_qcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_wfr_applyff_qcd/summary.tex

#visualize.py lqtaub_lephad/config-WjetsFakeRegion/applyFF/master/master_wjets.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_wfr_applyff_wjets/summary.tex

#visualize.py lqtaub_lephad/config-WjetsFakeRegion/applyFF/master/master_wjetsqcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_wfr_applyff_wjetsqcd/summary.tex

### TCR
visualize.py lqtaub_lephad/config-WjetsFakeRegion/applyFF/master/master_tcr.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_tcr_applyff/summary.tex
