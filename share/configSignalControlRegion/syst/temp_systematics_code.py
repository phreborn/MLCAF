#!/usr/bin/env python2
from QFramework import *
from ROOT import *
import os
import argparse

parser = argparse.ArgumentParser(description='process systematics script')
parser.add_argument('--channel', default='lephad',
                    help='channel to run over (ehad, muhad, lephad)')
parser.add_argument('--campaign', default='c16a',
                    help='campaign to run over (c16a, c16d, c16e)')
parser.add_argument('--isbtag', action='store_true',
                    help='apply btag corrections or not')
parser.add_argument('--systype', default='none',
                    help='select which type of systematic to process')
parser.add_argument('--nosys', action='store_true',
                    help='dry run or not')
args = parser.parse_args()

pair = ROOT.std.pair('TString','TString')
channel = args.channel
campaign = args.campaign
b_doSys = not args.nosys
b_isbtag = args.isbtag
#### NEW!! we don't want to use mc in anti-iso region in btag category,
#### so we neeed to run this script two times - one for bveto and one for btag and give a bit different
#### sf paths

if b_isbtag:
  l_cuts=[
    'CutBtag1p',
    'CutBtag3p',
    'CutVRBtag1p',
    'CutVRBtag3p',
    'CutTCRBtag1p',
    'CutTCRBtag3p',
    'CutWCRBtag1p',
    'CutWCRBtag3p',
    ]
else:
  l_cuts=[
    'CutBveto1p',
    'CutBveto3p',
    'CutVRBveto1p',
    'CutVRBveto3p',
    #'CutTCRBveto1p',
    #'CutTCRBveto3p',
    'CutWCRBveto1p',
    'CutWCRBveto3p',
#    'CutBveto1pBDT1',
#    'CutBveto1pBDT2',
#    'CutBveto1pBDT3',
#    'CutBveto1pBDT4',
#    'CutBveto3pBDT1',
#    'CutBveto3pBDT2',
#    'CutBveto3pBDT3',
    ]

print(channel, campaign, b_isbtag, args.systype)

def main():
  handler = TQSystematicsHandler ('systematics')
  dir = 'sampleFolders/analyzed/samples-analyzed-htautau_lephad_sr-'
  #dir = 'output/htautau_lephad_vr'
  # The name of the TQSampleFolder object within your files
  # Alternatively, you can just use ':*' to have the code grab the first instance of TQSampleFolder that it finds
  sfname = ':samples'
  nominal_file_path = dir + 'NOMINAL.root' + sfname


  path_mc = '/bkg/{:s}/{:s}/[Ztautau+Zll+Top+Diboson]'.format(channel,campaign)
  path_wjets_data = '/bkg/{:s}/{:s}/Fakes/ID/data'.format(channel,campaign)
  path_wjets_mc = '/bkg/{:s}/{:s}/Fakes/ID/mc/[Ztautau+Zll+Top+Diboson]'.format(channel,campaign)
  path_wjets_qcd = '/bkg/{:s}/{:s}/Fakes/ID/ISO/data'.format(channel,campaign)
  path_qcd_data = '/bkg/{:s}/{:s}/Fakes/ISO/data'.format(channel,campaign)
  path_qcd_mc = ''
    # different sf paths because we dont use mc in btag anti-iso (qcd bkg)
  if not b_isbtag:
    path_qcd_mc = '-/bkg/{:s}/{:s}/Fakes/ISO/mc/[Ztautau+Zll+Top+Diboson]'.format(channel,campaign)
  path_qcd = path_qcd_data + path_qcd_mc

  nominal_sf_path = path_mc+'+'+path_wjets_data+'-'+path_wjets_mc+'-'+path_wjets_qcd+'+'+path_qcd


  handler.setNominalFilePath(nominal_file_path)
  handler.setNominalSampleFolderPath(nominal_sf_path)
  handler.setTagBool("lazy",True)

  # here we use similar list as in submit systematics, but we have to group them:
  # lets instead separate out the systematic types into sublists, and append them to the grand list on request
  # so first initialise the grand list of systematics
  l_systematics=[]

  l_fakevars=[
  ['fakevar',   'FakeFactor_WjetsBtag1p_1up',    'FakeFactor_WjetsBtag1p_1down'],
  ['fakevar',   'FakeFactor_WjetsBtag3p_1up',    'FakeFactor_WjetsBtag3p_1down'],
  ['fakevar',   'FakeFactor_WjetsBveto1p_1up',   'FakeFactor_WjetsBveto1p_1down'],
  ['fakevar',   'FakeFactor_WjetsBveto3p_1up',   'FakeFactor_WjetsBveto3p_1down'],
  ]

  l_bdt_fakevars=[
#  ['fakevar',   'FakeFactor_WjetsBtag1pBDT1_1up',   'FakeFactor_WjetsBtag1pBDT1_1down'],
#  ['fakevar',   'FakeFactor_WjetsBtag1pBDT2_1up',   'FakeFactor_WjetsBtag1pBDT2_1down'],
#  ['fakevar',   'FakeFactor_WjetsBtag1pBDT3_1up',   'FakeFactor_WjetsBtag1pBDT3_1down'],
#  ['fakevar',   'FakeFactor_WjetsBtag1pBDT4_1up',   'FakeFactor_WjetsBtag1pBDT4_1down'],
#  ['fakevar',   'FakeFactor_WjetsBtag3pBDT1_1up',   'FakeFactor_WjetsBtag3pBDT1_1down'],
#  ['fakevar',   'FakeFactor_WjetsBtag3pBDT2_1up',   'FakeFactor_WjetsBtag3pBDT2_1down'],
#  ['fakevar',   'FakeFactor_WjetsBtag3pBDT3_1up',   'FakeFactor_WjetsBtag3pBDT3_1down'],
#  ['fakevar',   'FakeFactor_WjetsBveto1pBDT1_1up',   'FakeFactor_WjetsBveto1pBDT1_1down'],
#  ['fakevar',   'FakeFactor_WjetsBveto1pBDT2_1up',   'FakeFactor_WjetsBveto1pBDT2_1down'],
#  ['fakevar',   'FakeFactor_WjetsBveto1pBDT3_1up',   'FakeFactor_WjetsBveto1pBDT3_1down'],
#  ['fakevar',   'FakeFactor_WjetsBveto1pBDT4_1up',   'FakeFactor_WjetsBveto1pBDT4_1down'],
#  ['fakevar',   'FakeFactor_WjetsBveto3pBDT1_1up',   'FakeFactor_WjetsBveto3pBDT1_1down'],
#  ['fakevar',   'FakeFactor_WjetsBveto3pBDT2_1up',   'FakeFactor_WjetsBveto3pBDT2_1down'],
#  ['fakevar',   'FakeFactor_WjetsBveto3pBDT3_1up',   'FakeFactor_WjetsBveto3pBDT3_1down'],
  ]

  l_isovars=[
  ['isovar',   'FakeFactor_LepElBveto_1up',   'FakeFactor_LepElBveto_1down'],
  ['isovar',   'FakeFactor_LepElBtag_1up',    'FakeFactor_LepElBtag_1down'],
  ['isovar',   'FakeFactor_LepMuBveto_1up',   'FakeFactor_LepMuBveto_1down'],
  ['isovar',   'FakeFactor_LepMuBtag_1up',    'FakeFactor_LepMuBtag_1down'],
  ]

  l_ttbarweights=[
  ['ttbarweight', 'TTBAR_Radiation_1up', 'TTBAR_Radiation_1down'],
  ['ttbarweight', 'TTBAR_ShowerUE_1up',  'TTBAR_ShowerUE_1down'],
  ]

  l_weightvars=[
#  ['weightvar', 'LPX_KFACTOR_ALPHAS_1down_lpx_kfactor', 'LPX_KFACTOR_ALPHAS_1up_lpx_kfactor'],
#  ['weightvar', 'LPX_KFACTOR_BEAM_ENERGY_1down_lpx_kfactor', 'LPX_KFACTOR_BEAM_ENERGY_1up_lpx_kfactor'],
#  ['weightvar', 'LPX_KFACTOR_CHOICE_HERAPDF20_lpx_kfactor'],
#  ['weightvar', 'LPX_KFACTOR_CHOICE_NNPDF30_lpx_kfactor'],
#  #['weightvar', 'LPX_KFACTOR_PDF_1down_lpx_kfactor', 'LPX_KFACTOR_PDF_1up_lpx_kfactor'],
#  ['weightvar', 'LPX_KFACTOR_PDF_EV1_lpx_kfactor'],
#  ['weightvar', 'LPX_KFACTOR_PDF_EV2_lpx_kfactor'],
#  ['weightvar', 'LPX_KFACTOR_PDF_EV3_lpx_kfactor'],
#  ['weightvar', 'LPX_KFACTOR_PDF_EV4_lpx_kfactor'],
#  ['weightvar', 'LPX_KFACTOR_PDF_EV5_lpx_kfactor'],
#  ['weightvar', 'LPX_KFACTOR_PDF_EV6_lpx_kfactor'],
#  ['weightvar', 'LPX_KFACTOR_PDF_EV7_lpx_kfactor'],
#  ['weightvar', 'LPX_KFACTOR_PDF_EW_1down_lpx_kfactor', 'LPX_KFACTOR_PDF_EW_1up_lpx_kfactor'],
#  ['weightvar', 'LPX_KFACTOR_PI_1down_lpx_kfactor', 'LPX_KFACTOR_PI_1up_lpx_kfactor'],
#  ['weightvar', 'LPX_KFACTOR_REDCHOICE_NNPDF30_lpx_kfactor'],
#  ['weightvar', 'LPX_KFACTOR_SCALE_W_1down_lpx_kfactor', 'LPX_KFACTOR_SCALE_W_1up_lpx_kfactor'],
#  ['weightvar', 'LPX_KFACTOR_SCALE_Z_1down_lpx_kfactor', 'LPX_KFACTOR_SCALE_Z_1up_lpx_kfactor'],
#
#
#  ['weightvar', 'mu_eff_stat_low',      'mu_eff_stat_high'],
#  ['weightvar', 'mu_eff_statlowpt_low', 'mu_eff_statlowpt_high'],
#  ['weightvar', 'mu_eff_sys_low',       'mu_eff_sys_high'],
#  ['weightvar', 'mu_eff_syslowpt_low',  'mu_eff_syslowpt_high'],
#  ['weightvar', 'mu_eff_trigstat_low',  'mu_eff_trigstat_high'],
#  ['weightvar', 'mu_eff_trigsys_low',   'mu_eff_trigsys_high'],
#  ['weightvar', 'mu_eff_isostat_low',   'mu_eff_isostat_high'],
#  ['weightvar', 'mu_eff_isosys_low',    'mu_eff_isosys_high'],
#  ['weightvar', 'mu_eff_ttvastat_low',  'mu_eff_ttvastat_high'],
#  ['weightvar', 'mu_eff_ttvasys_low',   'mu_eff_ttvasys_high'],
#
#  ['weightvar', 'el_eff_id_low',      'el_eff_id_high'],
#  ['weightvar', 'el_eff_iso_low',     'el_eff_iso_high'],
#  ['weightvar', 'el_eff_reco_low',    'el_eff_reco_high'],
#  ['weightvar', 'el_eff_trigger_low', 'el_eff_trigger_high'],
#
  ['weightvar', 'tau_eff_reco_total_low',         'tau_eff_reco_total_high'],
  ['weightvar', 'tau_eff_reco_highpt_low',        'tau_eff_reco_highpt_high'],
  ['weightvar', 'tau_eff_eleolr_trueelectron_low','tau_eff_eleolr_trueelectron_high'],
  ['weightvar', 'tau_eff_eleolr_truehadtau_low',  'tau_eff_eleolr_truehadtau_high'],
  ['weightvar', 'tau_eff_jetid_total_low', 'tau_eff_jetid_total_high'],
  ['weightvar', 'tau_eff_jetid_highpt_low', 'tau_eff_jetid_highpt_high'],
#
#  ['weightvar', 'btag_b_0_low', 'btag_b_0_high'],
#  ['weightvar', 'btag_b_1_low', 'btag_b_1_high'],
#  ['weightvar', 'btag_b_2_low', 'btag_b_2_high'],
#
#  ['weightvar', 'btag_c_0_low', 'btag_c_0_high'],
#  ['weightvar', 'btag_c_1_low', 'btag_c_1_high'],
#  ['weightvar', 'btag_c_2_low', 'btag_c_2_high'],
#
#  ['weightvar', 'btag_light_0_low', 'btag_light_0_high'],
#  ['weightvar', 'btag_light_1_low', 'btag_light_1_high'],
#  ['weightvar', 'btag_light_2_low', 'btag_light_2_high'],
#  ['weightvar', 'btag_light_3_low', 'btag_light_3_high'],
#  ['weightvar', 'btag_light_4_low', 'btag_light_4_high'],
#
#  ['weightvar', 'btag_extrapolation_low', 'btag_extrapolation_high'],
#  ['weightvar', 'btag_extrapolation_from_charm_low', 'btag_extrapolation_from_charm_high'],
#
#  ['weightvar', 'jet_jvteff_low', 'jet_jvteff_high'],
#
#  ['weightvar', 'pu_prw_high', 'pu_prw_low'],
  ]

  l_treevariations=[
#  # below the systematic must be actual tree name in ntuples
#  ['treevariation', 'MUON_ID_1down', 'MUON_ID_1up'],
#  ['treevariation', 'MUON_MS_1down', 'MUON_MS_1up'],
#  ['treevariation', 'MUON_SAGITTA_RESBIAS_1down', 'MUON_SAGITTA_RESBIAS_1up'],
#  ['treevariation', 'MUON_SAGITTA_RHO_1down', 'MUON_SAGITTA_RHO_1up'],
#  ['treevariation', 'MUON_SCALE_1down',       'MUON_SCALE_1up'],
#  ['treevariation', 'EG_RESOLUTION_ALL_1down',  'EG_RESOLUTION_ALL_1up'],
#  ['treevariation', 'EG_SCALE_ALLCORR_1down',   'EG_SCALE_ALLCORR_1up'],
#  ['treevariation', 'EG_SCALE_E4SCINTILLATOR_1down',        'EG_SCALE_E4SCINTILLATOR_1up'],
#  ['treevariation', 'EG_SCALE_LARCALIB_EXTRA2015PRE_1down', 'EG_SCALE_LARCALIB_EXTRA2015PRE_1up'],
#  ['treevariation', 'EG_SCALE_LARTEMPERATURE_EXTRA2015PRE_1down', 'EG_SCALE_LARTEMPERATURE_EXTRA2015PRE_1up'],
#  ['treevariation', 'EG_SCALE_LARTEMPERATURE_EXTRA2016PRE_1down', 'EG_SCALE_LARTEMPERATURE_EXTRA2016PRE_1up'],
  ['treevariation', 'TAUS_TRUEHADTAU_SME_TES_DETECTOR_1down',   'TAUS_TRUEHADTAU_SME_TES_DETECTOR_1up'],
  ['treevariation', 'TAUS_TRUEHADTAU_SME_TES_INSITU_1down',     'TAUS_TRUEHADTAU_SME_TES_INSITU_1up'],
  ['treevariation', 'TAUS_TRUEHADTAU_SME_TES_MODEL_1down',      'TAUS_TRUEHADTAU_SME_TES_MODEL_1up'],
#  ['treevariation', 'JET_EtaIntercalibration_NonClosure_1up', 'JET_EtaIntercalibration_NonClosure_1down'],
#  ['treevariation', 'JET_GroupedNP_1_1up', 'JET_GroupedNP_1_1down'],
#  ['treevariation', 'JET_GroupedNP_2_1up', 'JET_GroupedNP_2_1down'],
#  ['treevariation', 'JET_GroupedNP_3_1up', 'JET_GroupedNP_3_1down'],
#  ['treevariation', 'JET_JER_SINGLE_NP_1up'],
#  ['treevariation', 'JET_TILECORR_Uncertainty_1down', 'JET_TILECORR_Uncertainty_1up'],
#  ['treevariation', 'MET_SoftTrk_ResoPara'],
#  ['treevariation', 'MET_SoftTrk_ResoPerp'],
#  ['treevariation', 'MET_SoftTrk_ScaleDown', 'MET_SoftTrk_ScaleUp'],
  ]

  # now we add the systematic sublists we want to run over into the grand list
  # this is controlled by the arg parser, so I can run the show from an external submission script
  if args.systype == "fakevar":
      l_systematics.extend(l_fakevars)
  if args.systype == "isovar":
      l_systematics.extend(l_isovars)
  if args.systype == "ttbarweight":
      l_systematics.extend(l_ttbarweights)
  if args.systype == "weightvar":
      l_systematics.extend(l_weightvars)
  if args.systype == "treevariation":
      l_systematics.extend(l_treevariations)


  for sysline in l_systematics:
    option = sysline[0]
    sysup = sysline[1]
    if len(sysline) > 2:
      sysdown = sysline[2]
      name=sysup
      name=name.replace('_1up','').replace('_1down','').replace('_low','').replace('_high','')
      # Add a systematic uncertainty to the handler
      # The first argument is a string that will be used as an identifier for this uncertainty;
      # it should not contain special characters or blanks, but is otherwise arbitrary.
      # The second and optional third arguments are std::pairs of the form (file path, sample folder path)
      # where the desired systematic variation(s) reside. The ordering of the 2nd and 3rd args is arbitrary.
      handler.addSystematic(name,
      pair('{:s}{:s}.root'.format(dir,sysup), nominal_sf_path),
      pair('{:s}{:s}.root'.format(dir,sysdown), nominal_sf_path)
      )

    else: # one sided systs
      handler.addSystematic(sysup.replace('_1up','').replace('_1down','').replace('_low','').replace('_high',''),
      pair('{:s}{:s}.root'.format(dir,sysup), nominal_sf_path)
      )

  # add 10% variation on MC in anti-id region
  handler.addSystematic('MCAntiID',
      pair(nominal_file_path,  path_mc+'+'+path_wjets_data+'-0.9*'+path_wjets_mc+'-'+path_wjets_qcd+'+'+path_qcd),
      pair(nominal_file_path,  path_mc+'+'+path_wjets_data+'-1.1*'+path_wjets_mc+'-'+path_wjets_qcd+'+'+path_qcd)
      )

  # add 50% variation on MC in id anti-iso region
  if not b_isbtag:
    handler.addSystematic('MCAntiISO',
        pair(nominal_file_path, path_mc+'+'+path_wjets_data+'-'+path_wjets_mc+'-'+path_wjets_qcd+'+'+path_qcd_data+'-0.5*'+path_qcd_mc),
        pair(nominal_file_path, path_mc+'+'+path_wjets_data+'-'+path_wjets_mc+'-'+path_wjets_qcd+'+'+path_qcd_data+'-1.5*'+path_qcd_mc)
        )


  # An empty string for either path means the handler will use the respective nominal path
  # There are also convenience methods for using the nominal file path or sfolder path
  ###handler.addSystematicFromSampleFolderPath(
  ###'EGReso',
  ###'bkg/[em_EG_RESOLUTION__1down+me_EG_RESOLUTION__1down]/',
  ###'bkg/[em_EG_RESOLUTION__1up+me_EG_RESOLUTION__1up]/'
  ###)
  ## equivalent to:
  #handler.addSystematic(
  # 'EGReso',
  # pair(nominal_file_path, 'bkg/[em_EG_RESOLUTION__1down+me_EG_RESOLUTION__1down]/'),
  # pair(nominal_file_path, 'bkg/[em_EG_RESOLUTION__1up+me_EG_RESOLUTION__1up]/')
  # )

  ###handler.addSystematic(
  ###'METSoftCaloReso',
  ###dir + 'samples-run2-METSoftCaloReso.root' + sfname
  ###)
  ## equivalent to:
  #handler.addSystematic(
  # 'METSoftCaloReso',
  # pair(dir + 'samples-run2-METSoftCaloReso.root' + sfname, nominal_sf_path)
  # )
  if not b_doSys:
    return
  # Add all the cut stages at which you want to extract the systematic uncertainties to the handler
  for cut in l_cuts:
    handler.addCut(cut)

  # Have the handler print the systematic uncertainties to the console to be sure that you did 'the right thing'
  handler.printSystematics()

  # Have the handler do it's magic
  # Depending on the size of your input files and the speed of your system, this step might take some time
  handler.collectSystematics()

  # Export the systematics to an instance of TQFolder and write the 'yellow-band' to file
  systematics = handler.exportSystematics()
  bchannel='bveto'
  if b_isbtag:
    bchannel='btag'
  systematics.writeToFile(dir+'sys_band_'+campaign+'_'+channel+'_'+bchannel+'_'+option+'.root',True,0)
  # Produce a table with the ranking of systematic uncertainties at some cut stage table
  # Table.printPlain() to write it as a LaTeX and a CSV file
  for cut in l_cuts:
    table = handler.getTable(cut)
    table.writeLaTeX(dir+'sys_table_'+campaign+'_'+channel+'_'+bchannel+'_'+option+'_'+cut+'.tex')
    print(cut)
    table.printPlain()

if __name__ == "__main__":
  TQLibrary.getQLibrary().setApplicationName("createSystematics");
  main();
