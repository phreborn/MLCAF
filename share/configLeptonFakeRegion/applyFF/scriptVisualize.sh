#!/bin/bash

visualize.py configLeptonFakeRegion/applyFF/htautau_lephad_lfr_applyff.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_lfr_applyff/summary.tex

visualize.py configLeptonFakeRegion/applyFF/htautau_lephad_lfr_applyff_qcd.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_lfr_applyff_qcd/summary.tex
