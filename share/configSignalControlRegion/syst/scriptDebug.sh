#!/bin/bash

echo "Running over $1 set..."
if [ "$1" == "NOM" ]; then
    analyze.py configSignalControlRegion/syst/htautau_lephad_sr_sys.cfg --debug --restrict /bkg/?/c16a/Fakes/ISO/mc/Top/single --option aliases.isovar=FakeFactor_LepElBveto_1up isovar=FakeFactor_LepElBveto_1up
elif [ "$1" == "SYS" ]; then
    analyze.py configSignalControlRegion/syst/htautau_lephad_sr_sys.cfg --debug --restrict /bkg/?/c16a/Top/single --option inputFile='sampleFolders/initialized/samples-initialized-htautau_lephad_common-TAUS_TRUEHADTAU_SME_TES_DETECTOR_1down.root'
else
    echo "Systematic set not recognised."
    return 1
fi
