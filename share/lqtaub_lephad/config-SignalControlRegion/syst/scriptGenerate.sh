#!/bin/bash

for CHANNEL in "ehad" "muhad"; do
    echo "Generating systematic bands for: ${CHANNEL}..."

    python "${CAFANALYSISBASE:?}/tools/generateSystematicsBands.py" \
        --input "sampleFolders/analyzed/samples-analyzed-lqtaub_lephad_sr_sys.root" \
        --systematics "${CAFANALYSISSHARE:?}/lqtaub_lephad/config-SignalControlRegion/syst/lists/all.tq" \
        --reloadcuts --pathPattern "/bkg/${CHANNEL}"'$(Variation)'"/[c16a+c16d+c16e]/[Ztautau+Zll+Top+Diboson+Fakes/[ISO/[data-mc]+ID/[data-[mc+ISO/[data-mc]]]]]" \
        --output "systband_${CHANNEL}.root"
done
