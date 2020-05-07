#!/bin/bash

### VR
visualize.py lqtaub_lephad/config-SignalControlRegion/master/master_vr.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_vr/summary.tex

#visualize.py lqtaub_lephad/config-SignalControlRegion/master/master_vr_qcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_vr_qcd/summary.tex

#visualize.py lqtaub_lephad/config-SignalControlRegion/master/master_vr_wjets.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_vr_wjets/summary.tex

#visualize.py lqtaub_lephad/config-SignalControlRegion/master/master_vr_wjetsqcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_vr_wjetsqcd/summary.tex


### SR
visualize.py lqtaub_lephad/config-SignalControlRegion/master/master.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_sr/summary.tex
