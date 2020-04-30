#!/bin/bash

# config
REGION="config-SignalControlRegion"
CONFIG="master"
IDENT="SR"
JOBSLIST=(
    "data"
    "bkgCommon"
    "bkgZjets"
    "bkgTTbarNOMINAL"
    "fakesISO"
    "fakesID"
    "fakesIDISO"
    "signal"
)

# execute
source "${CAFANALYSISSHARE:?}/lqtaub_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
