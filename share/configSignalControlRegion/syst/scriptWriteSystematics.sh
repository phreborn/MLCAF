#!/bin/bash

python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --isbtag False --systype fakevar
python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --isbtag True --systype fakevar
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --isbtag False --systype fakevar
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --isbtag True --systype fakevar
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --isbtag False --systype fakevar
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --isbtag True --systype fakevar

python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --isbtag False --systype isovar
python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --isbtag True --systype isovar
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --isbtag False --systype isovar
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --isbtag True --systype isovar
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --isbtag False --systype isovar
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --isbtag True --systype isovar

python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --isbtag False --systype ttbarweight
python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --isbtag True --systype ttbarweight
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --isbtag False --systype ttbarweight
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --isbtag True --systype ttbarweight
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --isbtag False --systype ttbarweight
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --isbtag True --systype ttbarweight

python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --isbtag False --systype weightvar
python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --isbtag True --systype weightvar
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --isbtag False --systype weightvar
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --isbtag True --systype weightvar
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --isbtag False --systype weightvar
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --isbtag True --systype weightvar

python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --isbtag False --systype treevariation
python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --isbtag True --systype treevariation
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --isbtag False --systype treevariation
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --isbtag True --systype treevariation
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --isbtag False --systype treevariation
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --isbtag True --systype treevariation
