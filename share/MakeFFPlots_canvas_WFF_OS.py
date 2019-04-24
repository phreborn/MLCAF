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

    Tags = "Bveto"

    #Ntracks = "1p"
    Ntracks = "3p"

    ATLAStitle = "Work in Progress"
    
    path = "/scratchfs/atlas/yehf/BSMtautauCAF/BSMtautauCAF/share/FakeFactors/"

    file_FF_dphi1 = TFile.Open(path+"WFR"+Year+Tags+channel+"TauPtFF"+Tags+Ntracks+"Dphi1.root") 
    file_FF_dphi2 = TFile.Open(path+"WFR"+Year+Tags+channel+"TauPtFF"+Tags+Ntracks+"Dphi2.root")
    file_FF_dphi3 = TFile.Open(path+"WFR"+Year+Tags+channel+"TauPtFF"+Tags+Ntracks+"Dphi3.root")

    #file_FF_dphi1 = TFile.Open(path+"WFR17"+Tags+channel+"TauPtDphi1"+FFName+"FF.root") 
    #file_FF_dphi2 = TFile.Open(path+"WFR17"+Tags+channel+"TauPtDphi2"+FFName+"FF.root")
    #file_FF_dphi3 = TFile.Open(path+"WFR17"+Tags+channel+"TauPtDphi3"+FFName+"FF.root")

    if not file_FF_dphi1 or not file_FF_dphi2 or not file_FF_dphi3:
        print "Error! Can not open the file!"
        return

    Canvas1 = file_FF_dphi1.Get("c1")
    Canvas1.SaveAs(path+"WFR"+Year+Tags+channel+"TauPtFF"+Tags+Ntracks+"Dphi1.png")

    Canvas2 = file_FF_dphi2.Get("c1")
    Canvas2.SaveAs(path+"WFR"+Year+Tags+channel+"TauPtFF"+Tags+Ntracks+"Dphi2.png")

    Canvas3 = file_FF_dphi3.Get("c1")
    Canvas3.SaveAs(path+"WFR"+Year+Tags+channel+"TauPtFF"+Tags+Ntracks+"Dphi3.png")



 
    file_FF_dphi1.Close()
    file_FF_dphi2.Close()
    file_FF_dphi3.Close()    


    return

if __name__ == '__main__':
    MakeFFPlots()
