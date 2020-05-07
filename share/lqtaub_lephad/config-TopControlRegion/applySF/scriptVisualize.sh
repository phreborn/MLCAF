#!/bin/bash

### VR
visualize.py lqtaub_lephad/config-TopControlRegion/applySF/master/master_vr.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_vr/summary.tex

### TCR
visualize.py lqtaub_lephad/config-TopControlRegion/applySF/master/master.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_tcr_applysf/summary.tex
