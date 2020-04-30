#!/bin/bash

# handle arguments
if [ -z "$1" ]; then
    echo "No argument provided!"
    return
fi

# check arguments
if [ "$1" == "NOM" ]; then
    SYST="lff"
    SAMPLE="/bkg/?/c16a/Fakes/ISO/mc/Ztautau/Z"
elif [ "$1" == "SYS" ]; then
    SYST="lpx"
    SAMPLE="/bkg/?/c16a/Ztautau/Z"
else
    echo "Rejecting argument: $1"
    return
fi

# execute
analyze.py lqtaub_lephad/config-SignalControlRegion/syst/master/master_sys_"${SYST}".cfg --debug --restrict "${SAMPLE}"
