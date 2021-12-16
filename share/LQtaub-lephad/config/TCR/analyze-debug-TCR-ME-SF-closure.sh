#!/bin/bash

TASK="TCR-ME-SF-closure"
analyze.py LQtaub-lephad/config/TCR/master/analyze-${TASK}.cfg --debug \
      --restrict /bkg/?/c16a/mcReal/Top/ME
