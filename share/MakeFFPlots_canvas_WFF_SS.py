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

    #Year = "15"
    Year = "17"
    #Year = "18"

    
    #channel = "ehad"
    channel = "muhad"

    Tags = "Btag"

    

    ATLAStitle = "Work in Progress"
    
    path = "/scratchfs/atlas/yehf/BSMtautauCAF/BSMtautauCAF/share/FakeFactors/"

    file_FF_dphi1 = TFile.Open(path+"SSWFR"+Year+Tags+channel+"TauPtFF"+Tags+"1p.root") 
    file_FF_dphi2 = TFile.Open(path+"SSWFR"+Year+Tags+channel+"TauPtFF"+Tags+"3p.root")


    if not file_FF_dphi1 or not file_FF_dphi2:
        print "Error! Can not open the file!"
        return

    Canvas1 = file_FF_dphi1.Get("c1")
    Canvas1.SaveAs(path+"SSWFR"+Year+Tags+channel+"TauPtFF"+Tags+"1p.png")

    Canvas2 = file_FF_dphi2.Get("c1")
    Canvas2.SaveAs(path+"SSWFR"+Year+Tags+channel+"TauPtFF"+Tags+"3p.png")



 
    file_FF_dphi1.Close()
    file_FF_dphi2.Close()


    return

if __name__ == '__main__':
    MakeFFPlots()
