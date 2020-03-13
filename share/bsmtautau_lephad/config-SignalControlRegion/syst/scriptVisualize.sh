#!/bin/bash

### WCR
#visualize.py configSignalControlRegion/syst/htautau_lephad_wcr_sys.cfg
#source scripts/tqpdflatex.sh results/htautau_lephad_wcr_sys/summary.tex

#visualize.py configSignalControlRegion/htautau_lephad_wcr_wjets.cfg
#visualize.py configSignalControlRegion/htautau_lephad_wcr_qcd.cfg
#visualize.py configSignalControlRegion/htautau_lephad_wcr_wjetsqcd.cfg

### TCR
visualize.py configSignalControlRegion/syst/htautau_lephad_tcr_sys.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_tcr_sys/summary.tex

#visualize.py configSignalControlRegion/htautau_lephad_tcr_wjets.cfg
#visualize.py configSignalControlRegion/htautau_lephad_tcr_qcd.cfg
#visualize.py configSignalControlRegion/htautau_lephad_tcr_wjetsqcd.cfg

### VR
visualize.py configSignalControlRegion/syst/htautau_lephad_vr_sys.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_vr_sys/summary.tex

#visualize.py configSignalControlRegion/htautau_lephad_vr_wjets.cfg
#visualize.py configSignalControlRegion/htautau_lephad_vr_qcd.cfg
#visualize.py configSignalControlRegion/htautau_lephad_vr_wjetsqcd.cfg

### SR
visualize.py configSignalControlRegion/syst/htautau_lephad_sr_sys.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_sr_sys/summary.tex
