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
  marker_list = [20, 22, 23, 33]

  for fn in list_to_compare:
    hist = obtainHistFromFile(fn+".root", fn)
    hist_list.append(hist)

  hist_color = zip(hist_list, color_list, marker_list)
  c = TCanvas("c","",800,600) 
  index = 0

  minimum = 1e9
  maximum = -1e9
  for hist, color, marker in hist_color:
    hist.SetLineWidth(2)
    hist.SetLineColor(color)
    hist.SetMarkerStyle(marker)
    hist.SetMarkerColor(color)
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

  leg = TLegend(0.6,0.8,0.9,0.9)
  leg.SetFillColor(0)
  leg.SetBorderSize(0)
  for hist in hist_list:
    name = hist.GetTitle()
    leg.AddEntry(hist,name,'lp')
  leg.Draw()

  c.Update()
  c.SaveAs(fig_name)


if __name__ == '__main__':

  ROOT.gROOT.LoadMacro("/afs/ihep.ac.cn/users/x/xiaozhong/dybfs/ATLAS/Analysis/Htautau/Development/BSMtautauCAF/share/scripts/AtlasStyle/AtlasStyle.C")
  ROOT.gROOT.LoadMacro("/afs/ihep.ac.cn/users/x/xiaozhong/dybfs/ATLAS/Analysis/Htautau/Development/BSMtautauCAF/share/scripts/AtlasStyle/AtlasUtils.C")
  ROOT.gROOT.SetBatch(kTRUE)
  ROOT.SetAtlasStyle()
  
  '''
  list_to_compare = ["MultiJetsLFRAllehadSSBtagLeptonPtCentralFF",
                     "MultiJetsLFRNoTopCorrectionAllehadSSBtagLeptonPtCentralFF"]
  ComparePlot(list_to_compare, "ehad_Btag_Central.png")
  list_to_compare = ["MultiJetsLFRAllehadSSBtagLeptonPtForwardFF",
                     "MultiJetsLFRNoTopCorrectionAllehadSSBtagLeptonPtForwardFF"]
  ComparePlot(list_to_compare, "ehad_Btag_Forward.png")
  list_to_compare = ["MultiJetsLFRAllmuhadSSBtagLeptonPtCentralFF",
                     "MultiJetsLFRNoTopCorrectionAllmuhadSSBtagLeptonPtCentralFF"]
  ComparePlot(list_to_compare, "muhad_Btag_Central.png")
  list_to_compare = ["MultiJetsLFRAllmuhadSSBtagLeptonPtForwardFF",
                     "MultiJetsLFRNoTopCorrectionAllmuhadSSBtagLeptonPtForwardFF"]
  ComparePlot(list_to_compare, "muhad_Btag_Forward.png")
  '''
  '''
  list_to_compare = ["MultiJetsLFRAllehadOSBtagLeptonPtCentralFF",
                     "MultiJetsLFRAllehadSSBtagLeptonPtCentralFF"]
  ComparePlot(list_to_compare, "ehad_Btag_Central.png")
  
  list_to_compare = ["MultiJetsLFRAllehadOSBtagLeptonPtForwardFF",
                     "MultiJetsLFRAllehadSSBtagLeptonPtForwardFF"]
  ComparePlot(list_to_compare, "ehad_Btag_Forward.png")
  
  list_to_compare = ["MultiJetsLFRAllehadOSBvetoLeptonPtCentralFF",
                     "MultiJetsLFRAllehadSSBvetoLeptonPtCentralFF"]
  ComparePlot(list_to_compare, "ehad_Bveto_Central.png")
  
  list_to_compare = ["MultiJetsLFRAllehadOSBvetoLeptonPtForwardFF",
                     "MultiJetsLFRAllehadSSBvetoLeptonPtForwardFF"]
  ComparePlot(list_to_compare, "ehad_Bveto_Forward.png")
  
  list_to_compare = ["MultiJetsLFRAllmuhadOSBtagLeptonPtCentralFF",
                     "MultiJetsLFRAllmuhadSSBtagLeptonPtCentralFF"]
  ComparePlot(list_to_compare, "muhad_Btag_Central.png")
  
  list_to_compare = ["MultiJetsLFRAllmuhadOSBtagLeptonPtForwardFF",
                     "MultiJetsLFRAllmuhadSSBtagLeptonPtForwardFF"]
  ComparePlot(list_to_compare, "muhad_Btag_Forward.png")
  
  list_to_compare = ["MultiJetsLFRAllmuhadOSBvetoLeptonPtCentralFF",
                     "MultiJetsLFRAllmuhadSSBvetoLeptonPtCentralFF"]
  ComparePlot(list_to_compare, "muhad_Bveto_Central.png")
  
  list_to_compare = ["MultiJetsLFRAllmuhadOSBvetoLeptonPtForwardFF",
                     "MultiJetsLFRAllmuhadSSBvetoLeptonPtForwardFF"]
  ComparePlot(list_to_compare, "muhad_Bveto_Forward.png")
  '''
  '''
  list_to_compare = ["OtherJetsTFRAllmuhadSSLowMTHighDphiTauPtFF",
                     "OtherJetsTFRAllmuhadSSMediumMTHighDphiTauPtFF",
                     "OtherJetsTFRAllmuhadSSHighMTHighDphiTauPtFF",
                     ]
  ComparePlot(list_to_compare, "muhad_Bveto_SS_HighDphi.png")

  list_to_compare = ["OtherJetsTFRAllmuhadSSLowMTLowDphiTauPtFF",
                     "OtherJetsTFRAllmuhadSSMediumMTLowDphiTauPtFF",
                     "OtherJetsTFRAllmuhadSSHighMTLowDphiTauPtFF",
                     ]
  ComparePlot(list_to_compare, "muhad_Bveto_SS_LowDphi.png")
  
  list_to_compare = ["OtherJetsTFRAllmuhadOSMediumMTLowDphiTauPtFF",
                     "OtherJetsTFRAllmuhadOSMediumMTHighDphiTauPtFF",
                     ]
  ComparePlot(list_to_compare, "muhad_Bveto_OS_MediumMT.png")
  '''

  list_to_compare = ["OtherJetsTFRAllehadOSBtagMediumMT1pTauPtFF",
                     "OtherJetsTFRAllmuhadOSBtagMediumMT1pTauPtFF"
                     ]
  ComparePlot(list_to_compare, "OS_Btag_1p.png")
  
  list_to_compare = ["OtherJetsTFRAllehadOSBtagMediumMT3pTauPtFF",
                     "OtherJetsTFRAllmuhadOSBtagMediumMT3pTauPtFF"
                     ]
  ComparePlot(list_to_compare, "OS_Btag_3p.png")
  
  list_to_compare = ["OtherJetsTFRAllehadOSBvetoMediumMT1pTauPtFF",
                     "OtherJetsTFRAllmuhadOSBvetoMediumMT1pTauPtFF"
                     ]
  ComparePlot(list_to_compare, "OS_Bveto_1p.png")
  
  list_to_compare = ["OtherJetsTFRAllehadOSBvetoMediumMT3pTauPtFF",
                     "OtherJetsTFRAllmuhadOSBvetoMediumMT3pTauPtFF"
                     ]
  ComparePlot(list_to_compare, "OS_Bveto_3p.png")
  
  list_to_compare = ["OtherJetsTFRAllehadSSBtagMediumMT1pTauPtFF",
                     "OtherJetsTFRAllmuhadSSBtagMediumMT1pTauPtFF"
                     ]
  ComparePlot(list_to_compare, "SS_Btag_1p.png")
  
  list_to_compare = ["OtherJetsTFRAllehadSSBtagMediumMT3pTauPtFF",
                     "OtherJetsTFRAllmuhadSSBtagMediumMT3pTauPtFF"
                     ]
  ComparePlot(list_to_compare, "SS_Btag_3p.png")
  
  list_to_compare = ["OtherJetsTFRAllehadSSBvetoMediumMT1pTauPtFF",
                     "OtherJetsTFRAllmuhadSSBvetoMediumMT1pTauPtFF"
                     ]
  ComparePlot(list_to_compare, "SS_Bveto_1p.png")
  
  list_to_compare = ["OtherJetsTFRAllehadSSBvetoMediumMT3pTauPtFF",
                     "OtherJetsTFRAllmuhadSSBvetoMediumMT3pTauPtFF"
                     ]
  ComparePlot(list_to_compare, "SS_Bveto_3p.png")
  
  '''
  list_to_compare = ["OtherJetsTFRMCAllehadOSBtagMediumMT1pTauPtFF",
                     "OtherJetsTFRMCAllmuhadOSBtagMediumMT1pTauPtFF"
                     ]
  ComparePlot(list_to_compare, "OS_Btag_1p.png")
  
  list_to_compare = ["OtherJetsTFRMCAllehadOSBtagMediumMT3pTauPtFF",
                     "OtherJetsTFRMCAllmuhadOSBtagMediumMT3pTauPtFF"
                     ]
  ComparePlot(list_to_compare, "OS_Btag_3p.png")
  
  list_to_compare = ["OtherJetsTFRMCAllehadOSBvetoMediumMT1pTauPtFF",
                     "OtherJetsTFRMCAllmuhadOSBvetoMediumMT1pTauPtFF"
                     ]
  ComparePlot(list_to_compare, "OS_Bveto_1p.png")
  
  list_to_compare = ["OtherJetsTFRMCAllehadOSBvetoMediumMT3pTauPtFF",
                     "OtherJetsTFRMCAllmuhadOSBvetoMediumMT3pTauPtFF"
                     ]
  ComparePlot(list_to_compare, "OS_Bveto_3p.png")
  
  list_to_compare = ["OtherJetsTFRMCAllehadSSBtagMediumMT1pTauPtFF",
                     "OtherJetsTFRMCAllmuhadSSBtagMediumMT1pTauPtFF"
                     ]
  ComparePlot(list_to_compare, "SS_Btag_1p.png")
  
  list_to_compare = ["OtherJetsTFRMCAllehadSSBtagMediumMT3pTauPtFF",
                     "OtherJetsTFRMCAllmuhadSSBtagMediumMT3pTauPtFF"
                     ]
  ComparePlot(list_to_compare, "SS_Btag_3p.png")
  
  list_to_compare = ["OtherJetsTFRMCAllehadSSBvetoMediumMT1pTauPtFF",
                     "OtherJetsTFRMCAllmuhadSSBvetoMediumMT1pTauPtFF"
                     ]
  ComparePlot(list_to_compare, "SS_Bveto_1p.png")
  
  list_to_compare = ["OtherJetsTFRMCAllehadSSBvetoMediumMT3pTauPtFF",
                     "OtherJetsTFRMCAllmuhadSSBvetoMediumMT3pTauPtFF"
                     ]
  ComparePlot(list_to_compare, "SS_Bveto_3p.png")
  '''
