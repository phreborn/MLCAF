#!/bin/bash

analyze.py AHZ-lephad/config/MultiJetsLFR/master/analyze-MultiJetsLFR-opt.cfg --debug \
      --restrict /bkg/?/c16a/mc/Top/ttbar/nominal \
      "${CI_OPTS[@]}"
