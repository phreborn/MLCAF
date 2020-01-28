#!/bin/bash

# add "contid" as argument to executing this script to run over contid

REGION="configWjetsFakeRegion/applyFF/applySF"
JOBS="jobsWFR_applyFFSF.txt"
CONFIG="htautau_lephad_wfr_applyffsf"
IDENT="WFRapplyFFSF"

if [ "$1" == "contid" ]; then
  CONFIG="${CONFIG}_contid"
  IDENT="${IDENT}contid"
fi

source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${JOBS}" "${IDENT}"
