prepare.py configApplyBackLeptonFakeRegion/htautau_lephad_lfr_applyff_mc16a.cfg
prepare.py configApplyBackLeptonFakeRegion/htautau_lephad_lfr_applyff_mc16c.cfg

initialize.py configApplyBackLeptonFakeRegion/htautau_lephad_lfr_applyff_mc16a.cfg
initialize.py configApplyBackLeptonFakeRegion/htautau_lephad_lfr_applyff_mc16c.cfg

tqmerge -o sampleFolders/initialized/samples-initialized-htautau_lephad_lfr_applyff.root -t initialize sampleFolders/initialized/samples-initialized-htautau_lephad_lfr_applyff_mc16*.root
