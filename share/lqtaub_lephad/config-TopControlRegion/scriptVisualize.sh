#!/bin/bash

### TCR
visualize.py lqtaub_lephad/config-TopControlRegion/master/master.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_tcr/summary.tex
