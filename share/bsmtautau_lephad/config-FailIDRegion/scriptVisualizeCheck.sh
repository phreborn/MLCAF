#!/bin/bash

### VR
visualize.py configFailIDRegion/htautau_lephad_vr_check.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_vr_failid_check/summary.tex

### SR
visualize.py configFailIDRegion/htautau_lephad_sr_check.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_sr_failid_check/summary.tex

### TCR
visualize.py configFailIDRegion/htautau_lephad_tcr_check.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_tcr_failid_check/summary.tex

### WCR
visualize.py configFailIDRegion/htautau_lephad_wcr_check.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_wcr_failid_check/summary.tex
