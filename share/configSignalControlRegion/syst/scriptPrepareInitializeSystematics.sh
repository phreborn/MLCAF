#!/bin/bash

python configSignalControlRegion/syst/submit_systematics.py --systype weightvar --submit True --makeSamples True
python configSignalControlRegion/syst/submit_systematics.py --systype treevariation --submit True --makeSamples True
