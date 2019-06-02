#!/bin/bash

# add "contid" as argument to executing this script to run over contid

REGION="configWjetsFakeRegion/applyFF"
JOBS="jobsWFR_applyff.txt"
CONFIG="htautau_lephad_wfr_applyff"
IDENT="WFRapplyFF"

if [ "$1" == "contid" ]; then
  CONFIG="${CONFIG}_contid"
  IDENT="${IDENT}contid"
fi

source configCommon/scriptSubmit.sh ${REGION} ${CONFIG} ${JOBS} ${IDENT}
