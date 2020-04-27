#!/bin/bash

### WFR
visualize.py bsmtautau_lephad/config-WjetsFakeRegion/applyFF/applySF/master/master.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_wfr_applyffsf/summary.tex

#visualize.py bsmtautau_lephad/config-WjetsFakeRegion/applyFF/applySF/master/master_qcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_wfr_applyffsf_qcd/summary.tex

#visualize.py bsmtautau_lephad/config-WjetsFakeRegion/applyFF/applySF/master/master_wjets.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_wfr_applyffsf_wjets/summary.tex

#visualize.py bsmtautau_lephad/config-WjetsFakeRegion/applyFF/applySF/master/master_wjetsqcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_wfr_applyffsf_wjetsqcd/summary.tex

### TCR
visualize.py bsmtautau_lephad/config-WjetsFakeRegion/applyFF/applySF/master/master_tcr.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_tcr_applyffsf/summary.tex
