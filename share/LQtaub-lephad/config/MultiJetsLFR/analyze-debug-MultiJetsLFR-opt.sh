#!/bin/bash

analyze.py LQtaub-lephad/config/MultiJetsLFR/master/analyze-MultiJetsLFR-opt.cfg --debug \
      --restrict /bkg/?/c16a/mc/Top/ttbar/nominal \
      "${CI_OPTS[@]}"
