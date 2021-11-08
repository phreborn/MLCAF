#!/bin/bash

TASK="TCR-SF-closure"
analyze.py AHZ-lephad/config/TCR/master/analyze-${TASK}.cfg --debug \
      --restrict /bkg/?/c16a/mcReal/Top/single
