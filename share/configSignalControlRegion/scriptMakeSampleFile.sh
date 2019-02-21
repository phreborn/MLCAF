# this script combines mc16a and mc16c
# input ntuple files into the final
# input/htautau_lephad_sr.root sample folder.

python makeSampleFile.py ConfigSignalRegion/htautau_lephad_sr_mc16a.cfg
python makeSampleFile.py ConfigSignalRegion/htautau_lephad_sr_mc16c.cfg
tqmerge -o input/htautau_lephad_sr.root -t makeSampleFile input/htautau_lephad_sr_mc16*.root
