#!/bin/bash

# config
REGION="config-WjetsFakeRegion/applyFF"
CONFIG="master"
IDENT="WFRapplyFF"
JOBSLIST=(
    "fakesID"
    "fakesIDISO"
)

# execute
source "${CAFANALYSISSHARE:?}/bsmtautau_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
