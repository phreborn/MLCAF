#!/bin/bash

# config
REGION="configWjetsFakeRegion/applySF"
CONFIG="htautau_lephad_wfr_applysf"
IDENT="WFRapplySF"
JOBSLIST=(
    "data"
    "bkgCommon"
    "bkgZjets"
    "bkgTTbarNOMINAL"
    "fakesISO"
)

# execute
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
