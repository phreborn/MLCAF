# this script combines mc16a and mc16c
# input ntuple files into the final
# input/htautau_lephad_wcr.root sample folder.

python makeSampleFile.py ConfigWjetsControlRegion/htautau_lephad_wcr_mc16a.cfg
python makeSampleFile.py ConfigWjetsControlRegion/htautau_lephad_wcr_mc16c.cfg
tqmerge -o input/htautau_lephad_wcr.root -t makeSampleFile input/htautau_lephad_wcr_mc16*.root
