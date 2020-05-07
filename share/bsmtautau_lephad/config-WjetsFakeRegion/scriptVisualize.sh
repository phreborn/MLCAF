#!/bin/bash

visualize.py bsmtautau_lephad/config-WjetsFakeRegion/master/master.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_wfr/summary.tex
