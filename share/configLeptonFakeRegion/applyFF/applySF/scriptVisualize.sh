#!/bin/bash

visualize.py configLeptonFakeRegion/applyFF/applySF/htautau_lephad_lfr_applyffsf.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_lfr_applyffsf/summary.tex

visualize.py configLeptonFakeRegion/applyFF/applySF/htautau_lephad_lfr_applyffsf_qcd.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_lfr_applyffsf_qcd/summary.tex
