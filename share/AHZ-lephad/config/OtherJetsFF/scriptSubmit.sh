#!/bin/bash

# config
REGION="config-WjetsFakeRegion"
CONFIG="master"
IDENT="WFR"
JOBSLIST=(
    "data"
    "bkg_common_TTL"
    "bkg_Zjets_TTL"
    "bkg_ttbar_nominal_TTL"
    "bkg_QCDFakes_LFF"
)

# execute
source "${CAFANALYSISSHARE:?}/bsmtautau_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
