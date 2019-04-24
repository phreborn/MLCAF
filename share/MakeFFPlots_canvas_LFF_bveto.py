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

    #Lumi = "36.21"
    #Lumi = "43.58"
    #Lumi = "58.45"
    
    #channel = "ehad"
    channel = "muhad"

    #Tags = "Btag"
    Tags = "Bveto"

    #FFName = "ELEBTAG"
    #FFName = "ELEBVETO"
    #FFName = "MUONBTAG"
    FFName = "MUONBVETO"

    ATLAStitle = "Work in Progress"
    
    path = "/scratchfs/atlas/yehf/BSMtautauCAF/BSMtautauCAF/share/FakeFactors/"

    file_FF_dphi1 = TFile.Open(path+"LFR"+Year+Tags+channel+"LeptonPtDphi1"+FFName+"FF.root") 
    file_FF_dphi2 = TFile.Open(path+"LFR"+Year+Tags+channel+"LeptonPtDphi2"+FFName+"FF.root")
    file_FF_dphi3 = TFile.Open(path+"LFR"+Year+Tags+channel+"LeptonPtDphi3"+FFName+"FF.root")
    file_FF_dphi4 = TFile.Open(path+"LFR"+Year+Tags+channel+"LeptonPtDphi4"+FFName+"FF.root")

    #file_FF_dphi1 = TFile.Open(path+"LFR17"+Tags+channel+"LeptonPtDphi1"+FFName+"FF.root") 
    #file_FF_dphi2 = TFile.Open(path+"LFR17"+Tags+channel+"LeptonPtDphi2"+FFName+"FF.root")
    #file_FF_dphi3 = TFile.Open(path+"LFR17"+Tags+channel+"LeptonPtDphi3"+FFName+"FF.root")
    #file_FF_dphi4 = TFile.Open(path+"LFR17"+Tags+channel+"LeptonPtDphi4"+FFName+"FF.root")

    if not file_FF_dphi1 or not file_FF_dphi2 or not file_FF_dphi3 or not file_FF_dphi4:
        print "Error! Can not open the file!"
        return

    Canvas1 = file_FF_dphi1.Get("c1")
    Canvas1.SaveAs(path+"LFR"+Year+Tags+channel+"LeptonPtDphi1"+FFName+"FF.png")

    Canvas2 = file_FF_dphi2.Get("c1")
    Canvas2.SaveAs(path+"LFR"+Year+Tags+channel+"LeptonPtDphi2"+FFName+"FF.png")

    Canvas3 = file_FF_dphi3.Get("c1")
    Canvas3.SaveAs(path+"LFR"+Year+Tags+channel+"LeptonPtDphi3"+FFName+"FF.png")

    Canvas4 = file_FF_dphi4.Get("c1")
    Canvas4.SaveAs(path+"LFR"+Year+Tags+channel+"LeptonPtDphi4"+FFName+"FF.png")


 
    file_FF_dphi1.Close()
    file_FF_dphi2.Close()
    file_FF_dphi3.Close()    
    file_FF_dphi4.Close()    


    return

if __name__ == '__main__':
    MakeFFPlots()
