# add "applyff" as argument to executing this script to run over applyff

APPLYFF="false"
if [ "$1" == "applyff" ]; then
  APPLYFF="true"
fi

if [ "$APPLYFF" == "true" ]; then
  submit.py configLeptonFakeRegion/htautau_lephad_lfr_applyff.cfg --jobs configLeptonFakeRegion/jobsLFR.txt --identifier LFRapplyff --allowArgChanges --submit condor
else
  submit.py configLeptonFakeRegion/htautau_lephad_lfr.cfg --jobs configLeptonFakeRegion/jobsLFR.txt --identifier LFR --allowArgChanges --submit condor
fi

####

# use either --merge option (the script will wait for all jobs to finish)
# or merge yourself with
echo "Merge with:"
echo "tqmerge -o sampleFolders/analyzed/samples-analyzed-htautau_lephad_lfr-nominal.root -t analyze batchOutput/unmerged_LFR/*.root"
echo "tqmerge -o sampleFolders/analyzed/samples-analyzed-htautau_lephad_lfr_applyff-nominal.root -t analyze batchOutput/unmerged_LFRapplyff/*.root"
