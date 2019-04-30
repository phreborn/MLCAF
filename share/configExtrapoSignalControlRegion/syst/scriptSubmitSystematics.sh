#!/bin/bash

python configExtrapoSignalControlRegion/syst/submit_systematics.py --systype fakevar --submit
python configExtrapoSignalControlRegion/syst/submit_systematics.py --systype isovar --submit
python configExtrapoSignalControlRegion/syst/submit_systematics.py --systype ttbarweight --submit
python configExtrapoSignalControlRegion/syst/submit_systematics.py --systype weightvar --submit
python configExtrapoSignalControlRegion/syst/submit_systematics.py --systype treevariation --submit
python configExtrapoSignalControlRegion/syst/submit_systematics.py --systype extraposf --submit
