#!/bin/bash

# config
REGION="config-LeptonFakeRegion/applyFF"
CONFIG="master"
IDENT="LFRapplyFF"
JOBSLIST=(
    "fakesISO"
)

# execute
source "${CAFANALYSISSHARE:?}/bsmtautau_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
