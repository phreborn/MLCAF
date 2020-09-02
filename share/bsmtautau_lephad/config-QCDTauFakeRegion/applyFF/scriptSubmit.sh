#!/bin/bash

# config
REGION="config-QCDTauFakeRegion/applyFF"
CONFIG="master"
IDENT="QCDTFRapplyFF"
JOBSLIST=(
    "bkg_QCDFakes"
)

# execute
source "${CAFANALYSISSHARE:?}/bsmtautau_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
