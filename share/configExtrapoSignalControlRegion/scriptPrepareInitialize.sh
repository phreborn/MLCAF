prepare.py configExtrapoSignalControlRegion/htautau_lephad_sr_reweight_mc16a.cfg
prepare.py configExtrapoSignalControlRegion/htautau_lephad_sr_reweight_mc16c.cfg

initialize.py configExtrapoSignalControlRegion/htautau_lephad_sr_reweight_mc16a.cfg
initialize.py configExtrapoSignalControlRegion/htautau_lephad_sr_reweight_mc16c.cfg

tqmerge -o sampleFolders/initialized/samples-initialized-htautau_lephad_sr_reweight.root -t initialize sampleFolders/initialized/samples-initialized-htautau_lephad_sr_reweight_mc16*.root
