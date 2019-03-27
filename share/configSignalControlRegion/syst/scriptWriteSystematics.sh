#!/bin/bash

python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --systype fakevar
python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --systype fakevar --isbtag
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --systype fakevar
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --systype fakevar --isbtag
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --systype fakevar
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --systype fakevar --isbtag

python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --systype isovar
python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --systype isovar --isbtag
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --systype isovar
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --systype isovar --isbtag
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --systype isovar
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --systype isovar --isbtag

python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --systype ttbarweight
python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --systype ttbarweight --isbtag
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --systype ttbarweight
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --systype ttbarweight --isbtag
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --systype ttbarweight
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --systype ttbarweight --isbtag

python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --systype weightvar
python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --systype weightvar --isbtag
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --systype weightvar
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --systype weightvar --isbtag
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --systype weightvar
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --systype weightvar --isbtag

python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --systype treevariation
python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --systype treevariation --isbtag
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --systype treevariation
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --systype treevariation --isbtag
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --systype treevariation
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --systype treevariation --isbtag
