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

    Year = "15"
    #Year = "17"
    #Year = "18"

    #Lumi = "36.21"
    #Lumi = "43.58"
    Lumi = "58.45"
    
    channel = "ehad"
    #channel = "muhad"

    Tags = "Btag"
    #Tags = "Bveto"

    FFName = "ELEBTAG"
    #FFName = "ELEBVETO"
    #FFName = "MUONBTAG"
    #FFName = "MUONBVETO"

    ATLAStitle = "Work in Progress"
    
    path = "/scratchfs/atlas/yehf/QFramework/Htautau/share/FakeFactors/"

    #file_FF_dphi1 = TFile.Open(path+"FLR"+Year+Tags+channel+"LeptonPtDphi1"+FFName+"FF.root") 
    #file_FF_dphi2 = TFile.Open(path+"FLR"+Year+Tags+channel+"LeptonPtDphi2"+FFName+"FF.root")
    #file_FF_dphi3 = TFile.Open(path+"FLR"+Year+Tags+channel+"LeptonPtDphi3"+FFName+"FF.root")

    file_FF_dphi1 = TFile.Open(path+"FLR17"+Tags+channel+"LeptonPtDphi1"+FFName+"FF.root") 
    file_FF_dphi2 = TFile.Open(path+"FLR17"+Tags+channel+"LeptonPtDphi2"+FFName+"FF.root")
    file_FF_dphi3 = TFile.Open(path+"FLR17"+Tags+channel+"LeptonPtDphi3"+FFName+"FF.root")

    if not file_FF_dphi1 or not file_FF_dphi2 or not file_FF_dphi3 :
        print "Error! Can not open the file!"
        return

    Hist_FF_dphi1 = file_FF_dphi1.Get(Tags+"FF_"+channel+"_LeptonPtDphi1"+FFName+"FF")
    Hist_FF_dphi2 = file_FF_dphi2.Get(Tags+"FF_"+channel+"_LeptonPtDphi2"+FFName+"FF")
    Hist_FF_dphi3 = file_FF_dphi3.Get(Tags+"FF_"+channel+"_LeptonPtDphi3"+FFName+"FF")

    Hist_FF_dphi1.SetLineColor(kRed)
    Hist_FF_dphi2.SetLineColor(kBlue)
    Hist_FF_dphi3.SetLineColor(kViolet)
    #Hist_FF_dphi4.SetLineColor(kSpring)

    Hist_FF_dphi1.SetLineWidth(2)
    Hist_FF_dphi2.SetLineWidth(2)
    Hist_FF_dphi3.SetLineWidth(2)
    #Hist_FF_dphi4.SetLineWidth(2)
  
    Hist_FF_dphi1.SetTitle("Lepton Fake Factor")    
    Hist_FF_dphi2.SetTitle("Lepton Fake Factor")    
    Hist_FF_dphi3.SetTitle("Lepton Fake Factor")    


    #if "1p" in Ntracks:
    #    Hist_FF_dphi1.SetMinimum(-0.05)
    #    Hist_FF_dphi1.SetMaximum(0.4)
    #if "3p" in Ntracks:
    #    Hist_FF_dphi1.SetMinimum(-0.02)
    #    Hist_FF_dphi1.SetMaximum(0.1)

 
    Canvas = TCanvas("Canvas","FLR"+Year+Tags+channel+"LeptonPtDphi"+FFName+"FF")
    Canvas.cd()
    TGaxis.SetMaxDigits(3)
    Hist_FF_dphi2.Draw()
    Hist_FF_dphi1.Draw("same")
    Hist_FF_dphi3.Draw("same")
    #Hist_FF_dphi4.Draw("same")

    leg = TLegend(0.3,0.8,0.5,0.9)
    leg.AddEntry(Hist_FF_dphi1,"#Delta#phi(lep,MET)<0.5","l")
    leg.AddEntry(Hist_FF_dphi2,"0.5<#Delta#phi(lep,MET)<1.0","l")
    leg.AddEntry(Hist_FF_dphi3,"#Delta#phi(lep,MET)>1.0","l")
    #leg.AddEntry(Hist_FF_dphi3,"1.0<#Delta#phi(lep,MET)<2.0","l")
    #leg.AddEntry(Hist_FF_dphi4,"#Delta#phi(#tau,MET)>2.5","l")
    leg.Draw()
    leg.SetFillColor(0)

    tex1 = TLatex(0.6,0.8,"#it{#bf{ATLAS}}  "+ATLAStitle)
    tex1.SetNDC();
    tex1.SetTextFont(42)
    tex1.SetTextSize(0.04)
    tex1.SetLineWidth(2)
    tex1.Draw()

    tex2 = TLatex(0.6,0.72,"#int Ldt = "+Lumi+" fb^{-1}, #sqrt{s} = 13 TeV")
    tex2.SetNDC();
    tex2.SetTextFont(42)
    tex2.SetTextSize(0.03)
    tex2.SetLineWidth(2)
    tex2.Draw()

    tex3 = TLatex(0.6,0.64,"Lepton FF, "+channel+", "+FFName)
    tex3.SetNDC();
    tex3.SetTextFont(42)
    tex3.SetTextSize(0.033)
    tex3.SetLineWidth(2)
    tex3.Draw()    

    Canvas.Update()
    Canvas.SaveAs(path+"FLR"+Year+Tags+channel+"LeptonPtDphi"+FFName+"FF.png")
 
    file_FF_dphi1.Close()
    file_FF_dphi2.Close()
    file_FF_dphi3.Close()    
    #file_FF_dphi4.Close()    


    return

if __name__ == '__main__':
    MakeFFPlots()
