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
s_config_path='bsmtautau_lephad/config-SignalControlRegion/syst-old/master/master.cfg'
s_common_config_path='bsmtautau_lephad/config-Common/master/master.cfg'

# Input MC files for the systematic jobs (Input data files are not changed)
s_sys_file_path='bsmtautau_lephad/config-Common/master/master_campaigns_sys.cfg'

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
['lpxvar',  'LPX_KFACTOR_PDF_Corr_1up'],
['lpxvar',  'LPX_KFACTOR_PDF_Corr_1down'],
['lpxvar',  'LPX_KFACTOR_PDF_EW_Corr_1up'],
['lpxvar',  'LPX_KFACTOR_PDF_EW_Corr_1down'],
['lpxvar',  'LPX_KFACTOR_PDF_epWZ16_Corr_1up'],
['lpxvar',  'LPX_KFACTOR_PDF_epWZ16_Corr_1down'],
['lpxvar',  'LPX_KFACTOR_PI_Corr_1up'],
['lpxvar',  'LPX_KFACTOR_PI_Corr_1down'],
['lpxvar',  'LPX_KFACTOR_SCALE_W_Corr_1up'],
['lpxvar',  'LPX_KFACTOR_SCALE_W_Corr_1down'],
['lpxvar',  'LPX_KFACTOR_SCALE_Z_Corr_1up'],
['lpxvar',  'LPX_KFACTOR_SCALE_Z_Corr_1down'],
['lpxvar',  'LPX_KFACTOR_CHOICE_HERAPDF20_Corr'],
['lpxvar',  'LPX_KFACTOR_CHOICE_NNPDF30_Corr'],
['lpxvar',  'LPX_KFACTOR_CHOICE_epWZ16_Corr'],
['lpxvar',  'LPX_KFACTOR_REDCHOICE_NNPDF30_Corr'],
]

l_topvars=[
['topvar', 'TTBar_ME'],
['topvar', 'TTBar_PS'],
['topvar', 'TTBar_ISR_1up'],
['topvar', 'TTBar_ISR_1down'],
['topvar', 'TTBar_FSR_1up'],
['topvar', 'TTBar_FSR_1down'],
]

l_weightvars=[
['weightvar', 'PRW_DATASF_1up'],
['weightvar', 'PRW_DATASF_1down'],
['weightvar', 'EL_EFF_Trigger_1up'],
['weightvar', 'EL_EFF_Trigger_1down'],
['weightvar', 'EL_EFF_Reco_TOTAL_1up'],
['weightvar', 'EL_EFF_Reco_TOTAL_1down'],
['weightvar', 'EL_EFF_ID_TOTAL_1up'],
['weightvar', 'EL_EFF_ID_TOTAL_1down'],
['weightvar', 'EL_EFF_Iso_TOTAL_1up'],
['weightvar', 'EL_EFF_Iso_TOTAL_1down'],
['weightvar', 'MUON_EFF_Trigger_STAT_1up'],
['weightvar', 'MUON_EFF_Trigger_STAT_1down'],
['weightvar', 'MUON_EFF_Trigger_SYST_1up'],
['weightvar', 'MUON_EFF_Trigger_SYST_1down'],
['weightvar', 'MUON_EFF_RECO_STAT_1up'],
['weightvar', 'MUON_EFF_RECO_STAT_1down'],
['weightvar', 'MUON_EFF_RECO_SYS_1up'],
['weightvar', 'MUON_EFF_RECO_SYS_1down'],
['weightvar', 'MUON_EFF_ISO_STAT_1up'],
['weightvar', 'MUON_EFF_ISO_STAT_1down'],
['weightvar', 'MUON_EFF_ISO_SYS_1up'],
['weightvar', 'MUON_EFF_ISO_SYS_1down'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RECO_TOTAL_1up'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RECO_TOTAL_1down'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_ELEOLR_TOTAL_1up'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_ELEOLR_TOTAL_1down'],
['weightvar', 'TAUS_TRUEELECTRON_EFF_ELEOLR_STAT_1up'],
['weightvar', 'TAUS_TRUEELECTRON_EFF_ELEOLR_STAT_1down'],
['weightvar', 'TAUS_TRUEELECTRON_EFF_ELEOLR_SYST_1up'],
['weightvar', 'TAUS_TRUEELECTRON_EFF_ELEOLR_SYST_1down'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPT2025_1up'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPT2025_1down'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPT2530_1up'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPT2530_1down'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPT3040_1up'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPT3040_1down'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPTGE40_1up'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPTGE40_1down'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPT2025_1up'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPT2025_1down'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPT2530_1up'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPT2530_1down'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPT3040_1up'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPT3040_1down'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPTGE40_1up'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPTGE40_1down'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RNNID_SYST_1up'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RNNID_SYST_1down'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RNNID_HIGHPT_1up'],
['weightvar', 'TAUS_TRUEHADTAU_EFF_RNNID_HIGHPT_1down'],
['weightvar', 'JET_JvtEfficiency_1up'],
['weightvar', 'JET_JvtEfficiency_1down'],
['weightvar', 'FT_EFF_Eigen_B_0_1up'],
['weightvar', 'FT_EFF_Eigen_B_0_1down'],
['weightvar', 'FT_EFF_Eigen_B_1_1up'],
['weightvar', 'FT_EFF_Eigen_B_1_1down'],
['weightvar', 'FT_EFF_Eigen_B_2_1up'],
['weightvar', 'FT_EFF_Eigen_B_2_1down'],
['weightvar', 'FT_EFF_Eigen_C_0_1up'],
['weightvar', 'FT_EFF_Eigen_C_0_1down'],
['weightvar', 'FT_EFF_Eigen_C_1_1up'],
['weightvar', 'FT_EFF_Eigen_C_1_1down'],
['weightvar', 'FT_EFF_Eigen_C_2_1up'],
['weightvar', 'FT_EFF_Eigen_C_2_1down'],
['weightvar', 'FT_EFF_Eigen_C_3_1up'],
['weightvar', 'FT_EFF_Eigen_C_3_1down'],
['weightvar', 'FT_EFF_Eigen_Light_0_1up'],
['weightvar', 'FT_EFF_Eigen_Light_0_1down'],
['weightvar', 'FT_EFF_Eigen_Light_1_1up'],
['weightvar', 'FT_EFF_Eigen_Light_1_1down'],
['weightvar', 'FT_EFF_Eigen_Light_2_1up'],
['weightvar', 'FT_EFF_Eigen_Light_2_1down'],
['weightvar', 'FT_EFF_Eigen_Light_3_1up'],
['weightvar', 'FT_EFF_Eigen_Light_3_1down'],
['weightvar', 'FT_EFF_Eigen_Light_4_1up'],
['weightvar', 'FT_EFF_Eigen_Light_4_1down'],
['weightvar', 'FT_EFF_extrapolation_1up'],
['weightvar', 'FT_EFF_extrapolation_1down'],
['weightvar', 'FT_EFF_extrapolation_from_charm_1up'],
['weightvar', 'FT_EFF_extrapolation_from_charm_1down'],
]

l_treevars=[
['treevar', 'NOMINAL'],
#['treevar', 'MUON_ID_1down'],
#['treevar', 'MUON_ID_1up'],
#['treevar', 'MUON_MS_1down'],
#['treevar', 'MUON_MS_1up'],
#['treevar', 'MUON_SAGITTA_RESBIAS_1down'],
#['treevar', 'MUON_SAGITTA_RESBIAS_1up'],
#['treevar', 'MUON_SAGITTA_RHO_1down'],
#['treevar', 'MUON_SAGITTA_RHO_1up'],
#['treevar', 'MUON_SCALE_1down'],
#['treevar', 'MUON_SCALE_1up'],
#['treevar', 'EG_RESOLUTION_ALL_1down'],
#['treevar', 'EG_RESOLUTION_ALL_1up'],
#['treevar', 'EG_SCALE_AF2_1down'],
#['treevar', 'EG_SCALE_AF2_1up'],
#['treevar', 'EG_SCALE_ALL_1down'],
#['treevar', 'EG_SCALE_ALL_1up'],
#['treevar', 'EG_SCALE_ALLCORR_1down'],
#['treevar', 'EG_SCALE_ALLCORR_1up'],
#['treevar', 'EG_SCALE_E4SCINTILLATOR_1down'],
#['treevar', 'EG_SCALE_E4SCINTILLATOR_1up'],
#['treevar', 'EG_SCALE_LARCALIB_EXTRA2015PRE_1down'],
#['treevar', 'EG_SCALE_LARCALIB_EXTRA2015PRE_1up'],
#['treevar', 'EG_SCALE_LARTEMPERATURE_EXTRA2015PRE_1down'],
#['treevar', 'EG_SCALE_LARTEMPERATURE_EXTRA2015PRE_1up'],
#['treevar', 'EG_SCALE_LARTEMPERATURE_EXTRA2016PRE_1down'],
#['treevar', 'EG_SCALE_LARTEMPERATURE_EXTRA2016PRE_1up'],
#['treevar', 'TAUS_TRUEHADTAU_SME_TES_AFII_1down'],
#['treevar', 'TAUS_TRUEHADTAU_SME_TES_AFII_1up'],
#['treevar', 'TAUS_TRUEHADTAU_SME_TES_INSITUEXP_1down'],
#['treevar', 'TAUS_TRUEHADTAU_SME_TES_INSITUEXP_1up'],
#['treevar', 'TAUS_TRUEHADTAU_SME_TES_INSITUFIT_1down'],
#['treevar', 'TAUS_TRUEHADTAU_SME_TES_INSITUFIT_1up'],
#['treevar', 'TAUS_TRUEHADTAU_SME_TES_MODEL_CLOSURE_1down'],
#['treevar', 'TAUS_TRUEHADTAU_SME_TES_MODEL_CLOSURE_1up'],
#['treevar', 'TAUS_TRUEHADTAU_SME_TES_PHYSICSLIST_1down'],
#['treevar', 'TAUS_TRUEHADTAU_SME_TES_PHYSICSLIST_1up'],
#['treevar', 'JET_EtaIntercalibration_NonClosure_highE_1up'],
#['treevar', 'JET_EtaIntercalibration_NonClosure_highE_1down'],
#['treevar', 'JET_EtaIntercalibration_NonClosure_negEta_1up'],
#['treevar', 'JET_EtaIntercalibration_NonClosure_negEta_1down'],
#['treevar', 'JET_EtaIntercalibration_NonClosure_posEta_1up'],
#['treevar', 'JET_EtaIntercalibration_NonClosure_posEta_1down'],
#['treevar', 'JET_EtaIntercalibration_NonClosure_2018data_1up'],
#['treevar', 'JET_EtaIntercalibration_NonClosure_2018data_1down'],
#['treevar', 'JET_Flavor_Response_1up'],
#['treevar', 'JET_Flavor_Response_1down'],
#['treevar', 'JET_GroupedNP_1_1up'],
#['treevar', 'JET_GroupedNP_1_1down'],
#['treevar', 'JET_GroupedNP_2_1up'],
#['treevar', 'JET_GroupedNP_2_1down'],
#['treevar', 'JET_GroupedNP_3_1up'],
#['treevar', 'JET_GroupedNP_3_1down'],
#['treevar', 'JET_JER_DataVsMC_MC16_1up'],
#['treevar', 'JET_JER_EffectiveNP_1_1up'],
#['treevar', 'JET_JER_EffectiveNP_2_1up'],
#['treevar', 'JET_JER_EffectiveNP_3_1up'],
#['treevar', 'JET_JER_EffectiveNP_4_1up'],
#['treevar', 'JET_JER_EffectiveNP_5_1up'],
#['treevar', 'JET_JER_EffectiveNP_6_1up'],
#['treevar', 'JET_JER_EffectiveNP_7restTerm_1up'],
#['treevar', 'JET_TILECORR_Uncertainty_1down'],
#['treevar', 'JET_TILECORR_Uncertainty_1up'],
#['treevar', 'MET_SoftTrk_ResoPara'],
#['treevar', 'MET_SoftTrk_ResoPerp'],
#['treevar', 'MET_SoftTrk_ScaleDown'],
#['treevar', 'MET_SoftTrk_ScaleUp'],
]



def create_cmd_log(option, sys, stage):
  cmd = ''
  if stage == 'initialize':
    cmd="initialize.py {:s} --options verbose=False printFolderTags=td campaignsConfig='{:s}' postInit_patches='bsmtautau_lephad/config-Common/patches/postinitialize-patch.txt, bsmtautau_lephad/config-Common/patches/postinitialize_mc-patch.txt, bsmtautau_lephad/config-Common/patches/postinitialize_clean-patch.txt' mcTreeName='{:s}' outputFile='sampleFolders/initialized/samples-initialized-bsmtautau_lephad_common-{:s}.root'".format(s_common_config_path,s_sys_file_path,sys,sys)
    print cmd
  elif stage == 'analyze':
    # different option for different sys
    extra_option = ''
    if option == 'treevar':
      extra_option = "inputFile='sampleFolders/initialized/samples-initialized-bsmtautau_lephad_common-{:s}.root'".format(sys)
    elif option == 'weightvar' or option == 'topvar' or option == 'lpxvar':
      extra_option = "inputFile='sampleFolders/initialized/samples-initialized-bsmtautau_lephad_common-NOMINAL.root' aliases.{:s}={:s} {:s}={:s}".format(option,sys,option,sys)
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
      l_files.append('unmerged_*_bkg_X_c16?_*Fakes*.root')
      l_files.append('unmerged_*_sig_X_c16?_*.root')
      jobs_file = "jobsSYS-lpxvar.txt"
    elif option=='weightvar' or option=='treevar':
      l_files.append('unmerged_*_bkg_X_c16?_*Fakes*.root')
      jobs_file = "jobsSYS-weighttreevar.txt"
    elif option=='topvar':
      l_files.append('unmerged_*_bkg_X_c16?_Diboson*.root')
      l_files.append('unmerged_*_bkg_X_c16?_Top_single*.root')
      l_files.append('unmerged_*_bkg_X_c16?_Z*.root')
      l_files.append('unmerged_*_bkg_X_c16?_Fakes_*.root')
      l_files.append('unmerged_*_sig_X_c16?_*.root')
      jobs_file = "jobsSYS-topvar.txt"
    
    jobs_file = "bsmtautau_lephad/config-SignalControlRegion/syst-old/jobLists/" + jobs_file

    # make output folder, the same as the submitAnalysis.py would create;
    os.system('mkdir -pv batchOutput/unmerged_SRsys_{:s}'.format(sys))
    # copy those files which should not be run over for this particular systematic;
    for files in l_files:
      l_file = []
      if "Fake" in files or "data" in files:
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
    elif os.environ['USER'] == "xiaozhon":
      submit_config += " --submit condor --account atlas"

    if option == 'weightvar' or option == 'treevar' or option == "lpxvar":
      if os.environ['USER'] == "yehf":
        submit_config += " --maxSampleSize 35000 "
      elif os.environ['USER'] == "xiaozhong":
        submit_config += " --maxSampleSize 35000 "
      cmd='submit.py {:s} --jobs {:s} --identifier SRsys_{:s} --allowArgChanges {:s} --options {:s}'.format(s_config_path,jobs_file,sys,submit_config,extra_option)
    else:
      if os.environ['USER'] == "yehf":
        submit_config += " --maxSampleSize 7000 "
      elif os.environ['USER'] == "xiaozhon":
        submit_config += " --maxSampleSize 7000 "
      cmd='submit.py {:s} --jobs {:s} --identifier SRsys_{:s} --allowArgChanges {:s} --options {:s}'.format(s_config_path,jobs_file,sys,submit_config,extra_option)

  #######################
  # Merge samples
  #######################
  elif stage == 'merge':
    cmd='tqmerge -o sampleFolders/analyzed/samples-analyzed-bsmtautau_lephad_sr-{:s}.root -t analyze batchOutput/unmerged_SRsys_{:s}/*.root'.format(sys,sys)
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
