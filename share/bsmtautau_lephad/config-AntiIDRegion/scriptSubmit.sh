#!/bin/bash

# config
REGION="configAntiIDRegion"
CONFIG="htautau_lephad_anti_id"
IDENT="AntiID"
JOBSLIST=(
    "data"
    "bkgCommon"
    "bkgZjets"
    "bkgTTbarNOMINAL"
    "bkgWjets"
    "fakesISO"
    "fakesJetWjets"
)

# execute
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
