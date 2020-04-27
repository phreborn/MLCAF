#!/bin/bash

visualize.py bsmtautau_lephad/config-LeptonFakeRegion/master/master.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_lfr/summary.tex
