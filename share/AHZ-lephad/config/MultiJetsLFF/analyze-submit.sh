#!/bin/bash

# config
REGION="config-QCDLeptonFakeRegion"
CONFIG="master"
IDENT="QCDLFR"
JOBSLIST=(
    "data"
    "bkg_common_TTL"
    "bkg_Zjets_TTL"
    "bkg_ttbar_nominal_TTL"
    "bkg_Wjets_TTL"
    "bkg_common_JFT"
    "bkg_Zjets_JFT"
    "bkg_ttbar_nominal_JFT"
    "bkg_Wjets_JFT"
)

# execute
source "${CAFANALYSISSHARE:?}/bsmtautau_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
