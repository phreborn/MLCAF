prepare.py configWjetsFakeRegion/htautau_lephad_wfr_mc16a.cfg
prepare.py configWjetsFakeRegion/htautau_lephad_wfr_mc16c.cfg

initialize.py configWjetsFakeRegion/htautau_lephad_wfr_mc16a.cfg
initialize.py configWjetsFakeRegion/htautau_lephad_wfr_mc16c.cfg

tqmerge -o sampleFolders/initialized/samples-initialized-htautau_lephad_wfr.root -t initialize sampleFolders/initialized/samples-initialized-htautau_lephad_wfr_mc16*.root
