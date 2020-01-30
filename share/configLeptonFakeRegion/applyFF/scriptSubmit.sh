#!/bin/bash

# config
REGION="configLeptonFakeRegion/applyFF"
CONFIG="htautau_lephad_lfr_applyff"
IDENT="LFRapplyFF"
JOBSLIST=(
    "fakesISO"
)

# submit
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST}"
