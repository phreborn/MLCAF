#!/bin/bash

### WFR
visualize.py lqtaub_lephad/config-WjetsFakeRegion/applySF/master/master.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_wfr_applysf/summary.tex

#visualize.py lqtaub_lephad/config-WjetsFakeRegion/applySF/master/master_qcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_wfr_applysf_qcd/summary.tex

#visualize.py lqtaub_lephad/config-WjetsFakeRegion/applySF/master/master_wjets.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_wfr_applysf_wjets/summary.tex

#visualize.py lqtaub_lephad/config-WjetsFakeRegion/applySF/master/master_wjetsqcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_wfr_applysf_wjetsqcd/summary.tex