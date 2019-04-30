#!/bin/bash

python configExtrapoSignalControlRegion/syst/submit_systematics.py --systype fakevar --merge
python configExtrapoSignalControlRegion/syst/submit_systematics.py --systype isovar --merge
python configExtrapoSignalControlRegion/syst/submit_systematics.py --systype ttbarweight --merge
python configExtrapoSignalControlRegion/syst/submit_systematics.py --systype weightvar --merge
python configExtrapoSignalControlRegion/syst/submit_systematics.py --systype treevariation --merge
python configExtrapoSignalControlRegion/syst/submit_systematics.py --systype extraposf --merge
