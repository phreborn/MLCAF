# this script combines mc16a and mc16c
# input ntuple files into the final
# input/htautau_lephad_flr.root sample folder.

prepare.py ConfigFakeLeptonRegion/htautau_lephad_flr_mc16a.cfg
prepare.py ConfigFakeLeptonRegion/htautau_lephad_flr_mc16c.cfg
tqmerge -o input/htautau_lephad_flr.root -t makeSampleFile input/htautau_lephad_flr_mc16*.root
