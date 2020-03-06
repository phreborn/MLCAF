#!/bin/bash

# config
REGION="configLeptonFakeRegion/applyFF/applySF"
CONFIG="htautau_lephad_lfr_applyffsf"
IDENT="LFRapplyFFSF"
JOBSLIST=(
    "fakesISO"
)

# execute
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
