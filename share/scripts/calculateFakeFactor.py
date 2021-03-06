#!/user/bin/env python2

def getOverallError(hist):
  error = .0
  for binIndex in range(1, hist.GetNbinsX()+1):
    error += hist.GetBinError(binIndex) * hist.GetBinError(binIndex)
  return sqrt(error)


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
def addSysError(oldHist,additionalHist):
    # here we need to change oldHist - add additionalHist in quadrature
    nBinsX = additionalHist.GetNbinsX()
    if nBinsX != oldHist.GetNbinsX():
        print "Error: different binning"
        return None
    # add content to oldHist
    for binIndex in range(0,nBinsX+2):
        additionalError = additionalHist.GetBinContent(binIndex)
        oldError = oldHist.GetBinContent(binIndex)
        totalError = sqrt(additionalError**2+oldError**2)
        oldHist.SetBinContent(binIndex, totalError)

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

# plotting FFs: hist error is MC and data statistics
#               up/down is MC and data statistics, and systematic uncertainties of MC subtraction
def plotFakeFactor(hist,up,down,name='someFF'):
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

    gr.GetYaxis().SetTitle('Fake Factor')
    c1.Update()
    c1.Write()


# calculation of fake factor
#       [datapath-mcpath]:nominator/histogram
# FF =  ---------------------------------------
#       [datapath-mcpath]:denominator/histogram
# Considering statistical uncertainty and sys of mc subtraction 
# FF will be saved to root files named prefix+histogram+'.root' 
def calcFakeFactor(datapath, bkgpath, nominator, denominator, histogram, prefix, nomVar=0.1, denomVar=0.1):
  print 'Calculate Fake Factor in ', prefix, histogram

  # nominal histogram
  histoPass = reader.getHistogram('{:s}-{:s}'.format(dataPath,bkgpath),'{:s}/{:s}'.format(nominator,histogram))
  histoFail = reader.getHistogram('{:s}-{:s}'.format(dataPath,bkgpath),'{:s}/{:s}'.format(denominator,histogram))

  # add overflow
  addOverflow(histoPass)
  addOverflow(histoFail)

  # calculate nominal FF
  FF_nom = histoPass.Clone()
  FF_nom.Divide(histoFail)
  FF_nom.SetName(prefix+histogram)
  checkNegative(FF_nom)

  # create error hist, this should contain errors with respect to 0
  FF_nom_error = FF_nom.Clone()
  for i in range(0, FF_nom_error.GetNbinsX()+2):
    FF_nom_error.SetBinContent(i, FF_nom_error.GetBinError(i))
    FF_nom_error.SetBinError(i, 0)
    

  if nomVar != 0.0 or denomVar != 0.0:
    histoPass_up   = reader.getHistogram('{:s}-{:s}*{:s}'.format(dataPath,str(1+nomVar),bkgpath),'{:s}/{:s}'.format(nominator,histogram))
    histoPass_down = reader.getHistogram('{:s}-{:s}*{:s}'.format(dataPath,str(1-nomVar),bkgpath),'{:s}/{:s}'.format(nominator,histogram))
    histoFail_up   = reader.getHistogram('{:s}-{:s}*{:s}'.format(dataPath,str(1+denomVar),bkgpath),'{:s}/{:s}'.format(denominator,histogram))
    histoFail_down = reader.getHistogram('{:s}-{:s}*{:s}'.format(dataPath,str(1-denomVar),bkgpath),'{:s}/{:s}'.format(denominator,histogram))
    # add overflow
    addOverflow(histoPass_up)
    addOverflow(histoPass_down)
    addOverflow(histoFail_up)
    addOverflow(histoFail_down)

    # up variation
    temp_up =histoPass_up.Clone()
    temp_up.Divide(histoFail_down)
    # down variation
    temp_down =histoPass_down.Clone()
    temp_down.Divide(histoFail_up)

    overall_nominal= histoPass.GetSumOfWeights()/histoFail.GetSumOfWeights()
    overall_up = histoPass_up.GetSumOfWeights()/histoFail_down.GetSumOfWeights()
    overall_down = histoPass_down.GetSumOfWeights()/histoFail_up.GetSumOfWeights()
    overall_ave = 0.5*(overall_down-overall_up)
    print "pass:\t", histoPass.GetSumOfWeights(), "\t", getOverallError(histoPass)
    print "fail:\t", histoFail.GetSumOfWeights(), "\t", getOverallError(histoFail)
    print "result\t", overall_nominal, "+-", overall_ave

    # difference
    temp_up.Add(FF_nom,-1)
    temp_down.Add(FF_nom,-1)
    
    # make positive definite and find average
    temp_ave = averageHist(temp_up, temp_down)

    # add difference to error hist
    addSysError(FF_nom_error,temp_ave)

  # at this point FF_nom_error contain stat and, if doMCSys, mc subtraction error
  FF_nom_up = FF_nom.Clone()
  FF_nom_up.Add(FF_nom_error)
  FF_nom_up.SetName(FF_nom.GetName()+'_up')
  checkNegative(FF_nom_up)

  FF_nom_down = FF_nom.Clone()
  FF_nom_down.Add(FF_nom_error,-1)
  FF_nom_down.SetName(FF_nom.GetName()+'_down')
  checkNegative(FF_nom_down)

  outfile = TFile(analysis+'/auxData/FakeFactors/'+FF_nom.GetName()+'.root','RECREATE')
  outfile.cd()
  FF_nom.Write()
  FF_nom_up.Write()
  FF_nom_down.Write()
  plotFakeFactor(FF_nom,FF_nom_up,FF_nom_down,FF_nom.GetName())
  outfile.Close()

if __name__=='__main__':
  from optparse import OptionParser

  parser=OptionParser(usage="usage: python %prog [options] REGION")
  parser.add_option("-d","--debug",  action="store_true"  ,dest="debug"  ,default=False     ,help="show DEBUG output")

  (options,args)=parser.parse_args()

  import sys
  # argument
  if len(args)==1: ##### Change
    print 'You must submit an argument REGION: \n\t MultiJetsLFR; \n\t OtherJetsTFR; \n\t etc.'
    print 'And an argument ANALYSIS: \n\t AHZ-lephad; \n\t etc.'
    sys.exit()
  analysis = args[0]
  region   = args[1]

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
  if region == 'OtherJetsTFR':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-OtherJetsTFR-FF.root'
  elif region == 'OtherJetsSSR':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-OtherJetsSSR-FF.root'
  elif region == 'MultiJetsLFR':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-MultiJetsLFR-FF.root'
  else:
    print ("ERROR: unsupported region: ", region)
    sys.exit()
  #get the sample folder:
  samples = TQSampleFolder.loadLazySampleFolder(sFile+':samples')
  reader = TQSampleDataReader(samples)

  if region == 'OtherJetsTFR':
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
        bkgPath = 'bkg/{:s}/{:s}/[mcReal+MultiJetsFake]'.format(channel_path, period_path)
        
        prefix = region+period_name+channel_name
        if 'LQtaub-lephad' not in analysis: 
          calcFakeFactor(dataPath, bkgPath, 'CutOSBvetoMediumMT1pPassTauID', 'CutOSBvetoMediumMT1pFailTauID', 'TauPtFF', prefix+"OSBvetoMediumMT1p", 0.1,0.1)
          calcFakeFactor(dataPath, bkgPath, 'CutOSBvetoMediumMT3pPassTauID', 'CutOSBvetoMediumMT3pFailTauID', 'TauPtFF', prefix+"OSBvetoMediumMT3p", 0.1,0.1)
          calcFakeFactor(dataPath, bkgPath, 'CutOSBtagMediumMT1pPassTauID', 'CutOSBtagMediumMT1pFailTauID', 'BTBinTauPtFF', prefix+"OSBtagMediumMT1p", 0.1,0.1)
          calcFakeFactor(dataPath, bkgPath, 'CutOSBtagMediumMT3pPassTauID', 'CutOSBtagMediumMT3pFailTauID', 'BTBinTauPtFF', prefix+"OSBtagMediumMT3p", 0.1,0.1)
        
          calcFakeFactor(dataPath, bkgPath, 'CutSSBvetoMediumMT1pPassTauID', 'CutSSBvetoMediumMT1pFailTauID', 'TauPtFF', prefix+"SSBvetoMediumMT1p", 0.1,0.1)
          calcFakeFactor(dataPath, bkgPath, 'CutSSBvetoMediumMT3pPassTauID', 'CutSSBvetoMediumMT3pFailTauID', 'TauPtFF', prefix+"SSBvetoMediumMT3p", 0.1,0.1)
          calcFakeFactor(dataPath, bkgPath, 'CutSSBtagMediumMT1pPassTauID', 'CutSSBtagMediumMT1pFailTauID', 'BTBinTauPtFF', prefix+"SSBtagMediumMT1p", 0.1,0.1)
          calcFakeFactor(dataPath, bkgPath, 'CutSSBtagMediumMT3pPassTauID', 'CutSSBtagMediumMT3pFailTauID', 'BTBinTauPtFF', prefix+"SSBtagMediumMT3p", 0.1,0.1)
        elif 'LQtaub-lephad' == analysis:
          calcFakeFactor(dataPath, bkgPath, 'CutTFR1pPassTauID', 'CutTFR1pFailTauID', 'TauPtFF', prefix+"Btag1p", 0.1,0.1)
          calcFakeFactor(dataPath, bkgPath, 'CutTFR3pPassTauID', 'CutTFR3pFailTauID', 'TauPtFF', prefix+"Btag3p", 0.1,0.1)
          


    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/FakeFactors/OtherJetsTFR_FF.root "+analysis+"/auxData/FakeFactors/OtherJetsTFRAll*.root\033[0m")
  
  elif region == 'QCDTFR':
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
        bkgPath = 'bkg/{:s}/{:s}/mc/TTL/[Ztautau+Zll+Top+Diboson+Wjets]'.format(channel_path, period_path)
        
        prefix = region+period_name+channel_name
        # bveto 1D FF
        calcFakeFactor(dataPath, bkgPath, 'CutOSBvetoQCDTFR1pPassTauID', 'CutOSBvetoQCDTFR1pFailTauID', 'Bveto1pTauPtFF', prefix, 0.1,0.1)
        calcFakeFactor(dataPath, bkgPath, 'CutOSBvetoQCDTFR3pPassTauID', 'CutOSBvetoQCDTFR3pFailTauID', 'Bveto3pTauPtFF', prefix, 0.1,0.1)
        # btag 1D FF
        calcFakeFactor(dataPath, bkgPath, 'CutOSBtagQCDTFR1pPassTauID',  'CutOSBtagQCDTFR1pFailTauID', 'Btag1pTauPtFF', prefix, 0.1,0.1)
        calcFakeFactor(dataPath, bkgPath, 'CutOSBtagQCDTFR3pPassTauID',  'CutOSBtagQCDTFR3pFailTauID', 'Btag3pTauPtFF', prefix, 0.1,0.1)

  elif region == 'MultiJetsLFR':
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
        bkgPath = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets+Top+Diboson+Wjets]'.format(channel_path, period_path)
        
        prefix = region+"TopCorrected"+period_name+channel_name
        if "AHZ-lephad" == analysis:
        # 2D FF
          calcFakeFactor(dataPath, bkgPath, 'CutOSBvetoMultiJetsLFRPassISO', 'CutOSBvetoMultiJetsLFRFailISO', 'BvetoLeptonPtCentralFF', prefix+"OS", 0.1,0.2)
          calcFakeFactor(dataPath, bkgPath, 'CutSSBvetoMultiJetsLFRPassISO', 'CutSSBvetoMultiJetsLFRFailISO', 'BvetoLeptonPtCentralFF', prefix+"SS", 0.1,0.2)
          calcFakeFactor(dataPath, bkgPath, 'CutOSBvetoMultiJetsLFRPassISO', 'CutOSBvetoMultiJetsLFRFailISO', 'BvetoLeptonPtForwardFF', prefix+"OS", 0.1,0.2)
          calcFakeFactor(dataPath, bkgPath, 'CutSSBvetoMultiJetsLFRPassISO', 'CutSSBvetoMultiJetsLFRFailISO', 'BvetoLeptonPtForwardFF', prefix+"SS", 0.1,0.2)
          calcFakeFactor(dataPath, bkgPath, 'CutOSBtagMultiJetsLFRPassISO', 'CutOSBtagMultiJetsLFRFailISO', 'BtagLeptonPtCentralFF', prefix+"OS", 0.1,0.2)
          calcFakeFactor(dataPath, bkgPath, 'CutSSBtagMultiJetsLFRPassISO', 'CutSSBtagMultiJetsLFRFailISO', 'BtagLeptonPtCentralFF', prefix+"SS", 0.1,0.2)
          calcFakeFactor(dataPath, bkgPath, 'CutOSBtagMultiJetsLFRPassISO', 'CutOSBtagMultiJetsLFRFailISO', 'BtagLeptonPtForwardFF', prefix+"OS", 0.1,0.2)
          calcFakeFactor(dataPath, bkgPath, 'CutSSBtagMultiJetsLFRPassISO', 'CutSSBtagMultiJetsLFRFailISO', 'BtagLeptonPtForwardFF', prefix+"SS", 0.1,0.2)
        else:
          calcFakeFactor(dataPath, bkgPath, 'CutBtagMultiJetsLFRPassISO', 'CutBtagMultiJetsLFRFailISO', 'BtagLeptonPtCentralFF', prefix+"SS", 0.15,0.2)
          calcFakeFactor(dataPath, bkgPath, 'CutBtagMultiJetsLFRPassISO', 'CutBtagMultiJetsLFRFailISO', 'BtagLeptonPtForwardFF', prefix+"SS", 0.15,0.2)

    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/FakeFactors/MultiJetsLFR_FF.root "+analysis+"/auxData/FakeFactors/MultiJetsLFR*All*FF.root\033[0m")

  if region == 'OtherJetsSSR':
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
        bkgPath = 'bkg/{:s}/{:s}/[mcReal+MultiJetsFake]'.format(channel_path, period_path)
        
        prefix = region+period_name+channel_name
        
        calcFakeFactor(dataPath, bkgPath, 'CutSS1pPassTauID', 'CutSS1pFailTauID', 'TauPtFF', prefix+"Btag1p", 0.1,0.1)
        calcFakeFactor(dataPath, bkgPath, 'CutSS3pPassTauID', 'CutSS3pFailTauID', 'TauPtFF', prefix+"Btag3p", 0.1,0.1)

    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/FakeFactors/OtherJetsSSR_FF.root "+analysis+"/auxData/FakeFactors/OtherJetsSSRAll*.root\033[0m")
  
