#!/bin/bash

python configSignalControlRegion/syst/submit_systematics.py --systype weightvar --submit --makeSamples
python configSignalControlRegion/syst/submit_systematics.py --systype treevariation --submit --makeSamples
