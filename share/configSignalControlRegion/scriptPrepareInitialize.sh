prepare.py configSignalControlRegion/htautau_lephad_sr_mc16a.cfg
prepare.py configSignalControlRegion/htautau_lephad_sr_mc16c.cfg

initialize.py configSignalControlRegion/htautau_lephad_sr_mc16a.cfg
initialize.py configSignalControlRegion/htautau_lephad_sr_mc16c.cfg

tqmerge -o sampleFolders/initialized/samples-initialized-htautau_lephad_sr.root -t initialize sampleFolders/initialized/samples-initialized-htautau_lephad_sr_mc16*.root

#tqmerge -o sampleFolders/initialized/samples-initialized-htautau_lephad_sr_treevar.root -t initialize sampleFolders/initialized/samples-initialized-htautau_lephad_sr_treevar_mc16*.root

