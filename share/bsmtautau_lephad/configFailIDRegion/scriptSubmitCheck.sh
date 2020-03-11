#!/bin/bash

# config
REGION="configFailIDRegion"
CONFIG="htautau_lephad_sr_check"
IDENT="SRfailid_check"
JOBSLIST=(
    "data"
    "bkgCommon"
    "bkgZjets"
    "bkgTTbarNOMINAL"
    "bkgWjets"
    "fakesISO"
    "fakesJet"
    "fakesLep"
    "fakesTruthTau"
)

# execute
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
