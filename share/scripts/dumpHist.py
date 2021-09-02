#!/usr/bin/env python2
import argparse
import os,sys
from QFramework import *
from ROOT import *



def main(args, dataset_dict, sample_dict, region_dict, hist_dict):
  # Read files
  file_path = args.inputfilepath
  INFO("Reading sample file {:s}".format(file_path))
  samples = TQSampleFolder.loadSampleFolder(file_path+":samples")
  if not samples:
    BREAK("Unable to open sample file {:s}".format(file_path))
  reader = TQSampleDataReader(samples)

  # systematic name
  sys_name = file_path.split("-")[-1]
  sys_name = sys_name.split(".")[0]
  # some hacks for systematics
  if sys_name != "NOMINAL":
    sys_name=sys_name.replace('ScaleUp', 'Scale_1up')
    sys_name=sys_name.replace('ScaleDown', 'Scale_1down')
    # 1 side syst 
    if 'JET_JER' in sys_name:
      sys_name = sys_name.replace('_1up', '')
      sys_name = sys_name.replace('__1up', '')
    sys_name_list = sys_name.split("_")
    while '' in sys_name_list:
      sys_name_list.remove('')
    sys_name_list[-1]=sys_name_list[-1].replace('high','1up')  
    sys_name_list[-1]=sys_name_list[-1].replace('low','1down') 
    sys_name_list[-1]=sys_name_list[-1].replace('1up','_1up')
    sys_name_list[-1]=sys_name_list[-1].replace('1down','_1down')
    sys_name = "_".join(sys_name_list)
    sys_name = "ATLAS_"+sys_name

  # Output file dir
  dir_out = "dumpHist/{:s}/{:s}/{:s}".format(sys_name,args.datasets,args.channel) 
  os.system('mkdir -p {:s}'.format(dir_out))

  # Dump hists reduce files !! channel campain region
  for region_name, region_path in region_dict.items():
    # Output file name
    fn_out = '{:s}_{:s}_{:s}.root'.format(args.datasets,region_name,args.channel)
    # Open output file
    f_out = TFile.Open("{:s}/{:s}".format(dir_out,fn_out),"RECREATE")
    if sys_name != "NOMINAL":
      dir_sys = f_out.mkdir(sys_name, sys_name)
    for sample_name, sample_path in sample_dict.items():
      sample_path = sample_path.format(args.channel, dataset_dict[args.datasets])
      for hist_name, hist_rename in hist_dict.items():
        hist = reader.getHistogram(sample_path, '{:s}/{:s}'.format(region_path,hist_name))
        if not hist:
          WARN("Unable to find hist {:s} : {:s}/{:s}".format(sample_path, region_path, hist_name))
          continue
        # hist name

        if 'bbH' in sample_name or 'ggH' in sample_name:
          if "Btag" in region_name:
            hist_new_name = sample_name.split("tag")[0] + '1tag' + sample_name.split("tag")[1]
          elif "Bveto" in region_name:
            hist_new_name = sample_name.split("tag")[0] + '0tag' + sample_name.split("tag")[1]
          else:
            BREAK("Unexpected region name {:s}".format(region_name))
        else:
          hist_new_name = sample_name    

#        hist_new_name += "_"+hist_rename
  
#        if sys_name != "NOMINAL":
 #         hist_new_name += "_"+sys_name
        
        hist.SetNameTitle(hist_new_name, hist_new_name)
        f_out.cd()
        if sys_name != "NOMINAL":
          dir_sys.cd()
        hist.Write()
        del hist
    f_out.Write()
    f_out.Close()
    INFO("All histograms have been dumped !")

if __name__ == "__main__":

  parser = argparse.ArgumentParser(description='Dump histogram for statistical analysis.')
  parser.add_argument('inputfilepath', metavar='FILEPATH', type=str,
            default="sampleFolders/analyzed/samples-analyzed-sampleFolders/analyzed/samples-analyzed-AHZ-lephad-SR-FF.root",
            help='sample file to be used')
  parser.add_argument('datasets', metavar='DATASETS', type=str,
            default="c16ade",
            help='datasets to be used')
  parser.add_argument('channel', metavar='CHANNEL', type=str,
            default="ehad",
            help='channel to be used')
  args = parser.parse_args()

  dataset_dict = {
    'c16a': 'c16a',
    'c16d': 'c16d',
    'c16e': 'c16e',
    'c16ade': '[c16a+c16d+c16e]',
  }

  ### The following Samples will be dumped
  sample_dict = {
    'data':         "data/{:s}/{:s}/",
    'Top':          "bkg/{:s}/{:s}/mcReal/Top/", 
    'Diboson':      "bkg/{:s}/{:s}/mcReal/Diboson/", 
    'DYZ':          "bkg/{:s}/{:s}/mcReal/Zjets/[ee+mumu]", 
    'ZplusJets':    "bkg/{:s}/{:s}/mcReal/Zjets/tautau", 
    'QCDFakes':     "bkg/{:s}/{:s}/MultiJetsFake", 
    'WJETSFakes':   "bkg/{:s}/{:s}/ddOtherJetsFake",
    'bbHlhtag125':     "sig/{:s}/{:s}/bbH/125/",
    'bbHlhtag150':     "sig/{:s}/{:s}/bbH/150/",
    'bbHlhtag200':     "sig/{:s}/{:s}/bbH/200/",
    'bbHlhtag250':     "sig/{:s}/{:s}/bbH/250/",
    'bbHlhtag300':     "sig/{:s}/{:s}/bbH/300/",
    'bbHlhtag350':     "sig/{:s}/{:s}/bbH/350/",
    'bbHlhtag400':     "sig/{:s}/{:s}/bbH/400/",
    'bbHlhtag500':     "sig/{:s}/{:s}/bbH/500/",
    'bbHlhtag600':     "sig/{:s}/{:s}/bbH/600/",
    'bbHlhtag700':     "sig/{:s}/{:s}/bbH/700/",
    'bbHlhtag800':     "sig/{:s}/{:s}/bbH/800/",
    'bbHlhtag1000':    "sig/{:s}/{:s}/bbH/1000/",
    'bbHlhtag1200':    "sig/{:s}/{:s}/bbH/1200/",
    'bbHlhtag1500':    "sig/{:s}/{:s}/bbH/1500/",
    'bbHlhtag2000':    "sig/{:s}/{:s}/bbH/2000/",
    'bbHlhtag2500':    "sig/{:s}/{:s}/bbH/2500/",
    'ggHlhtag200':     "sig/{:s}/{:s}/ggH/200/",
    'ggHlhtag250':     "sig/{:s}/{:s}/ggH/250/",
    'ggHlhtag300':     "sig/{:s}/{:s}/ggH/300/",
    'ggHlhtag350':     "sig/{:s}/{:s}/ggH/350/",
    'ggHlhtag400':     "sig/{:s}/{:s}/ggH/400/",
    'ggHlhtag500':     "sig/{:s}/{:s}/ggH/500/",
    'ggHlhtag600':     "sig/{:s}/{:s}/ggH/600/",
    'ggHlhtag700':     "sig/{:s}/{:s}/ggH/700/",
    'ggHlhtag800':     "sig/{:s}/{:s}/ggH/800/",
    'ggHlhtag1000':    "sig/{:s}/{:s}/ggH/1000/",
    'ggHlhtag1200':    "sig/{:s}/{:s}/ggH/1200/",
    'ggHlhtag1500':    "sig/{:s}/{:s}/ggH/1500/",
    'ggHlhtag2000':    "sig/{:s}/{:s}/ggH/2000/",
    'ggHlhtag2500':    "sig/{:s}/{:s}/ggH/2500/",
  }

  ### The following regions will be dumped
  region_dict = {
    "OSBtagSR"  :   'CutOSBtagLowMT',
#    "OSBtagSR3p"  :   'CutOSBtag3pLowMT',
    "OSBvetoSR"  :   'CutOSBvetoLowMT',
#    "OSBvetoSR3p"  :   'CutOSBveto3pLowMT',
    #"OSBtagVR1p"  :   'CutOSBtagVR1p',
    #"OSBtagVR3p"  :   'CutOSBtagVR3p',
    #"OSBvetoVR1p"  :   'CutOSBvetoVR1p',
    #"OSBvetoVR3p"  :   'CutOSBvetoVR3p',
  }

  ### The following hists will be dumped
  hist_dict = {
    #"BvetoTauPt"        : "BinTauPt",
    #"BtagTauPt"         : "BinTauPt",
    #"BvetoLeptonPt"     : "BinLeptonPt",
    #"BtagLeptonPt"      : "BinLeptonPt",
#    "BvetoMTTOT"        : "BinMTTOT",
 #   "BtagMTTOT"         : "BinMTTOT",
    "MTTOT"             : "MTTOT",
  }

  main(args, dataset_dict, sample_dict, region_dict, hist_dict); 
