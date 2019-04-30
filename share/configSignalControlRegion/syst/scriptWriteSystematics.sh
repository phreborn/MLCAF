#!/bin/bash

for channel in "ehad" "muhad" "lephad"; do
    for campaign in "c16a" "c16d" "c16e"; do
        for systype in "fakevar" "isovar" "ttbarweight" "weightvar" "treevariation"; do
            python configSignalControlRegion/syst/temp_systematics_code.py --channel $channel --campaign $campaign --systype $systype
            python configSignalControlRegion/syst/temp_systematics_code.py --channel $channel --campaign $campaign --systype $systype --isbtag
        done
    done
done
