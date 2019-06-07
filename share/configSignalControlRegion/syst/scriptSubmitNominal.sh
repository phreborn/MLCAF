#!/bin/bash

REGION="configSignalControlRegion"
JOBS="syst/jobsSYS.txt --options inputFile='sampleFolders/initialized/samples-initialized-htautau_lephad_sr-NOMINAL.root'"
CONFIG="syst/htautau_lephad_sr_sys"
IDENT="SRsys"
SUBMIT="--submit condor --maxSampleSize 60000 --maxSampleCount 75"

submit.py ${REGION}/${CONFIG}.cfg --jobs ${REGION}/${JOBS} --identifier ${IDENT} --allowArgChanges ${SUBMIT}
