#!/bin/bash

python configSignalControlRegion/syst/submit_systematics.py --systype fakevar --submit
python configSignalControlRegion/syst/submit_systematics.py --systype isovar --submit
python configSignalControlRegion/syst/submit_systematics.py --systype ttbarweight --submit
python configSignalControlRegion/syst/submit_systematics.py --systype weightvar --submit
python configSignalControlRegion/syst/submit_systematics.py --systype treevariation --submit
