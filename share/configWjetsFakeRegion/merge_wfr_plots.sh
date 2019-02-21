#!/usr/bin/env bash

#must be in plots folder
pdfjoin --outfile ../muhad_bveto1p_merge.pdf  muhad-CutBveto1p*
pdfjoin --outfile ../muhad_bveto3p_merge.pdf  muhad-CutBveto3p*
pdfjoin --outfile ../muhad_btag1p_merge.pdf  muhad-CutBtag1p*
pdfjoin --outfile ../muhad_btag3p_merge.pdf  muhad-CutBtag3p*


pdfjoin --outfile ../ehad_bveto1p_merge.pdf  ehad-CutBveto1p*
pdfjoin --outfile ../ehad_bveto3p_merge.pdf  ehad-CutBveto3p*
pdfjoin --outfile ../ehad_btag1p_merge.pdf  ehad-CutBtag1p*
pdfjoin --outfile ../ehad_btag3p_merge.pdf  ehad-CutBtag3p*

pdftk ehad-CutBtag* cat output ../ehad_btag_merge.pdf
pdftk ehad-CutBveto* cat output ../ehad_bveto_merge.pdf
pdftk muhad-CutBtag* cat output ../muhad_btag_merge.pdf
pdftk muhad-CutBveto* cat output ../muhad_bveto_merge.pdf

pdftk ehad-CutBtag* cat output ../ehad_btag_merge.pdf
pdftk ehad-CutBveto* cat output ../ehad_bveto_merge.pdf
pdftk muhad-CutBtag* cat output ../muhad_btag_merge.pdf
pdftk muhad-CutBveto* cat output ../muhad_bveto_merge.pdf

pdftk muhad-CutNO* cat output ../muhad_NO_merge.pdf

pdftk ehad-CutNO* cat output ../ehad_NO_merge.pdf

pdfjoin --outfile ../muhad_bveto1p_merge.pdf  muhad-CutVRBveto1p*
pdfjoin --outfile ../muhad_bveto3p_merge.pdf  muhad-CutVRBveto3p*
pdfjoin --outfile ../muhad_btag1p_merge.pdf  muhad-CutVRBtag1p*
pdfjoin --outfile ../muhad_btag3p_merge.pdf  muhad-CutVRBtag3p*


pdfjoin --outfile ../ehad_bveto1p_merge.pdf  ehad-CutVRBveto1p*
pdfjoin --outfile ../ehad_bveto3p_merge.pdf  ehad-CutVRBveto3p*
pdfjoin --outfile ../ehad_btag1p_merge.pdf  ehad-CutVRBtag1p*
pdfjoin --outfile ../ehad_btag3p_merge.pdf  ehad-CutVRBtag3p*


#
#
#pdftk lephad-CutBveto1p* cat output ../lephad_bveto1p_merge.pdf
#pdftk lephad-CutBveto3p* cat output ../lephad_bveto3p_merge.pdf
#pdftk lephad-CutBtag1p* cat output ../lephad_btag1p_merge.pdf
#pdftk lephad-CutBtag3p* cat output ../lephad_btag3p_merge.pdf
#
#pdftk muhad-CutBveto* cat output ../muhad_bveto_merge.pdf
#pdftk muhad-CutBtag* cat output ../muhad_btag_merge.pdf
#pdftk ehad-CutBveto* cat output ../ehad_bveto_merge.pdf
#pdftk ehad-CutBtag* cat output ../ehad_btag_merge.pdf
#
'''
import os

l_samples=[
['/bkg/?/Diboson','Diboson'],
['/bkg/?/Zee','Zee'],
['/bkg/?/Zmumu','Zmumu'],
['/bkg/?/Ztautau','Ztautau'],
['/bkg/?/Top','Top'],
['/sig/?','sig'],
['/data/?','data']
]

for sample in l_samples:
	command='bsub python runAnalysis.py ConfigSignalRegion/htautau_lephad_sr.cfg --restrict {:s} --options outputFile:output/htautau_lephad_sr/nominal_{:s}.root'.format(sample[0],sample[1])
	os.system(command)
'''

#!/bin/env python

import re
import os

path = os.getenv("TQPATH")+"/Root/"

gettag = re.compile('getTag(String|Integer|Double|Bool)[^(]*\("([^"]*)"')
getfunc = re.compile("[ ]*[void|int|TString|std::string|bool]+[ *]+([A-Za-z0-9_]+)::([A-Za-z0-9_]+)[ <>A-Za-z0-9]*\(.*")


for fname in os.listdir(path):
    if not fname.endswith(".cxx"): continue
    with open(path+fname) as f:
        for line in f.readlines():
            if "::" in line:
                func = getfunc.match(line)
                if func:
                    classname = func.group(1)
                    funcname = func.group(2)
            if "getTag" in line:
                match = gettag.search(line)
                if match:
                    tagtype = match.group(1).lower()
                    key = match.group(2)
                    print(fname + ": " + classname + "::" + funcname + ": " + key + " (" + tagtype + ")")


