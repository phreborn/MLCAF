#!/bin/bash

# add "contid" as argument to executing this script to run over contid

REGION="configFailIDRegion"
JOBS="jobsALL.txt"
CONFIG="htautau_lephad_sr_check"
IDENT="SRfailid_check"

if [ "$1" == "contid" ]; then
  CONFIG="${CONFIG}_contid"
  IDENT="${IDENT}contid"
fi

source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${JOBS}" "${IDENT}"
