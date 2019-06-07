e!/bin/bash
NCORES=1
python configSignalControlRegion/syst/submit_systematics.py --systype isovar --stage analyze --ncores ${NCORES}
python configSignalControlRegion/syst/submit_systematics.py --systype fakevar --stage analyze --ncores ${NCORES}
python configSignalControlRegion/syst/submit_systematics.py --systype extraposf --stage analyze --ncores ${NCORES}
python configSignalControlRegion/syst/submit_systematics.py --systype treevariation --stage analyze --ncores ${NCORES}
python configSignalControlRegion/syst/submit_systematics.py --systype weightvar --stage analyze --ncores ${NCORES}
python configSignalControlRegion/syst/submit_systematics.py --systype ttbarweight --stage analyze --ncores ${NCORES}
