#!/bin/bash

# config
REGION="config-WjetsFakeRegion/applySF"
CONFIG="master"
IDENT="WFRapplySF"
JOBSLIST=(
    "data"
    "bkgCommon"
    "bkgZjets"
    "bkgTTbarNOMINAL"
    "fakesISO"
)

# execute
source "${CAFANALYSISSHARE:?}/lqtaub_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
