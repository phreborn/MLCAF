#!/bin/bash

### VR
visualize.py bsmtautau_lephad/config-SignalControlRegion/master/master_vr.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_vr/summary.tex

#visualize.py bsmtautau_lephad/config-SignalControlRegion/master/master_vr_qcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_vr_qcd/summary.tex

#visualize.py bsmtautau_lephad/config-SignalControlRegion/master/master_vr_wjets.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_vr_wjets/summary.tex

#visualize.py bsmtautau_lephad/config-SignalControlRegion/master/master_vr_wjetsqcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_vr_wjetsqcd/summary.tex

### TCR
visualize.py bsmtautau_lephad/config-SignalControlRegion/master/master_tcr.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_tcr/summary.tex

#visualize.py bsmtautau_lephad/config-SignalControlRegion/master/master_tcr_qcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_tcr_qcd/summary.tex

#visualize.py bsmtautau_lephad/config-SignalControlRegion/master/master_tcr_wjets.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_tcr_wjets/summary.tex

#visualize.py bsmtautau_lephad/config-SignalControlRegion/master/master_tcr_wjetsqcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_tcr_wjetsqcd/summary.tex

### SR
visualize.py bsmtautau_lephad/config-SignalControlRegion/master/master.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_sr/summary.tex
