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
    #Year = "17"
    Year = "18"

    #Lumi = "36.21"
    #Lumi = "43.58"
    Lumi = "58.45"
    
    #channel = "ehad"
    channel = "muhad"

    Tags = "Btag"
    #Tags = "Bveto"

    #FFName = "ELEBTAG"
    #FFName = "ELEBVETO"
    #FFName = "MUONBTAG"
    #FFName = "MUONBVETO"

    #Ntracks = "1p"
    #Ntracks = "3p"

    ATLAStitle = "Work in Progress"
    
    path = "/scratchfs/atlas/yehf/QFramework/Htautau/share/FakeFactors/"

    #file_FF_dphi1 = TFile.Open(path+"SSWCR"+Year+Tags+channel+"TauPtFF"+Tags+"1p.root") 
    #file_FF_dphi2 = TFile.Open(path+"SSWCR"+Year+Tags+channel+"TauPtFF"+Tags+"3p.root")
    file_FF_dphi1 = TFile.Open(path+"SSWCR17"+Tags+channel+"TauPtFF"+Tags+"1p.root") 
    file_FF_dphi2 = TFile.Open(path+"SSWCR17"+Tags+channel+"TauPtFF"+Tags+"3p.root")
    #file_FF_dphi3 = TFile.Open(path+"WCR"+Year+Tags+channel+"TauPtFF"+Tags+Ntracks+"Dphi3.root")
    #file_FF_dphi4 = TFile.Open(path+"WCR"+Year+Tags+channel+"TauPtFF"+Tags+Ntracks+"Dphi4.root")

    if not file_FF_dphi1 or not file_FF_dphi2 :
        print "Error! Can not open the file!"
        return

    Hist_FF_dphi1 = file_FF_dphi1.Get(Tags+"FF_"+channel+"_TauPtFF"+Tags+"1p")
    Hist_FF_dphi2 = file_FF_dphi2.Get(Tags+"FF_"+channel+"_TauPtFF"+Tags+"3p")
    #Hist_FF_dphi3 = file_FF_dphi3.Get(Tags+"FF_"+channel+"_TauPtFF"+Tags+Ntracks+"Dphi3")
    #Hist_FF_dphi4 = file_FF_dphi4.Get(Tags+"FF_"+channel+"_TauPtFF"+Tags+Ntracks+"Dphi4")

    Hist_FF_dphi1.SetLineColor(kRed)
    Hist_FF_dphi2.SetLineColor(kBlue)
    #Hist_FF_dphi3.SetLineColor(kViolet)
    #Hist_FF_dphi4.SetLineColor(kSpring)

    Hist_FF_dphi1.SetLineWidth(2)
    Hist_FF_dphi2.SetLineWidth(2)
    #Hist_FF_dphi3.SetLineWidth(2)
    #Hist_FF_dphi4.SetLineWidth(2)
  
    Hist_FF_dphi1.SetTitle("#tau Fake Factor")    


    #if "1p" in Ntracks:
    Hist_FF_dphi1.SetMinimum(-0.1)
    Hist_FF_dphi1.SetMaximum(0.3)
    #if "3p" in Ntracks:
    #    Hist_FF_dphi1.SetMinimum(-0.05)
    #    Hist_FF_dphi1.SetMaximum(0.1)

 
    Canvas = TCanvas("Canvas","SSWCR"+Year+Tags+channel+"TauPtFF"+Tags)
    Canvas.cd()
    TGaxis.SetMaxDigits(3)
    Hist_FF_dphi1.Draw()
    Hist_FF_dphi2.Draw("same")
    #Hist_FF_dphi3.Draw("same")
    #Hist_FF_dphi4.Draw("same")

    leg = TLegend(0.3,0.8,0.5,0.9)
    leg.AddEntry(Hist_FF_dphi1,"SS btag 1p","l")
    leg.AddEntry(Hist_FF_dphi2,"SS btag 3p","l")
    #leg.AddEntry(Hist_FF_dphi3,"2.0<#Delta#phi(#tau,MET)<2.5","l")
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

    tex3 = TLatex(0.6,0.64,"Tau FF, "+channel+", "+Tags)
    tex3.SetNDC();
    tex3.SetTextFont(42)
    tex3.SetTextSize(0.033)
    tex3.SetLineWidth(2)
    tex3.Draw()    

    Canvas.Update()
    Canvas.SaveAs(path+"SSWCR"+Year+Tags+channel+"TauPtFF"+Tags+".png")
 
    file_FF_dphi1.Close()
    file_FF_dphi2.Close()
    #file_FF_dphi3.Close()    
    #file_FF_dphi4.Close()    


    return

if __name__ == '__main__':
    MakeFFPlots()
