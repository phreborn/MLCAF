#!/bin/bash

visualize.py bsmtautau_lephad/config-WjetsFakeRegion/master/master_os.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_os_wfr/summary.tex

visualize.py bsmtautau_lephad/config-WjetsFakeRegion/master/master_ss.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_ss_wfr/summary.tex
