#!/bin/bash

### WCR
visualize.py configSignalControlRegion/htautau_lephad_wcr.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_wcr/summary.tex

#visualize.py configSignalControlRegion/htautau_lephad_wcr_wjets.cfg
#visualize.py configSignalControlRegion/htautau_lephad_wcr_qcd.cfg
#visualize.py configSignalControlRegion/htautau_lephad_wcr_wjetsqcd.cfg

### TCR
visualize.py configSignalControlRegion/htautau_lephad_tcr.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_tcr/summary.tex

#visualize.py configSignalControlRegion/htautau_lephad_tcr_wjets.cfg
#visualize.py configSignalControlRegion/htautau_lephad_tcr_qcd.cfg
#visualize.py configSignalControlRegion/htautau_lephad_tcr_wjetsqcd.cfg

### VR
visualize.py configSignalControlRegion/htautau_lephad_vr.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_vr/summary.tex

#visualize.py configSignalControlRegion/htautau_lephad_vr_wjets.cfg
#visualize.py configSignalControlRegion/htautau_lephad_vr_qcd.cfg
#visualize.py configSignalControlRegion/htautau_lephad_vr_wjetsqcd.cfg

### SR
visualize.py configSignalControlRegion/htautau_lephad_sr.cfg
source scripts/tqpdflatex.sh results/htautau_lephad_sr/summary.tex
