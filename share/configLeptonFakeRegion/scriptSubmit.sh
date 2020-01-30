#!/bin/bash

# config
REGION="configLeptonFakeRegion"
CONFIG="htautau_lephad_lfr"
IDENT="LFR"
JOBSLIST=(
    "data"
    "bkgCommon"
    "bkgZjets"
    "bkgTTbarNOMINAL"
    "bkgWjets"
)

# submit
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST}"
