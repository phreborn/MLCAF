#!/bin/bash

analyze.py AHZ-lephad/config/OtherJetsTCR/master/analyze-OtherJetsTCR-opt.cfg --debug \
      --restrict /bkg/?/c16a/mcReal/Top/ttbar/nominal \
      "${CI_OPTS[@]}"
