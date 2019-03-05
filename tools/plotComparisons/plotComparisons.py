#!/usr/bin/env python
import argparse
import sys
import QFramework as QF
from CommonAnalysisHelpers import common
toolsPath = common.findConfigPath("../tools")
sys.path.append(toolsPath)
from plotUtils import setup_style, get_style_ATLAS, drawWithRatio, findSmartHistRange, myText, drawATLASLabel, mkdir_p
from copy import deepcopy
import ROOT

##############################################################################
##############################################################################
#
# This tool allows to make quick comparison plots between different processes at different
# cut stages and for several observables. It uses the general concepts of patches and tags
# in CAF including a config file for steering this script.
# 
# In order to make a new plot comparison you need to do the following:
#   -- Adapt the config file 'plotComparisons.cfg' (or write a new one) to your needs
#   -- Adapt the style file 'style-plotComparisons.txt' (or write a new one) to your needs
#   -- Run this script with:
#       'python plotComparisons.py <plotCategory>', 
#       where <plotCategory> specifies the section in your config file.
#
# Note, that you can also write your own config and style files and point to them accordingly.
# (For pointing to a new config file please specify the '--config' argument when running this script.
# For pointing to a new style file please adapt the 'patches' tag in your config.)
# 
##############################################################################
##############################################################################

# --------------------------------------------------------
# Some useful functions
# --------------------------------------------------------

def getCustomAxisLabel(var, tags):
  if tags.hasTag("xlabel."+var):
    xlabel = tags.getTagStandardStringDefault("xlabel."+var, "No Label")
    return xlabel
  else:
    return None

def getLegendEntry(samplepath, reader):
  f = reader.getListOfSampleFolders(samplepath).At(0) # if [em+me] is specified read label from one channel (needs to be the same)
  if not f: QF.BREAK("Something is wrong! Check your configuration!")
  leg_label = ROOT.TString()
  if not f.getTagString("label", leg_label):
    QF.WARN("No label found for sample with path '{:s}'. Please specify one with the 'label' tag in your style configuration.".format(f.getPath()))
    return "No label"
  return str(leg_label)

def setAxesRange(hist, var, tags):
  if tags.hasTag("xrange."+var+".0") and tags.hasTag("xrange."+var+".1"):
    xlow, xhigh = ROOT.Double(), ROOT.Double()
    tags.getTagDouble("xrange."+var+".0", xlow)
    tags.getTagDouble("xrange."+var+".1", xhigh)
    hist.GetXaxis().SetRangeUser(xlow, xhigh)
  else:
    pass
  
def rebinHistogram(hist, var, tags):
  if tags.hasTag("rebin."+var):
    hist.Rebin(tags.getTagIntegerDefault("rebin."+var, 1))
  else:
    pass

# ----------------------------------------------------
# Main
# ----------------------------------------------------

def main(args):

  QF.INFO("Running script plotComparisons.py")

  # -------------------------------------------------------
  # Reading config
  
  parser = common.createConfigParser()
  configpath = ROOT.TString(common.findConfigPath(args.config))
  parsed = parser.read(configpath.Data())
  if not parsed:
    QF.BREAK("Configuration file with path '{:s}' could not be read! Exiting...".format(configpath))
  if not parser.has_section(args.plotCategory):
    QF.BREAK("No section with name '{:s}' found in configuration file! Exiting...".format(args.plotCategory))

  tags = QF.TQTaggable()
  
  # Tags in section 'common' will be overwritten by more specific sections
  if parser.has_section("common"):
    common.getTagsFromConfigParser(parser,tags, "common")

  # Get tags from specific plot category
  common.getTagsFromConfigParser(parser, tags, args.plotCategory)
  inputFilePath = ROOT.TString()
  if tags.getTagString("input", inputFilePath):
    inputFilePath = common.findConfigPath(inputFilePath)
    samples = QF.TQSampleFolder.loadSampleFolder(inputFilePath)
  else:
    QF.BREAK("Please specify an input sample folder!")
  styleFilePath = tags.getTagStringDefault("patches", common.findConfigPath("../tools/plotComparisons/style-plotComparisons.txt"))
  common.patchSampleFolder([styleFilePath], samples)
  reader = QF.TQSampleDataReader(samples)
  
  # -----------------------------------------------------
  # Style, label and legend settings
  
  atlasStyle = get_style_ATLAS("ATLAS")
  print "\nApplying ATLAS style settings...\n"
  ROOT.gROOT.SetStyle("ATLAS")
  ROOT.gROOT.ForceStyle()
  
  c1 = ROOT.TCanvas("can","can",600,600)
  
  ypos1D = 1 - ROOT.gStyle.GetPadTopMargin() - 0.08
  xpos1D = ROOT.gStyle.GetPadLeftMargin()+0.03
  textsize = 0.04
  
  labelSizeScale = 1
  if tags.getTagBoolDefault("drawRatio", False):
    labelSizeScale = 1.5
  
  label = ["#sqrt{#it{s}} = 13 TeV"]
  additional_labels = []
  if not len(tags.getTagVString("label")) == 0:
    for ilabel in tags.getTagVString("label"):
      label.append(str(ilabel))
      
  legXlow = tags.getTagDoubleDefault("geometry.legend.xlow", 0.52)
  legXhigh = tags.getTagDoubleDefault("geometry.legend.xhigh", 0.85)
  legYlow = tags.getTagDoubleDefault("geometry.legend.ylow", 0.7)
  legYhigh = tags.getTagDoubleDefault("geometry.legend.yhigh", ypos1D)
  leg_cl = ROOT.TLegend(legXlow,legYlow,legXhigh,legYhigh)
  leg_cl.SetBorderSize(0)
  leg_cl.SetFillStyle(0)
  leg_cl.SetTextFont(42)
  leg_cl.SetTextSize(tags.getTagDoubleDefault("legend.textSize", 0.04)*labelSizeScale)

  #-----------------------------------------------------------------------
  # Start looping
  
  # Loop over cuts ---->
  for cut in tags.getTagVString("cuts"):
    QF.INFO("Produce histograms at cut: "+str(cut))
    
    # Loop over variables ---->
    if len(tags.getTagVString("observables")) == 0: QF.BREAK("Please specify observables to plot with the tag 'observables;!")
    for var in tags.getTagVString("observables"):
      QF.INFO("Plot variable: "+str(var))
      histograms=[]
      legentries=[]
      QF.INFO("For processes: "+", ".join(map(str,tags.getTagVString("samplePaths"))))
      
      # Loop over processes ---->
      if len(tags.getTagVString("samplePaths")) == 0: QF.BREAK("Please specifiy processes to plot with the tag 'samplePaths'!")
      for proc in tags.getTagVString("samplePaths"):
        commonPath = ROOT.TString()
        if tags.getTagString("commonPath", commonPath):
          samplepath = QF.TQFolder.concatPaths(commonPath, proc)
        else:
          samplepath = proc
        processname = proc
          
        # get Histogram
        hist = reader.getHistogram(samplepath,QF.TQFolder.concatPaths(cut,var))
        if not hist:
          QF.WARN("histogram with definition 'getHistogram({:s},{:s})' not found! Skipping process!".format(samplepath, QF.TQFolder.concatPaths(cut,var)))
          continue
        
        # Set labels
        xlabel = hist.GetXaxis().GetTitle()
        custom_xlabel = getCustomAxisLabel(var, tags)
        if custom_xlabel:
          xlabel = custom_xlabel
        if tags.getTagBoolDefault("normed", True):
          hist.Scale(1./hist.Integral())
          setup_style(hist, xlabel, "Normalized Events" )
        else:
          setup_style(hist, xlabel, "Events" )

        # rebin histogram (if specified in dictionary 'rebins')
        rebinHistogram(hist, var, tags)

        # set custom axis range if specified in dictionary 'axesranges'
        setAxesRange(hist, var, tags)
          
        # Get max of hists
        maxVal = -999.9
        if hist.GetMaximum() > maxVal:
          maxVal=hist.GetMaximum()
        
        # get legend name for process
        leg_cl.AddEntry(hist, getLegendEntry(samplepath, reader), "l")
        
        # Add histogram to list
        histograms.append(hist)
        
      # <---- End loop over processes
      if len(histograms) < 1:
        continue

      logX = tags.getTagBoolDefault("logX", False)
      logY = tags.getTagBoolDefault("logY", False)
      if len(histograms) == 2 and tags.getTagBoolDefault("drawRatio", False):
        ratio_yrange = [0.5, 2]
        if tags.hasTag("ratio.yrange.0"): ratio_yrange[0] = tags.getTagVDouble("ratio.yrange")[0]
        if tags.hasTag("ratio.yrange.1"): ratio_yrange[1] = tags.getTagVDouble("ratio.yrange")[1]
        ratio_ylabel = tags.getTagStandardStringDefault("ratio.ylabel", "Nominal / Variation")
        c1,pad1,pad2 = drawWithRatio(histograms[0], histograms[1], ratio_yrange = ratio_yrange, ratio_ylabel = ratio_ylabel, plot_options = "histE", logx = logX, logy = logY, gridlines_in_ratio = True)
        c1.cd()
        pad2.Draw("same")  
        pad1.cd()
      else:
        histograms[0].SetMaximum(1.5*maxVal)
        c1.SetLogx(logX)
        c1.SetLogy(logY)
        histograms[0].Draw("histE")
        for i in range(1,len(histograms)):
          histograms[i].Draw("histe same") 
        histograms[0].Draw("histesame")

      drawATLASLabel(xpos1D , ypos1D, "Internal", ROOT.kBlack, textsize*1.2*labelSizeScale, 0.25)
      shift = 0.06*(1+(labelSizeScale-1)/2.)
      for i, l in enumerate(label):
        myText(xpos1D, (ypos1D-shift)-i*shift, ROOT.kBlack, l, textsize*labelSizeScale)

      leg_cl.Draw()

      outputfolder = tags.getTagStringDefault("outputFolder", "results/1DShapePlots")
      mkdir_p(outputfolder.Data())
      histname = str(cut)+"_"+str(var)
      outPath = '{dirct}/{la}'.format(dirct=outputfolder, la=histname)
      outPath = ROOT.TString(QF.TQPathManager.getPathManager().getTargetPath(outPath))
      
      plotformat = ["pdf", "png"]
      if tags.hasTag("plotFormat.0"): plotformat = tags.getTagVString("plotFormat")
      for pf in plotformat:
        c1.SaveAs(outPath.Data()+"."+pf)
      c1.Clear()
      leg_cl.Clear()

if __name__ == "__main__":
  # parse the CLI arguments
  parser = argparse.ArgumentParser(description='make a shape plots for processes shapes')

  parser.add_argument("plotCategory", type=str,  help="Plots that should be produced (section in config file)")
  parser.add_argument("--config", type=str, default=common.findConfigPath("../tools/plotComparisons/plotComparisons.cfg"), help="Configuration file to be read (please provide path relative to share or absolute path)")
  args = parser.parse_args()

  # setup ROOT
  import ROOT
  ROOT.gROOT.SetBatch(True)
  QF.TQLibrary.getQLibrary().setApplicationName("1D shape plots per process");

  # call the main function
  main(args);

  
