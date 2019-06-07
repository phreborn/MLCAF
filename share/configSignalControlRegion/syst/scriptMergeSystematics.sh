#!/bin/bash
NCORES=1
python configSignalControlRegion/syst/submit_systematics.py --systype fakevar --stage merge --ncores ${NCORES}
python configSignalControlRegion/syst/submit_systematics.py --systype isovar --stage merge --ncores ${NCORES}
python configSignalControlRegion/syst/submit_systematics.py --systype extraposf --stage merge --ncores ${NCORES}
python configSignalControlRegion/syst/submit_systematics.py --systype treevariation --stage merge --ncores ${NCORES}
python configSignalControlRegion/syst/submit_systematics.py --systype ttbarweight --stage merge --ncores ${NCORES}
python configSignalControlRegion/syst/submit_systematics.py --systype weightvar --stage merge --ncores ${NCORES}
