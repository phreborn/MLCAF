from ROOT import *
import QFramework

#samples_0 = TQSampleFolder.loadSampleFolder("sampleFolders/analyzed/samples-analyzed-LQtaub-lephad-SR-FakeComposition-NOMINAL.root")
#samples_0 = TQSampleFolder.loadSampleFolder("sampleFolders/analyzed/samples-analyzed-LQtaub-lephad-OtherJetsTFR-FakeComposition-NOMINAL.root")
samples_0 = TQSampleFolder.loadSampleFolder("sampleFolders/analyzed/samples-analyzed-LQtaub-lephad-OtherJetsSSR-FakeComposition-NOMINAL.root")
cv = TCanvas("cv","cv",700,700)

#hStack = THStack("hs1", "Composition of  jet faking tau in FTR,  OS")
hStack = THStack("hs1", "Composition of  jet faking tau in SSR,  OS")
#hStack = THStack("hs1", "Composition of jet faking tau in SR,  OS")

#cut="CutTFRLowST"
cut="CutSSBtag"
#cut="CutOSBtagLowBJetPt"
#cut="CutOSBtagHighBJetPt"
#cut="CutHighVisMass"
histName="TauPt"

hgluon = samples_0.getHistogram("/bkg/ehad/[c16a+c16d+c16e]/Gluon/Top/ttbar/nominal", "{:s}/{:s}".format(cut,histName))
hbottom = samples_0.getHistogram("/bkg/ehad/[c16a+c16d+c16e]/bottom/Top/ttbar/nominal", "{:s}/{:s}".format(cut,histName))
hcharm = samples_0.getHistogram("/bkg/ehad/[c16a+c16d+c16e]/charm/Top/ttbar/nominal", "{:s}/{:s}".format(cut,histName))
huds = samples_0.getHistogram("/bkg/ehad/[c16a+c16d+c16e]/uds/Top/ttbar/nominal", "{:s}/{:s}".format(cut,histName))
hother = samples_0.getHistogram("/bkg/ehad/[c16a+c16d+c16e]/other/Top/ttbar/nominal", "{:s}/{:s}".format(cut,histName))


hgluon_frac=hgluon.Clone()
hgluon_frac.Reset()

hbottom_frac = hbottom.Clone()
hbottom_frac.Reset()

hcharm_frac = hcharm.Clone()
hcharm_frac.Reset()

huds_frac = huds.Clone()
huds_frac.Reset()

hother_frac = hother.Clone()
hother_frac.Reset()


for i in range(1,hgluon.GetNbinsX()+1):

  incGluon = hgluon.GetBinContent(i)
  if incGluon < 0:
    incGluon = 0
  
  incBottom = hbottom.GetBinContent(i)
  if incBottom < 0:
    incBottom = 0
  
  incCharm = hcharm.GetBinContent(i)
  if incCharm < 0:
    incCharm = 0

  incUDS = huds.GetBinContent(i)
  if incUDS < 0:
    incUDS = 0

  incOther = hother.GetBinContent(i)
  if incOther < 0: 
    incOther = 0

  
  total = incGluon+incBottom+incCharm+incUDS+incOther

  if total != 0:
    hgluon_frac.SetBinContent(i, incGluon/total)
    hbottom_frac.SetBinContent(i, incBottom/total)
    hcharm_frac.SetBinContent(i, incCharm/total)
    huds_frac.SetBinContent(i, incUDS/total)
    hother_frac.SetBinContent(i, incOther/total)
  else:
    hgluon_frac.SetBinContent(i, 0)
    hbottom_frac.SetBinContent(i, 0)
    hcharm_frac.SetBinContent(i, 0)
    huds_frac.SetBinContent(i, 0)
    hother_frac.SetBinContent(i, 0)




hgluon_frac.SetFillColor(kGreen+3)
hgluon_frac.SetLineColor(kGreen+3)
hbottom_frac.SetFillColor(kCyan)
hbottom_frac.SetLineColor(kCyan)
hcharm_frac.SetFillColor(kMagenta)
hcharm_frac.SetLineColor(kMagenta)
huds_frac.SetFillColor(kYellow)
huds_frac.SetLineColor(kYellow)
hother_frac.SetFillColor(kBlue-6)
hother_frac.SetLineColor(kBlue-6)


#hgluon_frac.Draw()
#huds_frac.Draw()

hStack.Add(hother_frac)
hStack.Add(hbottom_frac)
hStack.Add(hcharm_frac)
hStack.Add(huds_frac)
hStack.Add(hgluon_frac)

legend = TLegend(0.12, 0.3, 0.22, 0.5)
legend.AddEntry(hother_frac, "Other")
legend.AddEntry(hbottom_frac, "b")
legend.AddEntry(hcharm_frac, "c")
legend.AddEntry(huds_frac, "uds")
legend.AddEntry(hgluon_frac, "g")
legend.SetBorderSize(0);
legend.SetTextSize(0.025)
legend.SetFillStyle(0)

hStack.Draw()
hStack.GetYaxis().SetTitle("Fraction")
hStack.GetXaxis().SetTitle("Tau pT")

#hStack.GetYaxis().SetRangeUser(0,1.4)
hStack.GetXaxis().SetLimits(-0.15,1)
legend.Draw()

#cv.SaveAs("ttbarehadFTROS.png")
cv.SaveAs("ttbarehadSSRSS.png")
#cv.SaveAs("ttbarehadSROS.png")
#cv.SaveAs("ttbarehadSROS_lowbjetpt.png")
#cv.SaveAs("ttbarehadSROS_highbjetpt.png")


#huds.Draw()
#huds.GetBinContent(

raw_input()

