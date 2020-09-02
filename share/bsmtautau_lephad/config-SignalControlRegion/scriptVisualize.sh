#!/bin/bash

### VR
#visualize.py bsmtautau_lephad/config-SignalControlRegion/master/master_os_vr.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_os_vr/summary.tex

#visualize.py bsmtautau_lephad/config-SignalControlRegion/master/master_ss_vr.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_ss_vr/summary.tex

### SR
visualize.py bsmtautau_lephad/config-SignalControlRegion/master/master_os_sr.cfg
source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_os_sr/summary.tex

#visualize.py bsmtautau_lephad/config-SignalControlRegion/master/master_ss_sr.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_ss_sr/summary.tex

### Check the purity of QCD fakes in different categories
#visualize.py bsmtautau_lephad/config-SignalControlRegion/master/master_qcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_qcd/summary.tex

### Check the purity of Wjets fakes in different categories
#visualize.py bsmtautau_lephad/config-SignalControlRegion/master/master_wjets.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_wjets/summary.tex

### Check the purity of QCD fakes in Wjets fakes in different categories
#visualize.py bsmtautau_lephad/config-SignalControlRegion/master/master_wjets_qcd.cfg
#source "${CAFANALYSISSHARE:?}/scripts/tqpdflatex.sh" results/bsmtautau_lephad_wjets_qcd/summary.tex
