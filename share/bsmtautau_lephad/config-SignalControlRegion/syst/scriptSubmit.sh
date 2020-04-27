#!/bin/bash

### common
REGION="config-SignalControlRegion/syst"

### lff
# config
CONFIG="master_sys_lff"
IDENT="SRsyslff"
JOBSLIST=(
    "fakesISO"
    "fakesIDISO"
)

# execute
source "${CAFANALYSISSHARE:?}/bsmtautau_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"

### lsf
# config
CONFIG="master_sys_lsf"
IDENT="SRsyslsf"
JOBSLIST=(
    "fakesISO"
    "fakesIDISO"
)

# execute
source "${CAFANALYSISSHARE:?}/bsmtautau_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"

### wff
# config
CONFIG="master_sys_wff"
IDENT="SRsyswff"
JOBSLIST=(
    "fakesID"
    "fakesIDISO"
)

# execute
source "${CAFANALYSISSHARE:?}/bsmtautau_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"

### wsf
# config
CONFIG="master_sys_wsf"
IDENT="SRsyswsf"
JOBSLIST=(
    "fakesID"
    "fakesIDISO"
)

# execute
source "${CAFANALYSISSHARE:?}/bsmtautau_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"

### vsf
# config
CONFIG="master_sys_vsf"
IDENT="SRsysvsf"
JOBSLIST=(
    "fakesID"
    "fakesIDISO"
)

# execute
source "${CAFANALYSISSHARE:?}/bsmtautau_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"

### material
# config
#CONFIG="master_sys_material"
#IDENT="SRsysmaterial"
#JOBSLIST=(
#)

# execute
#source "${CAFANALYSISSHARE:?}/bsmtautau_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"

### lpx
# config
CONFIG="master_sys_lpx"
IDENT="SRsyslpx"
JOBSLIST=(
    "bkgZjets"
)

# execute
source "${CAFANALYSISSHARE:?}/bsmtautau_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"

### top
# config
CONFIG="master_sys_top"
IDENT="SRsystop"
JOBSLIST=(
    "bkgTTbarNOMINAL"
#    "bkgTTbarME"
#    "bkgTTbarPS"
#    "bkgTTbarISRup"
)

# execute
source "${CAFANALYSISSHARE:?}/bsmtautau_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"

### weight
# config
CONFIG="master_sys_weight"
IDENT="SRsysweight"
JOBSLIST=(
    "bkgCommon"
    "bkgZjets"
    "bkgTTbarNOMINAL"
    "signal"
)

# execute
source "${CAFANALYSISSHARE:?}/bsmtautau_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"

### p4
# config
CONFIG="master_sys_p4"
IDENT="SRsysp4"
JOBSLIST=(
    "bkgCommon"
    "bkgZjets"
    "bkgTTbarNOMINAL"
    "signal"
)

# execute
source "${CAFANALYSISSHARE:?}/bsmtautau_lephad/config-Common/scriptSubmit.sh" "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
