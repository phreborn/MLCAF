#!/bin/bash

for campaign in "[c16a+c16d+c16e]" "c16a" "c16d" "c16e"; do
    for channel in "ehad" "muhad"; do
        python configSignalControlRegion/syst/temp_systematics_code.py --channel $channel --campaign $campaign --systype partial
    done
done
