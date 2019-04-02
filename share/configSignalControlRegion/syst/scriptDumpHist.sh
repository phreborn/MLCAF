#!/bin/bash

# dump histograms to ROOT files
for systematic in $(ls -1 sampleFolders/analyzed/samples-analyzed-htautau_lephad_sr-*.root | grep -v "sys_band"); do
    for campaign in mc16a; do
        for channel in ehad muhad; do
            python scripts/dumpHist.py $systematic $campaign $channel
        done
    done
done

# hadd histograms to common files
for campaign in mc16a; do
    for cut in wcr1pBtag wcr1pBveto wcr3pBtag wcr3pBveto vr1pBtag vr1pBveto vr3pBtag vr3pBveto tcr1pBtag tcr3pBtag; do
        hadd -n 11 -f dumpHist/${campaign}_${cut}.root dumpHist/*/${campaign}/*/${campaign}_*_${cut}_*.root
    done
done
