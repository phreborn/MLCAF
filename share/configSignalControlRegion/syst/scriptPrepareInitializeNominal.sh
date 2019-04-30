#!/bin/bash

prepare.py configSignalControlRegion/htautau_lephad_sr.cfg --options campaignsConfig='configCommon/htautau_lephad_common_campaigns_input_sys.cfg' outputFile='sampleFolders/prepared/samples-prepared-htautau_lephad_sr-NOMINAL.root'
initialize.py configSignalControlRegion/htautau_lephad_sr.cfg --options campaignsConfig='configCommon/htautau_lephad_common_campaigns_input_sys.cfg' inputFile='sampleFolders/prepared/samples-prepared-htautau_lephad_sr-NOMINAL.root' outputFile='sampleFolders/initialized/samples-initialized-htautau_lephad_sr-NOMINAL.root'
