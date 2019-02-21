#!/usr/bin/env python

import os
import sys

#some configurations
b_queue='medium'

doQCDFakes=True
systfilenameQCDFakes = 'systematics/fake_factor_qcd_systematics.txt'

doSF=False

#___________________________________________________________________________________
def readSysFile(filename):
  #open fake factor systematics file:
  if not os.path.isfile(filename):
    print 'Unable to open systematics file:', filename,
    return []
  else:
    systematicsfile = open(filename,'r')

  #read systematics file and make syst list [['option','systname'],['option','systname']...]:
  l_systematics = []
  for line in systematicsfile.readlines():
    splitline = line.split()
    if len(splitline)<2 or '#' in line:
      continue
    l_systematics.append(splitline)
  #for debugging
  print l_systematics

  systematicsfile.close()
  return l_systematics
#___________________________________________________________________________________

if __name__=='__main__':
  if doQCDFakes:
    l_systematics = readSysFile(systfilenameQCDFakes)
    #submit jobs with systematics:
    for syst in l_systematics:
        for sys in syst:
          if 'var' in sys:
            option = sys
            continue
          command='bsub -q {:s} python runAnalysis.py configLeptonFakeRegion/htautau_lephad_lfr_applyff.cfg --options {:s}:{:s} outputFile:output/htautau_lephad_lfr/{:s}_applyff.root'.format(b_queue,option,sys,sys)
          print command
          os.system(command)
