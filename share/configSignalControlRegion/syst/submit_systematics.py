#!/usr/bin/env python

import os
import sys
import glob
import argparse
from JobHandler import LocalJobHandler

# The results of some jobs will not be changed for the systematics, these jobs will be copied from the following dir
s_standard_dir='batchOutput/unmerged_SR'
s_nominal_dir='batchOutput/unmerged_SRsys_NOMINAL'
# Cofiguration for the systematic jobs
s_config_path='configSignalControlRegion/syst/htautau_lephad_sr_sys.cfg'
s_common_config_path='configCommon/htautau_lephad_common.cfg'
# Input MC files for the systematic jobs (Input data files are not changed)
s_sys_file_path='configCommon/htautau_lephad_common_campaigns_sys.cfg'
# list of all systematics, comment out the ones you don't want to run:
# lets instead separate out the systematic types into sublists, and append them to the grand list on request
# so first initialize the grand list of systematics
# fakevars:     12(24)
# isovars:      6(12)
# topvars:      NEW: 4(6)   2 one-side | OLD: 2(2) 2 one-side
# weightvars:   36(72)
# treevars:     35(60) 10 one-side 
l_fakevars=[
['fakevar',   'FakeFactor_WjetsBtag1p_1up'],
['fakevar',   'FakeFactor_WjetsBtag1p_1down'],
['fakevar',   'FakeFactor_WjetsBtag3p_1up'],
['fakevar',   'FakeFactor_WjetsBtag3p_1down'],
['fakevar',   'FakeFactor_WjetsBveto1p_1up'],
['fakevar',   'FakeFactor_WjetsBveto1p_1down'],
['fakevar',   'FakeFactor_WjetsBveto3p_1up'],
['fakevar',   'FakeFactor_WjetsBveto3p_1down'],

["fakevar",   "FakeFactor_WjetsReweight_ElHadBveto1p_1up"],
["fakevar",   "FakeFactor_WjetsReweight_ElHadBveto1p_1down"],
["fakevar",   "FakeFactor_WjetsReweight_ElHadBveto3p_1up"],
["fakevar",   "FakeFactor_WjetsReweight_ElHadBveto3p_1down"],
["fakevar",   "FakeFactor_WjetsReweight_ElHadBtag1p_1up"],
["fakevar",   "FakeFactor_WjetsReweight_ElHadBtag1p_1down"],
["fakevar",   "FakeFactor_WjetsReweight_ElHadBtag3p_1up"],
["fakevar",   "FakeFactor_WjetsReweight_ElHadBtag3p_1down"],
["fakevar",   "FakeFactor_WjetsReweight_MuHadBveto1p_1up"],
["fakevar",   "FakeFactor_WjetsReweight_MuHadBveto1p_1down"],
["fakevar",   "FakeFactor_WjetsReweight_MuHadBveto3p_1up"],
["fakevar",   "FakeFactor_WjetsReweight_MuHadBveto3p_1down"],
["fakevar",   "FakeFactor_WjetsReweight_MuHadBtag1p_1up"],
["fakevar",   "FakeFactor_WjetsReweight_MuHadBtag1p_1down"],
["fakevar",   "FakeFactor_WjetsReweight_MuHadBtag3p_1up"],
["fakevar",   "FakeFactor_WjetsReweight_MuHadBtag3p_1down"],

["fakevar",   "FakeFactor_ExtraSysBveto1p_1down"],
["fakevar",   "FakeFactor_ExtraSysBveto1p_1up"],
["fakevar",   "FakeFactor_ExtraSysBveto3p_1down"],
["fakevar",   "FakeFactor_ExtraSysBveto3p_1up"],
["fakevar",   "FakeFactor_ExtraSysBtag1p_1down"],
["fakevar",   "FakeFactor_ExtraSysBtag1p_1up"],
["fakevar",   "FakeFactor_ExtraSysBtag3p_1down"],
["fakevar",   "FakeFactor_ExtraSysBtag3p_1up"],
]

l_isovars=[
['isovar',   'FakeFactor_LepElBveto_1up'],
['isovar',   'FakeFactor_LepElBveto_1down'],
['isovar',   'FakeFactor_LepElBtag_1up'],
['isovar',   'FakeFactor_LepElBtag_1down'],
['isovar',   'FakeFactor_LepMuBveto_1up'],
['isovar',   'FakeFactor_LepMuBveto_1down'],
['isovar',   'FakeFactor_LepMuBtag_1up'],
['isovar',   'FakeFactor_LepMuBtag_1down'],
['isovar',   'FakeFactor_QCDReweight_MuHadBtag_1up'],
['isovar',   'FakeFactor_QCDReweight_MuHadBtag_1down'],
['isovar',   'FakeFactor_QCDReweight_MuHadBveto_1up'],
['isovar',   'FakeFactor_QCDReweight_MuHadBveto_1down'],
]

l_lpxvars=[
['lpxvar',  'LPX_KFACTOR_ALPHAS_Corr_1up'],
['lpxvar',  'LPX_KFACTOR_ALPHAS_Corr_1down'],
['lpxvar',  'LPX_KFACTOR_BEAM_ENERGY_Corr_1up'],
['lpxvar',  'LPX_KFACTOR_BEAM_ENERGY_Corr_1down'],
['lpxvar',  'LPX_KFACTOR_CHOICE_HERAPDF20_Corr_1up'],
['lpxvar',  'LPX_KFACTOR_CHOICE_HERAPDF20_Corr_1down'],
['lpxvar',  'LPX_KFACTOR_CHOICE_NNPDF30_Corr_1up'],
['lpxvar',  'LPX_KFACTOR_CHOICE_NNPDF30_Corr_1down'],
['lpxvar',  'LPX_KFACTOR_CHOICE_epWZ16_Corr_1up'],
['lpxvar',  'LPX_KFACTOR_CHOICE_epWZ16_Corr_1down'],
['lpxvar',  'LPX_KFACTOR_PDF_Corr_1up'],
['lpxvar',  'LPX_KFACTOR_PDF_Corr_1down'],
['lpxvar',  'LPX_KFACTOR_PDF_EW_Corr_1up'],
['lpxvar',  'LPX_KFACTOR_PDF_EW_Corr_1down'],
['lpxvar',  'LPX_KFACTOR_PDF_epWZ16_Corr_1up'],
['lpxvar',  'LPX_KFACTOR_PDF_epWZ16_Corr_1down'],
['lpxvar',  'LPX_KFACTOR_PI_Corr_1up'],
['lpxvar',  'LPX_KFACTOR_PI_Corr_1down'],
['lpxvar',  'LPX_KFACTOR_REDCHOICE_NNPDF30_Corr_1up'],
['lpxvar',  'LPX_KFACTOR_REDCHOICE_NNPDF30_Corr_1down'],
['lpxvar',  'LPX_KFACTOR_SCALE_W_Corr_1up'],
['lpxvar',  'LPX_KFACTOR_SCALE_W_Corr_1down'],
['lpxvar',  'LPX_KFACTOR_SCALE_Z_Corr_1up'],
['lpxvar',  'LPX_KFACTOR_SCALE_Z_Corr_1down'],
]

l_topvars=[
['topvar', 'TTBAR_Radiation_1up'],
['topvar', 'TTBAR_Radiation_1down'],
['topvar', 'TTBAR_ShowerUE_1up'],
['topvar', 'TTBAR_ShowerUE_1down'],
['topvar', 'TTBar_ME'],
['topvar', 'TTBar_PS'],
['topvar', 'TTBar_ISR_1up'],
['topvar', 'TTBar_ISR_1down'],
['topvar', 'TTBar_FSR_1up'],
['topvar', 'TTBar_FSR_1down'],
]

l_weightvars=[
['weightvar', 'mu_eff_stat_low'],
['weightvar', 'mu_eff_stat_high'],
['weightvar', 'mu_eff_statlowpt_low'],
['weightvar', 'mu_eff_statlowpt_high'],
['weightvar', 'mu_eff_sys_low'],
['weightvar', 'mu_eff_sys_high'],
['weightvar', 'mu_eff_syslowpt_low'],
['weightvar', 'mu_eff_syslowpt_high'],
['weightvar', 'mu_eff_trigstat_low'],
['weightvar', 'mu_eff_trigstat_high'],
['weightvar', 'mu_eff_trigsys_low'],
['weightvar', 'mu_eff_trigsys_high'],
['weightvar', 'mu_eff_isostat_low'],
['weightvar', 'mu_eff_isostat_high'],
['weightvar', 'mu_eff_isosys_low'],
['weightvar', 'mu_eff_isosys_high'],
['weightvar', 'mu_eff_ttvastat_low'],
['weightvar', 'mu_eff_ttvastat_high'],
['weightvar', 'mu_eff_ttvasys_low'],
['weightvar', 'mu_eff_ttvasys_high'],
['weightvar', 'el_eff_id_low'],
['weightvar', 'el_eff_id_high'],
['weightvar', 'el_eff_iso_low'],
['weightvar', 'el_eff_iso_high'],
['weightvar', 'el_eff_reco_low'],
['weightvar', 'el_eff_reco_high'],
['weightvar', 'el_eff_trigger_low'],
['weightvar', 'el_eff_trigger_high'],
['weightvar', 'tau_eff_reco_total_low'],
['weightvar', 'tau_eff_reco_total_high'],
['weightvar', 'tau_eff_reco_highpt_low'],
['weightvar', 'tau_eff_reco_highpt_high'],
['weightvar', 'tau_eff_eleolr_trueelectron_low'],
['weightvar', 'tau_eff_eleolr_trueelectron_high'],
['weightvar', 'tau_eff_eleolr_truehadtau_low'],
['weightvar', 'tau_eff_eleolr_truehadtau_high'],
['weightvar', 'tau_eff_jetid_total_low'],
['weightvar', 'tau_eff_jetid_total_high'],
['weightvar', 'tau_eff_jetid_highpt_low'],
['weightvar', 'tau_eff_jetid_highpt_high'],
['weightvar', 'btag_b_0_low'],
['weightvar', 'btag_b_0_high'],
['weightvar', 'btag_b_1_low'],
['weightvar', 'btag_b_1_high'],
['weightvar', 'btag_b_2_low'],
['weightvar', 'btag_b_2_high'],
['weightvar', 'btag_c_0_low'],
['weightvar', 'btag_c_0_high'],
['weightvar', 'btag_c_1_low'],
['weightvar', 'btag_c_1_high'],
['weightvar', 'btag_c_2_low'],
['weightvar', 'btag_c_2_high'],
['weightvar', 'btag_c_3_low'],
['weightvar', 'btag_c_3_high'],
['weightvar', 'btag_light_0_low'],
['weightvar', 'btag_light_0_high'],
['weightvar', 'btag_light_1_low'],
['weightvar', 'btag_light_1_high'],
['weightvar', 'btag_light_2_low'],
['weightvar', 'btag_light_2_high'],
['weightvar', 'btag_light_3_low'],
['weightvar', 'btag_light_3_high'],
['weightvar', 'btag_light_4_low'],
['weightvar', 'btag_light_4_high'],
['weightvar', 'btag_extrapolation_low'],
['weightvar', 'btag_extrapolation_high'],
['weightvar', 'btag_extrapolation_from_charm_low'],
['weightvar', 'btag_extrapolation_from_charm_high'],
['weightvar', 'jet_jvteff_low'],
['weightvar', 'jet_jvteff_high'],
['weightvar', 'pu_prw_high'],
['weightvar', 'pu_prw_low'],
]

l_treevars=[
['treevar', 'NOMINAL'],
['treevar', 'MUON_ID_1down'],
['treevar', 'MUON_ID_1up'],
['treevar', 'MUON_MS_1down'],
['treevar', 'MUON_MS_1up'],
['treevar', 'MUON_SAGITTA_RESBIAS_1down'],
['treevar', 'MUON_SAGITTA_RESBIAS_1up'],
['treevar', 'MUON_SAGITTA_RHO_1down'],
['treevar', 'MUON_SAGITTA_RHO_1up'],
['treevar', 'MUON_SCALE_1down'],
['treevar', 'MUON_SCALE_1up'],
['treevar', 'EG_RESOLUTION_ALL_1down'],
['treevar', 'EG_RESOLUTION_ALL_1up'],
['treevar', 'EG_SCALE_AF2_1down'],
['treevar', 'EG_SCALE_AF2_1up'],
['treevar', 'EG_SCALE_ALL_1down'],
['treevar', 'EG_SCALE_ALL_1up'],
['treevar', 'EG_SCALE_ALLCORR_1down'],
['treevar', 'EG_SCALE_ALLCORR_1up'],
['treevar', 'EG_SCALE_E4SCINTILLATOR_1down'],
['treevar', 'EG_SCALE_E4SCINTILLATOR_1up'],
['treevar', 'EG_SCALE_LARCALIB_EXTRA2015PRE_1down'],
['treevar', 'EG_SCALE_LARCALIB_EXTRA2015PRE_1up'],
['treevar', 'EG_SCALE_LARTEMPERATURE_EXTRA2015PRE_1down'],
['treevar', 'EG_SCALE_LARTEMPERATURE_EXTRA2015PRE_1up'],
['treevar', 'EG_SCALE_LARTEMPERATURE_EXTRA2016PRE_1down'],
['treevar', 'EG_SCALE_LARTEMPERATURE_EXTRA2016PRE_1up'],
['treevar', 'TAUS_TRUEHADTAU_SME_TES_DETECTOR_1down'],
['treevar', 'TAUS_TRUEHADTAU_SME_TES_DETECTOR_1up'],
['treevar', 'TAUS_TRUEHADTAU_SME_TES_INSITU_1down'],
['treevar', 'TAUS_TRUEHADTAU_SME_TES_INSITU_1up'],
['treevar', 'TAUS_TRUEHADTAU_SME_TES_MODEL_1down'],
['treevar', 'TAUS_TRUEHADTAU_SME_TES_MODEL_1up'],
['treevar', 'JET_EtaIntercalibration_NonClosure_highE_1up'],
['treevar', 'JET_EtaIntercalibration_NonClosure_highE_1down'],
['treevar', 'JET_EtaIntercalibration_NonClosure_negEta_1up'],
['treevar', 'JET_EtaIntercalibration_NonClosure_negEta_1down'],
['treevar', 'JET_EtaIntercalibration_NonClosure_posEta_1up'],
['treevar', 'JET_EtaIntercalibration_NonClosure_posEta_1down'],
['treevar', 'JET_Flavor_Response_1up'],
['treevar', 'JET_Flavor_Response_1down'],
['treevar', 'JET_GroupedNP_1_1up'],
['treevar', 'JET_GroupedNP_1_1down'],
['treevar', 'JET_GroupedNP_2_1up'],
['treevar', 'JET_GroupedNP_2_1down'],
['treevar', 'JET_GroupedNP_3_1up'],
['treevar', 'JET_GroupedNP_3_1down'],
['treevar', 'JET_JER_DataVsMC_MC16_1up'],
['treevar', 'JET_JER_EffectiveNP_1_1up'],
['treevar', 'JET_JER_EffectiveNP_2_1up'],
['treevar', 'JET_JER_EffectiveNP_3_1up'],
['treevar', 'JET_JER_EffectiveNP_4_1up'],
['treevar', 'JET_JER_EffectiveNP_5_1up'],
['treevar', 'JET_JER_EffectiveNP_6_1up'],
['treevar', 'JET_JER_EffectiveNP_7restTerm_1up'],
['treevar', 'JET_TILECORR_Uncertainty_1down'],
['treevar', 'JET_TILECORR_Uncertainty_1up'],
['treevar', 'MET_SoftTrk_ResoPara'],
['treevar', 'MET_SoftTrk_ResoPerp'],
['treevar', 'MET_SoftTrk_ScaleDown'],
['treevar', 'MET_SoftTrk_ScaleUp'],
]



def create_cmd_log(option, sys, stage):
  cmd = ''
  if stage == 'initialize':
    cmd="initialize.py {:s} --options verbose=False printFolderTags=td campaignsConfig='{:s}' postInit_patches='configCommon/htautau_lephad_common_postinit.tags, configCommon/htautau_lephad_common_postinit_clean.tags' mcTreeName='{:s}' outputFile='sampleFolders/initialized/samples-initialized-htautau_lephad_common-{:s}.root'".format(s_common_config_path,s_sys_file_path,sys,sys)
  elif stage == 'analyze':
    # different option for different sys
    extra_option = ''
    if option == 'treevar':
      extra_option = "inputFile='sampleFolders/initialized/samples-initialized-htautau_lephad_common-{:s}.root'".format(sys)
    elif option == 'weightvar' or option == 'topvar' or option == 'lpxvar':
      extra_option = "inputFile='sampleFolders/initialized/samples-initialized-htautau_lephad_common-NOMINAL.root' aliases.{:s}={:s} {:s}={:s}".format(option,sys,option,sys)
    else:
      extra_option = "aliases.{:s}={:s} {:s}={:s}".format(option,sys,option,sys)

    # different files to be copied
    l_files = []
    jobs_file = ''
    l_files.append('unmerged_*_data_X_c16?*.root')
    if option=='fakevar':
      l_files.append('unmerged_*_bkg_X_c16?_Diboson*.root')
      l_files.append('unmerged_*_bkg_X_c16?_Top*.root')
      l_files.append('unmerged_*_bkg_X_c16?_Z*.root')
      l_files.append('unmerged_*_bkg_X_c16?_Fakes_ISO_*.root')
      l_files.append('unmerged_*_sig_X_c16?_*.root')
      jobs_file = "jobsSYS-fakevar.txt"
    elif option=='isovar':
      l_files.append('unmerged_*_bkg_X_c16?_Diboson*.root')
      l_files.append('unmerged_*_bkg_X_c16?_Top*.root')
      l_files.append('unmerged_*_bkg_X_c16?_Z*.root')
      l_files.append('unmerged_*_bkg_X_c16?_Fakes_ID_data*.root')
      l_files.append('unmerged_*_bkg_X_c16?_Fakes_ID_mc_*.root')
      l_files.append('unmerged_*_sig_X_c16?_*.root')
      jobs_file = "jobsSYS-isovar.txt"
    elif option=='lpxvar':
      l_files.append('unmerged_*_bkg_X_c16?_Diboson*.root')
      l_files.append('unmerged_*_bkg_X_c16?_Top*.root')
      l_files.append('unmerged_*_bkg_X_c16?_Fakes_*.root')
      l_files.append('unmerged_*_sig_X_c16?_*.root')
      jobs_file = "jobsSYS-lpxvar.txt"
    elif option=='weightvar' or option=='treevar':
      l_files.append('unmerged_*_bkg_X_c16?_Fakes_*.root')
      jobs_file = "jobsSYS-weighttreevar.txt"
    elif option=='topvar':
      l_files.append('unmerged_*_bkg_X_c16?_Diboson*.root')
      l_files.append('unmerged_*_bkg_X_c16?_Top_single*.root')
      l_files.append('unmerged_*_bkg_X_c16?_Z*.root')
      l_files.append('unmerged_*_bkg_X_c16?_Fakes_*.root')
      l_files.append('unmerged_*_sig_X_c16?_*.root')
      jobs_file = "jobsSYS-topvar.txt"

    # make output folder, the same as the submitAnalysis.py would create;
    os.system('mkdir -pv batchOutput/unmerged_SRsys_{:s}'.format(sys))
    # copy those files which should not be run over for this particular systematic;
    for files in l_files:
      l_file = []
      if "Fake" in files:
        l_file = glob.glob('{:s}/{:s}'.format(s_standard_dir,files))
      else:
        l_file = glob.glob('{:s}/{:s}'.format(s_nominal_dir,files))
      for afile in l_file:
        os.system('ln -sv ../../{:s} batchOutput/unmerged_SRsys_{:s}'.format(afile,sys))
    # obtain the command
    submit_config = "--time 4320 --memory 1024 --maxSampleSize 7000"

    if ".shef.ac.uk" in os.environ['HOSTNAME']:
      submit_config += " --submit condor --maxSampleSize 20000"
    elif os.environ['USER'] == "yehf":
      submit_config += " --submit condor --account atlas"
    elif os.environ['USER'] == "xiaozhong":
      submit_config += " --submit condor --account atlas"

    if option == 'weightvar' or option == 'treevar' or option == "lpxvar":
      if os.environ['USER'] == "yehf":
        submit_config += " --maxSampleSize 35000 "
      elif os.environ['USER'] == "xiaozhong":
        submit_config += " --maxSampleSize 35000 "
      cmd='submit.py {:s} --jobs configSignalControlRegion/syst/{:s} --identifier SRsys_{:s} --allowArgChanges {:s} --options {:s}'.format(s_config_path,jobs_file,sys,submit_config,extra_option)
    else:
      if os.environ['USER'] == "yehf":
        submit_config += " --maxSampleSize 7000 "
      elif os.environ['USER'] == "xiaozhong":
        submit_config += " --maxSampleSize 7000 "
      cmd='submit.py {:s} --jobs configSignalControlRegion/syst/{:s} --identifier SRsys_{:s} --allowArgChanges {:s} --options {:s}'.format(s_config_path,jobs_file,sys,submit_config,extra_option)

  #######################
  # Merge samples
  #######################
  elif stage == 'merge':
    cmd='tqmerge -o sampleFolders/analyzed/samples-analyzed-htautau_lephad_sr-{:s}.root -t analyze batchOutput/unmerged_SRsys_{:s}/*.root'.format(sys,sys)
  else:
    print "Error. Not recognized stage ..."
  # create log file
  log_dir='logs/{0}_syst/{1}'.format(stage, option)
  if not os.path.isdir(log_dir):
    os.makedirs(log_dir)
  log='{}/{}_{}_{}.log'.format(log_dir,stage,option,sys)

  return cmd, log

if __name__ == '__main__':
  # introduce argument parser
  parser = argparse.ArgumentParser(description='submit systematics script')
  parser.add_argument('--stage', default='none',
                    help='select the stage: prepare, initialize, analyze, merge')
  parser.add_argument('--systype', default='none',
                    help='select which type of systematic to process')
  parser.add_argument('--ncores', default=1, type=int,
                    help='number of cores to run')
  args = parser.parse_args()

  # now we add the systematic sublists we want to run over into the grand list
  # this is controlled by the arg parser, so I can run the show from an external submission script

  l_systematics=[]
  if args.systype == "isovar":
    l_systematics.extend(l_isovars)
  if args.systype == "fakevar":
    l_systematics.extend(l_fakevars)
  if args.systype == "lpxvar":
    l_systematics.extend(l_lpxvars)
  if args.systype == "topvar":
    l_systematics.extend(l_topvars)
  if args.systype == "weightvar":
    l_systematics.extend(l_weightvars)
  if args.systype == "treevar":
    l_systematics.extend(l_treevars)

  # create job list    
  cmd_list = []
  log_list = []

  for systematics in l_systematics:
    option = systematics[0]
    sys = systematics[1]
    # create cmd for this setup
    cmd, log = create_cmd_log(option, sys, args.stage)
    cmd_list.append(cmd)
    log_list.append(log)

  if not len(cmd_list):
    sys.exit()

  NCORES = args.ncores
  if 1 == NCORES:
    for cmd in cmd_list:
      os.system(cmd)
  else:
    cmd_log = zip(cmd_list, log_list)
    local_job_handler = LocalJobHandler(cmd_log, NCORES)
    local_job_handler.run()
