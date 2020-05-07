#!/bin/bash

visualize.py lqtaub_lephad/config-LeptonFakeRegion/master/master.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_lfr/summary.tex
