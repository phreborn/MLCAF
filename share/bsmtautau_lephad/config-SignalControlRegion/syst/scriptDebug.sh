#!/bin/bash

analyze.py configSignalControlRegion/syst/htautau_lephad_sr_nom.cfg --debug --restrict /bkg/?/c16a/Ztautau/Z

analyze.py configSignalControlRegion/syst/htautau_lephad_sr_sys_iso.cfg --debug --restrict /bkg/?/c16a/Fakes/ISO/mc/Ztautau/Z
analyze.py configSignalControlRegion/syst/htautau_lephad_sr_sys_fake.cfg --debug --restrict /bkg/?/c16a/Fakes/ID/mc/Ztautau/Z
