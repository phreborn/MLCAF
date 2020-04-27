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
import array
from ROOT import TH1D,TFile,TEfficiency,TCanvas,TLegend,TGaxis,TGraphAsymmErrors,TLatex,TLine
from ROOT import kBlack,kBlue,kRed,kAzure,kOrange,kTRUE

ROOT.gROOT.SetBatch(1)

def obtainHistFromFile(fn, hn):
  f = TFile.Open(fn, 'r')
  hist = f.Get(hn)
  hist.SetDirectory(0)
  f.Close()
  return hist

def ComparePlot(list_to_compare, fig_name):
  # obtain the list of histgram
  hist_list = []
  color_list = [kBlue,kRed,kBlack,kAzure]
  for fn in list_to_compare:
    hist = obtainHistFromFile(fn+".root", fn)
    hist_list.append(hist)

  hist_color = zip(hist_list, color_list)
  c = TCanvas("c","",800,600) 
  index = 0

  minimum = 1e9
  maximum = -1e9
  for hist, color in hist_color:
    hist.SetLineWidth(2)
    hist.SetLineColor(color)
    if 0 == index:
      hist.Draw('e')
    else:
      hist.Draw('e same')
    index = index+1
    if hist.GetMinimum() < minimum:
      minimum = hist.GetMinimum()
    if hist.GetMaximum() > maximum:
      maximum = hist.GetMaximum()
  hist_list[0].SetMinimum(minimum*0.8)
  hist_list[0].SetMaximum(maximum*1.2)

  leg = TLegend(0.7,0.8,0.9,0.9)
  leg.SetFillColor(0)
  for hist in hist_list:
    name = hist.GetName()
    leg.AddEntry(hist,name,'l')
  leg.Draw()

  c.Update()
  c.SaveAs(fig_name)


if __name__ == '__main__':
  list_to_compare = ['LFRAllehadBvetoLeptonPtFF','LFRAllehadBtagLeptonPtFF']
  ComparePlot(list_to_compare, "LFRAllehadLeptonPtFF_Compare.png")

