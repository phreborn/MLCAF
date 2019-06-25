#!/bin/bash

# add "contid" as argument to executing this script to run over contid

REGION="configFailIDSignalControlRegion"
JOBS="jobsALL.txt"
CONFIG="htautau_lephad_sr_lffcheck"
IDENT="SR_lffcheck"

if [ "$1" == "contid" ]; then
  CONFIG="${CONFIG}_contid"
  IDENT="${IDENT}contid"
fi

source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${JOBS}" "${IDENT}"
