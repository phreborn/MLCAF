#!/bin/bash

python configSignalControlRegion/syst/submit_systematics.py --systype fakevar --merge
python configSignalControlRegion/syst/submit_systematics.py --systype isovar --merge
python configSignalControlRegion/syst/submit_systematics.py --systype ttbarweight --merge
python configSignalControlRegion/syst/submit_systematics.py --systype weightvar --merge
python configSignalControlRegion/syst/submit_systematics.py --systype treevariation --merge
