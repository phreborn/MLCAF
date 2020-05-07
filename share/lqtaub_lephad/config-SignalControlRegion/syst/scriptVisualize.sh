#!/bin/bash

### WCR
#visualize.py lqtaub_lephad/config-SignalControlRegion/syst/master/master_wcr.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_wcr_sys/summary.tex

#visualize.py lqtaub_lephad/config-SignalControlRegion/master/master_wcr_wjets.cfg
#visualize.py lqtaub_lephad/config-SignalControlRegion/master/master_wcr_qcd.cfg
#visualize.py lqtaub_lephad/config-SignalControlRegion/master/master_wcr_wjetsqcd.cfg

### TCR
visualize.py lqtaub_lephad/config-SignalControlRegion/syst/master/master_tcr.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_tcr_sys/summary.tex

#visualize.py lqtaub_lephad/config-SignalControlRegion/master/master_tcr_wjets.cfg
#visualize.py lqtaub_lephad/config-SignalControlRegion/master/master_tcr_qcd.cfg
#visualize.py lqtaub_lephad/config-SignalControlRegion/master/master_tcr_wjetsqcd.cfg

### VR
visualize.py lqtaub_lephad/config-SignalControlRegion/syst/master/master_vr.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_vr_sys/summary.tex

#visualize.py lqtaub_lephad/config-SignalControlRegion/master/master_vr_wjets.cfg
#visualize.py lqtaub_lephad/config-SignalControlRegion/master/master_vr_qcd.cfg
#visualize.py lqtaub_lephad/config-SignalControlRegion/master/master_vr_wjetsqcd.cfg

### SR
visualize.py lqtaub_lephad/config-SignalControlRegion/syst/master/master.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/lqtaub_lephad_sr_sys/summary.tex
