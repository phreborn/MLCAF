#!/bin/bash

python configSignalControlRegion/syst/submit_systematics.py --systype fakevar --submit True
python configSignalControlRegion/syst/submit_systematics.py --systype isovar --submit True
python configSignalControlRegion/syst/submit_systematics.py --systype ttbarweight --submit True
python configSignalControlRegion/syst/submit_systematics.py --systype weightvar --submit True
python configSignalControlRegion/syst/submit_systematics.py --systype treevariation --submit True
