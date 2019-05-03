#!/usr/bin/env python2

import argparse
import os,sys
import imp, ROOT

parser = argparse.ArgumentParser(description='calculate signal strength.')
parser.add_argument('inputfilepath', metavar='FILEPATH', type=str,
          default="output/htautau_lephad_sr_2D/FakeFactor_LepElBtag_1down.root",
          help='sample file to be used')
parser.add_argument('datasets', metavar='DATASETS', type=str,
          default="c16a",
          help='datasets to be used')
parser.add_argument('channel', metavar='CHANNEL', type=str,
          default="ehad",
          help='channel to be used')
#parser.add_argument('varWanted', metavar='varName', type=str,
#          default="mvis",
#          help='var to be getten')
args = parser.parse_args()
# the alias is the 'appliation name' that will be dumped to the info tags of any
# sample folder created
alias = "plotSystematicsHistograms"
sfName = "samples" # samples or systematics
datasets = args.datasets
datasets_data = "?"
datasets_sig = "siga"
if datasets == "mc16a":
    datasets_data = "[data15*+data16*]"
    datasets_name = "data1516"
    datasets_sig = "siga"
if datasets == "mc16c" or datasets == "mc16d":
    datasets_data = "[data17*]"
    datasets_name = "data17"
    datasets_sig = "sigc"
if datasets == "mc16e":
    datasets_data = "[data18*]"
    datasets_name = "data18"
    datasets_sig = "sige"

channel = args.channel
basepath = "." #basepath in sample folder to get list of histograms from
sflist = [
          "sig/{:s}/{:s}/bbH/1000/".format(channel,datasets),
          "sig/{:s}/{:s}/ggH/1000/".format(channel,datasets),
          "data/{:s}/{:s}/".format(channel,datasets),
          "bkg/{:s}/{:s}/Top/".format(channel,datasets),
          "bkg/{:s}/{:s}/Diboson/".format(channel,datasets),
#          "bkg/{:s}/{:s}/Zee/".format(channel,datasets),
#          "bkg/{:s}/{:s}/Zmumu/".format(channel,datasets),
          "bkg/{:s}/{:s}/Zll/".format(channel,datasets),
          "bkg/{:s}/{:s}/Ztautau/".format(channel,datasets),
#          "bkg/{:s}/{:s}/QCDFakes/data/".format(channel,datasets),
#          "bkg/{:s}/{:s}/QCDFakes/mc/Diboson/".format(channel,datasets),
#          "bkg/{:s}/{:s}/QCDFakes/mc/Top/".format(channel,datasets),
#          "bkg/{:s}/{:s}/QCDFakes/mc/Zee/".format(channel,datasets),
#          "bkg/{:s}/{:s}/QCDFakes/mc/Zmumu/".format(channel,datasets),
#          "bkg/{:s}/{:s}/QCDFakes/mc/Ztautau/".format(channel,datasets),
          "bkg/{:s}/{:s}/Fakes/ISO/[data-mc/[Ztautau+Zll+Top+Diboson]]".format(channel,datasets),
#          "bkg/{:s}/{:s}/WJETSFakes/data/".format(channel,datasets),
#          "bkg/{:s}/{:s}/WJETSFakes/mc/Diboson/".format(channel,datasets),
#          "bkg/{:s}/{:s}/WJETSFakes/mc/Top/".format(channel,datasets),
#          "bkg/{:s}/{:s}/WJETSFakes/mc/Zee/".format(channel,datasets),
#          "bkg/{:s}/{:s}/WJETSFakes/mc/Zmumu/".format(channel,datasets),
#          "bkg/{:s}/{:s}/WJETSFakes/mc/Ztautau/".format(channel,datasets),
#          "bkg/{:s}/{:s}/WJETSFakes/QCD/data/".format(channel,datasets),
#          "bkg/{:s}/{:s}/WJETSFakes/QCD/mc/Diboson/".format(channel,datasets),
#          "bkg/{:s}/{:s}/WJETSFakes/QCD/mc/Top/".format(channel,datasets),
#          "bkg/{:s}/{:s}/WJETSFakes/QCD/mc/Zee/".format(channel,datasets),
#          "bkg/{:s}/{:s}/WJETSFakes/QCD/mc/Zmumu/".format(channel,datasets),
#          "bkg/{:s}/{:s}/WJETSFakes/QCD/mc/Ztautau/".format(channel,datasets),
          "bkg/{:s}/{:s}/Fakes/ID/[data-mc/[Ztautau+Zll+Top+Diboson]-ISO/data]".format(channel,datasets)
]
#sflist = ["bkg/{:s}/{:s}/?/".format(channel,datasets)]

#some definitions for what to do:

varDict = {
#"MuonPt"                                             : "MuonPt",                                              
#"MuonEta"                                            : "MuonEta",                                              
#"MuonPhi"                                            : "MuonPhi",                                              
#"TauPt"                                              : "TauPt",                                               
#"LeptonPt"                                           : "LeptonPt",                                               
#"TauMETDphi"                                              : "TauMETDphi",                                               
#"LepMETDphi"                                              : "LepMETDphi",                                               
#"bvetoMTTOT"                                               : "bvetoMTTOT",
#"btagMTTOT"                                               : "btagMTTOT",
"MTTOT"                                               : "MTtot",
#"TauEta"                                             : "TauEta",
#"TauPhi"                                             : "TauPhi",
#"SumCosDPhi"                                         : "SumCosDPhi",
#"MET"                                                : "MET",
#"MT"                                                 : "MT",
#"tauNTracks"                                         : "tauNTracks",                                         
#"taunwidetrk"                                        : "taunwidetrk",                                                                                              
}

catDict = {
"CutBtag1p" : "sr1pBtag",
"CutBtag3p" : "sr3pBtag",
"CutBveto1p" : "sr1pBveto",
"CutBveto3p" : "sr3pBveto",
#"CutWCRBtag1p" : "wcr1pBtag",
#"CutWCRBtag3p" : "wcr3pBtag",
#"CutWCRBveto1p" : "wcr1pBveto",
#"CutWCRBveto3p" : "wcr3pBveto",
#"CutVRBtag1p" : "vr1pBtag",
#"CutVRBtag3p" : "vr3pBtag",
#"CutVRBveto1p" : "vr1pBveto",
#"CutVRBveto3p" : "vr3pBveto",
"CutTCRBtag1p" : "tcr1pBtag",
"CutTCRBtag3p" : "tcr3pBtag",
#"[CutBtag1p+CutBtag3p]" : "srBtag",
#"[CutBveto1p+CutBveto3p]" : "srBveto",
#"[CutTCRBtag1p+CutTCRBtag3p]" : "tcrBtag",
}

def setHistName(path, orgHistName,inputfile):
  pathlist = path.split("/")
  print "pathlist",pathlist
  histname = orgHistName.Data();
  print histname
  namelist = histname.split("/")
  print namelist
  distname = namelist.pop()
  print distname
  print inputfile
  if inputfile != "NOMINAL":
    inputfilenamelist=inputfile.split("_")
    inputfilenamevar=inputfilenamelist[-1]
    inputfilename=inputfile.replace("_"+inputfilenamevar, "")
  #if "mvis" not in distname : 
  #  print "not", distname
  #  return ""
  #if "CutWControl" not in namelist[0] : 
  #  print "not", namelist[0]
  #  return ""
  
  histOutName=""
  histOutName0=""
  histOutName0=datasets+"_"
  histOutName0+=pathlist[0]+"_"
  if ( pathlist[0] == "bkg" or pathlist[0] == "sig" ) and pathlist[0] != "data":
#    if pathlist[0] == "{:s}".format(datasets_sig):
#        histOutName0+="{:s}_".format(datasets)
#    else:
#        histOutName0+=pathlist[0]+"_"
#  if  pathlist[0] == "{:s}".format(datasets) and pathlist[0] != "data":
#    histOutName0+=pathlist[0]+"_"
#    if pathlist[2] != "QCDFakes" and pathlist[2] != "WJETSFakes": 
    if pathlist[3] == "Zll":
        histOutName+="DYZ"
    elif pathlist[3] == "Ztautau":
        histOutName+="ZplusJets"
    if pathlist[3] == "Fakes":
        if pathlist[4] == "ISO":
            histOutName+="QCDFakes"
        elif pathlist[4] == "ID":
            histOutName+="WJETSFakes"
    elif pathlist[3] == "bbH" or pathlist[3] == "ggH":
        histOutName+=pathlist[3].replace("H", "Hlh")
        histOutName+=pathlist[4]
    else:
        histOutName+=pathlist[3]
#    elif pathlist[2] == "QCDFakes" and pathlist[3] == "data":
#       histOutName+=pathlist[2]+"_"+pathlist[3]
#    elif pathlist[2] == "QCDFakes" and pathlist[3] == "mc":
#       histOutName+=pathlist[2]+"_"+pathlist[3]+"_"+pathlist[4]
#    elif pathlist[2] == "WJETSFakes" and pathlist[3] == "data":
#       histOutName+=pathlist[2]+"_"+pathlist[3]
#    elif pathlist[2] == "WJETSFakes" and pathlist[3] == "mc":
#       histOutName+=pathlist[2]+"_"+pathlist[3]+"_"+pathlist[4]
#    elif pathlist[2] == "WJETSFakes" and pathlist[3] == "QCD":
#       if pathlist[4] == "data":
#          histOutName+=pathlist[2]+"_"+pathlist[3]+"_"+pathlist[4]
#       elif pathlist[4] == "mc": 
#          histOutName+=pathlist[2]+"_"+pathlist[3]+"_"+pathlist[4]+"_"+pathlist[5] 
  else:
#    histOutName0+=pathlist[0]+"_"
    histOutName+="data"

  if pathlist[1] == "ehad":
    Channel = "ElHad"
  elif pathlist[1] == "muhad":
    Channel = "MuHad"

  if "TCR" in namelist[0]:
    Channel+="Tcr"

  if "Btag" in namelist[0]:
    Tags = "1tag0jet"
  elif "Bveto" in namelist[0]:
    Tags = "0tag0jet"

  #if pathlist[0] == "data":
  #  histOutFileName=histOutName+"_"
  #else:
  #  histOutFileName=histOutName0+histOutName+"_"
  histOutFileName=histOutName0+histOutName+"_"

  histOutFileName+=catDict[ namelist[0] ]
  histOutFileName+="_"+pathlist[1]+"_"
  histOutFileName+=varDict[distname]

  histOutName=histOutName+"_"+Tags+"_0ptv_"+Channel+"_"+varDict[distname]
  if inputfile != "NOMINAL":
    histOutName+="_ATLAS_"+inputfilename+"__"+inputfilenamevar

  return [histOutName, histOutFileName]


def findHist(path, orgHistName):
  pathlist = path.split("/")
  histname = orgHistName.Data();
  print histname
  namelist = histname.split("/")
  distname = namelist.pop()
  print namelist
  print distname

  print "has var",varDict.has_key(distname)
  print "has cat",catDict.has_key(namelist[0])

  if varDict.has_key(distname) is False : return 0
  if catDict.has_key(namelist[0]) is False : return 0

  #if histWanted not in distname :
  #  return 0

  return 1

def main(args):
  # print a welcome message
  print(TQStringUtils.makeBoldWhite("dump histo"))
  
  # open the samplefile
  filepath=TString(args.inputfilepath)

  # get the input file name
  s_file = args.inputfilepath
  inputfilenamelist=s_file.split("/")
  inputfilename=inputfilenamelist[-1]
  inputfilelist=inputfilename.split(".")
  inputfilebasename=inputfilelist[0]
  inputfilebasenamelist=inputfilebasename.split("-")
  inputfile=inputfilebasenamelist[-1]

  os.system('mkdir -p dumpHist/{:s}/{:s}/{:s}'.format(inputfile,datasets,channel))

  dir_sys = ROOT.TDirectory

  #outfilepath = TString(args.outputfilepath)
  INFO("reading sample file '{:s}' ".format(filepath))
  samples = TQSampleFolder.loadSampleFolder(filepath+TString(":")+sfName)
  if not samples:
    BREAK("unable to open sample file '{:s}' - please check the filepath!".format(filepath))
  tags = TQTaggable()
  tags.setTagBool("ensureDirectory",True)
  tags.setTagString("scaleScheme",".default")
  reader = TQSampleDataReader(samples)
  hlist = reader.getListOfHistogramNames()
  for (index,path) in enumerate(sflist):
    for hname in hlist:
      if hname is None: continue 
      histname = hname.GetString().Data();
      print histname.split("/")
      namelist = histname.split("/")
      print histname
      distname = namelist.pop()
      print distname
      pathlist = path.split("/")
      print(pathlist)

      if pathlist[0] == "data" and inputfile != "NOMINAL":
          print("no systematics for data")
          continue
    
      if findHist(path, hname.GetString()) is 0 : 
        print " not the wanted histogram "
        continue

      #if "mvis" not in distname : 
      #  print "not", distname
      #  continue

      #if "CutWControl" not in namelist[0] : 
      #  print "not", namelist[0]
      #  continue

      hist = reader.getHistogram(path,hname.GetString(),tags)

      histOutName=setHistName(path, hname.GetString(),inputfile )
      print histOutName
      hist.SetNameTitle( histOutName[0], histOutName[0] )
     
      OutputSystFolderNameListFull = histOutName[0].split("_")
      OutputSystFolderNameList = OutputSystFolderNameListFull[5:]
      print(OutputSystFolderNameList)
      #OutputSystFolderName = OutputSystFolderNameList[-5]+"_"+OutputSystFolderNameList[-4]+"_"+OutputSystFolderNameList[-3]+"__"+OutputSystFolderNameList[-1]
      OutputSystFolderName = "_".join(OutputSystFolderNameList)
      print OutputSystFolderName
 
      if hist is None: continue
      #do to hist what ever you want :)
      hist.Print()

      ouptfilename = histOutName[1].replace("?","X")
      ouptfilename += ".root"
      outfile = TFile.Open( "dumpHist/{:s}/{:s}/{:s}/".format(inputfile,datasets,channel)+ouptfilename,"RECREATE")
      #outfile = TFile.Open(outfilepath.Data(),"RECREATE")
 
      if inputfile != "NOMINAL" :
        dir_sys = outfile.mkdir( OutputSystFolderName, OutputSystFolderName )

      outfile.cd()
      if inputfile != "NOMINAL" :
        dir_sys.cd()
      hist.Write()
      del hist
      outfile.Write()
      outfile.Close()



if __name__ == "__main__":
  # parse the CLI arguments
#  parser = argparse.ArgumentParser(description='calculate signal strength.')
#  parser.add_argument('inputfilepath', metavar='FILEPATH', type=str,
#            default="output/htautau_lephad_sr_2D/FakeFactor_LepElBtag_1down.root",
#            help='sample file to be used')
#  parser.add_argument('outputfilepath', metavar='FILEPATH', type=str,
#            default="myHistograms.root",
#            help='output file to be used')
#  parser.add_argument('varWanted', metavar='varName', type=str,
#            default="mvis",
#            help='var to be getten')
#  args = parser.parse_args()

  from QFramework import *
  from ROOT import *
  TQLibrary.getQLibrary().setApplicationName(alias);
  main(args); 
