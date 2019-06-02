#!/bin/bash

# add "contid" as argument to executing this script to run over contid

REGION="configLeptonFakeRegion/applyFF"
JOBS="jobsLFR_applyFF.txt"
CONFIG="htautau_lephad_lfr_applyff"
IDENT="LFRapplyFF"

if [ "$1" == "contid" ]; then
  CONFIG="${CONFIG}_contid"
  IDENT="${IDENT}contid"
fi

source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${JOBS}" "${IDENT}"
