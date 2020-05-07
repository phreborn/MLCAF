#!/bin/bash

# config
REGION="config-TopControlRegion"
CONFIG="master"
IDENT="TCR"
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
