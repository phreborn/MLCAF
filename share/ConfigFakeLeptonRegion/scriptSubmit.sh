APPLYFF=false

SUBMIT=bsub
if [ $USER == zorbas ]; then
  SUBMIT=condor_qsub
fi

python submitAnalysis.py --submit $SUBMIT --queue medium --jobs ConfigFakeLeptonRegion/jobsFLR.txt --identifier FLR --downmerge --memory 0.01 ConfigFakeLeptonRegion/htautau_lephad_flr.cfg

if [ $APPLYFF == true ]; then
  python submitAnalysis.py --submit $SUBMIT --queue medium --jobs ConfigFakeLeptonRegion/jobsFLR.txt --identifier FLRapplyff --downmerge --memory 0.01 ConfigFakeLeptonRegion/htautau_lephad_flr_applyff.cfg
fi

####

# use either --merge option (the script will wait for all jobs to finish)
# or merge yourself with
#tqmerge -o output/htautau_lephad_flr/nominal.root -t runAnalysis -Sum output/unmerged_FLR/*.root
#tqmerge -o output/htautau_lephad_flr/nominal_applyff.root -t runAnalysis -Sum output/unmerged_FLRapplyff/*.root
