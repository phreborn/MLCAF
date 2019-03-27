#!/bin/bash

python configSignalControlRegion/syst/submit_systematics.py --systype fakevar --merge True
python configSignalControlRegion/syst/submit_systematics.py --systype isovar --merge True
python configSignalControlRegion/syst/submit_systematics.py --systype ttbarweight --merge True
python configSignalControlRegion/syst/submit_systematics.py --systype weightvar --merge True
python configSignalControlRegion/syst/submit_systematics.py --systype treevariation --merge True
