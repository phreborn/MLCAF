#!/bin/bash

# initialize required arguments
ACCESS_TYPE=""
NTUPLE_PATH=""

# collect command line arguments
if [ -z "$1" ]; then
    echo -e "\e[91mNo access type specified!\e[39m" >&2
    return 1
else
    ACCESS_TYPES=("local" "remote")
    if [[ ! "${ACCESS_TYPES[*]}" =~ $1 ]]; then
        echo -e "\e[91mUnsupported access type '$1'!\e[39m" >&2
        echo -e "\e[91mPlease specify from: ${ACCESS_TYPES[*]}\e[39m" >&2
        return 1
    else
        ACCESS_TYPE="$1"
    fi
fi

if [ -z "$2" ]; then
    echo -e "\e[91mNo location specified!\e[39m"
    return 1
else
    NTUPLE_PATH="$2"
fi

# declare global variables and functions
STORAGE_DIR="${CAFANALYSISSHARE:?}/inputs/FileLists"
OUTPUT_BASE="${STORAGE_DIR:?}/htautau_lephad_common_filelist"

collect_samples_local() {
    local INPUT="$1"

    find "${NTUPLE_PATH:?}/${INPUT:?}" -type f -name "*.root*"
}

collect_samples_remote() {
    local INPUT="$1"
    local XRD_ADDRESS="root://eosatlas.cern.ch/"

    xrdfs "${XRD_ADDRESS:?}" ls -R -u "${NTUPLE_PATH:?}/${INPUT:?}" | grep ".root"
}

# apply access type
COLLECT_SAMPLES=""

if [ "${ACCESS_TYPE}" == "local" ]; then
    COLLECT_SAMPLES="collect_samples_local"
elif [ "${ACCESS_TYPE}" == "remote" ]; then
    COLLECT_SAMPLES="collect_samples_remote"
fi

# begin collecting samples
echo -e "\e[94mSaving file lists to directory: ${STORAGE_DIR:?}\e[39m"
mkdir -p "${STORAGE_DIR:?}"

for YEAR in "data15" "data16" "data17" "data18"; do
    echo -e "\e[93mScanning ${YEAR}...\e[39m"
    "${COLLECT_SAMPLES:?}" "data/${YEAR:?}" > "${OUTPUT_BASE:?}_${YEAR:?}.txt"
done

echo -e "\e[94mCombining data15+data16...\e[39m"
cat "${OUTPUT_BASE:?}_data15.txt" "${OUTPUT_BASE:?}_data16.txt" > "${OUTPUT_BASE:?}_data1516.txt"

for TYPE in "nom" "sys"; do
    for CAMPAIGN in "mc16a" "mc16d" "mc16e"; do
        echo -e "\e[93mScanning ${TYPE} ${CAMPAIGN}...\e[39m"
        "${COLLECT_SAMPLES:?}" "mc/${CAMPAIGN:?}/${TYPE:?}" > "${OUTPUT_BASE:?}_${TYPE:?}_${CAMPAIGN:?}.txt"
    done
done

echo -e "\e[92mDone!\e[39m"
