#!/bin/bash

echo "Running over $1 set..."
if [ "$1" == "NOM" ]; then
    #analyze.py bsmtautau_lephad/config-SignalControlRegion/syst-old/master/master.cfg --debug --restrict /bkg/?/c16a/mc/TTL/Zll --option inputFile='sampleFolders/initialized/samples-initialized-bsmtautau_lephad_common-NOMINAL.root' aliases.lpxvar=LPX_KFACTOR_ALPHAS_Corr_1down lpxvar=LPX_KFACTOR_ALPHAS_Corr_1down
    analyze.py bsmtautau_lephad/config-SignalControlRegion/syst-old/master/master.cfg --debug --restrict /bkg/?/c16a/mc/TTL/Zll --option inputFile='sampleFolders/initialized/samples-initialized-bsmtautau_lephad_common-NOMINAL.root' aliases.weightvar=jet_jvteff_low weightvar=jet_jvteff_low
elif [ "$1" == "SYS" ]; then
    analyze.py bsmtautau_lephad/config-SignalControlRegion/syst-old/master/master.cfg --debug --restrict /bkg/?/c16a/mc/TTL/Top/single --option inputFile='sampleFolders/initialized/samples-initialized-bsmtautau_lephad_common-NOMINAL.root'
else
    echo "Systematic set not recognised."
    return 1
fi
