#!/bin/bash

# config
REGION="configWjetsFakeRegion"
CONFIG="htautau_lephad_wfr"
IDENT="WFR"
JOBSLIST=(
    "data"
    "bkgCommon"
    "bkgZjets"
    "bkgTTbarNOMINAL"
    "fakesISO"
)

# execute
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
