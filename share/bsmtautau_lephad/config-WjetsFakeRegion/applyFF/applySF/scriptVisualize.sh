#!/bin/bash

### WFR
visualize.py configWjetsFakeRegion/applyFF/applySF/htautau_lephad_wfr_applyffsf.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_wfr_applyffsf/summary.tex

#visualize.py configWjetsFakeRegion/applyFF/htautau_lephad_wfr_applyff_qcd.cfg
#source scripts/tqpdflatex.sh results/htautau_lephad_wfr_applyff_qcd/summary.tex

#visualize.py configWjetsFakeRegion/applyFF/htautau_lephad_wfr_applyff_wjets.cfg
#source scripts/tqpdflatex.sh results/htautau_lephad_wfr_applyff_wjets/summary.tex

#visualize.py configWjetsFakeRegion/applyFF/htautau_lephad_wfr_applyff_wjetsqcd.cfg
#source scripts/tqpdflatex.sh results/htautau_lephad_wfr_applyff_wjetsqcd/summary.tex

### TCR
visualize.py configWjetsFakeRegion/applyFF/applySF/htautau_lephad_tcr_applyffsf.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_tcr_applyffsf/summary.tex
