#!/bin/bash

NTUPLE_PATH="/eos/atlas/atlascerngroupdisk/phys-higgs/HSG6/Htautau/lephad/ntuples/190530"
XRD_ADDRESS="root://eosatlas.cern.ch/"
STORAGE_DIR="${CAFANALYSISSHARE:?}/inputs/FileLists"
OUTPUT_NAME="htautau_lephad_common_filelist"

collect_samples() {
    local INPUT="$1"

    xrdfs "${XRD_ADDRESS:?}" ls -R -u "${NTUPLE_PATH:?}/${INPUT:?}" | grep ".root"
}

mkdir -p "${STORAGE_DIR:?}"

for YEAR in "data15" "data16" "data17" "data18"; do
    collect_samples "data/${YEAR:?}" > "${STORAGE_DIR:?}/${OUTPUT_NAME:?}_${YEAR:?}.txt"
done

cat "${STORAGE_DIR:?}/${OUTPUT_NAME:?}_data15.txt" "${STORAGE_DIR:?}/${OUTPUT_NAME:?}_data16.txt" > "${STORAGE_DIR:?}/${OUTPUT_NAME:?}_data1516.txt"

for TYPE in "nom" "sys"; do
    for CAMPAIGN in "mc16a" "mc16d" "mc16e"; do
        collect_samples "mc/${CAMPAIGN:?}/${TYPE:?}" > "${STORAGE_DIR:?}/${OUTPUT_NAME:?}_${TYPE:?}_${CAMPAIGN:?}.txt"
    done
done
