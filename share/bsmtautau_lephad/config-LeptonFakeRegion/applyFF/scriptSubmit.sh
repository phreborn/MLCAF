#!/bin/bash

# config
REGION="configLeptonFakeRegion/applyFF"
CONFIG="htautau_lephad_lfr_applyff"
IDENT="LFRapplyFF"
JOBSLIST=(
    "fakesISO"
)

# execute
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
