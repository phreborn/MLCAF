#!/bin/bash

# add "contid" as argument to executing this script to run over contid

REGION="configLeptonFakeRegion"
JOBS="jobsLFR.txt"
CONFIG="htautau_lephad_lfr"
IDENT="LFR"

if [ "$1" == "contid" ]; then
  CONFIG="${CONFIG}_contid"
  IDENT="${IDENT}contid"
fi

source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${JOBS}" "${IDENT}"
