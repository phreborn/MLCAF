#!/bin/bash

### VR
visualize.py configFailIDRegion/htautau_lephad_vr.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_vr_failid/summary.tex

### SR
visualize.py configFailIDRegion/htautau_lephad_sr.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_sr_failid/summary.tex

### TCR
visualize.py configFailIDRegion/htautau_lephad_tcr.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_tcr_failid/summary.tex

### WCR
visualize.py configFailIDRegion/htautau_lephad_wcr.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_wcr_failid/summary.tex
