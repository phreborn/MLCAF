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
    BREAK("Unable to open sample file {:s}".formath(file_path))
  
  reader = TQSampleDataReader(samples)

  # systematic name
  sys_name = file_path.split("-")[-1]
  sys_name = sys_name.split(".")[0]
  # some hacks for systematics
  if sys_name != "NOMINAL":
    sys_name=sys_name.replace('ScaleUp', 'Scale_1up')
    sys_name=sys_name.replace('ScaleDown', 'Scale_1down')
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
        hist_new_name = sample_name
        if "Btag" in region_name:
          hist_new_name += "_1tag0jet_0ptv_"
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
        if "tcr" in region_name:
          hist_new_name += "Tcr"

        hist_new_name += "_"+hist_rename
  
        if sys_name != "NOMINAL":
          hist_new_name += "_"+sys_name
        
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
            default="sampleFolders/analyzed/samples-analyzed-htautau_lephad_sr-TAUS_TRUEHADTAU_SME_TES_MODEL_1up.root",
            help='sample file to be used')
  parser.add_argument('datasets', metavar='DATASETS', type=str,
            default="c16a",
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
    'Top':          "bkg/{:s}/{:s}/Top/", 
    'Diboson':      "bkg/{:s}/{:s}/Diboson/", 
    'DYZ':          "bkg/{:s}/{:s}/Zll/", 
    'ZplusJets':    "bkg/{:s}/{:s}/Ztautau/", 
    'QCDFakes':     "bkg/{:s}/{:s}/Fakes/ISO/[data-mc]", 
    'WJETSFakes':   "bkg/{:s}/{:s}/Fakes/ID/[data-[mc+ISO/[data-mc]]]", 
    'bbHlh200':     "sig/{:s}/{:s}/bbH/200/",
    'bbHlh300':     "sig/{:s}/{:s}/bbH/300/",
    'bbHlh600':     "sig/{:s}/{:s}/bbH/600/",
    'bbHlh1000':    "sig/{:s}/{:s}/bbH/1000/",
    'bbHlh1500':    "sig/{:s}/{:s}/bbH/1500/",
    'bbHlh2000':    "sig/{:s}/{:s}/bbH/2000/",
    'bbHlh2500':    "sig/{:s}/{:s}/bbH/2500/",
    'ggHlh200':     "sig/{:s}/{:s}/ggH/200/",
    'ggHlh300':     "sig/{:s}/{:s}/ggH/300/",
    'ggHlh600':     "sig/{:s}/{:s}/ggH/600/",
    'ggHlh1000':    "sig/{:s}/{:s}/ggH/1000/",
    'ggHlh1500':    "sig/{:s}/{:s}/ggH/1500/",
    'ggHlh2000':    "sig/{:s}/{:s}/ggH/2000/",
    'ggHlh2500':    "sig/{:s}/{:s}/ggH/2500/",
  }

  ### The following regions will be dumped
  region_dict = {
    #"sr1pBtag"  :   'CutBtag1p',
    #"sr3pBtag"  :   'CutBtag3p',
    #"sr1pBveto"  :   'CutBveto1p',
    #"sr3pBveto"  :   'CutBveto3p',
    #"tcr1pBtag"  :  'CutTCRBtag1p',
    #"tcr3pBtag"  :  'CutTCRBtag3p',
    "vr1pBtag"  :   'CutVRBtag1p',
    "vr3pBtag"  :   'CutVRBtag3p',
    "vr1pBveto"  :   'CutVRBveto1p',
    "vr3pBveto"  :   'CutVRBveto3p',
  }

  ### The following hists will be dumped
  hist_dict = {
    #"bvetoTauMETDphi"  : "TauMETDphi",
    #"btagTauMETDphi"   : "TauMETDphi",
    #"bvetoLepMETDphi"  : "LepMETDphi",
    #"btagLepMETDphi"   : "LepMETDphi",
    "bvetoTauPt"        : "TauPt",
    "btagTauPt"         : "TauPt",
    "bvetoMTTOT"        : "MTTOT",
    "btagMTTOT"         : "MTTOT",
    #"bvetoLeptonPt"    : "LeptonPt",
    #"btagLeptonPt"     : "LeptonPt",
    #"MTTOT"            : "MTTOT",
  }

  main(args, dataset_dict, sample_dict, region_dict, hist_dict); 
