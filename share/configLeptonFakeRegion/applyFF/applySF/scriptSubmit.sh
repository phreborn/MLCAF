#!/bin/bash

# add "contid" as argument to executing this script to run over contid

REGION="configLeptonFakeRegion/applyFF/applySF"
JOBS="jobsLFR_applyFFSF.txt"
CONFIG="htautau_lephad_lfr_applyffsf"
IDENT="LFRapplyFFSF"

if [ "$1" == "contid" ]; then
  CONFIG="${CONFIG}_contid"
  IDENT="${IDENT}contid"
fi

source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${JOBS}" "${IDENT}"
