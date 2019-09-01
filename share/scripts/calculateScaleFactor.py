#!/user/bin/env python2

# add overflow to the last bin
def addOverflow(hist):
  lastBin = hist.GetNbinsX()
  # content
  lastBinContent = hist.GetBinContent(lastBin)
  overflowBinContent = hist.GetBinContent(lastBin+1)
  newContent = lastBinContent+overflowBinContent
  hist.SetBinContent(lastBin, newContent)
  hist.SetBinContent(lastBin+1,0)
  # error
  lastBinError = hist.GetBinError(lastBin)
  overflowBinError = hist.GetBinError(lastBin+1)
  newError = sqrt(lastBinError*lastBinError+overflowBinError*overflowBinError)
  hist.SetBinError(lastBin, newError)
  hist.SetBinError(lastBin+1,0)
  # entries
  hist.SetEntries(hist.GetEntries()-2)

# force each histogram to be positive, and averge
def averageHist(hist1, hist2):
    nBinsX = hist1.GetNbinsX()
    if nBinsX != hist2.GetNbinsX():
        print "Error: different binning"
        return None
    # make positive
    for bin in range(0,nBinsX+2):
        hist1.SetBinContent(bin, fabs(hist1.GetBinContent(bin)))
        hist2.SetBinContent(bin, fabs(hist2.GetBinContent(bin)))
    # average
    temp = hist1.Clone()
    temp.Add(hist1,hist2,0.5,0.5)
    return temp

# add systematic uncertainty in quadrature
def addSysError(histError,hist1):
    # here we need to change histError - add hist1 in quadrature
    nBinsX = hist1.GetNbinsX()
    if nBinsX != histError.GetNbinsX():
        print "Error: different binning"
        return None
    # add content to histError
    for bin in range(0,nBinsX+2):
        tempError = hist1.GetBinContent(bin)
        oldError = histError.GetBinContent(bin)
        histError.SetBinContent(bin, sqrt(tempError**2+oldError**2))

# force histogram to be non-negative
def checkNegative(hist):
    nBinsX = hist.GetNbinsX()
    for bin in range(0,nBinsX+2):
        temp = hist.GetBinContent(bin)
        if temp<0:
            hist.SetBinContent(bin,0)

# convert to TGraphAsymmErrors
def convertToAsyGraph(hist, up, down):
    x=array('f')
    exl=array('f')
    exh=array('f')
    y=array('f')
    eyl=array('f')
    eyh=array('f')

    nBinsX=hist.GetNbinsX()
    for bin in range(1,nBinsX+1):
        x.append( hist.GetBinCenter(bin) )
        y.append( hist.GetBinContent(bin) )
        exl.append( hist.GetBinWidth(bin)/2. )
        eyl.append( hist.GetBinContent(bin) - down.GetBinContent(bin) )
        exh.append( hist.GetBinWidth(bin)/2. )
        eyh.append( up.GetBinContent(bin) - hist.GetBinContent(bin) )

    gr = TGraphAsymmErrors(nBinsX,x,y,exl,exh,eyl,eyh)
    gr.GetXaxis().SetTitle(hist.GetXaxis().GetTitle())
    return gr
# plotting SFs: hist error is MC statistics
#               up/down is MC statistics and MC subtraction
def plotScaleFactor(hist,up,down,name='someFF'):
    print ' Now Plotting FakeFacotr: '+name

    c1 = TCanvas( 'c1', '', 200, 10, 700, 500 )
    c1.SetGrid()

    # set proper range
    max = up.GetMaximum()
    min = down.GetMinimum()
    hist.GetYaxis().SetRangeUser(min-0.1, max+0.1);
    hist.SetStats(0)

    gr = convertToAsyGraph(hist, up, down) 
    gr.SetTitle(name);
    gr.SetFillColor(6);
    gr.SetFillStyle(3005);
    gr.SetMarkerColor(4);
    gr.SetMarkerStyle(21);
    gr.Draw("A2");
    hist.Draw('X0same')

    #ATLAS label
    lumi = '139.0' if ("All" in name) else '58.4' if ("18" in name) else '44.3' if ("17" in name) else '36.2'
    ATLAS_LABEL(0.37,0.85,kBlack)
    myText(0.49,0.85,kBlack, "Internal");
    myText(0.37,0.79,kBlack, '\sqrt s=13TeV, \int L dt = {:s} fb^-1'.format(lumi));
    # derive what ff is this
    text = ''
    text_list = ['LFR', 'WFR', 'TCR', 'ehad', 'muhad', 'lephad', '1p', '3p']
    for t in text_list:
        if t in name:
            text += t
    myText(0.37,0.73,kBlack, text);

    gr.GetYaxis().SetTitle('Scale Factor')
    c1.Update()
    c1.Write()


###############################################################
# calculation of scale factor
#       [datapath-mcpath1]:cut/histogram
# FF =  ---------------------------------------
#       [mcpath2]:cut/histogram
# Considering statistical uncertainty and sys of mc subtraction 
# FF will be saved to root files named prefix+histogram+'.root' 
###############################################################
def calcScaleFactor(datapath, bkgpath1, bkgpath2, cut, histogram, prefix, mcVar1=0.1, mcVar2=0.1):
  print '----------------------------------------------------------'
  print 'Now running Scale Factor in ', prefix, histogram
  print '--------------------------------------------------------\n'

  doMCSys = True #True
  
  # nominal histogram
  histoObs = reader.getHistogram('{:s}-{:s}'.format(dataPath,bkgpath1),'{:s}/{:s}'.format(cut,histogram))
  histoExp = reader.getHistogram('{:s}'.format(bkgpath2),'{:s}/{:s}'.format(cut,histogram))

  # add overflow
  addOverflow(histoObs)
  addOverflow(histoExp)

  # calculate nominal SF
  SF_nom = histoObs.Clone()
  SF_nom.Divide(histoExp)
  SF_nom.SetName(prefix+histogram)
  checkNegative(SF_nom)

  # create error hist, this should contain errors with respect to 0
  SF_nom_error = SF_nom.Clone()
  for i in range(0, SF_nom_error.GetNbinsX()+2):
    SF_nom_error.SetBinContent(i, SF_nom_error.GetBinError(i))
    SF_nom_error.SetBinError(i, 0)

  if doMCSys:
    histoObs_up   = reader.getHistogram('{:s}-{:s}*{:s}'.format(dataPath,str(1+mcVar1),bkgpath1),'{:s}/{:s}'.format(cut,histogram))
    histoObs_down = reader.getHistogram('{:s}-{:s}*{:s}'.format(dataPath,str(1-mcVar1),bkgpath1),'{:s}/{:s}'.format(cut,histogram))
    histoExp_up   = reader.getHistogram('{:s}*{:s}'.format(str(1+mcVar2),bkgpath2),'{:s}/{:s}'.format(cut,histogram))
    histoExp_down = reader.getHistogram('{:s}*{:s}'.format(str(1-mcVar2),bkgpath2),'{:s}/{:s}'.format(cut,histogram))
    # add overflow
    addOverflow(histoObs_up)
    addOverflow(histoObs_down)
    addOverflow(histoExp_up)
    addOverflow(histoExp_down)

    # up variation
    temp_up =histoObs_up.Clone()
    temp_up.Divide(histoExp_down)
    # down variation
    temp_down =histoObs_down.Clone()
    temp_down.Divide(histoExp_up)

    # difference
    temp_up.Add(SF_nom,-1)
    temp_down.Add(SF_nom,-1)
    
    # make positive definite and find average
    temp_ave = averageHist(temp_up, temp_down)

    # add difference to error hist
    addSysError(SF_nom_error,temp_ave)

  # at this point SF_nom_error contain stat and, if doMCSys, mc subtraction error
  SF_nom_up = SF_nom.Clone()
  SF_nom_up.Add(SF_nom_error)
  SF_nom_up.SetName(SF_nom.GetName()+'_up')
  checkNegative(SF_nom_up)

  SF_nom_down = SF_nom.Clone()
  SF_nom_down.Add(SF_nom_error,-1)
  SF_nom_down.SetName(SF_nom.GetName()+'_down')
  checkNegative(SF_nom_down)

  outfile = TFile('ScaleFactors/'+SF_nom.GetName()+'.root','RECREATE')
  outfile.cd()
  SF_nom.Write()
  SF_nom_up.Write()
  SF_nom_down.Write()
  plotScaleFactor(SF_nom,SF_nom_up,SF_nom_down,SF_nom.GetName())
  outfile.Close()

if __name__=='__main__':
  from optparse import OptionParser

  parser=OptionParser(usage="usage: python %prog [options] REGION")
  parser.add_option("-d","--debug",  action="store_true"  ,dest="debug"  ,default=False     ,help="show DEBUG output")

  (options,args)=parser.parse_args()

  import sys
  # argument
  if len(args)==0:
    print 'You must submit an argument REGION: \n\t WFR; \n\t LFR; \n\t etc.'
    sys.exit()
  region = args[0]

  from QFramework import *
  from math import *
  from ROOT import *
  from array import array
  import itertools

  ROOT.gROOT.LoadMacro("scripts/AtlasStyle/AtlasStyle.C")
  ROOT.gROOT.LoadMacro("scripts/AtlasStyle/AtlasUtils.C")
  ROOT.gROOT.SetBatch(kTRUE)
  SetAtlasStyle()

  debug = options.debug

  # decide which file is needed:
  if region == 'WFR':
    sFile = 'sampleFolders/analyzed/samples-analyzed-htautau_lephad_wfr_applyff.root'
  elif region == 'LFR':
    sFile = 'sampleFolders/analyzed/samples-analyzed-htautau_lephad_lfr_applyff.root'
  elif region == 'TCR':
    sFile = 'sampleFolders/analyzed/samples-analyzed-htautau_lephad_wfr_applyff.root'
  elif region == 'VR':
    sFile = 'sampleFolders/analyzed/samples-analyzed-htautau_lephad_sr.root'

  #get the sample folder:
  samples = TQSampleFolder.loadLazySampleFolder(sFile+':samples')
  reader = TQSampleDataReader(samples)

  if region == 'WFR':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                'ehad': 'ehad',
                'muhad': 'muhad',
                #'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[Ztautau+Zll+Top+Diboson+Fakes/ISO/[data-mc]]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/Fakes/ID/[data-[mc+ISO/[data-mc]]]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        # bveto 1D SF
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto1pOSPassID', 'Bveto1pDphiTauPt1SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto1pOSPassID', 'Bveto1pDphiTauPt2SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto1pOSPassID', 'Bveto1pDphiTauPt3SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto1pOSPassID', 'Bveto1pDphiTauPt4SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto1pOSPassID', 'Bveto1pDphiTauPt5SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto1pOSPassID', 'Bveto1pDphiTauPt6SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto1pOSPassID', 'Bveto1pDphiTauPt7SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto1pOSPassID', 'Bveto1pDphiTauPt8SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto1pOSPassID', 'Bveto1pDphiTauPt9SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto1pOSPassID', 'Bveto1pDphiTauPt10SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto1pOSPassID', 'Bveto1pDphiTauPt11SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto1pOSPassID', 'Bveto1pDphiTauPt12SF', prefix, 0.1, 0.1)

        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto3pOSPassID', 'Bveto3pDphiTauPt1SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto3pOSPassID', 'Bveto3pDphiTauPt2SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto3pOSPassID', 'Bveto3pDphiTauPt3SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto3pOSPassID', 'Bveto3pDphiTauPt4SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto3pOSPassID', 'Bveto3pDphiTauPt5SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto3pOSPassID', 'Bveto3pDphiTauPt6SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto3pOSPassID', 'Bveto3pDphiTauPt7SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto3pOSPassID', 'Bveto3pDphiTauPt8SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto3pOSPassID', 'Bveto3pDphiTauPt9SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto3pOSPassID', 'Bveto3pDphiTauPt10SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto3pOSPassID', 'Bveto3pDphiTauPt11SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBveto3pOSPassID', 'Bveto3pDphiTauPt12SF', prefix, 0.1, 0.1)


  elif region == 'VR':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                'ehad': 'ehad',
                'muhad': 'muhad',
                #'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[Ztautau+Zll+Top+Diboson+Fakes/ISO/[data-mc]]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/Fakes/ID/[data-[mc+ISO/[data-mc]]]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        # bveto 1D SF
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutVRBveto1p', 'Bveto1pTauPtDphi1SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutVRBveto1p', 'Bveto1pTauPtDphi2SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutVRBveto1p', 'Bveto1pTauPtDphi3SF', prefix, 0.1, 0.1)

        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutVRBveto3p', 'Bveto3pTauPtDphi1SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutVRBveto3p', 'Bveto3pTauPtDphi2SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutVRBveto3p', 'Bveto3pTauPtDphi3SF', prefix, 0.1, 0.1)
  elif region == 'LFR':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                'muhad': 'muhad',
                #'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[Ztautau+Zll+Top+Diboson+Wjets]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/Fakes/ISO/[data-mc]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        # bveto 2D SF
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBvetoBDTSLPassISO', 'BvetoTauPtDphi1SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBvetoBDTSLPassISO', 'BvetoTauPtDphi2SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBvetoBDTSLPassISO', 'BvetoTauPtDphi3SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBvetoBDTSLPassISO', 'BvetoTauPtDphi4SF', prefix, 0.1, 0.1)
        # btag 2D SF
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBtagBDTSLPassISO', 'BtagTauPtDphi1SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBtagBDTSLPassISO', 'BtagTauPtDphi2SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutBtagBDTSLPassISO', 'BtagTauPtDphi3SF', prefix, 0.1, 0.1)
  elif region == 'TCR':
    # Loop over data taking period and channels
    periods = {
                '1516': 'c16a',
                '17': 'c16d',
                '18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                'ehad': 'ehad',
                'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[Ztautau+Zll+Diboson+Fakes/ISO/[data-mc]+Fakes/ID/[data-[mc+ISO/[data-mc]]]]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/Top'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        # btag 1D SF
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRBtag1p', 'Btag1pTauPtSF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRBtag3p', 'Btag3pTauPtSF', prefix, 0.1, 0.1)
