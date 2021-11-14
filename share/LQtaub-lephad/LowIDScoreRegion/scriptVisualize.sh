#!/bin/bash

visualize.py lqtaub_lephad/config-LowIDScoreRegion/master/master.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_lsr/summary.tex
