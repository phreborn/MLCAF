#!/bin/bash

# config
REGION="config-LeptonFakeRegion"
CONFIG="master"
IDENT="LFR"
JOBSLIST=(
    "data"
    "bkgCommon"
    "bkgZjets"
    "bkgTTbarNOMINAL"
    "bkgWjets"
)

# execute
source "${CAFANALYSISSHARE:?}/lqtaub_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
