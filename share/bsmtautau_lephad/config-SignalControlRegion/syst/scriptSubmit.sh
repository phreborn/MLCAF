#!/bin/bash

# common config
REGION="config-SignalControlRegion/syst"
CONFIG_BASE="master_sys"
IDENT_BASE="SRsys"
JOBSLIST=(
    "bkgCommon"
    "bkgZjets"
    "bkgTTbarNOMINAL"
    "fakesISO"
    "fakesID"
    "fakesIDISO"
    "signal"
)

# handle arguments
if [ -z "$*" ]; then
    echo "No arguments provided!"
    return
fi
echo "Accepting arguments: $*"

# loop execute
for ARG in "$@"; do
    echo ""
    echo "Submitting systematic: ${ARG}"

    # config
    CONFIG="${CONFIG_BASE}_${ARG}"
    IDENT="${IDENT_BASE}${ARG}"

    # execute
    source "${CAFANALYSISSHARE:?}/bsmtautau_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
done

################### legacy #####################

### lff
#JOBSLIST=(
#    "fakesISO"
#    "fakesIDISO"
#)

### lsf
#JOBSLIST=(
#    "fakesISO"
#    "fakesIDISO"
#)

### wff
#JOBSLIST=(
#    "fakesID"
#    "fakesIDISO"
#)

### wsf
#JOBSLIST=(
#    "fakesID"
#    "fakesIDISO"
#)

### vsf
#JOBSLIST=(
#    "fakesID"
#    "fakesIDISO"
#)

### material
##JOBSLIST=(
##)

### lpx
#JOBSLIST=(
#    "bkgZjets"
#)

### top
#JOBSLIST=(
#    "bkgTTbarNOMINAL"
##    "bkgTTbarME"
##    "bkgTTbarPS"
##    "bkgTTbarISRup"
#)

### weight
#JOBSLIST=(
#    "bkgCommon"
#    "bkgZjets"
#    "bkgTTbarNOMINAL"
#    "signal"
#)

### p4
#JOBSLIST=(
#    "bkgCommon"
#    "bkgZjets"
#    "bkgTTbarNOMINAL"
#    "signal"
#)
