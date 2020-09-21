#!/bin/bash

# config
REGION="config-QCDLeptonFakeRegion/applyFF"
CONFIG="master"
IDENT="QCDLFRapplyFF"
JOBSLIST=(
    "bkg_QCDFakes_LFF"
)

# execute
source "${CAFANALYSISSHARE:?}/bsmtautau_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
