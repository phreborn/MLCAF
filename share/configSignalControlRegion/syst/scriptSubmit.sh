#!/bin/bash

### nominal
# config
REGION="configSignalControlRegion/syst"
CONFIG="htautau_lephad_sr_nom"
IDENT="SRnom"
JOBSLIST=(
    "data"
    "bkgCommon"
    "bkgZjets"
    "bkgTTbarNOMINAL"
    "fakesISO"
    "fakesID"
    "fakesIDISO"
    "signal"
)

# execute
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"

### lff
# config
CONFIG="htautau_lephad_sr_sys_lff"
IDENT="SRsyslff"
JOBSLIST=(
    "fakesISO"
    "fakesIDISO"
)

# execute
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"

### lsf
# config
CONFIG="htautau_lephad_sr_sys_lsf"
IDENT="SRsyslsf"
JOBSLIST=(
    "fakesISO"
    "fakesIDISO"
)

# execute
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"

### wff
# config
CONFIG="htautau_lephad_sr_sys_wff"
IDENT="SRsyswff"
JOBSLIST=(
    "fakesID"
    "fakesIDISO"
)

# execute
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"

### wsf
# config
CONFIG="htautau_lephad_sr_sys_wsf"
IDENT="SRsyswsf"
JOBSLIST=(
    "fakesID"
    "fakesIDISO"
)

# execute
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"

### vsf
# config
CONFIG="htautau_lephad_sr_sys_vsf"
IDENT="SRsysvsf"
JOBSLIST=(
    "fakesID"
    "fakesIDISO"
)

# execute
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"

### material
# config
#CONFIG="htautau_lephad_sr_sys_material"
#IDENT="SRsysmaterial"
#JOBSLIST=(
#)

# execute
#source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"

### lpx
# config
CONFIG="htautau_lephad_sr_sys_lpx"
IDENT="SRsyslpx"
JOBSLIST=(
    "bkgZjets"
)

# execute
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"

### top
# config
CONFIG="htautau_lephad_sr_sys_top"
IDENT="SRsystop"
JOBSLIST=(
    "bkgTTbarNOMINAL"
    "bkgTTbarME"
    "bkgTTbarPS"
    "bkgTTbarISRup"
)

# execute
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"

### weight
# config
CONFIG="htautau_lephad_sr_sys_weight"
IDENT="SRsysweight"
JOBSLIST=(
    "bkgCommon"
    "bkgZjets"
    "bkgTTbarNOMINAL"
    "signal"
)

# execute
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"

### p4
# config
CONFIG="htautau_lephad_sr_sys_p4"
IDENT="SRsysp4"
JOBSLIST=(
    "bkgCommon"
    "bkgZjets"
    "bkgTTbarNOMINAL"
    "signal"
)

# execute
source configCommon/scriptSubmit.sh "${REGION}" "${CONFIG}" "${IDENT}" "${JOBSLIST[@]}"
