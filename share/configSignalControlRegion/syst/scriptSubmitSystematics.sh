#!/bin/bash
NCORES=10

python configSignalControlRegion/syst/submit_systematics.py --systype fakevar --stage analyze --ncores ${NCORES}
python configSignalControlRegion/syst/submit_systematics.py --systype isovar --stage analyze --ncores ${NCORES}
python configSignalControlRegion/syst/submit_systematics.py --systype topvar --stage analyze --ncores ${NCORES}
python configSignalControlRegion/syst/submit_systematics.py --systype treevar --stage analyze --ncores ${NCORES}
python configSignalControlRegion/syst/submit_systematics.py --systype weightvar --stage analyze --ncores ${NCORES}
