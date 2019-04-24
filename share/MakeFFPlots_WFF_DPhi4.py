import argparse,os, sys, ROOT, math
from ROOT import TFile,TEfficiency,TCanvas,TLegend,TGaxis,TGraphAsymmErrors,TLatex
from ROOT import kSpring,kViolet,kBlue,kRed,kTRUE

#parser = argparse.ArgumentParser()
#parser.add_argument('--tauID',type=str)
#parser.add_argument('--taupT',type=str)
#result = parser.parse_args()

ROOT.gStyle.SetOptStat(0)
ROOT.gROOT.SetBatch(kTRUE)

def MakeFFPlots():

    #DPHI = "Dphi4"

    Year = "15"
    #Year = "17"

    Lumi = "36.21"
    #Lumi = "43.58"
    
    channel = "ehad"
    #channel = "muhad"

    #Tags = "Btag"
    Tags = "Bveto"

    #FFName = "ELEBTAG"
    #FFName = "ELEBVETO"
    #FFName = "MUONBTAG"
    #FFName = "MUONBVETO"

    Ntracks = "1p"
    #Ntracks = "3p"

    #ATLAStitle = "Work in Progress"
    
    path1 = "/scratchfs/atlas/yehf/QFramework/Htautau/share/FakeFactors/"

    file_stat = TFile.Open(path1+"WCR"+Year+Tags+channel+"TauPtFF"+Tags+Ntracks+"Dphi.root")

    #if not file_FF_dphi1 or not file_FF_dphi2 or not file_FF_dphi3 :
    #    print "Error! Can not open the file!"
    #    return
    if not file_stat :
        print "Error! Can not open the file!"
        return
    Canvas_stat = file_stat.Get("c1")
    Canvas_stat.SaveAs(path1+"WCR"+Year+Tags+channel+"TauPtFF"+Tags+Ntracks+"Dphi_stat.png")

 
    file_stat.Close()


    return

if __name__ == '__main__':
    MakeFFPlots()
