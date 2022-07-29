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
    text_list = ['MFR', 'TFR', 'TCR', 'ehad', 'muhad', 'lephad', '1p', '3p']
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

  print "observed:\t", histoObs.GetSumOfWeights()
  print "expected:\t", histoExp.GetSumOfWeights()
  print "result:\t", histoObs.GetSumOfWeights()/histoExp.GetSumOfWeights()

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
    #temp_up.Divide(histoExp_down)
    temp_up.Divide(histoExp_up)
    # down variation
    temp_down =histoObs_down.Clone()
    #temp_down.Divide(histoExp_up)
    temp_down.Divide(histoExp_down)

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

  outfile = TFile(analysis+'/auxData/ScaleFactors/'+SF_nom.GetName()+'.root','RECREATE')
  outfile.cd()
  SF_nom.Write()
  SF_nom_up.Write()
  SF_nom_down.Write()
  plotScaleFactor(SF_nom,SF_nom_up,SF_nom_down,SF_nom.GetName())
  outfile.Close()

def calcDiscrepancy(datapath, bkgpath, cut, histogram, prefix, mcVar1=0.1, mcVar2=0.1):
  print '----------------------------------------------------------'
  print 'Now running Scale Factor in ', prefix, histogram
  print '--------------------------------------------------------\n'

  doMCSys = False #True
  
  # nominal histogram
  histoObs = reader.getHistogram('{:s}'.format(dataPath),'{:s}/{:s}'.format(cut,histogram))
  histoExp = reader.getHistogram('{:s}'.format(bkgpath),'{:s}/{:s}'.format(cut,histogram))

  # add overflow
  addOverflow(histoObs)
  addOverflow(histoExp)

  # calculate nominal SF
  SF_nom = histoObs.Clone()
  SF_nom.Divide(histoExp)
  SF_nom.SetName(prefix+histogram)
  checkNegative(SF_nom)

  print "observed:\t", histoObs.GetSumOfWeights()
  print "expected:\t", histoExp.GetSumOfWeights()
  print "result:\t", histoObs.GetSumOfWeights()/histoExp.GetSumOfWeights()

  # create error hist, this should contain errors with respect to 0
  SF_nom_error = SF_nom.Clone()
  for i in range(0, SF_nom_error.GetNbinsX()+2):
    SF_nom_error.SetBinContent(i, SF_nom_error.GetBinError(i))
    SF_nom_error.SetBinError(i, 0)

  if doMCSys:
    histoObs_up   = reader.getHistogram('{:s}'.format(dataPath),'{:s}/{:s}'.format(cut,histogram))
    histoObs_down = reader.getHistogram('{:s}'.format(dataPath),'{:s}/{:s}'.format(cut,histogram))
    histoExp_up   = reader.getHistogram('{:s}*{:s}'.format(str(1+mcVar2),bkgpath),'{:s}/{:s}'.format(cut,histogram))
    histoExp_down = reader.getHistogram('{:s}*{:s}'.format(str(1-mcVar2),bkgpath),'{:s}/{:s}'.format(cut,histogram))
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

  outfile = TFile(analysis+'/auxData/ScaleFactors/'+SF_nom.GetName()+'.root','RECREATE')
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
    print 'You must submit an argument REGION: \n\t TCR; \n\t OtherJetsTFR; \n\t etc.'
    print 'And an argument Analysis: \n\t AHZ-lephad; \n\t etc.'
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
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-OtherJetsTFR-FF-closure.root'
    if analysis == 'LQtaub-lephad':
      sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-OtherJetsTFR-FF.root'
  elif region == 'TCRClosure':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-TCR-SF-closure.root'
  elif region == 'TTBar_nominal':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-TCR-SF.root'
  elif region == 'TCR_nominal':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-TCR-SF.root'
  elif region == 'TCR_PS':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-TCR-PS-SF.root'
  elif region == 'TCR_ME':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-TCR-ME-SF.root'
  elif region == 'TCR_ISRup':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-TCR-ISRup-SF.root'
  elif region == 'TCR_ISRdo':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-TCR-ISRdo-SF.root'
  elif region == 'TCR_FSRup':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-TCR-FSRup-SF.root'
  elif region == 'TCR_FSRdo':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-TCR-FSRdo-SF.root'
  elif region == 'TCR_PDFup':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-TCR-PDFup-SF.root'
  elif region == 'TCR_PDFdo':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-TCR-PDFdo-SF.root'
  elif region == 'TCR_STopPS':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-TCR-STopPS-SF.root'
  elif region == 'TCR_STopME':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-TCR-STopME-SF.root'
  elif region == 'TCR_STopISRup':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-TCR-STopISRup-SF.root'
  elif region == 'TCR_STopISRdo':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-TCR-STopISRdo-SF.root'
  elif region == 'TCR_STopFSRup':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-TCR-STopFSRup-SF.root'
  elif region == 'TCR_STopFSRdo':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-TCR-STopFSRdo-SF.root'
  elif region == 'TCR_STopPDFup':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-TCR-STopPDFup-SF.root'
  elif region == 'TCR_STopPDFdo':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-TCR-STopPDFdo-SF.root'
  elif region == 'TCR_STopWTInt':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-TCR-STopWTInt-SF.root'
  elif region == 'MultiJetsLFR':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-MultiJetsLFR-FF-closure.root'
  elif region == 'SSExtrap':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-SR-FF-NOMINAL.root'
  elif region == 'OtherJetsSSR':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-OtherJetsSSR-FF.root'
  elif region == 'OtherJetsSSR_withoutTopCorr':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-OtherJetsSSR-FF_withoutTopCorr.root'
  elif region == 'ZCR':
    sFile = 'sampleFolders/analyzed/samples-analyzed-'+analysis+'-ZCR-FF-NOMINAL.root'

  #get the sample folder:
  samples = TQSampleFolder.loadLazySampleFolder(sFile+':samples')
  reader = TQSampleDataReader(samples)

  if region == 'MultiJetsLFR':
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
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/MultiJetsFake'.format(channel_path, period_path)
        prefix = region+period_name+channel_name

        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBvetoMultiJetsLFRPassISO', 'BvetoTauPtDphi1SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBvetoMultiJetsLFRPassISO', 'BvetoTauPtDphi2SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBvetoMultiJetsLFRPassISO', 'BvetoTauPtDphi3SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBvetoMultiJetsLFRPassISO', 'BvetoTauPtDphi4SF', prefix, 0.1, 0.1)

        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBtagMultiJetsLFRPassISO', 'BtagTauPtDphi1SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBtagMultiJetsLFRPassISO', 'BtagTauPtDphi2SF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBtagMultiJetsLFRPassISO', 'BtagTauPtDphi3SF', prefix, 0.1, 0.1)

    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/MultiJetsLFR_SF.root "+analysis+"/auxData/ScaleFactors/MultiJetsLFRAll*.root\033[0m")

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
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+MultiJetsFake]'.format(channel_path, period_path)
        #bkgPath2 = 'bkg/{:s}/{:s}/ddOtherJetsFake'.format(channel_path, period_path)
        prefix = region+period_name+channel_name

        if 'LQtaub-lephad' not in analysis:
          bkgPath2 = 'bkg/{:s}/{:s}/ddOtherJetsFake'.format(channel_path, period_path)
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutOSBvetoMediumMT1pPassTauID', 'MTLepMETSF', prefix+"OSBvetoMediumMT1p", 0.1, 0.1)
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutOSBvetoMediumMT3pPassTauID', 'MTLepMETSF', prefix+"OSBvetoMediumMT3p", 0.1, 0.1)
        
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutOSBtagMediumMT1pPassTauID', 'MTLepMETSF', prefix+"OSBtagMediumMT1p", 0.1, 0.1)
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutOSBtagMediumMT3pPassTauID', 'MTLepMETSF', prefix+"OSBtagMediumMT3p", 0.1, 0.1)
        
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBvetoNoMT1pPassTauID', 'MTLepMETSF', prefix+"SSBvetoNoMT1p", 0.1, 0.1)
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBvetoNoMT3pPassTauID', 'MTLepMETSF', prefix+"SSBvetoNoMT3p", 0.1, 0.1)
        
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBtagNoMT1pPassTauID', 'MTLepMETSF', prefix+"SSBtagNoMT1p", 0.1, 0.1)
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBtagNoMT3pPassTauID', 'MTLepMETSF', prefix+"SSBtagNoMT3p", 0.1, 0.1)
        
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutOSBvetoMediumMT1pPassTauID', 'LeptonPtSF', prefix+"OSBvetoMediumMT1p", 0.1, 0.1)
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutOSBvetoMediumMT3pPassTauID', 'LeptonPtSF', prefix+"OSBvetoMediumMT3p", 0.1, 0.1)
        
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutOSBtagMediumMT1pPassTauID', 'LeptonPtSF', prefix+"OSBtagMediumMT1p", 0.1, 0.1)
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutOSBtagMediumMT3pPassTauID', 'LeptonPtSF', prefix+"OSBtagMediumMT3p", 0.1, 0.1)
        
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBvetoNoMT1pPassTauID', 'LeptonPtSF', prefix+"SSBvetoNoMT1p", 0.1, 0.1)
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBvetoNoMT3pPassTauID', 'LeptonPtSF', prefix+"SSBvetoNoMT3p", 0.1, 0.1)
        
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBtagNoMT1pPassTauID', 'LeptonPtSF', prefix+"SSBtagNoMT1p", 0.1, 0.1)
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBtagNoMT3pPassTauID', 'LeptonPtSF', prefix+"SSBtagNoMT3p", 0.1, 0.1)
        
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBvetoMediumMT1pPassTauID', 'LeptonPtSF', prefix+"SSBvetoMediumMT1p", 0.1, 0.1)
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBvetoMediumMT3pPassTauID', 'LeptonPtSF', prefix+"SSBvetoMediumMT3p", 0.1, 0.1)
        
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBtagMediumMT1pPassTauID', 'LeptonPtSF', prefix+"SSBtagMediumMT1p", 0.1, 0.1)
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBtagMediumMT3pPassTauID', 'LeptonPtSF', prefix+"SSBtagMediumMT3p", 0.1, 0.1)
        elif 'LQtaub-lephad' == analysis:
          bkgPath2 = 'bkg/{:s}/{:s}/mcFake'.format(channel_path, period_path)
          #calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTFR1pPassTauID', 'TauPtSF', prefix+"Btag1p", 0.1,0.1)
          #calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTFR3pPassTauID', 'TauPtSF', prefix+"Btag3p", 0.1,0.1)
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTFR1pPassTauID', 'TauPt1pSF', prefix+"Btag1p", 0.1,0.1)
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTFR3pPassTauID', 'TauPt3pSF', prefix+"Btag3p", 0.1,0.1)
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTFR1pPassTauID', 'TauPtSFOneBin', prefix+"Btag1p", 0.1,0.1)
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTFR3pPassTauID', 'TauPtSFOneBin', prefix+"Btag3p", 0.1,0.1)
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTFR1p5JetsPassID', 'TauPt1pSF', prefix+"Btag1p5Jets", 0.1,0.1)
          calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTFR3p5JetsPassID', 'TauPt3pSF', prefix+"Btag3p5Jets", 0.1,0.1)

    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/OtherJetsTFR_SF.root "+analysis+"/auxData/ScaleFactors/OtherJetsTFRAll*.root\033[0m")


  elif region == 'SSExtrap':
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
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+MultiJetsFake]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/ddOtherJetsFake'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        # bveto 2D SF
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBvetoLowMT', 'BvetoLowMT1pSF', prefix, 0.1, 0.1)        
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBvetoLowMT', 'BvetoLowMT3pSF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBtagLowMT', 'BtagLowMT1pSF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBtagLowMT', 'BtagLowMT3pSF', prefix, 0.1, 0.1)

        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBvetoLowMT', 'BvetoTauPt1pSF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBvetoLowMT', 'BvetoTauPt3pSF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBtagLowMT', 'BtagTauPt1pSF', prefix, 0.1, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSSBtagLowMT', 'BtagTauPt3pSF', prefix, 0.1, 0.1)


    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/SSExtrap_SF.root "+analysis+"/auxData/ScaleFactors/SSExtrapAll*.root\033[0m")

  elif region == 'TCRClosure':
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
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets+Wjets+Diboson]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/Top/[single/nominal+ttbar/nominal]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRPassTauID', 'LeptonPtSF', prefix+"Btag", 0.1, 0.1)
        
    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/TopCR_Closure_SF.root "+analysis+"/auxData/ScaleFactors/TCRClosureAll*.root\033[0m")

  elif region == 'TTBar_nominal':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                #'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets/[ee+mumu+tautau]+Wjets+Diboson+Top/single/nominal]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/Top/ttbar/nominal'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRPassTauID', 'StSF', prefix+"Btag", 0.1, 0.1)
        
    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/TTBarCor_SF_nominal.root "+analysis+"/auxData/ScaleFactors/TTBar_nominalAll*.root\033[0m")

  elif region == 'TCR_nominal':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                #'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets/[ee+mumu+tautau]+Wjets+Diboson]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/Top/[single/nominal+ttbar/nominal]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRPassTauID', 'StSF', prefix+"Btag", 0.1, 0.1)
        
    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/TopCR_SF_nominal.root "+analysis+"/auxData/ScaleFactors/TCR_nominalAll*.root\033[0m")

  elif region == 'TCR_FSRdo':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                #'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets/[ee+mumu+tautau]+Wjets+Diboson]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/Top/[single/nominal+ttbar/nominal]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRPassTauID', 'StSF', prefix+"Btag", 0.1, 0.1)
        
    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/TopCR_SF_FSRdo.root "+analysis+"/auxData/ScaleFactors/TCR_FSRdoAll*.root\033[0m")

  elif region == 'TCR_FSRup':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                #'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets/[ee+mumu+tautau]+Wjets+Diboson]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/Top/[single/nominal+ttbar/nominal]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRPassTauID', 'StSF', prefix+"Btag", 0.1, 0.1)
        
    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/TopCR_SF_FSRup.root "+analysis+"/auxData/ScaleFactors/TCR_FSRupAll*.root\033[0m")

  elif region == 'TCR_PDFdo':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                #'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets/[ee+mumu+tautau]+Wjets+Diboson]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/Top/[single/nominal+ttbar/nominal]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRPassTauID', 'StSF', prefix+"Btag", 0.1, 0.1)
        
    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/TopCR_SF_PDFdo.root "+analysis+"/auxData/ScaleFactors/TCR_PDFdoAll*.root\033[0m")

  elif region == 'TCR_PDFup':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                #'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets/[ee+mumu+tautau]+Wjets+Diboson]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/Top/[single/nominal+ttbar/nominal]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRPassTauID', 'StSF', prefix+"Btag", 0.1, 0.1)
        
    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/TopCR_SF_PDFup.root "+analysis+"/auxData/ScaleFactors/TCR_PDFupAll*.root\033[0m")

  elif region == 'TCR_ISRdo':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                #'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets+Wjets+Diboson]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/Top/[single/nominal+ttbar/nominal]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRPassTauID', 'StSF', prefix+"Btag", 0.1, 0.1)
        
    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/TopCR_SF_ISRdo.root "+analysis+"/auxData/ScaleFactors/TCR_ISRdoAll*.root\033[0m")

  elif region == 'TCR_ISRup':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                #'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets/[ee+mumu+tautau]+Wjets+Diboson]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/Top/[single/nominal+ttbar/ISRup]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRPassTauID', 'StSF', prefix+"Btag", 0.1, 0.1)
        
    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/TopCR_SF_ISRup.root "+analysis+"/auxData/ScaleFactors/TCR_ISRupAll*.root\033[0m")

  elif region == 'TCR_ME':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                #'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets/[ee+mumu+tautau]+Wjets+Diboson]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/Top/[single/nominal+ttbar/ME]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRPassTauID', 'StSF', prefix+"Btag", 0.1, 0.1)
        
    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/TopCR_SF_ME.root "+analysis+"/auxData/ScaleFactors/TCR_MEAll*.root\033[0m")

  elif region == 'TCR_PS':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                #'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets/[ee+mumu+tautau]+Wjets+Diboson]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/Top/[single/nominal+ttbar/PS]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRPassTauID', 'StSF', prefix+"Btag", 0.1, 0.1)
        
    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/TopCR_SF_PS.root "+analysis+"/auxData/ScaleFactors/TCR_PSAll*.root\033[0m")

  elif region == 'TCR_STopISRup':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                #'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets/[ee+mumu+tautau]+Wjets+Diboson]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/Top/[single/nominal+ttbar/nominal]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRPassTauID', 'StSF', prefix+"Btag", 0.1, 0.1)
        
    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/TopCR_SF_STopISRup.root "+analysis+"/auxData/ScaleFactors/TCR_STopISRupAll*.root\033[0m")

  elif region == 'TCR_STopISRdo':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                #'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets/[ee+mumu+tautau]+Wjets+Diboson]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/Top/[single/nominal+ttbar/nominal]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRPassTauID', 'StSF', prefix+"Btag", 0.1, 0.1)
        
    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/TopCR_SF_STopISRdo.root "+analysis+"/auxData/ScaleFactors/TCR_STopISRdoAll*.root\033[0m")

  elif region == 'TCR_STopFSRup':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                #'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets/[ee+mumu+tautau]+Wjets+Diboson]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/Top/[single/nominal+ttbar/nominal]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRPassTauID', 'StSF', prefix+"Btag", 0.1, 0.1)
        
    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/TopCR_SF_STopFSRup.root "+analysis+"/auxData/ScaleFactors/TCR_STopFSRupAll*.root\033[0m")

  elif region == 'TCR_STopFSRdo':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                #'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets/[ee+mumu+tautau]+Wjets+Diboson]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/Top/[single/nominal+ttbar/nominal]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRPassTauID', 'StSF', prefix+"Btag", 0.1, 0.1)
        
    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/TopCR_SF_STopFSRdo.root "+analysis+"/auxData/ScaleFactors/TCR_STopFSRdoAll*.root\033[0m")

  elif region == 'TCR_STopPDFup':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                #'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets/[ee+mumu+tautau]+Wjets+Diboson]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/Top/[single/nominal+ttbar/nominal]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRPassTauID', 'StSF', prefix+"Btag", 0.1, 0.1)
        
    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/TopCR_SF_STopPDFup.root "+analysis+"/auxData/ScaleFactors/TCR_STopPDFupAll*.root\033[0m")

  elif region == 'TCR_STopPDFdo':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                #'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets/[ee+mumu+tautau]+Wjets+Diboson]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/Top/[single/nominal+ttbar/nominal]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRPassTauID', 'StSF', prefix+"Btag", 0.1, 0.1)
        
    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/TopCR_SF_STopPDFdo.root "+analysis+"/auxData/ScaleFactors/TCR_STopPDFdoAll*.root\033[0m")

  elif region == 'TCR_STopME':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                #'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets/[ee+mumu+tautau]+Wjets+Diboson]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/Top/[single/ME+ttbar/nominal]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRPassTauID', 'StSF', prefix+"Btag", 0.1, 0.1)
        
    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/TopCR_SF_STopME.root "+analysis+"/auxData/ScaleFactors/TCR_STopMEAll*.root\033[0m")

  elif region == 'TCR_STopPS':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                #'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets/[ee+mumu+tautau]+Wjets+Diboson]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/Top/[single/PS+ttbar/nominal]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRPassTauID', 'StSF', prefix+"Btag", 0.1, 0.1)
        
    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/TopCR_SF_STopPS.root "+analysis+"/auxData/ScaleFactors/TCR_STopPSAll*.root\033[0m")

  elif region == 'TCR_STopWTInt':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                #'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }

    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/[Zjets/[ee+mumu+tautau]+Wjets+Diboson]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/[mcReal+mcFake]/Top/[single/WTInt+single/nominal+ttbar/nominal]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name

        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutTCRPassTauID', 'StSF', prefix+"Btag", 0.1, 0.1)

    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/TopCR_SF_STopWTInt.root "+analysis+"/auxData/ScaleFactors/TCR_STopWTIntAll*.root\033[0m")


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
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal/[Wjets+Zjets+Top+Diboson]+MultiJetsFake]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/mcFakeCorrected/[Wjets+Zjets+Top+Diboson]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name

        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSS1pPassTauID', 'TauPtSF', prefix+"Btag1p", 0.12, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSS3pPassTauID', 'TauPtSF', prefix+"Btag3p", 0.12, 0.1)

        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSS1pPassTauID', 'TauPtBjetPt1SF', prefix+"Btag1p", 0.12, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSS1pPassTauID', 'TauPtBjetPt2SF', prefix+"Btag1p", 0.12, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSS1pPassTauID', 'TauPtBjetPt3SF', prefix+"Btag1p", 0.12, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSS3pPassTauID', 'TauPtBjetPt1SF', prefix+"Btag3p", 0.12, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSS3pPassTauID', 'TauPtBjetPt2SF', prefix+"Btag3p", 0.12, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSS3pPassTauID', 'TauPtBjetPt3SF', prefix+"Btag3p", 0.12, 0.1)

    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/OtherJetsSSR_SF.root "+analysis+"/auxData/ScaleFactors/OtherJetsSSRAll*.root\033[0m")

  if region == 'OtherJetsSSR_withoutTopCorr':
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
        bkgPath1 = 'bkg/{:s}/{:s}/[mcReal/[Wjets+Zjets+Top+Diboson]+MultiJetsFake]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/mcFakeCorrected/[Wjets+Zjets+Top+Diboson]'.format(channel_path, period_path)
        prefix = region+period_name+channel_name

        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSS1pPassTauID', 'TauPtSF', prefix+"Btag1p", 0.12, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSS3pPassTauID', 'TauPtSF', prefix+"Btag3p", 0.12, 0.1)

        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSS1pPassTauID', 'TauPtBjetPt1SF', prefix+"Btag1p", 0.12, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSS1pPassTauID', 'TauPtBjetPt2SF', prefix+"Btag1p", 0.12, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSS1pPassTauID', 'TauPtBjetPt3SF', prefix+"Btag1p", 0.12, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSS3pPassTauID', 'TauPtBjetPt1SF', prefix+"Btag3p", 0.12, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSS3pPassTauID', 'TauPtBjetPt2SF', prefix+"Btag3p", 0.12, 0.1)
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutSS3pPassTauID', 'TauPtBjetPt3SF', prefix+"Btag3p", 0.12, 0.1)

    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/OtherJetsSSR_SF_withoutTopCorr.root "+analysis+"/auxData/ScaleFactors/OtherJetsSSR_withoutTopCorrAll*.root\033[0m")

  elif region == 'ZCR':
    # Loop over data taking period and channels
    periods = {
                #'1516': 'c16a',
                #'17': 'c16d',
                #'18': 'c16e',
                'All': '[c16a+c16d+c16e]',
             }
    channels = {
                #'ehad': 'ehad',
                #'muhad': 'muhad',
                'lephad': '[ehad+muhad]',
              }
    
    # We use same histograms for ehad, and muhad
    # Btag/Bveto, 1p/3p appears in the name of the histograms
    for channel_name, channel_path in channels.items():
      for period_name, period_path in periods.items():
        dataPath = 'data/{:s}/{:s}'.format(channel_path, period_path)
        bkgPath1 = 'bkg/{:s}/{:s}/[mcFakeCorrected+mcReal/[Top+Wjets+Diboson+Zjets/[ee+mumu+LF]]+MultiJetsFake]'.format(channel_path, period_path)
        bkgPath2 = 'bkg/{:s}/{:s}/mcReal/Zjets/HF'.format(channel_path, period_path)
        prefix = region+period_name+channel_name
        
        #calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutZLepTauDPhi', 'VisibleMassOneBin', prefix+"Btag", 0.1, 0.1) 
        calcScaleFactor(dataPath, bkgPath1, bkgPath2, 'CutZLepTauDPhi', 'VisibleMassOneBin', prefix+"Btag", 0.2, 0.1) 
        
    print("\033[92mHadd command: \nhadd "+analysis+"/auxData/ScaleFactors/Zjets_SF.root "+analysis+"/auxData/ScaleFactors/ZCRAll*.root\033[0m")
