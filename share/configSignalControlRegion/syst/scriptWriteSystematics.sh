#!/bin/bash

python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --isbtag False
python configSignalControlRegion/syst/temp_systematics_code.py --channel ehad --isbtag True
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --isbtag False
python configSignalControlRegion/syst/temp_systematics_code.py --channel muhad --isbtag True
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --isbtag False
python configSignalControlRegion/syst/temp_systematics_code.py --channel lephad --isbtag True
