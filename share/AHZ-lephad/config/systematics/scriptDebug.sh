#!/bin/bash

OPTION="indexLow=1 indexHigh=2"

analyze.py bsmtautau_lephad/config-SystematicVariations/master/analyze-systematics-CP-p4.cfg \
    --restrict /bkg/?/c16a/mc/TTL/Ztautau \
    --debug \
    --options ${OPTION}
