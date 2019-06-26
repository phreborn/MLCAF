import QFramework as QF
import ROOT
from copy import deepcopy
import os
import errno

def setup_global_style():
  
  ROOT.gStyle.SetCanvasBorderMode(0); #frame color of canvas
  ROOT.gStyle.SetCanvasColor(0);  #bkrd color of canvas
  ROOT.gStyle.SetStatBorderSize(0); #frame style of stat-box 1
  
  ROOT.gStyle.SetTitleBorderSize(0);
  ROOT.gStyle.SetTitleFillColor(0);
  ROOT.gStyle.SetPadColor(0);
  ROOT.gStyle.SetPadBorderMode(0);
  
  ROOT.gStyle.SetLineWidth(3); # width of ticks
  ROOT.gStyle.SetPadTickX(1); #1:ticks on upper,2: ticks+labels on upper xaxis
  ROOT.gStyle.SetPadTickY(0);
  
  ROOT.gStyle.SetPadLeftMargin(0.18); # 0.15
  ROOT.gStyle.SetPadRightMargin(0.05);
  ROOT.gStyle.SetPadTopMargin(0.07);          
  ROOT.gStyle.SetPadBottomMargin(0.21);#0.19      
  ROOT.gStyle.SetFrameLineWidth(3);
  
  #ROOT.gStyle.SetNdivisions(505,"x");
  
  #ROOT.gStyle.SetLabelOffset(0.01,"x");
  ROOT.gStyle.SetLabelSize(0.07,"x");
  ROOT.gStyle.SetTitleSize(0.07,"x");
  ROOT.gStyle.SetTitleOffset(1.1,"x");
  
  #ROOT.gStyle.SetLabelOffset(0.01,"y");
  ROOT.gStyle.SetLabelSize(0.07,"y");
  ROOT.gStyle.SetTitleSize(0.07,"y");
  ROOT.gStyle.SetTitleOffset(1.0,"y");
  
  ROOT.gStyle.SetLabelOffset(0.01,"z");
  ROOT.gStyle.SetLabelSize(0.07,"z");
  ROOT.gStyle.SetTitleSize(0.07,"z");
  ROOT.gStyle.SetTitleOffset(1.3,"z");
  
  ROOT.gStyle.SetLineWidth(3);
  ROOT.gStyle.SetFrameLineWidth(3);
  
  ROOT.gStyle.SetPaperSize(20,26);
  ROOT.gStyle.SetTextFont(42);
  ROOT.gStyle.SetTextSize(0.05);

def setup_style(histo,xtitle,ytitle, ratio=False):
  histo.SetTitleSize(0.06,"x");
  histo.SetTitleSize(0.06,"y");
  histo.SetNdivisions(505,"x");
  histo.SetNdivisions(505,"y");
  histo.SetLabelSize(0.06,"x");
  histo.SetLabelSize(0.06,"y");
  histo.SetLabelSize(0.05,"z");
  histo.SetTitleOffset(1.1,"x"); 
  histo.SetTitleOffset(1.0,"y"); 

  histo.SetLabelFont(42,"x");
  histo.SetTitleFont(42,"x");
  histo.SetLabelFont(42,"y");
  histo.SetTitleFont(42,"y");
  histo.SetLabelFont(42,"z");
  histo.SetTitleFont(42,"z");
  histo.SetTitle("");      
  histo.SetXTitle(xtitle);
  histo.SetYTitle(ytitle);
  #histo.SetLineWidth(3);
  histo.SetLabelSize(histo.GetLabelSize("x")/1.1,"x")     
  histo.SetLabelSize(histo.GetLabelSize("y")/1.1,"y")     
  histo.SetLabelOffset(0.009,"x");

  histo.SetMarkerStyle(20);
  histo.SetMarkerSize(0.0);
  if ratio==False:
    histo.SetMinimum(0);


def get_style_ATLAS(name = "ATLAS"):
  atlasStyle = ROOT.TStyle(name,name)
  icol=0 # WHITE
  atlasStyle.SetFrameBorderMode(icol)
  atlasStyle.SetFrameFillColor(icol)
  atlasStyle.SetCanvasBorderMode(icol)
  atlasStyle.SetCanvasColor(icol)
  atlasStyle.SetPadBorderMode(icol)
  atlasStyle.SetPadColor(icol)
  atlasStyle.SetStatColor(icol)
  #atlasStyle->SetFillColor(icol) // don't use: white fill color for *all* objects
  
  # set the paper & margin sizes
  atlasStyle.SetPaperSize(20,26)
  
  # set margin sizes
  atlasStyle.SetPadTopMargin(0.05)
  atlasStyle.SetPadRightMargin(0.05)
  atlasStyle.SetPadBottomMargin(0.16)
  atlasStyle.SetPadLeftMargin(0.16)
  
  # set title offsets (for axis label)
  atlasStyle.SetTitleXOffset(1.4)
  atlasStyle.SetTitleYOffset(1.4)
  
  #use large fonts
  #Int_t font=72; # Helvetica italics
  font=42; # Helvetica
  tsize=0.05;
  atlasStyle.SetTextFont(font)
  
  atlasStyle.SetTextSize(tsize)
  atlasStyle.SetLabelFont(font,"x")
  atlasStyle.SetTitleFont(font,"x")
  atlasStyle.SetLabelFont(font,"y")
  atlasStyle.SetTitleFont(font,"y")
  atlasStyle.SetLabelFont(font,"z")
  atlasStyle.SetTitleFont(font,"z")
  
  atlasStyle.SetLabelSize(tsize,"x")
  atlasStyle.SetTitleSize(tsize,"x")
  atlasStyle.SetLabelSize(tsize,"y")
  atlasStyle.SetTitleSize(tsize,"y")
  atlasStyle.SetLabelSize(tsize,"z")
  atlasStyle.SetTitleSize(tsize,"z")
  
  # use bold lines and markers
  atlasStyle.SetMarkerStyle(20)
  atlasStyle.SetMarkerSize(1.0)
  atlasStyle.SetHistLineWidth(2)
  atlasStyle.SetLineStyleString(2,"[12 12]") # postscript dashes
  
  # get rid of X error bars (as recommended in ATLAS figure guidelines)
  atlasStyle.SetErrorX(0.0001)
  # get rid of error bar caps
  atlasStyle.SetEndErrorSize(0.)
  
  # do not display any of the standard histogram decorations
  atlasStyle.SetOptTitle(0)
  #atlasStyle.SetOptStat(1111)
  atlasStyle.SetOptStat(0)
  #atlasStyle.SetOptStat(1101)
  #atlasStyle.SetOptFit(1111)
  atlasStyle.SetOptFit(0)
  
  # put tick marks on top and RHS of plots
  atlasStyle.SetPadTickX(1)
  atlasStyle.SetPadTickY(1)
  
  atlasStyle.SetStatY(0.91)
  atlasStyle.SetStatX(0.91)                
  atlasStyle.SetStatW(0.25)

  return atlasStyle

def forceStyleATLAS():
  atlasStyle = get_style_ATLAS("ATLAS")
  print "\nApplying ATLAS style settings...\n"
  ROOT.gROOT.SetStyle("ATLAS")
  ROOT.gROOT.ForceStyle()

def mkdir_p(path):
  """create a directory, emulating the behavior of 'mkdir -p'"""
  try:
    os.makedirs(path)
  except OSError as exc: 
    if exc.errno == errno.EEXIST and os.path.isdir(path):
      pass
    else: raise

def myText(x,y,color, text, tsize = 0.035):
  """ Draw text on canvas """
  # x, y relative to canvas
  l = ROOT.TLatex() #l.SetTextAlign(12) l.SetTextSize(tsize) 
  l.SetNDC()
  l.SetTextSize(tsize)
  l.SetTextColor(color)
  l.DrawLatex(x,y,text)
  
def drawATLASLabel(x,y,text,color,textsize=0.035, extra_shift = 0):
  """ Draw ATLAS label  on canvas """
  l = ROOT.TLatex()
  l.SetNDC()
  l.SetTextFont(72)
  l.SetTextColor(color)
  l.SetTextSize(textsize)
  delx = 0.115*696*ROOT.gPad.GetWh()/(472*ROOT.gPad.GetWw())*0.035/0.05*(1+2.5*textsize+extra_shift)
  
  l.DrawLatex(x,y,"ATLAS")
  if not text == "":
    p = ROOT.TLatex()
    p.SetNDC()
    p.SetTextFont(42)
    p.SetTextColor(color)
    p.SetTextSize(textsize)
    p.DrawLatex(x+delx,y,text)

def findSmartHistRange(hists, normalized = False, includeOverflowBins = True):
  """ Return suggested hist range based on maximum of histograms """
  # first find min and max of all graphs
  if not isinstance(hists, list): hists = [hists]
  if normalized:
    for h in hists:
      if includeOverflowBins:
        h.Scale(1./h.Integral(0,h.GetXaxis().GetNbins()+1)) # include over and underflow?
      else:
        h.Scale(1./h.Integral(1,h.GetXaxis().GetNbins())) # include over and underflow?
  ymax = [h.GetMaximum() for h in hists]
  ymax = max(ymax)
  low = 0
  high = 3/2.*ymax
  return low, high
    
def drawWithRatio(plots_numerator, plots_denominator, ratio_yrange = [0.6, 1.4], ratio_ylabel = "Ratio", plot_options = "PE1", logx = False, logy = False, gridlines_in_ratio = True, normalized = False):
  
  """ 
  Draw histograms/graphs with ratio plot! Returns the canvas and the two pads.
  Because of whatever reasons you should have the following lines in your code
  after calling this function in order for it to work properly and if you want to set
  labels on the upper pad after drawing:
        c1.cd()
        pad2.Draw("same")  
        pad1.cd()
  """
  
  c0 = ROOT.TCanvas("c0", "c0", 600, 600)
  P_1 = ROOT.TPad("P_1", "P_1", 0, .3, 1, 1) # upper pad
  P_2 = ROOT.TPad("P_2", "P_2", 0, 0, 1, .3) # lower pad with ratio
  if logx:
    P_1.SetLogx()
    P_2.SetLogx()
  if logy:
    P_1.SetLogy()
    
  P_1.SetTopMargin(0.05)
  P_1.SetBottomMargin(0.02)
  P_1.SetRightMargin(0.05)
  P_1.SetLeftMargin(0.16)
    
  P_2.SetBottomMargin(0.4)
  P_2.SetTopMargin(0)
  P_2.SetRightMargin(0.05)
  P_2.SetLeftMargin(0.16)
    
  P_1.Draw("same")
  P_2.Draw("same")

  orig_labelsizes =  []
  
  if not isinstance(plots_numerator, list):
    plots_numerator = [plots_numerator] 
  if not isinstance(plots_denominator, list):
    plots_denominator = [plots_denominator] 
  for p in plots_numerator+plots_denominator:
    p.GetXaxis().SetLabelSize(0)
    orig_labelsizes.append(p.GetXaxis().GetLabelSize())

  # Draw (normal) hists/graphs in upper pad
  if logx: 
    plots_numerator[0].GetXaxis().SetMoreLogLabels();
    plots_numerator[0].GetXaxis().SetNdivisions(999, ROOT.kTRUE);
    plots_numerator[0].GetXaxis().SetNoExponent();
  P_1.cd()
  if plots_numerator[0].InheritsFrom("TGraph"): 
    plots_numerator[0].Draw("A"+plot_options+"same")
  else:
    if normalized:
      for p in plots_numerator:
        p.Scale(1./p.Integral())
    ylow, yup = findSmartHistRange(plots_numerator[0])
    plots_numerator[0].GetYaxis().SetRangeUser(ylow, yup)
    plots_numerator[0].Draw(plot_options+"same")
  for g in plots_numerator:
    g.Draw(plot_options+"same")
  for g in plots_denominator:
    g.Draw(plot_options+"same")

  # want to have numerator on top  
  plots_numerator[0].Draw(plot_options+"same")
  
  ROOT.gPad.RedrawAxis()

  # Draw ratio
  P_2.cd()
  
  denoms = [deepcopy(g) for g in plots_denominator]
  numer = [deepcopy(g) for g in plots_numerator] # numerators
  numer[0].GetXaxis().SetLabelSize(0.1)
  numer[0].GetYaxis().SetLabelSize(0.1)
    
  numer[0].GetYaxis().SetTitleOffset(0.7)
  numer[0].GetXaxis().SetLabelOffset(0.025)
  numer[0].GetYaxis().SetTitleSize(0.1)
  numer[0].GetXaxis().SetTitleSize(0.12)
  numer[0].GetYaxis().SetTitle(ratio_ylabel)

  #ratios[0].SetLineWidth(2)
  numer[0].GetYaxis().SetNdivisions(6,2,1, True)

  # if length of denominators and numerators is the same
  # it is assumed that the ratios should be:
  # nom[0] / denom[0], nom[1] / denom[1],  ...
  ratios_to_plot = []
  if len(denoms) == len(numer): 
    if numer[0].InheritsFrom("TGraph"):
      for i in range(0, len(numer)):
        ratio = deepcopy(numer[i]) 
        x1, x2 = ROOT.Double(), ROOT.Double()
        y1, y2 = ROOT.Double(), ROOT.Double()
        for j in range(ratio.GetN()):
          ratio.GetPoint(j, x1, y1)
          denoms[i].GetPoint(j, x2, y2)
          if y2 == 0: ratio.SetPoint(j, x1, 999) 
          else: ratio.SetPoint(j, x1, y1/y2)
          xerr = ratio.GetErrorX(j)
          yerr1 = ratio.GetErrorY(j)
          yerr2 = denoms[i].GetErrorY(j)
          if y2 == 0 or y1 == 0: ratio.SetPointError(j, xerr, 1)
          else: ratio.SetPointError(j, xerr, y1/y2*math.sqrt((yerr1/y1)**2 + (yerr2/y2)**2))
          ratio.SetMarkerColor(ROOT.kBlack)
          ratio.SetLineColor(ROOT.kBlack)
        ratios_to_plot.append(ratio)
    else:
      for r,d in zip(numer, denoms):
        r.Divide(r, d)
        ratios_to_plot.append(r)
  elif len(denoms) > len(numer) and len(numer) == 1:
    # If one numerator and several denominators are specified:
    if numer[0].InheritsFrom("TGraph"):
      for i in range(0, len(denoms)):
        ratio = deepcopy(numer[0]) 
        x1, x2 = ROOT.Double(), ROOT.Double()
        y1, y2 = ROOT.Double(), ROOT.Double()
        for j in range(ratio.GetN()):
          ratio.GetPoint(j, x1, y1)
          denoms[i].GetPoint(j, x2, y2)
          if y2 == 0: ratio.SetPoint(j, x1, 999) 
          else: ratio.SetPoint(j, x1, y1/y2)
          xerr = ratio.GetErrorX(j)
          yerr1 = ratio.GetErrorY(j)
          yerr2 = denoms[i].GetErrorY(j)
          if y2 == 0 or y1 == 0: ratio.SetPointError(j, xerr, 1)
          else: ratio.SetPointError(j, xerr, y1/y2*math.sqrt((yerr1/y1)**2 + (yerr2/y2)**2))
          ratio.SetMarkerColor(ROOT.kBlack)
          ratio.SetLineColor(ROOT.kBlack)
        ratios_to_plot.append(ratio)
    else:
      for d in denoms:
        # copy axis style from numer[0] to d
        QF.TQHistogramUtils.copyAxisStyle(numer[0].GetXaxis(), d.GetXaxis())
        QF.TQHistogramUtils.copyAxisStyle(numer[0].GetYaxis(), d.GetYaxis())
        ratio = deepcopy(d)
        # not handled by copy Axis Style
        ratio.GetYaxis().SetTitle(ratio_ylabel)
        ratio.Divide(numer[0], d)
        ratios_to_plot.append(ratio)
  else:
    # All other cases are not supported yet
    QF.WARN("There were no ratios to plot!")
    QF.WARN("Maybe you specified an invalid number of numerators and demoninators when executing the function" \
            "' drawWithRatio(...)'!")
    QF.WARN("Having multiple numerators and only one denominator is currently not supported. "  \
           "Please specify your config in a way that you have one numerator and several denominator " \
         "rather than the other way around'")
      
  ratios_to_plot[0].GetYaxis().SetRangeUser(ratio_yrange[0], ratio_yrange[1]-0.05)
  if logx: 
    ratios_to_plot[0].GetXaxis().SetMoreLogLabels();
    ratios_to_plot[0].GetXaxis().SetNdivisions(999, ROOT.kTRUE);
    ratios_to_plot[0].GetXaxis().SetNoExponent();
  
  if ratios_to_plot[0].InheritsFrom("TGraph"): ratios_to_plot[0].Draw(plot_options+"Asame")
  else: ratios_to_plot[0].Draw(plot_options+"same")
  for r in ratios_to_plot:
    r.Draw(plot_options+"same")
    
  # draw lines in ratio plot as grid
  if gridlines_in_ratio: 
    lines = [ROOT.TLine(ratios_to_plot[0].GetXaxis().GetXmin(), yvalue,
                        ratios_to_plot[0].GetXaxis().GetXmax(), yvalue) for \
             yvalue in map(lambda x: 0.1*x, range(int(10*ratio_yrange[0]), int(10*ratio_yrange[1])))]
    for i, l in enumerate(lines):
      l.SetLineColorAlpha(ROOT.kBlack, 0.5)
      l.SetLineWidth(1)
      l.SetLineStyle(2)
      l.Draw("same")
  else:
    l = ROOT.TLine(ratios_to_plot[0].GetXaxis().GetXmin(), 1,
                       ratios_to_plot[0].GetXaxis().GetXmax(), 1)
    l.SetLineColorAlpha(ROOT.kBlack, 0.5)
    l.SetLineWidth(1)
    l.SetLineStyle(2)
    l.Draw("same")
     
  P_1.cd()
  ROOT.gPad.RedrawAxis()
  
  for i, g in enumerate(plots_numerator+plots_denominator):
    g.GetXaxis().SetLabelSize(orig_labelsizes[i])
    
  return c0, P_1, deepcopy(P_2)


def getDistributionsAtCutsForProcessesList(processes, cuts, distributions, compare, sr):

  """
  Return list of dictionaries with all the histogram information
  """
  
  # will become a list of dictionaries
  retHistsList = []
  
  if compare == "processes":
    QF.INFO("Retrieving distributions for fixed cut and different processes...")
    for icut, cut in enumerate(cuts):
      for ivar,var in enumerate(distributions):
        hists = getDistributionAtCutForProcesses(processes, cut, var, sr)
        if len(hists) < 1:
          QF.WARN("No histograms could be retrieved when calling getDistributionAtCutForProcesses([{:s}], {:s}, {:s}, <reader>)".format(",".join([str(p) for p in processes]), cut, var))
        else:
          histDict = {}
          histDict["cuts"] = [cut for i in range(len(hists))] # define as list for consistency later on
          histDict["variables"] = [var for i in range(len(hists))] # define as list for consistency later on
          histDict["processes"] = [p for p in processes] # to convert to python list for consistency
          histDict["hists"] = hists
          retHistsList.append(histDict)
  elif compare == "cuts":
    QF.INFO("Retrieving distributions for different cuts and fixed process...")
    for process in processes:
      for var in distributions:
        hists = getDistributionAtCutsForProcess(process, cuts, var, sr)
        if len(hists) < 1:
          QF.WARN("No histograms could be retrieved when calling getDistributionAtCutsForProcess({:s}, [{:s}], {:s}, <reader>)".format(process, ",".join([str(c) for c in cuts]), var))
        else:
          histDict = {}
          histDict["cuts"] = [cut for cut in cuts]
          histDict["variables"] = [var for i in range(len(hists))]
          histDict["processes"] = [process for i in range(len(hists))]
          histDict["hists"] = hists
          retHistsList.append(histDict)
  elif compare == "variables":
    QF.INFO("Retrieving different distributions for fixed cut and fixed process...")
    for process in processes:
      for cut in cuts:
        hists = getDistributionsAtCutForProcess(process, cut, distributions, sr)
        if len(hists) < 1:
          QF.WARN("No histograms could be retrieved when calling getDistributionsAtCutForProcess({:s}, [{:s}], {:s}, <reader>)".format(process, cut, ",".join([str(v) for v in distributions])))
        else:
          histDict = {}
          histDict["cuts"] = [cut for i in range(len(hists))]
          histDict["variables"] = [var for var in distributions]
          histDict["processes"] = [process for i in range(len(hists))]
          histDict["hists"] = hists
          retHistsList.append(histDict)
  else:
    QF.BREAK("No known compare type '{:s}' in function getDistributionsAtCutsForProcessesList(...)")
    
  return retHistsList

def getDistributionAtCutForProcesses(processes, cut, distribution, sr):
  """ 
  returns a list of the same distribution at the same cut for different processes
  Usage:
  hists = getDistributionAtCutForProcesses(processes = ["bkg/[em+me]/c16a/top", "bkg/[em+me]/c16a/WW"], cut = "CutFF", distribution = "Ptll", sr = sampleReader)
  """
  hists = []
  if not isinstance(processes, list) and not isinstance(processes, ROOT.vector('TString')): processes = [processes]
  for p in processes:
    hist = sr.getHistogram(p, QF.TQFolder.concatPaths(cut, distribution))
    if not hist:
      QF.WARN("No histogram found when calling 'reader.getHistogram({:s}, {:s})'".format(p, QF.TQFolder.concatPaths(cut, distribution)))
    else:
      hist.SetName(str(p))
      hists.append(hist)
  return hists

def getDistributionAtCutsForProcess(process, cuts, distribution, sr):
  """ 
  returns a list of the same distribution for the same process at different cuts
  Usage:
  hists = getDistributionAtCutsForProcess(process = "bkg/[em+me]/c16a/top", cut = ["CutFF", "CutGGF_0jet"], distribution = "Ptll", sr = sampleReader)
  """
  hists = []
  if not isinstance(cuts, list) and not isinstance(cuts, ROOT.vector('TString')): cuts = [cuts]
  for c in cuts:
    hist = sr.getHistogram(process, QF.TQFolder.concatPaths(c, distribution))
    if not hist:
      QF.WARN("No histogram found when calling 'reader.getHistogram({:s}, {:s})'".format(process, QF.TQFolder.concatPaths(c, distribution)))
    else:
      hist.SetName(str(c))
      hists.append(hist)
  return hists

def getDistributionsAtCutForProcess(process, cut, distributions, sr):
  """ 
  returns a list of different distributions for the same process at the same cut
  Usage:
  hists = getDistributionsAtCutForProcess(process = "bkg/[em+me]/c16a/top", cut = "CutFF", distributions = ["Ptll", "MT"], sr = sampleReader)
  """
  hists = []
  if not isinstance(distributions, list) and not isinstance(distributions, ROOT.vector('TString')): processes = [distributions]
  for d in distributions:
    hist = sr.getHistogram(process, QF.TQFolder.concatPaths(cut, d))
    if not hist:
      QF.WARN("No histogram found when calling 'reader.getHistogram({:s}, {:s})'".format(process, QF.TQFolder.concatPaths(cut, d)))
    else:
      hist.SetName(str(d))
      hists.append(hist)
  return hists

def rebinHistograms(hists, rebin):
  for h in hists:
    h.Rebin(rebin)
  
def getDefaultCanvas(name = "c"):
  c = ROOT.TCanvas(name, name, 600, 600)
  return c

def setStyleLegend(legend, textsize=0.035):
  legend.SetBorderSize(0)  # no border
  legend.SetFillColor(0)   # Legend background should be white
  legend.SetTextFont(42)
  legend.SetTextSize(textsize) # Increase entry font size!


def getListOfDistinguishableColors(number = -1):
  colors = ["#000000", "#0b80c3", "#5dbe5d", "#ffad35", "#d351ff", "#36bdbd", "#7c7c7c", "#5656d7", "#9a846d", "#bcbc93"]
  colors = map(lambda x: ROOT.TColor.GetColor(x), colors)
  colors = colors + [30, 32, 34, 36, 38, 12, 14, 16, 20, 22] # random colors
  if number == -1:
    return colors
  elif number > 20:
    print "WARNING in plotUtils.py function getListOfDistinguishableColors(): Return list with only 20 colors, not {} as specified".format(number)
    return colors
  else:
    return colors[0:number]
