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
  hist_up = f.Get(hn+"_up")
  hist_down = f.Get(hn+"_down")
  for i in range(1,hist.GetNbinsX()+1):
    up = hist_up.GetBinContent(i)
    down = hist_down.GetBinContent(i)
    error = 0.5*(up-down)
    hist.SetBinError(i,error)
  f.Close()
  return hist

def ComparePlot(map_to_compare, fig_name):
  # obtain the list of histgram
  hist_list = []
  color_list = [kBlue,kRed,kBlack,kOrange]
  for fn, hist_title in map_to_compare.items():
    hist = obtainHistFromFile(fn+".root", fn)
    hist.SetTitle(hist_title)
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
    name = hist.GetTitle()
    leg.AddEntry(hist,name,'l')
    hist.SetTitle("")
  leg.Draw()

  c.Update()
  c.SaveAs(fig_name)


if __name__ == '__main__':
  map_to_compare = {
                    'TCRAllehadBtag1pTauPtSF': 'ehad 1p', 
                    'TCRAllmuhadBtag1pTauPtSF': 'muhad 1p',
                    }
  ComparePlot(map_to_compare, "TCRAllBtag1pTauPtSF_Compare.png")

  map_to_compare = {
                    'TCRAllehadBtag3pTauPtSF': 'ehad 3p', 
                    'TCRAllmuhadBtag3pTauPtSF': 'muhad 3p',
                    }
  ComparePlot(map_to_compare, "TCRAllBtag3pTauPtSF_Compare.png")

  map_to_compare = {
                    'TCRAlllephadBtag1pTauPtSF': 'lephad 1p', 
                    'TCRAlllephadBtag3pTauPtSF': 'lephad 3p',
                    }
  ComparePlot(map_to_compare, "TCRAllBtagTauPtSF_Compare.png")

  map_to_compare = {
                    'TCR1516lephadBtag3pTauPtSF': '1516 lephad 3p', 
                    'TCR17lephadBtag3pTauPtSF': '17 lephad 3p',
                    'TCR18lephadBtag3pTauPtSF': '18 lephad 3p',
                    }
  ComparePlot(map_to_compare, "TCRlephadBtag3pTauPtSF_Compare.png")

