#!/bin/bash

# add "contid" as argument to executing this script to run over contid

REGION="configSignalControlRegion/applySF"
JOBS="jobsALL.txt"
CONFIG="htautau_lephad_sr_applysf"
IDENT="SRapplySF"

if [ "$1" == "contid" ]; then
  CONFIG="${CONFIG}_contid"
  IDENT="${IDENT}contid"
fi

source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${JOBS}" "${IDENT}"
