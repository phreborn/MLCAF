#########################################################################
# File Name: check_plots.py
# Description: 
# Author: xzh
# mail: huangxz@ihep.ac.cn
# Created Time: Sat May 25 13:46:48 2019
#########################################################################
#!/usr/bin/env python
import os
import commands
import ROOT

ROOT.gROOT.SetBatch(1)

def writeCanvas(fn):
  f = ROOT.TFile.Open(fn)
  c1 = f.Get("c1")
  c1.SaveAs(fn.replace('root', 'png'))
  f.Close()

if __name__ == '__main__':
  _, fn_list = commands.getstatusoutput('ls *.root')
  for fn in fn_list.split():
    writeCanvas(fn)
