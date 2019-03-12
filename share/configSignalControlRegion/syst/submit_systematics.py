#!/usr/bin/env python

import os
import sys

#some configurations
s_queue='medium'
s_nominal_dir='batchOutput/unmerged_SR'
s_config_path='configSignalControlRegion/htautau_lephad_sr.cfg'
#s_config_path='ConfigSignalRegion/htautau_lephad_srcontid.cfg'
s_sys_file_path='/atlas/zorbas/BSM_TauTau/LepHad/190116/mc/mc16a/sys/'
#s_sample_prefix='samples-htautau_lephad_sr'
#s_sample_prefix='samples-htautau_lephad_srcontid'

# if making sample files (for kinematic variation), only this will be performed and no other jobs will be submitted:
b_makeSamples = False
# if submitting samples, they won't be merged, because we need to wait for all jobs to finish:
b_submit = True
# merge samples, but you must make sure that all jobs are finished:
b_merge = False


# list of all systematics, comment out the ones you don't want to run:
l_systematics=[
#['fakevar',   'FakeFactor_WjetsBtag1pBDT1_1up'],
#['fakevar',   'FakeFactor_WjetsBtag1pBDT1_1down'],
#['fakevar',   'FakeFactor_WjetsBtag1pBDT2_1up'],
#['fakevar',   'FakeFactor_WjetsBtag1pBDT2_1down'],
#['fakevar',   'FakeFactor_WjetsBtag1pBDT3_1up'],
#['fakevar',   'FakeFactor_WjetsBtag1pBDT3_1down'],
#['fakevar',   'FakeFactor_WjetsBtag1pBDT4_1up'],
#['fakevar',   'FakeFactor_WjetsBtag1pBDT4_1down'],
#['fakevar',   'FakeFactor_WjetsBtag3pBDT1_1up'],
#['fakevar',   'FakeFactor_WjetsBtag3pBDT1_1down'],
#['fakevar',   'FakeFactor_WjetsBtag3pBDT2_1up'],
#['fakevar',   'FakeFactor_WjetsBtag3pBDT2_1down'],
#['fakevar',   'FakeFactor_WjetsBtag3pBDT3_1up'],
#['fakevar',   'FakeFactor_WjetsBtag3pBDT3_1down'],
#['fakevar',   'FakeFactor_WjetsBveto1pBDT1_1up'],
#['fakevar',   'FakeFactor_WjetsBveto1pBDT1_1down'],
#['fakevar',   'FakeFactor_WjetsBveto1pBDT2_1up'],
#['fakevar',   'FakeFactor_WjetsBveto1pBDT2_1down'],
#['fakevar',   'FakeFactor_WjetsBveto1pBDT3_1up'],
#['fakevar',   'FakeFactor_WjetsBveto1pBDT3_1down'],
#['fakevar',   'FakeFactor_WjetsBveto1pBDT4_1up'],
#['fakevar',   'FakeFactor_WjetsBveto1pBDT4_1down'],
#['fakevar',   'FakeFactor_WjetsBveto3pBDT1_1up'],
#['fakevar',   'FakeFactor_WjetsBveto3pBDT1_1down'],
#['fakevar',   'FakeFactor_WjetsBveto3pBDT2_1up'],
#['fakevar',   'FakeFactor_WjetsBveto3pBDT2_1down'],
#['fakevar',   'FakeFactor_WjetsBveto3pBDT3_1up'],
#['fakevar',   'FakeFactor_WjetsBveto3pBDT3_1down'],

#['fakevar',   'FakeFactor_WjetsBtag1p_1up'],
#['fakevar',   'FakeFactor_WjetsBtag1p_1down'],
#['fakevar',   'FakeFactor_WjetsBtag3p_1up'],
#['fakevar',   'FakeFactor_WjetsBtag3p_1down'],
#['fakevar',   'FakeFactor_WjetsBveto1p_1up'],
#['fakevar',   'FakeFactor_WjetsBveto1p_1down'],
#['fakevar',   'FakeFactor_WjetsBveto3p_1up'],
#['fakevar',   'FakeFactor_WjetsBveto3p_1down'],

['isovar',   'FakeFactor_LepElBveto_1up'],
['isovar',   'FakeFactor_LepElBveto_1down'],
['isovar',   'FakeFactor_LepElBtag_1up'],
['isovar',   'FakeFactor_LepElBtag_1down'],
['isovar',   'FakeFactor_LepMuBveto_1up'],
['isovar',   'FakeFactor_LepMuBveto_1down'],
['isovar',   'FakeFactor_LepMuBtag_1up'],
['isovar',   'FakeFactor_LepMuBtag_1down'],

#['ttbarweight', 'TTBAR_Radiation_1up'],
#['ttbarweight', 'TTBAR_Radiation_1down'],
#['ttbarweight', 'TTBAR_ShowerUE_1up'],
#['ttbarweight', 'TTBAR_ShowerUE_1down'],


#['weightvar', 'LPX_KFACTOR_ALPHAS_1down_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_ALPHAS_1up_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_BEAM_ENERGY_1down_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_BEAM_ENERGY_1up_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_CHOICE_HERAPDF20_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_CHOICE_NNPDF30_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_PDF_1down_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_PDF_1up_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_PDF_EV1_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_PDF_EV2_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_PDF_EV3_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_PDF_EV4_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_PDF_EV5_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_PDF_EV6_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_PDF_EV7_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_PDF_EW_1down_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_PDF_EW_1up_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_PI_1down_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_PI_1up_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_REDCHOICE_NNPDF30_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_SCALE_W_1down_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_SCALE_W_1up_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_SCALE_Z_1down_lpx_kfactor'],
#['weightvar', 'LPX_KFACTOR_SCALE_Z_1up_lpx_kfactor'],
#
#['weightvar', 'mu_eff_stat_low'],
#['weightvar', 'mu_eff_stat_high'],
#['weightvar', 'mu_eff_statlowpt_low'],
#['weightvar', 'mu_eff_statlowpt_high'],
#['weightvar', 'mu_eff_sys_low'],
#['weightvar', 'mu_eff_sys_high'],
#['weightvar', 'mu_eff_syslowpt_low'],
#['weightvar', 'mu_eff_syslowpt_high'],
#['weightvar', 'mu_eff_trigstat_low'],
#['weightvar', 'mu_eff_trigstat_high'],
#['weightvar', 'mu_eff_trigsys_low'],
#['weightvar', 'mu_eff_trigsys_high'],
#['weightvar', 'mu_eff_isostat_low'],
#['weightvar', 'mu_eff_isostat_high'],
#['weightvar', 'mu_eff_isosys_low'],
#['weightvar', 'mu_eff_isosys_high'],
#['weightvar', 'mu_eff_ttvastat_low'],
#['weightvar', 'mu_eff_ttvastat_high'],
#['weightvar', 'mu_eff_ttvasys_low'],
#['weightvar', 'mu_eff_ttvasys_high'],
#
#['weightvar', 'el_eff_id_low'],
#['weightvar', 'el_eff_id_high'],
#['weightvar', 'el_eff_iso_low'],
#['weightvar', 'el_eff_iso_high'],
#['weightvar', 'el_eff_reco_low'],
#['weightvar', 'el_eff_reco_high'],
#['weightvar', 'el_eff_trigger_low'],
#['weightvar', 'el_eff_trigger_high'],
#
#['weightvar', 'tau_eff_reco_total_low'],
#['weightvar', 'tau_eff_reco_total_high'],
#['weightvar', 'tau_eff_reco_highpt_low'],
#['weightvar', 'tau_eff_reco_highpt_high'],
#['weightvar', 'tau_eff_eleolr_trueelectron_low'],
#['weightvar', 'tau_eff_eleolr_trueelectron_high'],
#['weightvar', 'tau_eff_eleolr_truehadtau_low'],
#['weightvar', 'tau_eff_eleolr_truehadtau_high'],
#['weightvar', 'tau_eff_jetid_total_low'],
#['weightvar', 'tau_eff_jetid_total_high'],
#['weightvar', 'tau_eff_jetid_highpt_low'],
#['weightvar', 'tau_eff_jetid_highpt_high'],
#
#['weightvar', 'btag_b_0_low'],
#['weightvar', 'btag_b_0_high'],
#['weightvar', 'btag_b_1_low'],
#['weightvar', 'btag_b_1_high'],
#['weightvar', 'btag_b_2_low'],
#['weightvar', 'btag_b_2_high'],
#
#['weightvar', 'btag_c_0_low'],
#['weightvar', 'btag_c_0_high'],
#['weightvar', 'btag_c_1_low'],
#['weightvar', 'btag_c_1_high'],
#['weightvar', 'btag_c_2_low'],
#['weightvar', 'btag_c_2_high'],
#
#['weightvar', 'btag_light_0_low'],
#['weightvar', 'btag_light_0_high'],
#['weightvar', 'btag_light_1_low'],
#['weightvar', 'btag_light_1_high'],
#['weightvar', 'btag_light_2_low'],
#['weightvar', 'btag_light_2_high'],
#['weightvar', 'btag_light_3_low'],
#['weightvar', 'btag_light_3_high'],
#['weightvar', 'btag_light_4_low'],
#['weightvar', 'btag_light_4_high'],
#
#['weightvar', 'btag_extrapolation_low'],
#['weightvar', 'btag_extrapolation_high'],
#['weightvar', 'btag_extrapolation_from_charm_low'],
#['weightvar', 'btag_extrapolation_from_charm_high'],
#
#['weightvar', 'jet_jvteff_low'],
#['weightvar', 'jet_jvteff_high'],
#
#['weightvar', 'pu_prw_high'],
#['weightvar', 'pu_prw_low'],
#
## below the systematic must be actual tree name in ntuples
#['treevariation', 'MUON_ID_1down'],
#['treevariation', 'MUON_ID_1up'],
#['treevariation', 'MUON_MS_1down'],
#['treevariation', 'MUON_MS_1up'],
#['treevariation', 'MUON_SAGITTA_RESBIAS_1down'],
#['treevariation', 'MUON_SAGITTA_RESBIAS_1up'],
#['treevariation', 'MUON_SAGITTA_RHO_1down'],
#['treevariation', 'MUON_SAGITTA_RHO_1up'],
#['treevariation', 'MUON_SCALE_1down'],
#['treevariation', 'MUON_SCALE_1up'],
#['treevariation', 'EG_RESOLUTION_ALL_1down'],
#['treevariation', 'EG_RESOLUTION_ALL_1up'],
#['treevariation', 'EG_SCALE_ALLCORR_1down'],
#['treevariation', 'EG_SCALE_ALLCORR_1up'],
#['treevariation', 'EG_SCALE_E4SCINTILLATOR_1down'],
#['treevariation', 'EG_SCALE_E4SCINTILLATOR_1up'],
#['treevariation', 'EG_SCALE_LARCALIB_EXTRA2015PRE_1down'],
#['treevariation', 'EG_SCALE_LARCALIB_EXTRA2015PRE_1up'],
#['treevariation', 'EG_SCALE_LARTEMPERATURE_EXTRA2015PRE_1down'],
#['treevariation', 'EG_SCALE_LARTEMPERATURE_EXTRA2015PRE_1up'],
#['treevariation', 'EG_SCALE_LARTEMPERATURE_EXTRA2016PRE_1down'],
#['treevariation', 'EG_SCALE_LARTEMPERATURE_EXTRA2016PRE_1up'],
#['treevariation', 'TAUS_TRUEHADTAU_SME_TES_DETECTOR_1down'],
#['treevariation', 'TAUS_TRUEHADTAU_SME_TES_DETECTOR_1up'],
#['treevariation', 'TAUS_TRUEHADTAU_SME_TES_INSITU_1down'],
#['treevariation', 'TAUS_TRUEHADTAU_SME_TES_INSITU_1up'],
#['treevariation', 'TAUS_TRUEHADTAU_SME_TES_MODEL_1down'],
#['treevariation', 'TAUS_TRUEHADTAU_SME_TES_MODEL_1up'],
#['treevariation', 'JET_EtaIntercalibration_NonClosure_1up'],
#['treevariation', 'JET_EtaIntercalibration_NonClosure_1down'],
#['treevariation', 'JET_GroupedNP_1_1up'],
#['treevariation', 'JET_GroupedNP_1_1down'],
#['treevariation', 'JET_GroupedNP_2_1up'],
#['treevariation', 'JET_GroupedNP_2_1down'],
#['treevariation', 'JET_GroupedNP_3_1up'],
#['treevariation', 'JET_GroupedNP_3_1down'],
#['treevariation', 'JET_JER_SINGLE_NP_1up'],
#['treevariation', 'JET_TILECORR_Uncertainty_1down'],
#['treevariation', 'JET_TILECORR_Uncertainty_1up'],
#['treevariation', 'MET_SoftTrk_ResoPara'],
#['treevariation', 'MET_SoftTrk_ResoPerp'],
#['treevariation', 'MET_SoftTrk_ScaleDown'],
#['treevariation', 'MET_SoftTrk_ScaleUp'],
]

if __name__=='__main__':

  if b_submit:
    for systematic in l_systematics:
      option = systematic[0]
      sys = systematic[1]

      # make list of which files needs to be copied:
      l_files = []
      if option=='fakevar':
        # wff sys, dont need mc bkg and qcd
        #l_files.append('unmerged_*_mc16a_ehad_SherpaWjets.root')
        #l_files.append('unmerged_*_mc16a_muhad_SherpaWjets.root')
        l_files.append('unmerged_*_mc16a_X_Diboson.root')
        l_files.append('unmerged_*_mc16a_X_Top.root')
        l_files.append('unmerged_*_mc16a_X_Z*.root')
        l_files.append('unmerged_*_mc16a_X_QCDFakes_*.root')
        l_files.append('unmerged_*_siga_*.root')
      elif option=='isovar':
        # lepton ff sys, dont need mc bkg
        #l_files.append('unmerged_*_mc16a_ehad_SherpaWjets.root')
        #l_files.append('unmerged_*_mc16a_muhad_SherpaWjets.root')
        l_files.append('unmerged_*_mc16a_X_Diboson.root')
        l_files.append('unmerged_*_mc16a_X_Top.root')
        l_files.append('unmerged_*_mc16a_X_Z*.root')
        l_files.append('unmerged_*_mc16a_X_WJETSFakes_data_*.root')
        l_files.append('unmerged_*_mc16a_X_WJETSFakes_mc_*.root')
        l_files.append('unmerged_*_siga_*.root')
      elif option=='weightvar' or option=='treevariation':
        # mc sys, dont need wjets and qcd
        l_files.append('*-WJETSFakes*')
        l_files.append('*-QCDFakes*')
        # for this only top needed
      elif option=='ttbarweight':
        l_files.append('*-WJETSFakes*')
        l_files.append('*-QCDFakes*')
        l_files.append('*-sig*')
        l_files.append('*bkg_X_Diboson*')
        l_files.append('*bkg_X_Zee*')
        l_files.append('*bkg_X_Zmumu*')
        l_files.append('*bkg_X_Ztautau*')

      # make output folder, the same as the submitAnalysis.py would create;
      os.system('mkdir batchOutput/unmerged_SRsys_{:s}'.format(sys))

      # copy those files which should not be run over for this particular systematic;
      for file in l_files:
        os.system('ln -s ../../{:s}/{:s} batchOutput/unmerged_SRsys_{:s}'.format(s_nominal_dir,file,sys))

      # submit makeSampleFile.py for those systematics which need different trees:
      if b_makeSamples and option=='treevariation':
        command='bsub python makeSampleFile.py {:s} --options mcPaths=\'{:s}:{:s}\' sampleFile=\'input/htautau_lephad_sr_{:s}.root:samples\''.format(s_config_path,s_sys_file_path,sys,sys)
        os.system(command)

      if b_makeSamples:
        # if making sample files: continue, because we don't want to submit jobs before we have inputs ready;
        continue

      # submit other samples; use jobsSYS.txt file which does not have data;
      temp_option=''
      if option=='treevariation': # if tree variation, we need to provide different input file:
        temp_option='inputFile=\'input/htautau_lephad_sr_{:s}.root:samples\''.format(sys)
      elif option=='weightvar': # if sf variation, use nominal branch but sys samples:
        temp_option='inputFile=\'input/htautau_lephad_sr_sys.root:samples\' {:s}={:s}'.format(option,sys)
      else: # if fake variation, use samples with full events, change the name of the tag:
        temp_option=option+'='+sys

      #command='analyze.py --options {:s} --submit bsub --queue {:s} --jobs ConfigSignalRegion/jobsSYS.txt --identifier {:s} --downmerge --memory 0.01 {:s}'.format(temp_option,s_queue,sys,s_config_path)
      command='submit.py {:s} --jobs configSignalControlRegion/syst/jobsSYS-isovar.txt --identifier SRsys_{:s} --allowArgChanges --submit condor --options {:s}'.format(s_config_path,sys,temp_option)
      print command
      os.system(command)

  if b_merge and not b_submit:
    # merge nominal
    #command='bsub -q short tqmerge -o output/htautau_lephad_sr_contid/nominal.root -t runAnalysis -Sum {:s}/*'.format(s_nominal_dir)
    #os.system(command)
    # merge systematics
    for systematic in l_systematics:
      option = systematic[0]
      sys = systematic[1]

      # we need full sys files in htautau_lephad_sr folder
      #command='bsub -q short tqmerge -o output/htautau_lephad_sr_contid/{:s}.root -t runAnalysis -Sum  output/unmerged_{:s}/*'.format(sys,sys)
      command='tqmerge -o sampleFolders/analyzed/samples-analyzed-htautau_lephad_sr-{:s}.root -t analyze batchOutput/unmerged_SRsys_{:s}/*.root'.format(sys,sys)
      os.system(command)
