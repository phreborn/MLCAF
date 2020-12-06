#!/bin/bash

# config
REGION="config-WjetsFakeRegion/applyFF"
CONFIG="master"
IDENT="WFRapplyFF"
JOBSLIST=(
    "bkg_WTjetsFakes_TFF"
    "bkg_WTjetsFakes_TFF_QCDFakes_LFF"
)

# execute
source "${CAFANALYSISSHARE:?}/bsmtautau_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
