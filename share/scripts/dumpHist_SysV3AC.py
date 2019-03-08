#!/usr/bin/env python2

from array import array
import argparse
import sys
import imp

from QFramework import *
from ROOT import *

# list of all systematics, comment out the ones you don't want to run:
l_systematics=[
['fakevar',   'FakeFactor_WjetsBtag1p_1up'],
['fakevar',   'FakeFactor_WjetsBtag1p_1down'],
['fakevar',   'FakeFactor_WjetsBtag3p_1up'],
['fakevar',   'FakeFactor_WjetsBtag3p_1down'],
['fakevar',   'FakeFactor_WjetsBveto1p_1up'],
['fakevar',   'FakeFactor_WjetsBveto1p_1down'],
['fakevar',   'FakeFactor_WjetsBveto3p_1up'],
['fakevar',   'FakeFactor_WjetsBveto3p_1down'],

['isovar',   'FakeFactor_LepElBveto_1up'],
['isovar',   'FakeFactor_LepElBveto_1down'],
['isovar',   'FakeFactor_LepElBtag_1up'],
['isovar',   'FakeFactor_LepElBtag_1down'],
['isovar',   'FakeFactor_LepMuBveto_1up'],
['isovar',   'FakeFactor_LepMuBveto_1down'],
['isovar',   'FakeFactor_LepMuBtag_1up'],
['isovar',   'FakeFactor_LepMuBtag_1down'],

['weightvar', 'LPX_KFACTOR_ALPHAS_1down_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_ALPHAS_1up_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_BEAM_ENERGY_1down_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_BEAM_ENERGY_1up_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_CHOICE_HERAPDF20_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_CHOICE_NNPDF30_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_PDF_1down_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_PDF_1up_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_PDF_EV1_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_PDF_EV2_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_PDF_EV3_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_PDF_EV4_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_PDF_EV5_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_PDF_EV6_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_PDF_EV7_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_PDF_EW_1down_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_PDF_EW_1up_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_PI_1down_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_PI_1up_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_REDCHOICE_NNPDF30_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_SCALE_W_1down_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_SCALE_W_1up_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_SCALE_Z_1down_lpx_kfactor'],
['weightvar', 'LPX_KFACTOR_SCALE_Z_1up_lpx_kfactor'],

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
['weightvar', 'tau_eff_reco_highpt_low', 'tau_eff_reco_pthighpt_low'],
['weightvar', 'tau_eff_reco_highpt_high', 'tau_eff_reco_pthighpt_high'],
['weightvar', 'tau_eff_eleolr_trueelectron_low'],
['weightvar', 'tau_eff_eleolr_trueelectron_high'],
['weightvar', 'tau_eff_eleolr_truehadtau_low'],
['weightvar', 'tau_eff_eleolr_truehadtau_high'],
['weightvar', 'tau_eff_jetid_total_low'],
['weightvar', 'tau_eff_jetid_total_high'],
['weightvar', 'tau_eff_jetid_highpt_low', 'tau_eff_jetid_pthighpt_low'],
['weightvar', 'tau_eff_jetid_highpt_high', 'tau_eff_jetid_pthighpt_high'],

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

# below the systematic must be actual tree name in ntuples
['treevariation', 'MUON_ID_1down'],
['treevariation', 'MUON_ID_1up'],
['treevariation', 'MUON_MS_1down'],
['treevariation', 'MUON_MS_1up'],
['treevariation', 'MUON_SAGITTA_RESBIAS_1down'],
['treevariation', 'MUON_SAGITTA_RESBIAS_1up'],
['treevariation', 'MUON_SAGITTA_RHO_1down'],
['treevariation', 'MUON_SAGITTA_RHO_1up'],
['treevariation', 'MUON_SCALE_1down'],
['treevariation', 'MUON_SCALE_1up'],
['treevariation', 'EG_RESOLUTION_ALL_1down'],
['treevariation', 'EG_RESOLUTION_ALL_1up'],
['treevariation', 'EG_SCALE_ALLCORR_1down'],
['treevariation', 'EG_SCALE_ALLCORR_1up'],
['treevariation', 'EG_SCALE_E4SCINTILLATOR_1down'],
['treevariation', 'EG_SCALE_E4SCINTILLATOR_1up'],
['treevariation', 'EG_SCALE_LARCALIB_EXTRA2015PRE_1down'],
['treevariation', 'EG_SCALE_LARCALIB_EXTRA2015PRE_1up'],
['treevariation', 'EG_SCALE_LARTEMPERATURE_EXTRA2015PRE_1down'],
['treevariation', 'EG_SCALE_LARTEMPERATURE_EXTRA2015PRE_1up'],
['treevariation', 'EG_SCALE_LARTEMPERATURE_EXTRA2016PRE_1down'],
['treevariation', 'EG_SCALE_LARTEMPERATURE_EXTRA2016PRE_1up'],
['treevariation', 'TAUS_TRUEHADTAU_SME_TES_DETECTOR_1down'],
['treevariation', 'TAUS_TRUEHADTAU_SME_TES_DETECTOR_1up'],
['treevariation', 'TAUS_TRUEHADTAU_SME_TES_INSITU_1down'],
['treevariation', 'TAUS_TRUEHADTAU_SME_TES_INSITU_1up'],
['treevariation', 'TAUS_TRUEHADTAU_SME_TES_MODEL_1down'],
['treevariation', 'TAUS_TRUEHADTAU_SME_TES_MODEL_1up'],
['treevariation', 'JET_EtaIntercalibration_NonClosure_1up'],
['treevariation', 'JET_EtaIntercalibration_NonClosure_1down'],
['treevariation', 'JET_GroupedNP_1_1up'],
['treevariation', 'JET_GroupedNP_1_1down'],
['treevariation', 'JET_GroupedNP_2_1up'],
['treevariation', 'JET_GroupedNP_2_1down'],
['treevariation', 'JET_GroupedNP_3_1up'],
['treevariation', 'JET_GroupedNP_3_1down'],
['treevariation', 'JET_JER_SINGLE_NP_1up'],
['treevariation', 'JET_TILECORR_Uncertainty_1down'],
['treevariation', 'JET_TILECORR_Uncertainty_1up'],
['treevariation', 'MET_SoftTrk_ResoPara'],
['treevariation', 'MET_SoftTrk_ResoPerp'],
['treevariation', 'MET_SoftTrk_ScaleDown'],
['treevariation', 'MET_SoftTrk_ScaleUp']

]


def getTaggingHistogramName(tagname,histname):

  tagging=''
  histogram=''
  if 'Bveto' in tagname:
    tagging='0tag0jet'
  elif 'Btag' in tagname:
    tagging='1tag0jet'

  if 'Bveto' in histname:
    histogram='bvetoMTTOT1'
  elif 'Btag' in histname:
    histogram='btagMTTOT1'

  return tagging, histogram



def collectHistograms(mcfile,name=''):
  print 'adding ', name
  sysname=''
  if name!='':
    sysname='_'+name # so it would have the form _ATLAS_systematic__1up(1down) which is needed to append the histogram name

  # for each sample collect histos
  s_sample = {
    'Ztautau':'ZplusJets',
    '[Zmumu+Zee]':'DYZ',
    'Top':'Top',
    'Diboson':'Diboson'
    }
  s_signal = {
      'ggH125':'ggHlh125',
      'ggH300':'ggHlh300',
      'ggH700':'ggHlh700',
      'ggH1300':'ggHlh1300',
      'ggH1400':'ggHlh1400',
      'ggH1500':'ggHlh1500',

      'bbH300':'bbHlh300',
      'bbH500':'bbHlh500',
      'bbH600':'bbHlh600',
      'bbH1500':'bbHlh1500',
      'bbH1750':'bbHlh1750'
      }


  s_cat = {
    '[CutBveto1p+CutBveto3p]':'0tag0jet',
    '[CutBtag1p+CutBtag3p]':'1tag0jet'
    }

  s_ch = {
    'ehad':'ElHad',
    'muhad':'MuHad'
    }

  histogram='MTTOT'

  #have to have reader for each file
  samples = TQSampleFolder.loadLazySampleFolder(mcfile+':samples')
  reader = TQSampleDataReader(samples)
  if sysname=='':
    file.cd()
  else:
    file.cd(name)

  #get data
  if sysname=='':
    for c, cname in s_cat.iteritems():
      for ch, chname in s_ch.iteritems():
        tagging, histogram = getTaggingHistogramName(c,c)
        hist = reader.getHistogram('/data/{:s}'.format(ch),'{:s}/{:s}'.format(c,histogram))
        hist.SetName('{:s}_{:s}_0ptv_{:s}_MTtot{:s}'.format('data',tagging,chname,sysname))
        hist.Write()
  #get mc
  if (not 'Lep' in sysname and not 'Iso' in sysname and not 'Wjets' in sysname and not 'AntiID' in sysname) or sysname=='':
    for s, sname in s_sample.iteritems():
      for c, cname in s_cat.iteritems():
        for ch, chname in s_ch.iteritems():
          tagging, histogram = getTaggingHistogramName(c,c)
          hist = reader.getHistogram('/bkg/{:s}/{:s}'.format(ch,s),'{:s}/{:s}'.format(c,histogram))
          hist.SetName('{:s}_{:s}_0ptv_{:s}_MTtot{:s}'.format(sname,tagging,chname,sysname))
          hist.Write()
    #get signal
    for s, sname in s_signal.iteritems():
      for c, cname in s_cat.iteritems():
        for ch, chname in s_ch.iteritems():
          tagging, histogram = getTaggingHistogramName(c,c)
          hist = reader.getHistogram('/sig/{:s}/{:s}'.format(ch,s),'{:s}/{:s}'.format(c,histogram))
          hist.SetName('{:s}_{:s}_0ptv_{:s}_MTtot{:s}'.format(sname,tagging,chname,sysname))
          hist.Write()
  #get qcd
  if 'Lep' in sysname or 'Iso' in sysname or sysname=='':
    for c, cname in s_cat.iteritems():
      for ch, chname in s_ch.iteritems():
        tagging, histogram = getTaggingHistogramName(c,c)
        mcvar=1
        if ( ('ElAntiIso__1up' in name and ch=='ehad') or ('MuAntiIso__1up' in name and ch=='muhad') ):
          mcvar=0.5
        elif ( ('ElAntiIso__1down' in name and ch=='ehad') or ('MuAntiIso__1down' in name and ch=='muhad') ):
          mcvar=1.5

        path_qcd = '/QCDFakes/{:s}/data - {:s}*/QCDFakes/{:s}/mc/[Top+Ztautau+Diboson+Zee+Zmumu]'.format(ch,str(mcvar),ch)
        if '1tag' in tagging:
          path_qcd = '/QCDFakes/{:s}/data'.format(ch)

        hist = reader.getHistogram(path_qcd,'{:s}/{:s}'.format(c,histogram))
        hist.SetName('{:s}_{:s}_0ptv_{:s}_MTtot{:s}'.format('QCD',tagging,chname,sysname))
        hist.Write()
  #get wjets
  if 'Wjets' in sysname or 'AntiID' in sysname or 'Lep' in sysname or 'Iso' in sysname or sysname=='':
    for c, cname in s_cat.iteritems():
      for ch, chname in s_ch.iteritems():
        tagging, histogram = getTaggingHistogramName(c,c)

        mcvar=1
        if ('AntiID__1up' in name):
          mcvar=0.9
        elif ('AntiID__1down' in name):
          mcvar=1.1
        hist = reader.getHistogram('/WJETSFakes/{:s}/data - {:s}*/WJETSFakes/{:s}/bkg/[Top+Ztautau+Zee+Zmumu+Diboson] - /WJETSFakes/{:s}/bkg/QCD/data'.format(ch,str(mcvar),ch,ch),'{:s}/{:s}'.format(c,histogram))
        hist.SetName('{:s}_{:s}_0ptv_{:s}_MTtot{:s}'.format('Wjets',tagging,chname,sysname))
        hist.Write()


  samples.deleteAll()
  samples.Delete()
  reader.reset()



dir='output/htautau_lephad_sr/'

outputfile='rootfiles/lephad13TeV.root'
file = TFile(outputfile,'RECREATE')
#file = TFile(outputfile,'UPDATE')

# here I assume that all samples are in one file
mcfile=dir+'nominal_full.root'


file.cd()
collectHistograms(mcfile)

for sysline in l_systematics:
  option = sysline[0]
  systematic = sysline[1]
  sys = systematic
  if len(sysline)>2:
    sys=sysline[2]
  mcfile=dir+systematic+'_full.root'

  if 'Do' in sys or  '_1down' in sys or '_low' in sys:
    sys=sys.replace('Down','').replace('_1down','').replace('_low','').replace('Do','')
    sys=sys+'__1down'
  elif 'Up' in sys or '_1up' in sys or '_high' in sys:
    sys=sys.replace('Up','').replace('_1up','').replace('_high','')
    sys=sys+'__1up'
  else:
    sys=sys+'__1up' # for one sided sys
  sys='ATLAS_'+sys
  file.mkdir(sys)
  file.cd(sys)
  collectHistograms(mcfile,sys)
  file.cd()

for mcsys in ['ATLAS_MCSub_ElAntiIso__1up',
              'ATLAS_MCSub_ElAntiIso__1down',
              'ATLAS_MCSub_MuAntiIso__1up',
              'ATLAS_MCSub_MuAntiIso__1down',
              'ATLAS_MCSub_AntiID__1up',
              'ATLAS_MCSub_AntiID__1down'
              ]:
  mcfile=dir+'nominal_full.root'
  sys=mcsys
  file.mkdir(sys)
  file.cd(sys)
  collectHistograms(mcfile,sys)
  file.cd()


file.Close()
'''

# the alias is the 'appliation name' that will be dumped to the info tags of any
# sample folder created
alias = "plotSignificanceHistograms"
sfName = "samples"

#sflist = [
#  "sig/lephad/ggHlh1000/",
#  "sig/lephad/bbHlh1000/",
#  "sig/lephad/ggHlh400/",
#  "sig/lephad/bbHlh400/",
#  "bkg/lephad/top/",
#  "bkg/lephad/topTruthTau/",
#  "bkg/lephad/Ztt/",
#  "bkg/lephad/ZttTruthTau/",
#  "bkg/lephad/Zll/",
#  "bkg/lephad/ZllLepFake/",
#  "bkg/lephad/Wjets/",
#  "bkg/lephad/JetFake/",
#  "data/lephad/?/"]

sflist = [
  #"sig/lephad/Zprime/",
  #"sig/lephad/bbHlh2500/",
  #"sig/lephad/bbHlh2250/",
  #"sig/lephad/bbHlh2000/",
  #"sig/lephad/bbHlh1750/",
  #"sig/lephad/bbHlh1500/",
  #"sig/lephad/bbHlh1200/",
  #"sig/lephad/bbHlh1000/",
  #"sig/lephad/bbHlh800/",
  #"sig/lephad/bbHlh700/",
  #"sig/lephad/bbHlh600/",
  #"sig/lephad/bbHlh500/",
  #"sig/lephad/bbHlh400/",
  #"sig/lephad/bbHlh350/",
  "sig/?/bbH300",
  #"sig/lephad/bbHlh250/",
  #"sig/lephad/bbHlh200/",
  #"sig/lephad/bbHlh150/",
#
  #"sig/lephad/ggHlh2500/",
  #"sig/lephad/ggHlh2250/",
  #"sig/lephad/ggHlh2000/",
  #"sig/lephad/ggHlh1750/",
  #"sig/lephad/ggHlh1500/",
  #"sig/lephad/ggHlh1200/",
  #"sig/lephad/ggHlh1000/",
  #"sig/lephad/ggHlh800/",
  #"sig/lephad/ggHlh700/",
  #"sig/lephad/ggHlh600/",
  #"sig/lephad/ggHlh500/",
  #"sig/lephad/ggHlh400/",
  #"sig/lephad/ggHlh350/",
  "sig/?/ggH300",
  #"sig/lephad/ggHlh250/",
  #"sig/lephad/ggHlh200/",
  #"sig/lephad/ggHlh150/",

  "bkg/?/Diboson",
  #"bkg/lephad/dib/",
  #"bkg/lephad/dibTruthTau/",
  #"bkg/lephad/dibLepFake/",

  "bkg/?/Top",
  #"bkg/lephad/top/",
  #"bkg/lephad/topTruthTau/",
  #"bkg/lephad/topLepFake/",

  "bkg/?/Ztautau",
  #"bkg/lephad/Ztt/",
  #"bkg/lephad/ZttTruthTau/",
  #"bkg/lephad/ZttLepFake/",
  "bkg/?/[Zee+Zmumu]",


  "bkg/?/Wjets/",

  "bkg/?/JetFake/",

  #"bkg/lephad/JetFake/data/",
  #"bkg/lephad/JetFake/topTruthTau/",
  #"bkg/lephad/JetFake/topLepFake/",
  #"bkg/lephad/JetFake/ZttTruthTau/",
  #"bkg/lephad/JetFake/ZttLepFake/",
  #"bkg/lephad/JetFake/ZllLepFake/",

  "data/lephad/?/",
]
#some definitions for what to do:


varDict = {
"parentm" : "ParentM",
"LepPt" : "LepPt",
"TauPt" : "TauPt",
"TauEtaPhi" : "TauEtaPhi",
"MET"   : "MET",
"MT1"   : "MT1",
"MT2"   : "MT2",
"MT3"   : "MT3",
"mvis"  : "mvis",
"mvis2" : "mvis2",
"dphi"   : "dPhiLepTau",
"METLep" : "dPhiMETLep",
"METTau" : "dPhiMETTau",
#
"MTtotV0"  : "MTtotV0",
"MTtotV02" : "MTtotV02",
"MTtotV03" : "MTtotV03",
"MTtotV1"  : "MTtotV1",
"MTtotV12" : "MTtotV12",
"MTtotV13" : "MTtotV13",
"MTtotV4"  : "MTtot",
"MTtotV42" : "MTtot2",
"MTtotV43" : "MTtot3",
}

catDict = {
#####################
"CutMu09BTag"  : "btag",
"CutEl09BTag"  : "btag",
"CutMu09BVeto" : "bveto",
"CutEl09BVeto" : "bveto",
#"CutMu09HighMTBVeto" : "bvetohighMT",
#"CutEl09HighMTBVeto" : "bvetohighMT",
"CutMu09TCR" : "tcr",
"CutEl09TCR" : "tcr",
"CutMu08MT" : "inc",
"CutEl08MT" : "inc",
}

def setHistName(path, orgHistName):
  pathlist = path.split("/")
  #print "pathlist",pathlist
  histname = orgHistName.Data();
  #print histname
  namelist = histname.split("/")
  #print namelist
  distname = namelist.pop()
  #print distname

  #if "mvis" not in distname :
  #  print "not", distname
  #  return ""
  #if "CutWControl" not in namelist[0] :
  #  print "not", namelist[0]
  #  return ""

  histOutName=""
  if "bkg" in pathlist[0] or "sig" in pathlist[0] :
    histOutName+=pathlist[2].replace("Wjets", "Wlv")
    if "JetFake" in pathlist[2] and pathlist[3] is not '' :
      histOutName+=pathlist[3]
  else :
    histOutName+="data"

  histOutFileName=histOutName

  #if "FailedID" in namelist[0] :
  #  histOutFileName = histOutFileName.replace("0id","")
  #  histOutFileName+="_0id"
  #elif "ID" in namelist[0] :
  histOutFileName = histOutFileName.replace("1id","")
  #else :
  #  histOutFileName+="_5id"

  if "BTag" in namelist[0] or "TCR" in namelist[0] :
    histOutFileName+="_1tag"
  elif "09BVeto" in namelist[0] or "HighMTBVeto" in namelist[0] :
    histOutFileName+="_0tag"
  else :
    histOutFileName+="_inctag"

  histOutFileName+="0jet_0ptv" # match Hbb WSMaker naming

  histOutFileName+="_"

  #if "ehad"  in pathlist[1]   : histOutFileName+="ElHad"
  #elif "muhad" in pathlist[1] : histOutFileName+="MuHad"

  if "CutEl" in namelist[0]   : histOutFileName+="ElHad"
  elif "CutMu" in namelist[0] : histOutFileName+="MuHad"

  if "HighMT" in namelist[0] :
    histOutFileName+="Hmt"

  if "TCR" in namelist[0] :
    histOutFileName+="Tcr"

  #histOutFileName+=catDict[ namelist[0] ]

  #histOutFileName = histOutFileName.replace("5tag","")
  #histOutFileName = histOutFileName.replace("btag","")
  #histOutFileName = histOutFileName.replace("bveto","")

  print "Lei ",namelist[0]

  histOutFileName+="_"
  histOutFileName+=varDict[distname]

  histOutName=histOutName.replace("Wlv", "wjets")
  histOutName=histOutName.replace("Zll", "zll")
  histOutName=histOutName.replace("Ztt", "ztautau")
  histOutName="h_"+histOutName

  if "JetFake" in histOutFileName: histOutFileName = histOutFileName.replace("JetFake","Fakes")
  if "ZllLepFake" in histOutFileName: histOutFileName = histOutFileName.replace("ZllLepFake","DYZ")
  if "[dibTruthTau+dibLepFake]" in histOutFileName: histOutFileName = histOutFileName.replace("[dibTruthTau+dibLepFake]","Diboson")
  if "[topTruthTau+topLepFake]" in histOutFileName: histOutFileName = histOutFileName.replace("[topTruthTau+topLepFake]","Top")
  if "[ZttTruthTau+ZttLepFake]" in histOutFileName: histOutFileName = histOutFileName.replace("[ZttTruthTau+ZttLepFake]","ZplusJets")

  return [histOutName, histOutFileName]


def findHist(path, orgHistName ):
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

  return 1

def main(args):
  # print a welcome message
  print(TQStringUtils.makeBoldWhite("calculating mu"))

  # open the samplefile
  filepath=TString(args.inputfilepath)
  outfilepath = TString(args.outputfilepath)
  outfilepath.Prepend( "rootfiles/" )
  #outfilepath = "rootfiles/" + outfilepath
  outfile = TFile.Open(outfilepath.Data(),"RECREATE")
  INFO("reading sample file '{:s}' ".format(filepath))

  dir_sys = ROOT.TDirectory

  if args.HistFolder != "" :
    dir_sys = outfile.mkdir( args.HistFolder, args.HistFolder )

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
      print "path: ",path.split("/")
      pathlist = path.split("/")
      histname = hname.GetString().Data();
      print histname.split("/")
      namelist = histname.split("/")
      print histname
      distname = namelist.pop()
      print distname

      if findHist(path, hname.GetString() ) is 0 :
        print " not the wanted histogram "
        continue

      #if "mvis" not in distname :
      #  print "not", distname
      #  continue

      #if "CutWControl" not in namelist[0] :
      #  print "not", namelist[0]
      #  continue

      hist = reader.getHistogram(path,hname.GetString(),tags)
      print "hist add ", hist
      if not hist:
        print "not hist path ",path," hname  ",hname
        #hist = reader.getHistogram(path,hname.GetString(),tags)
        continue

      ### test
      ##hist .Rebin(100)
      ##hist .Rebin(10)
      #binning = array('d',[0, 100, 200, 300, 400, 600, 1000, 1400])
      #hist = hist .Rebin(7, "test", binning)


  ## BEFORE unblind !!!!
      #hist .Scale( 1./2.368039 )
      #hist .Scale(1./0.306)

      #if "TCR" not in str(hname) :
      #  print " Scale Hist: ",path," hname  ",hname
      #  hist.Scale(1./0.35)

      # Scale the signal for plotting
      # !!! Not for Limit !!!
      # mass  tanb  gg->H->tautau gg->A->tautau bb->H->tautau bb->A->tautau total
      # 1500  50    0.000033      0.000048      0.002615      0.002613      0.005309
      # 1000  25    0.000119      0.000313      0.006804      0.006804      0.014041
      # 800   15    0.000275      0.000949      0.007434      0.007418      0.016076
      # 600   15    0.002094      0.004789      0.029696      0.029486      0.066065
      # 400   10    0.025828      0.034147      0.075288      0.069932      0.205195
      # 250   10    0.175824      0.077584      0.502903      0.529303      1.285614

      ###if "bbHlh2000/" in path : hist.Scale(1./0.35)
      ##if "bbHlh1500/" in path : hist.Scale(0.000033 + 0.000048)
      ##if "bbHlh1000/" in path : hist.Scale(0.000119 + 0.000313)
      ##if "bbHlh800/"  in path : hist.Scale(0.000275 + 0.000949)
      ##if "bbHlh600/"  in path : hist.Scale(0.002094 + 0.004789)
      ##if "bbHlh400/"  in path : hist.Scale(0.025828 + 0.034147)
      ###if "bbHlh300/"  in path : hist.Scale()
      ###if "bbHlh200/"  in path : hist.Scale(1./0.35)

      ###if "ggHlh2000/" in path : hist.Scale(1./0.35)
      ##if "ggHlh1500/" in path : hist.Scale(0.002615 + 0.002613)
      ##if "ggHlh1000/" in path : hist.Scale(0.006804 + 0.006804)
      ##if "ggHlh800/"  in path : hist.Scale(0.007434 + 0.007418)
      ##if "ggHlh600/"  in path : hist.Scale(0.029696 + 0.029486)
      ##if "ggHlh400/"  in path : hist.Scale(0.075288 + 0.069932)
      ###if "ggHlh300/"  in path : hist.Scale(1./0.35)
      ###if "ggHlh200/"  in path : hist.Scale(1./0.35)

      #if str(path).startswith("data") :
      #  continue;

      tmppath = path.replace("?","_")

      histOutName=setHistName(path, hname.GetString() )

      if args.HistFolder != "" :
        histOutName[1] = histOutName[1] + "_" + args.HistFolder

      hist.SetNameTitle( histOutName[1], histOutName[1] )

      if hist is None: continue
      #do to hist what ever you want :)
      hist.Print()

      #ouptfilename = "inputForPlots/"
      #ouptfilename += histOutName[1]
      #ouptfilename += ".root"
      #outfile = TFile.Open( ouptfilename,"RECREATE")
      outfile.cd()

      if args.HistFolder != "" :
        dir_sys.cd()

      hist.Write()
      #outfile.Add(hist)
      del hist
  outfile.Write()
  outfile.Close()



if __name__ == "__main__":
  # parse the CLI arguments
  parser = argparse.ArgumentParser(description='calculate signal strength.')
  parser.add_argument('inputfilepath', metavar='FILEPATH', type=str,
            default="results/nominal_unblinded/samples_cutbased.root",
            help='sample file to be used')

  parser.add_argument('outputfilepath', metavar='FILEPATH', type=str,
            default="myHistograms.root",
            help='output file to be used')

  parser.add_argument('HistFolder', metavar='HistFolder', type=str,
            default="",
            help='output hist dir in root file ')
#  parser.add_argument('varWanted', metavar='varName', type=str,
#            default="mvis",
#            help='var to be getten')
  args = parser.parse_args()

  from QFramework import *
  from ROOT import *
  TQLibrary.getQLibrary().setApplicationName(alias);
  main(args);
'''