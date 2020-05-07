#!/bin/bash

# config
REGION="config-LeptonFakeRegion/applyFF/applySF"
CONFIG="master"
IDENT="LFRapplyFFSF"
JOBSLIST=(
    "fakesISO"
)

# execute
source "${CAFANALYSISSHARE:?}/lqtaub_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
