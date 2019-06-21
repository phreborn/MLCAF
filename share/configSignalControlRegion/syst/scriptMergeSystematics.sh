#!/bin/bash

NCORES=1

python configSignalControlRegion/syst/submit_systematics.py --systype fakevar --stage merge --ncores ${NCORES}
python configSignalControlRegion/syst/submit_systematics.py --systype isovar --stage merge --ncores ${NCORES}

#python configSignalControlRegion/syst/submit_systematics.py --systype extraposf --stage merge --ncores ${NCORES}

#python configSignalControlRegion/syst/submit_systematics.py --systype topvar --stage merge --ncores ${NCORES}

#python configSignalControlRegion/syst/submit_systematics.py --systype weightvar --stage merge --ncores ${NCORES}
#python configSignalControlRegion/syst/submit_systematics.py --systype treevar --stage merge --ncores ${NCORES}
