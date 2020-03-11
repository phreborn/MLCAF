#!/bin/bash

# config
REGION="configWjetsFakeRegion/applyFF/applySF"
CONFIG="htautau_lephad_wfr_applyffsf"
IDENT="WFRapplyFFSF"
JOBSLIST=(
    "data"
    "bkgCommon"
    "bkgZjets"
    "bkgTTbarNOMINAL"
    "fakesISO"
    "fakesID"
    "fakesIDISO"
)

# execute
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
