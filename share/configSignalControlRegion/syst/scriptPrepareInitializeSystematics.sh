#!/bin/bash
NCORES=1
python configSignalControlRegion/syst/submit_systematics.py --systype treevariation --stage prepare --ncores ${NCORES}
python configSignalControlRegion/syst/submit_systematics.py --systype treevariation --stage initialize --ncores ${NCORES}
