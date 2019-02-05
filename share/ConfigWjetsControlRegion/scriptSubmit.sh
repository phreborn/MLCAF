# add "contid" as argument to executing this script to run over contid

CONTID="false"
if [ "$1" == "contid" ]; then
  CONTID="true"
fi

SUBMIT="bsub"
if [ "$USER" == "zorbas" ]; then
  SUBMIT="condor_qsub"
fi

if [ "$CONTID" == "true" ]; then
  python submitAnalysis.py --submit $SUBMIT --queue medium --jobs ConfigWjetsControlRegion/jobsWCR.txt --identifier WCRcontid --downmerge --memory 0.01 ConfigWjetsControlRegion/htautau_lephad_wcr_contid.cfg
else
  python submitAnalysis.py --submit $SUBMIT --queue medium --jobs ConfigWjetsControlRegion/jobsWCR.txt --identifier WCR --downmerge --memory 0.01 ConfigWjetsControlRegion/htautau_lephad_wcr.cfg
fi

####

# use either --merge option (the script will wait for all jobs to finish)
# or merge yourself with
#tqmerge -o output/htautau_lephad_wcr/nominal.root -t runAnalysis -Sum output/unmerged_WCR/*.root
#tqmerge -o output/htautau_lephad_wcr_contid/nominal.root -t runAnalysis -Sum output/unmerged_WCRcontid/*.root
