#!/bin/bash

# add "contid" as argument to executing this script to run over contid

REGION="configAntiIDRegion"
JOBS="jobsAntiID.txt"
CONFIG="htautau_lephad_anti_id"
IDENT="AntiID"

if [ "$1" == "contid" ]; then
  CONFIG="${CONFIG}_contid"
  IDENT="${IDENT}contid"
fi

source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${JOBS}" "${IDENT}"
