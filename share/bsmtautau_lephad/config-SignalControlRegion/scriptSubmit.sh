#!/bin/bash

# config
REGION="config-SignalControlRegion"
CONFIG="master"
IDENT="SR"
JOBSLIST=(
    "data"
    "bkg_common_TTL"
    "bkg_Zjets_TTL"
    "bkg_ttbar_nominal_TTL"
    "bkg_QCDFakes_LFF"
    "bkg_WTjetsFakes_TFF"
    "bkg_WTjetsFakes_TFF_QCDFakes_LFF"
    "signal"
)

# execute
source "${CAFANALYSISSHARE:?}/bsmtautau_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
