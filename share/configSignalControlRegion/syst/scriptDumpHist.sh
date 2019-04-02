#!/bin/bash

for systematic in $(ls -1 sampleFolders/analyzed/samples-analyzed-htautau_lephad_sr-*.root | grep -v "sys_band"); do
    for campaign in mc16a; do
        for channel in ehad muhad lephad; do
            python scripts/dumpHist.py $systematic $campaign $channel
        done
    done
done
