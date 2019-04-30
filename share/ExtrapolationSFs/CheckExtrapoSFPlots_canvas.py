import argparse,os, sys, ROOT, math
from ROOT import TFile,TEfficiency,TCanvas,TLegend,TGaxis,TGraphAsymmErrors,TLatex
from ROOT import kSpring,kViolet,kBlue,kRed,kTRUE

#parser = argparse.ArgumentParser()
#parser.add_argument('--tauID',type=str)
#parser.add_argument('--taupT',type=str)
#result = parser.parse_args()

ROOT.gStyle.SetOptStat(0)
ROOT.gROOT.SetBatch(kTRUE)

def CheckExtrapoSFPlots():

    Year = "15"
    #Year = "17"
    #Year = "18"
    
    channel = "ehad"
    #channel = "muhad"

    ATLAStitle = "Work in Progress"
    
    path = "/scratchfs/atlas/yehf/BSMtautauCAF/BSMtautauCAF/share/ExtrapolationSFs/"

    file_FF_dphi1 = TFile.Open(path+"VR"+Year+"Bveto1p"+channel+"bvetoTauPt.root") 
    file_FF_dphi2 = TFile.Open(path+"VR"+Year+"Bveto3p"+channel+"bvetoTauPt.root")
    file_FF_dphi3 = TFile.Open(path+"VR"+Year+"Btag1p"+channel+"btagTauPt.root")
    file_FF_dphi4 = TFile.Open(path+"VR"+Year+"Btag3p"+channel+"btagTauPt.root")


    if not file_FF_dphi1 or not file_FF_dphi2 or not file_FF_dphi3 or not file_FF_dphi4:
        print "Error! Can not open the file!"
        return

    Canvas1 = file_FF_dphi1.Get("c1")
    Canvas1.SaveAs(path+"VR"+Year+"Bveto1p"+channel+"bvetoTauPt.png")

    Canvas2 = file_FF_dphi2.Get("c1")
    Canvas2.SaveAs(path+"VR"+Year+"Bveto3p"+channel+"bvetoTauPt.png")

    Canvas3 = file_FF_dphi3.Get("c1")
    Canvas3.SaveAs(path+"VR"+Year+"Btag1p"+channel+"btagTauPt.png")

    Canvas4 = file_FF_dphi4.Get("c1")
    Canvas4.SaveAs(path+"VR"+Year+"Btag3p"+channel+"btagTauPt.png")


 
    file_FF_dphi1.Close()
    file_FF_dphi2.Close()
    file_FF_dphi3.Close()    
    file_FF_dphi4.Close()    


    return

if __name__ == '__main__':
    CheckExtrapoSFPlots()
