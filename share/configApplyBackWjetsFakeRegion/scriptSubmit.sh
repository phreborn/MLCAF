#!/bin/bash

# add "applyff"/"contid" as argument to executing this script to run over applyff/contid

REGION="configApplyBackWjetsFakeRegion"
JOBS="jobsWFR.txt"
CONFIG="htautau_lephad_wfr_applywff"
IDENT="WFRapplywff"

if [ "$1" == "applyff" ]; then
  CONFIG="${CONFIG}_applyff"
  IDENT="${IDENT}applyff"
fi
if [ "$1" == "contid" ]; then
  CONFIG="${CONFIG}_contid"
  IDENT="${IDENT}contid"
fi

source configCommon/scriptSubmit.sh ${REGION} ${CONFIG} ${JOBS} ${IDENT}
