# add "contid" as argument to executing this script to run over contid

DATE=`date '+%Y%m%d%H%M%S'`

CONTID="false"
if [ "$1" == "contid" ]; then
  CONTID="true"
fi

if [ "$CONTID" == "true" ]; then
  submit.py ConfigWjetsControlRegion/htautau_lephad_wcr_contid.cfg --jobs ConfigWjetsControlRegion/jobsWCR.txt --identifier WCRcontid --allowArgChanges --submit condor
else
  submit.py ConfigWjetsControlRegion/htautau_lephad_wcr.cfg --jobs ConfigWjetsControlRegion/jobsWCR.txt --identifier ${DATE}_WCR --allowArgChanges --submit condor
fi

####

# use either --merge option (the script will wait for all jobs to finish)
# or merge yourself with
echo "Merge with:"
echo "tqmerge -o sampleFolders/analyzed/samples-analyzed-htautau_lephad_wcr-nominal.root -t analyze batchOutput/unmerged_WCR/*.root"
echo "tqmerge -o sampleFolders/analyzed/samples-analyzed-htautau_lephad_wcr_contid-nominal.root -t analyze batchOutput/unmerged_WCRcontid/*.root"
