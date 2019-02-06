# add "applyff" as argument to executing this script to run over applyff

APPLYFF="false"
if [ "$1" == "applyff" ]; then
  APPLYFF="true"
fi

if [ "$APPLYFF" == "true" ]; then
  submit.py ConfigFakeLeptonRegion/htautau_lephad_flr_applyff.cfg --jobs ConfigFakeLeptonRegion/jobsFLR.txt --identifier FLRapplyff --allowArgChanges
else
  submit.py ConfigFakeLeptonRegion/htautau_lephad_flr.cfg --jobs ConfigFakeLeptonRegion/jobsFLR.txt --identifier FLR --allowArgChanges
fi

####

# use either --merge option (the script will wait for all jobs to finish)
# or merge yourself with
echo "Merge with:"
echo "tqmerge -o sampleFolders/analyzed/samples-analyzed-htautau_lephad_flr-nominal.root -t analyze batchOutput/unmerged_FLR/*.root"
echo "tqmerge -o sampleFolders/analyzed/samples-analyzed-htautau_lephad_flr_applyff-nominal.root -t analyze batchOutput/unmerged_FLRapplyff/*.root"
