#!/bin/bash

# dump histograms to ROOT files
#for systematic in $(ls -1 sampleFolders/analyzed/samples-analyzed-htautau_lephad_sr-*.root | grep -v "sys_band"); do
#    for campaign in "mc16a" "mc16c"; do
#        for channel in "ehad" "muhad"; do
#            python scripts/dumpHist.py $systematic $campaign $channel
#        done
#    done
#done

# hadd histograms to common files
#for campaign in "mc16a" "mc16c"; do
##    for cut in "sr1pBtag" "sr1pBveto" "sr3pBtag" "sr3pBveto" "tcr1pBtag" "tcr3pBtag"; do
##    for cut in "wcr1pBtag" "wcr1pBveto" "wcr3pBtag" "wcr3pBveto"; do
##    for cut in "wcr1pBveto" "wcr3pBveto"; do
#    for cut in "vr1pBveto" "vr3pBveto"; do
#        hadd -n 11 -f dumpHist/${campaign}_${cut}.root dumpHist/*/${campaign}/*/*_*_${cut}_*_*.root
#    done
#done
for campaign in "mc16a"; do
#    for cut in "sr1pBtag" "sr1pBveto" "sr3pBtag" "sr3pBveto" "tcr1pBtag" "tcr3pBtag"; do
#    for cut in "wcr1pBtag" "wcr1pBveto" "wcr3pBtag" "wcr3pBveto"; do
#    for cut in "wcr1pBveto" "wcr3pBveto"; do
    for cut in "vr1pBveto" "vr3pBveto" "wcr1pBveto" "wcr3pBveto"; do
        hadd -n 11 -f dumpHist/${campaign}_${cut}.root dumpHist/*/${campaign}/*/*_*_${cut}_*_*.root
    done
done
