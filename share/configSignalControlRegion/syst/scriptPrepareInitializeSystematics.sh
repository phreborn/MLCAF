#!/bin/bash
NCORES=10

python configSignalControlRegion/syst/submit_systematics.py --systype treevar --stage initialize --ncores ${NCORES}
