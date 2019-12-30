#!/bin/bash

### WFR
visualize.py configWjetsFakeRegion/applySF/htautau_lephad_wfr_applysf.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_wfr_applysf/summary.tex

#visualize.py configWjetsFakeRegion/applySF/htautau_lephad_wfr_applysf_qcd.cfg
#source scripts/tqpdflatex.sh results/htautau_lephad_wfr_applysf_qcd/summary.tex

#visualize.py configWjetsFakeRegion/applySF/htautau_lephad_wfr_applysf_wjets.cfg
#source scripts/tqpdflatex.sh results/htautau_lephad_wfr_applysf_wjets/summary.tex

#visualize.py configWjetsFakeRegion/applySF/htautau_lephad_wfr_applysf_wjetsqcd.cfg
#source scripts/tqpdflatex.sh results/htautau_lephad_wfr_applysf_wjetsqcd/summary.tex
