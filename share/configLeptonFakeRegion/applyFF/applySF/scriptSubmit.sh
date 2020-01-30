#!/bin/bash

# config
REGION="configLeptonFakeRegion/applyFF/applySF"
CONFIG="htautau_lephad_lfr_applyffsf"
IDENT="LFRapplyFFSF"
JOBSLIST=(
    "fakesISO"
)

# submit
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST}"
