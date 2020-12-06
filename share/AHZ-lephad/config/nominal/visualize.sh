#!/bin/bash

visualize.py AHZ-lephad/config/nominal/master/visualize-nominal-os-sr.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/AHZ-lephad-nominal-os-sr/summary.tex
