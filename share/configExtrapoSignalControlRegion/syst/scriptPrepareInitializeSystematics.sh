#!/bin/bash

python configExtrapoSignalControlRegion/syst/submit_systematics.py --systype weightvar --submit --makeSamples
python configExtrapoSignalControlRegion/syst/submit_systematics.py --systype treevariation --submit --makeSamples
