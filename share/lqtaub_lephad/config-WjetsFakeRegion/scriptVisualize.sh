#!/bin/bash

visualize.py lqtaub_lephad/config-WjetsFakeRegion/master/master.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_wfr/summary.tex
