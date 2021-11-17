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
  sys_name = file_path.split("-")[-1].split(".")[0]

  sys_name_list = []
  if sys_name != "NOMINAL":
  # Open the variation file
    with open(args.variation_file) as f:
      variation_names = f.readlines()
      #variation_names = [i.split()[0] for i in variation_names if i.startswith('#') or not len(i)]
    for i in variation_names:
      i = i.strip()
      if not len(i) or i.startswith('#'):
        continue
      if i.split()[-1] == 'one':
        INFO(i)
        sysName = i.split()[0]
        INFO(sysName)
        #if '1up' in sysName:
        #  sysName = sysName.split('_1up')[0]
        #elif '1down' in sysName:
        #  sysName = sysName.split('_1down')[0]
        #INFO(sysName)
        sys_name_list.append('ATLAS_'+sysName)
      elif i.split()[-1] == 'two':
        INFO(i)
        sysName = i.split()[0]
        INFO(sysName)
        sys_name_list.append('ATLAS_'+sysName+'_1up')
        sys_name_list.append('ATLAS_'+sysName+'_1down')
    #sys_name_list = ['ATLAS_'+i+'_1down' for i in variation_names]
    #sys_name_list.extend(['ATLAS_'+i+'_1up' for i in variation_names])

  else:
   sys_name_list = [args.channel]

  #Temp change (not sure if stll needed
  """
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

  """

  # Output file dir
  dir_out = "dumpHist_{:s}_l{:s}/{:s}/{:s}/{:s}".format(args.version,args.coupling,sys_name,args.datasets,args.channel) 
  os.system('mkdir -p {:s}'.format(dir_out))

  # Dump hists reduce files !! channel campain region
  for region_name, region_path in region_dict.items():
    # Output file name
    fn_out = '{:s}_{:s}_{:s}.root'.format(args.datasets,region_name,args.channel)
    # Open output file
    f_out = TFile.Open("{:s}/{:s}".format(dir_out,fn_out),"RECREATE")

    for sys in sys_name_list:
      
      if sys_name != 'NOMINAL':
        channel = args.channel + sys.split("ATLAS")[1]
        INFO(channel)
        if 'JET_JER' in sys:
          sys = sys.replace("_1up", "")
        if "1up" in sys:
          dir_sys = f_out.mkdir(sys.replace("1up", "_1up"), sys.replace("1up", "_1up"))
        elif "1down" in sys:
          dir_sys = f_out.mkdir(sys.replace("1down", "_1down"), sys.replace("1down", "_1down"))
        else:
          dir_sys = f_out.mkdir(sys, sys)

      for sample_name, sample_path in sample_dict.items():
        if sample_name == 'data':
          sample_path = sample_path.format(args.channel, dataset_dict[args.datasets])
        else:
          if sys_name != 'NOMINAL':
            if 'LQ' in sample_name:
              sample_path = sample_path.format(channel, dataset_dict[args.datasets], args.coupling)
            else:
              sample_path = sample_path.format(channel, dataset_dict[args.datasets])
          else:
            if 'LQ' in sample_name:
              sample_path = sample_path.format(args.channel, dataset_dict[args.datasets], args.coupling)
            else:
              sample_path = sample_path.format(args.channel, dataset_dict[args.datasets])

        for hist_name, hist_rename in hist_dict.items():
          hist = reader.getHistogram(sample_path, '{:s}/{:s}'.format(region_path,hist_name))
          if not hist:
            WARN("Unable to find hist {:s} : {:s}/{:s}".format(sample_path, region_path, hist_name))
            continue

          # hist name
          hist_new_name = sample_name
          if "Btag" in region_name:
            hist_new_name += "_1tag0jet_0ptv_"
            if "Low" in region_name:
              hist_new_name += "lowbjetpt_"
            elif "High" in region_name:
              hist_new_name += "highbjetpt_"
          elif "Bveto" in region_name:
            hist_new_name += "_0tag0jet_0ptv_"
          else:
            BREAK("Unexpcted region name {:s}".format(region_name))

          if args.channel == "ehad":
            hist_new_name += "ElHad"
          elif args.channel == "muhad":
            hist_new_name += "MuHad"
          else:
            BREAK("Unexpected channel {:s}".format(args.channel))
          if "TCR" in region_name:
            hist_new_name += "TCR"
          if "VR" in region_name:
            hist_new_name += "VR"

          hist_new_name += "_"+hist_rename

          if sys_name != "NOMINAL":
            hist_new_name += "_"+sys_name


          hist.SetNameTitle(hist_new_name, hist_new_name)
          f_out.cd()
          if sys_name != 'NOMINAL':
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
  parser.add_argument('variation_file', metavar='VARFILE', type=str,
            default = None,
            help = 'File with sys variations')
  parser.add_argument('version', metavar='VERSION', type=str,
            default="st300",
            help='version to be used')
  parser.add_argument('coupling', metavar='COUPLING', type=str,
            default="1_0",
            help='coupling to be used')
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
    'WJETSFakes':   "bkg/{:s}/{:s}/[mcReal/Wjets+mcFakeCorrected/[Wjets+Zjets+Top+Diboson]]",
    'LQlh900'    :  "sig/{:s}/{:s}/LQ/M900_l{:s}/",
    'LQlh2500'   :  "sig/{:s}/{:s}/LQ/M2500_l{:s}/",
  }

  ### The following regions will be dumped
  region_dict = {
    "OSBtagSRLowBJetPt"   :   "CutOSBtagLowBJetPt",
    "OSBtagSRHighBJetPt"  :   "CutOSBtagHighBJetPt",
  }

  ### The following hists will be dumped
  hist_dict = {
    "TauPt"     : "TauPt",
    "LeptonPt"  : "LeptonPt",
    "BjetPt"    : "BjetPt",
    "MET"       : "MET",
    "St"        : "St",
    "St_fineBin"        : "StFineBin",
  }

  main(args, dataset_dict, sample_dict, region_dict, hist_dict); 
