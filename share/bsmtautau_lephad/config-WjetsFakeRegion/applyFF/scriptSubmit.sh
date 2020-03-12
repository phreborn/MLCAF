#!/bin/bash

# config
REGION="configWjetsFakeRegion/applyFF"
CONFIG="htautau_lephad_wfr_applyff"
IDENT="WFRapplyFF"
JOBSLIST=(
    "fakesID"
    "fakesIDISO"
)

# execute
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
