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
  python submitAnalysis.py --submit $SUBMIT --queue medium --jobs ConfigSignalRegion/jobsALL.txt --identifier SRcontid --downmerge --memory 0.01 ConfigSignalRegion/htautau_lephad_sr_contid.cfg
else
  python submitAnalysis.py --submit $SUBMIT --queue medium --jobs ConfigSignalRegion/jobsALL.txt --identifier SR --downmerge --memory 0.01 ConfigSignalRegion/htautau_lephad_sr.cfg
fi

####

# use either --merge option (the script will wait for all jobs to finish)
# or merge yourself with
#tqmerge -o output/htautau_lephad_sr/nominal.root -t runAnalysis -Sum output/unmerged_SR/*.root
#tqmerge -o output/htautau_lephad_sr_contid/nominal.root -t runAnalysis -Sum output/unmerged_SRcontid/*.root
