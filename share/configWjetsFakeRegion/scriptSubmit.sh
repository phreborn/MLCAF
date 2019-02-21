# add "contid" as argument to executing this script to run over contid

DATE=`date '+%Y%m%d%H%M%S'`

CONTID="false"
if [ "$1" == "contid" ]; then
  CONTID="true"
fi

if [ "$CONTID" == "true" ]; then
  submit.py configWjetsFakeRegion/htautau_lephad_wfr_contid.cfg --jobs configWjetsFakeRegion/jobsWFR.txt --identifier WFRcontid_${DATE} --allowArgChanges --submit condor
  echo "tqmerge -o sampleFolders/analyzed/samples-analyzed-htautau_lephad_wfr_contid-nominal.root -t analyze batchOutput/unmerged_WFRcontid_${DATE}/*.root"
else
  submit.py configWjetsFakeRegion/htautau_lephad_wfr.cfg --jobs configWjetsFakeRegion/jobsWFR.txt --identifier WFR_${DATE} --allowArgChanges --submit condor
  echo "tqmerge -o sampleFolders/analyzed/samples-analyzed-htautau_lephad_wfr-nominal.root -t analyze batchOutput/unmerged_WFR_${DATE}/*.root"
fi

####

# use either --merge option (the script will wait for all jobs to finish)
# or merge yourself with
#echo "Merge with:"
