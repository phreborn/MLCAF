#include "BSMtautauCAF/ScaleFactor.h"
#include <limits>
#include <iostream>

#include "TAxis.h"
#include "TFile.h"
#include "TObjString.h"

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect

#include "QFramework/TQLibrary.h"

ClassImp(ScaleFactor)

//______________________________________________________________________________________________
ScaleFactor::ScaleFactor(){
  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________
ScaleFactor::~ScaleFactor(){
  // default destructor
  DEBUGclass("destructor called");
}

ScaleFactor::ScaleFactor(const TString& expression): LepHadObservable(expression) {
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);
  
  staticConditionsMask |= nominal;
  
  /*
  // Scale factor
  // MC weight: 1
  // Pileup reweight: 1 (1x2) 
  // EL: 4 (4x2)
  // MUON: 3 (6x2)
  // TAU: 2 (14x2)
  // JET: 2 (1x2)
  // Flavor Tagging: 28 (14x2)
  // Top theory uncertainty: 0 (2x2)
  */
  
  // MC weight, should always be appiled
  addScaleFactor(none, "weight_mc");
     
  /*
  // Pileup reweight: 1, systematic variations: 1x2
  // TODO: up and down variation are the same, to be checked 
  */
  
  // -- Systematic variatiions: 1x2
  Condition prw_sys = none;

  Condition prw_up = registerVariation("PRW_DATASF_1up");
  addScaleFactor(prw_up, "PRW_DATASF_1up_pileup_combined_weight");
  prw_sys |= prw_up;
  Condition prw_down = registerVariation("PRW_DATASF_1down");
  addScaleFactor(prw_down, "PRW_DATASF_1down_piledown_combined_weight");
  prw_sys |= prw_down;

  // Nominal scale factor
  addScaleFactor(none, prw_sys, "NOMINAL_pileup_combined_weight");
 
  /*
  // Electron scale factors: 4 (trigger, reco, id, iso), systematic variations: 4x2
  // If the lepton is muon, then the scale factor will be zero.
  // The scale factor should only be applied to electrons.
  */

  // Electron trigger efficiency SF
  // -- Systematic variations: 1x2 
  Condition el_eff_trigger_sys = none;

  Condition el_eff_trigger_up = registerVariation("EL_EFF_Trigger_1up");
  addScaleFactor(electron | lepiso | el_eff_trigger_up,
    "lep_0_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR_1up_EleEffSF_SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_2018_e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0_MediumLLH_d0z0_v13_isolGradient");
  el_eff_trigger_sys |= el_eff_trigger_up;
  Condition el_eff_trigger_down = registerVariation("EL_EFF_Trigger_1down");
  addScaleFactor(electron | lepiso | el_eff_trigger_down,
    "lep_0_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR_1down_EleEffSF_SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_2018_e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0_MediumLLH_d0z0_v13_isolGradient");
  el_eff_trigger_sys |= el_eff_trigger_down;
 
  // -- Nominal scale factor 
  addScaleFactor(electron | lepiso, el_eff_trigger_sys,
    "lep_0_NOMINAL_EleEffSF_SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_2018_e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0_MediumLLH_d0z0_v13_isolGradient");
  
  // Electron reconstruction efficiency SF
  // -- Systematic variations: 1x2
  Condition el_eff_reco_sys = none;

  Condition el_eff_reco_up = registerVariation("EL_EFF_Reco_TOTAL_1up");
  addScaleFactor(electron | el_eff_reco_up, "lep_0_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR_1up_EleEffSF_offline_RecoTrk");
  el_eff_reco_sys |= el_eff_reco_up;
  Condition el_eff_reco_down = registerVariation("EL_EFF_Reco_TOTAL_1down");
  addScaleFactor(electron | el_eff_reco_down, "lep_0_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR_1down_EleEffSF_offline_RecoTrk");
  el_eff_reco_sys |= el_eff_reco_down;

  // -- Nominal scale factor  
  addScaleFactor(electron, el_eff_reco_sys, "lep_0_NOMINAL_EleEffSF_offline_RecoTrk");
  
  // Electron id efficiency SF
  // -- Systematic variations: 1x2
  Condition el_eff_id_sys = none;

  Condition el_eff_id_up = registerVariation("EL_EFF_ID_TOTAL_1up");
  addScaleFactor(electron | el_eff_id_up, "lep_0_EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR_1up_EleEffSF_offline_MediumLLH_d0z0_v13");
  el_eff_id_sys |= el_eff_id_up;
  Condition el_eff_id_down = registerVariation("EL_EFF_ID_TOTAL_1down");
  addScaleFactor(electron | el_eff_id_down, "lep_0_EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR_1down_EleEffSF_offline_MediumLLH_d0z0_v13");
  el_eff_id_sys |= el_eff_id_down;

  // -- Nominal scale factor
  addScaleFactor(electron, el_eff_id_sys, "lep_0_NOMINAL_EleEffSF_offline_MediumLLH_d0z0_v13");

  // Electron isolation efficiency SF
  // SF != 1.0 for electron failing isolation, need to require lepiso when applyying the SFs
  TString eleIsoWP = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("ElectronIsoWP", eleIsoWP) ) {
    ERRORclass("ElectronIsoWP not set !!!");
  }
 
  // -- Systematic variations:  1x2
  Condition el_eff_iso_sys = none;
  
  Condition el_eff_iso_up = registerVariation("EL_EFF_Iso_TOTAL_1up"); 
  addScaleFactor(electron | lepiso | el_eff_iso_up, "lep_0_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR_1up_EleEffSF_Isolation_MediumLLH_d0z0_v13_" + eleIsoWP);
  el_eff_iso_sys |= el_eff_iso_up;
  Condition el_eff_iso_down = registerVariation("EL_EFF_Iso_TOTAL_1down");
  addScaleFactor(electron | lepiso | el_eff_iso_down, "lep_0_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR_1down_EleEffSF_Isolation_MediumLLH_d0z0_v13_" + eleIsoWP);
  el_eff_iso_sys |= el_eff_iso_down;
 
  // -- Nominal scale factor 
  addScaleFactor(electron | lepiso, el_eff_iso_sys, "lep_0_NOMINAL_EleEffSF_Isolation_MediumLLH_d0z0_v13_" + eleIsoWP);

  /*
  // Muon scale factors: 3 (trigger, reco, iso), systematic variatiions: 6x2 
  // If the lepton is electron, then the scale factor will be zero.
  // The scale factor should only be applied to electrons.
  // TTVA scale factor if not appiled since we do not apply cut on the impact parameter
  */
  
  // Muon trigger efficiency
  // -- Systematic variations: 2x2
  Condition mu_eff_trigger_sys = none;

  Condition mu_eff_trigger_stat_up = registerVariation("MUON_EFF_Trigger_STAT_1up");
  addScaleFactor(muon | y2015 | mu_eff_trigger_stat_up,  highpt,
    "lep_0_MUON_EFF_TrigStatUncertainty_1up_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium");
  addScaleFactor(muon | mu_eff_trigger_stat_up, highpt | y2015,
    "lep_0_MUON_EFF_TrigStatUncertainty_1up_MuEffSF_HLT_mu26_ivarmedium_QualMedium");
  addScaleFactor(muon | highpt | mu_eff_trigger_stat_up,
    "lep_0_MUON_EFF_TrigStatUncertainty_1up_MuEffSF_HLT_mu50_QualMedium");
  mu_eff_trigger_sys |= mu_eff_trigger_stat_up;
  Condition mu_eff_trigger_stat_down = registerVariation("MUON_EFF_Trigger_STAT_1down");
  addScaleFactor(muon | y2015 | mu_eff_trigger_stat_down,  highpt,
    "lep_0_MUON_EFF_TrigStatUncertainty_1down_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium");
  addScaleFactor(muon | mu_eff_trigger_stat_down, highpt | y2015,
    "lep_0_MUON_EFF_TrigStatUncertainty_1down_MuEffSF_HLT_mu26_ivarmedium_QualMedium");
  addScaleFactor(muon | highpt | mu_eff_trigger_stat_down,
    "lep_0_MUON_EFF_TrigStatUncertainty_1down_MuEffSF_HLT_mu50_QualMedium");
  mu_eff_trigger_sys |= mu_eff_trigger_stat_down;

  Condition mu_eff_trigger_syst_up = registerVariation("MUON_EFF_Trigger_SYST_1up");
  addScaleFactor(muon | y2015 | mu_eff_trigger_syst_up,  highpt,
    "lep_0_MUON_EFF_TrigStatUncertainty_1up_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium");
  addScaleFactor(muon | mu_eff_trigger_syst_up, highpt | y2015,
    "lep_0_MUON_EFF_TrigStatUncertainty_1up_MuEffSF_HLT_mu26_ivarmedium_QualMedium");
  addScaleFactor(muon | highpt | mu_eff_trigger_syst_up,
    "lep_0_MUON_EFF_TrigStatUncertainty_1up_MuEffSF_HLT_mu50_QualMedium");
  mu_eff_trigger_sys |= mu_eff_trigger_syst_up;
  Condition mu_eff_trigger_syst_down = registerVariation("MUON_EFF_Trigger_SYST_1down");
  addScaleFactor(muon | y2015 | mu_eff_trigger_syst_down,  highpt,
    "lep_0_MUON_EFF_TrigStatUncertainty_1down_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium");
  addScaleFactor(muon | mu_eff_trigger_syst_down, highpt | y2015,
    "lep_0_MUON_EFF_TrigStatUncertainty_1down_MuEffSF_HLT_mu26_ivarmedium_QualMedium");
  addScaleFactor(muon | highpt | mu_eff_trigger_syst_down,
    "lep_0_MUON_EFF_TrigStatUncertainty_1down_MuEffSF_HLT_mu50_QualMedium");
  mu_eff_trigger_sys |= mu_eff_trigger_syst_down;

  // -- Nominal scale factor
  addScaleFactor(muon | y2015, highpt | mu_eff_trigger_sys, 
    "lep_0_NOMINAL_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium");
  addScaleFactor(muon, highpt | y2015 | mu_eff_trigger_sys, 
    "lep_0_NOMINAL_MuEffSF_HLT_mu26_ivarmedium_QualMedium");
  addScaleFactor(muon | highpt, mu_eff_trigger_sys, 
    "lep_0_NOMINAL_MuEffSF_HLT_mu50_QualMedium");

  // Muon reconstruction efficiency
  // The analysis requires pT > 30 GeV, so lowpt variations is not needed
 
  // -- Systematic variatiions: 2x2
  Condition mu_eff_reco_sys = none;

  Condition mu_eff_reco_stat_up = registerVariation ("MUON_EFF_RECO_STAT_1up");
  addScaleFactor(muon | mu_eff_reco_stat_up, "lep_0_MUON_EFF_RECO_STAT_1up_MuEffSF_Reco_QualMedium");
  mu_eff_reco_sys |= mu_eff_reco_stat_up;
  Condition mu_eff_reco_stat_down = registerVariation ("MUON_EFF_RECO_STAT_1down");
  addScaleFactor(muon | mu_eff_reco_stat_down, "lep_0_MUON_EFF_RECO_STAT_1down_MuEffSF_Reco_QualMedium");
  mu_eff_reco_sys |= mu_eff_reco_stat_down;

  Condition mu_eff_reco_sys_up = registerVariation ("MUON_EFF_RECO_SYS_1up");
  addScaleFactor(muon | mu_eff_reco_sys_up, "lep_0_MUON_EFF_RECO_SYS_1up_MuEffSF_Reco_QualMedium");
  mu_eff_reco_sys |= mu_eff_reco_sys_up;
  Condition mu_eff_reco_sys_down = registerVariation ("MUON_EFF_RECO_SYS_1down");
  addScaleFactor(muon | mu_eff_reco_sys_down, "lep_0_MUON_EFF_RECO_SYS_1down_MuEffSF_Reco_QualMedium");
  mu_eff_reco_sys |= mu_eff_reco_sys_down;

  //  -- Nominal scale factor
  addScaleFactor(muon, mu_eff_reco_sys, "lep_0_NOMINAL_MuEffSF_Reco_QualMedium");
 
  // Muon isolation efficiency
  TString muonIsoWP = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("MuonIsoWP", muonIsoWP) ) {
    ERRORclass("MuonIsoWP not set !!!");
  }
  
  // -- Systematic variations: 2x2
  Condition mu_eff_iso_sys = none;

  Condition mu_eff_iso_stat_up = registerVariation("MUON_EFF_ISO_STAT_1up");
  addScaleFactor(muon | lepiso | mu_eff_iso_stat_up, "lep_0_MUON_EFF_ISO_STAT_1up_MuEffSF_Iso" + muonIsoWP);
  mu_eff_iso_sys |= mu_eff_iso_stat_up;
  Condition mu_eff_iso_stat_down = registerVariation("MUON_EFF_ISO_STAT_1down");
  addScaleFactor(muon | lepiso | mu_eff_iso_stat_down, "lep_0_MUON_EFF_ISO_STAT_1down_MuEffSF_Iso" + muonIsoWP);
  mu_eff_iso_sys |= mu_eff_iso_stat_down;

  Condition mu_eff_iso_sys_up = registerVariation("MUON_EFF_ISO_SYS_1up");
  addScaleFactor(muon | lepiso | mu_eff_iso_sys_up, "lep_0_MUON_EFF_ISO_SYS_1up_MuEffSF_Iso" + muonIsoWP);
  mu_eff_iso_sys |= mu_eff_iso_sys_up;
  Condition mu_eff_iso_sys_down = registerVariation("MUON_EFF_ISO_SYS_1down");
  addScaleFactor(muon | lepiso | mu_eff_iso_sys_down, "lep_0_MUON_EFF_ISO_SYS_1down_MuEffSF_Iso" + muonIsoWP);
  mu_eff_iso_sys |= mu_eff_iso_sys_down;

  // -- Nominal scale factor
  addScaleFactor(muon | lepiso, mu_eff_iso_sys, "lep_0_NOMINAL_MuEffSF_Iso" + muonIsoWP);
  
  /*
  // Tau related scale factors: 2 (reco+eveto, ID), systematic variations: 14x2 
  // Tau scale factors are only applied to those satisfying corresponding requirements
  // No need to add aditional requirement, still safe in LFR
  */

  // Tau reco + eleolr scale factor
  // -- systematic variations: 4x2
  Condition tau_eff_reco_sys = none;

  Condition tau_eff_reco_total_up = registerVariation("TAUS_TRUEHADTAU_EFF_RECO_TOTAL_1up");
  addScaleFactor(tau_eff_reco_total_up, "tau_0_TAUS_TRUEHADTAU_EFF_RECO_TOTAL_1up_TauEffSF_selection");
  tau_eff_reco_sys |= tau_eff_reco_total_up;
  Condition tau_eff_reco_total_down = registerVariation("TAUS_TRUEHADTAU_EFF_RECO_TOTAL_1down");
  addScaleFactor(tau_eff_reco_total_down, "tau_0_TAUS_TRUEHADTAU_EFF_RECO_TOTAL_1down_TauEffSF_selection");
  tau_eff_reco_sys |= tau_eff_reco_total_down;

  Condition tau_eff_eleolr_trueelectron_stat_up = registerVariation("TAUS_TRUEELECTRON_EFF_ELEBDT_STAT_1up");
  addScaleFactor(tau_eff_eleolr_trueelectron_stat_up, "tau_0_TAUS_TRUEELECTRON_EFF_ELEBDT_STAT_1up_TauEffSF_selection");
  tau_eff_reco_sys |= tau_eff_eleolr_trueelectron_stat_up;
  Condition tau_eff_eleolr_trueelectron_stat_down = registerVariation("TAUS_TRUEELECTRON_EFF_ELEBDT_STAT_1down");
  addScaleFactor(tau_eff_eleolr_trueelectron_stat_down, "tau_0_TAUS_TRUEELECTRON_EFF_ELEBDT_STAT_1down_TauEffSF_selection");
  tau_eff_reco_sys |= tau_eff_eleolr_trueelectron_stat_down;
  
  Condition tau_eff_eleolr_trueelectron_syst_up = registerVariation("TAUS_TRUEELECTRON_EFF_ELEBDT_SYST_1up");
  addScaleFactor(tau_eff_eleolr_trueelectron_syst_up, "tau_0_TAUS_TRUEELECTRON_EFF_ELEBDT_SYST_1up_TauEffSF_selection");
  tau_eff_reco_sys |= tau_eff_eleolr_trueelectron_syst_up;
  Condition tau_eff_eleolr_trueelectron_syst_down = registerVariation("TAUS_TRUEELECTRON_EFF_ELEBDT_SYST_1down");
  addScaleFactor(tau_eff_eleolr_trueelectron_syst_down, "tau_0_TAUS_TRUEELECTRON_EFF_ELEBDT_SYST_1down_TauEffSF_selection");
  tau_eff_reco_sys |= tau_eff_eleolr_trueelectron_syst_down;
  
  Condition tau_eff_eleolr_truehadtau_total_up = registerVariation("TAUS_TRUEHADTAU_EFF_ELEOLR_TOTAL_1up");
  addScaleFactor(tau_eff_eleolr_truehadtau_total_up, "tau_0_TAUS_TRUEHADTAU_EFF_ELEOLR_TOTAL_1up_TauEffSF_selection");
  tau_eff_reco_sys |= tau_eff_eleolr_truehadtau_total_up;
  Condition tau_eff_eleolr_truehadtau_total_down = registerVariation("TAUS_TRUEHADTAU_EFF_ELEOLR_TOTAL_1down");
  addScaleFactor(tau_eff_eleolr_truehadtau_total_down, "tau_0_TAUS_TRUEHADTAU_EFF_ELEOLR_TOTAL_1down_TauEffSF_selection");
  tau_eff_reco_sys |= tau_eff_eleolr_truehadtau_total_down;
  
  // -- nominal scale factor  
  addScaleFactor(none, tau_eff_reco_sys, "tau_0_NOMINAL_TauEffSF_selection");

  // TauID scale factor
  // -- TauID WP name is different for SFs and alias
  TString tauIDWP = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("TauIDWP", tauIDWP) ) {
    ERRORclass("TauIDWP not set !!! ");
  }
  tauIDWP = getTauIDWPName(tauIDWP); 

  // -- Systematic variations: 10x2  
  Condition tau_eff_rnnid_sys = none;

  Condition tau_eff_rnnid_1p_2025_up = registerVariation("TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPT2025_1up");
  addScaleFactor(tauid | tau_eff_rnnid_1p_2025_up, "tau_0_TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPT2025_1up_TauEffSF_Jet" + tauIDWP);
  tau_eff_rnnid_sys |= tau_eff_rnnid_1p_2025_up;
  Condition tau_eff_rnnid_1p_2025_down = registerVariation("TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPT2025_1down");
  addScaleFactor(tauid | tau_eff_rnnid_1p_2025_down, "tau_0_TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPT2025_1down_TauEffSF_Jet" + tauIDWP);
  tau_eff_rnnid_sys |= tau_eff_rnnid_1p_2025_down;
  
  Condition tau_eff_rnnid_1p_2530_up = registerVariation("TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPT2530_1up");
  addScaleFactor(tauid | tau_eff_rnnid_1p_2530_up, "tau_0_TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPT2530_1up_TauEffSF_Jet" + tauIDWP);
  tau_eff_rnnid_sys |= tau_eff_rnnid_1p_2530_up;
  Condition tau_eff_rnnid_1p_2530_down = registerVariation("TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPT2530_1down");
  addScaleFactor(tauid | tau_eff_rnnid_1p_2530_down, "tau_0_TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPT2530_1down_TauEffSF_Jet" + tauIDWP);
  tau_eff_rnnid_sys |= tau_eff_rnnid_1p_2530_down;
  
  Condition tau_eff_rnnid_1p_3040_up = registerVariation("TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPT3040_1up");
  addScaleFactor(tauid | tau_eff_rnnid_1p_3040_up, "tau_0_TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPT3040_1up_TauEffSF_Jet" + tauIDWP);
  tau_eff_rnnid_sys |= tau_eff_rnnid_1p_3040_up;
  Condition tau_eff_rnnid_1p_3040_down = registerVariation("TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPT3040_1down");
  addScaleFactor(tauid | tau_eff_rnnid_1p_3040_down, "tau_0_TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPT3040_1down_TauEffSF_Jet" + tauIDWP);
  tau_eff_rnnid_sys |= tau_eff_rnnid_1p_3040_down;
  
  Condition tau_eff_rnnid_1p_ge40_up = registerVariation("TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPTGE40_1up");
  addScaleFactor(tauid | tau_eff_rnnid_1p_ge40_up, "tau_0_TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPTGE40_1up_TauEffSF_Jet" + tauIDWP);
  tau_eff_rnnid_sys |= tau_eff_rnnid_1p_ge40_up;
  Condition tau_eff_rnnid_1p_ge40_down = registerVariation("TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPTGE40_1down");
  addScaleFactor(tauid | tau_eff_rnnid_1p_ge40_down, "tau_0_TAUS_TRUEHADTAU_EFF_RNNID_1PRONGSTATSYSTPTGE40_1down_TauEffSF_Jet" + tauIDWP);
  tau_eff_rnnid_sys |= tau_eff_rnnid_1p_ge40_down;
  
  Condition tau_eff_rnnid_3p_2025_up = registerVariation("TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPT2025_1up");
  addScaleFactor(tauid | tau_eff_rnnid_3p_2025_up, "tau_0_TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPT2025_1up_TauEffSF_Jet" + tauIDWP);
  tau_eff_rnnid_sys |= tau_eff_rnnid_3p_2025_up;
  Condition tau_eff_rnnid_3p_2025_down = registerVariation("TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPT2025_1down");
  addScaleFactor(tauid | tau_eff_rnnid_3p_2025_down, "tau_0_TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPT2025_1down_TauEffSF_Jet" + tauIDWP);
  tau_eff_rnnid_sys |= tau_eff_rnnid_3p_2025_down;
  
  Condition tau_eff_rnnid_3p_2530_up = registerVariation("TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPT2530_1up");
  addScaleFactor(tauid | tau_eff_rnnid_3p_2530_up, "tau_0_TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPT2530_1up_TauEffSF_Jet" + tauIDWP);
  tau_eff_rnnid_sys |= tau_eff_rnnid_3p_2530_up;
  Condition tau_eff_rnnid_3p_2530_down = registerVariation("TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPT2530_1down");
  addScaleFactor(tauid | tau_eff_rnnid_3p_2530_down, "tau_0_TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPT2530_1down_TauEffSF_Jet" + tauIDWP);
  tau_eff_rnnid_sys |= tau_eff_rnnid_3p_2530_down;
  
  Condition tau_eff_rnnid_3p_3040_up = registerVariation("TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPT3040_1up");
  addScaleFactor(tauid | tau_eff_rnnid_3p_3040_up, "tau_0_TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPT3040_1up_TauEffSF_Jet" + tauIDWP);
  tau_eff_rnnid_sys |= tau_eff_rnnid_3p_3040_up;
  Condition tau_eff_rnnid_3p_3040_down = registerVariation("TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPT3040_1down");
  addScaleFactor(tauid | tau_eff_rnnid_3p_3040_down, "tau_0_TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPT3040_1down_TauEffSF_Jet" + tauIDWP);
  tau_eff_rnnid_sys |= tau_eff_rnnid_3p_3040_down;
  
  Condition tau_eff_rnnid_3p_ge40_up = registerVariation("TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPTGE40_1up");
  addScaleFactor(tauid | tau_eff_rnnid_3p_ge40_up, "tau_0_TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPTGE40_1up_TauEffSF_Jet" + tauIDWP);
  tau_eff_rnnid_sys |= tau_eff_rnnid_3p_ge40_up;
  Condition tau_eff_rnnid_3p_ge40_down = registerVariation("TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPTGE40_1down");
  addScaleFactor(tauid | tau_eff_rnnid_3p_ge40_down, "tau_0_TAUS_TRUEHADTAU_EFF_RNNID_3PRONGSTATSYSTPTGE40_1down_TauEffSF_Jet" + tauIDWP);
  tau_eff_rnnid_sys |= tau_eff_rnnid_3p_ge40_down;
  
  Condition tau_eff_rnnid_syst_up = registerVariation("TAUS_TRUEHADTAU_EFF_RNNID_SYST_1up");  
  addScaleFactor(tauid | tau_eff_rnnid_syst_up, "tau_0_TAUS_TRUEHADTAU_EFF_RNNID_SYST_1up_TauEffSF_Jet" + tauIDWP);
  tau_eff_rnnid_sys |= tau_eff_rnnid_syst_up;
  Condition tau_eff_rnnid_syst_down = registerVariation("TAUS_TRUEHADTAU_EFF_RNNID_SYST_1down");  
  addScaleFactor(tauid | tau_eff_rnnid_syst_down, "tau_0_TAUS_TRUEHADTAU_EFF_RNNID_SYST_1down_TauEffSF_Jet" + tauIDWP);
  tau_eff_rnnid_sys |= tau_eff_rnnid_syst_down;

  Condition tau_eff_rnnid_highpt_up = registerVariation("TAUS_TRUEHADTAU_EFF_RNNID_HIGHPT_1up");
  addScaleFactor(tauid | tau_eff_rnnid_highpt_up, "tau_0_TAUS_TRUEHADTAU_EFF_RNNID_HIGHPT_1up_TauEffSF_Jet" + tauIDWP);
  tau_eff_rnnid_sys |= tau_eff_rnnid_highpt_up;
  Condition tau_eff_rnnid_highpt_down = registerVariation("TAUS_TRUEHADTAU_EFF_RNNID_HIGHPT_1down");
  addScaleFactor(tauid | tau_eff_rnnid_highpt_down, "tau_0_TAUS_TRUEHADTAU_EFF_RNNID_HIGHPT_1down_TauEffSF_Jet" + tauIDWP);
  tau_eff_rnnid_sys |= tau_eff_rnnid_highpt_down;

  // -- nominal SF
  addScaleFactor(tauid, tau_eff_rnnid_sys, "tau_0_NOMINAL_TauEffSF_Jet" + tauIDWP);

  /*
  // Jet scale factors: 2 (jvt eff, jvt ineff), systematic variations: 1x2 (anti-correlated) 
  */
  
  // Jet jvt efficiency
  // -- Systematic variations: 1x2
  Condition jet_eff_jvt_sys  = none;
  
  Condition jet_eff_jvt_up = registerVariation("JET_JvtEfficiency_1up");
  addScaleFactor(jet_eff_jvt_up, "jet_JET_JvtEfficiency_1up_central_jets_global_effSF_JVT");
  addScaleFactor(jet_eff_jvt_up, "jet_JET_JvtEfficiency_1up_central_jets_global_ineffSF_JVT");
  jet_eff_jvt_sys |= jet_eff_jvt_up;
  Condition jet_eff_jvt_down = registerVariation("JET_JvtEfficiency_1down");
  addScaleFactor(jet_eff_jvt_down, "jet_JET_JvtEfficiency_1down_central_jets_global_effSF_JVT");
  addScaleFactor(jet_eff_jvt_down, "jet_JET_JvtEfficiency_1down_central_jets_global_ineffSF_JVT");
  jet_eff_jvt_sys |= jet_eff_jvt_down;

  // -- Nominal scale factor
  addScaleFactor(none, jet_eff_jvt_sys, "jet_NOMINAL_central_jets_global_effSF_JVT");
  addScaleFactor(none, jet_eff_jvt_sys, "jet_NOMINAL_central_jets_global_ineffSF_JVT");
 
  /*
  // Flavor tagging scale factors: 28 (eff, ineff), systematic variations: 14x2 (anti-correlated) 
  */
  
  Condition btag_sys = none;

  TString btaggingWP = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("BtaggingWP", btaggingWP) ) {
    ERRORclass("BtaggingWP not set !!! ");
  }

  // Eigen_B
  // -- Systematic variations: 3x2 
  const int N_BTAG_B = 3;
  Condition btag_eigen_b_up[N_BTAG_B];
  Condition btag_eigen_b_down[N_BTAG_B];

  for (int i = 0; i < N_BTAG_B; i++) {
    btag_eigen_b_up[i] = registerVariation(TString::Format("FT_EFF_Eigen_B_%d_1up", i));
    addScaleFactor(btag_eigen_b_up[i], TString::Format("jet_FT_EFF_Eigen_B_%d_1up_global_effSF_" + btaggingWP, i));
    addScaleFactor(btag_eigen_b_up[i], TString::Format("jet_FT_EFF_Eigen_B_%d_1up_global_ineffSF_" + btaggingWP, i));
    btag_sys |= btag_eigen_b_up[i];
    
    btag_eigen_b_down[i] = registerVariation(TString::Format("FT_EFF_Eigen_B_%d_1down", i));
    addScaleFactor(btag_eigen_b_down[i], TString::Format("jet_FT_EFF_Eigen_B_%d_1down_global_effSF_" + btaggingWP, i));
    addScaleFactor(btag_eigen_b_down[i], TString::Format("jet_FT_EFF_Eigen_B_%d_1down_global_ineffSF_" + btaggingWP, i));
    btag_sys |= btag_eigen_b_down[i];
  }

  // Eigen_C
  // -- Systematic variatiions: 4x2
  const int N_BTAG_C = 4;
  Condition btag_eigen_c_up[N_BTAG_C];
  Condition btag_eigen_c_down[N_BTAG_C];

  for (int i = 0; i < N_BTAG_C; i++) {
    btag_eigen_c_up[i] = registerVariation(TString::Format("FT_EFF_Eigen_C_%d_1up", i));
    addScaleFactor(btag_eigen_c_up[i], TString::Format("jet_FT_EFF_Eigen_C_%d_1up_global_effSF_" + btaggingWP, i));
    addScaleFactor(btag_eigen_c_up[i], TString::Format("jet_FT_EFF_Eigen_C_%d_1up_global_ineffSF_" + btaggingWP, i));
    btag_sys |= btag_eigen_c_up[i];
    
    btag_eigen_c_down[i] = registerVariation(TString::Format("FT_EFF_Eigen_C_%d_1down", i));
    addScaleFactor(btag_eigen_c_down[i], TString::Format("jet_FT_EFF_Eigen_C_%d_1down_global_effSF_" + btaggingWP, i));
    addScaleFactor(btag_eigen_c_down[i], TString::Format("jet_FT_EFF_Eigen_C_%d_1down_global_ineffSF_" + btaggingWP, i));
    btag_sys |= btag_eigen_c_down[i];
  }

  // Light
  // -- Systematic variations: 5x2
  const int N_BTAG_LIGHT = 5;
  Condition btag_eigen_light_up[N_BTAG_LIGHT];
  Condition btag_eigen_light_down[N_BTAG_LIGHT];

  for (int i = 0; i < N_BTAG_LIGHT; i++) {
    btag_eigen_light_up[i] = registerVariation(TString::Format("FT_EFF_Eigen_Light_%d_1up", i));
    addScaleFactor(btag_eigen_light_up[i], TString::Format("jet_FT_EFF_Eigen_Light_%d_1up_global_effSF_" + btaggingWP, i));
    addScaleFactor(btag_eigen_light_up[i], TString::Format("jet_FT_EFF_Eigen_Light_%d_1up_global_ineffSF_" + btaggingWP, i));
    btag_sys |= btag_eigen_light_up[i];
    
    btag_eigen_light_down[i] = registerVariation(TString::Format("FT_EFF_Eigen_Light_%d_1down", i));
    addScaleFactor(btag_eigen_light_down[i], TString::Format("jet_FT_EFF_Eigen_Light_%d_1down_global_effSF_" + btaggingWP, i));
    addScaleFactor(btag_eigen_light_down[i], TString::Format("jet_FT_EFF_Eigen_Light_%d_1down_global_ineffSF_" + btaggingWP, i));
    btag_sys |= btag_eigen_light_down[i];
  }

  // Extrapolation
  // -- Systematic variations: 2x2
  Condition btag_extrapolation_up = registerVariation("FT_EFF_extrapolation_1up");
  addScaleFactor(btag_extrapolation_up, "jet_FT_EFF_extrapolation_1up_global_effSF_" + btaggingWP);
  addScaleFactor(btag_extrapolation_up, "jet_FT_EFF_extrapolation_1up_global_ineffSF_" + btaggingWP);
  btag_sys |= btag_extrapolation_up;
  Condition btag_extrapolation_down = registerVariation("FT_EFF_extrapolation_1down");
  addScaleFactor(btag_extrapolation_down, "jet_FT_EFF_extrapolation_1down_global_effSF_" + btaggingWP);
  addScaleFactor(btag_extrapolation_down, "jet_FT_EFF_extrapolation_1down_global_ineffSF_" + btaggingWP);
  btag_sys |= btag_extrapolation_down;

  Condition btag_extrapolation_from_charm_up = registerVariation("FT_EFF_extrapolation_from_charm_1up");
  addScaleFactor(btag_extrapolation_from_charm_up, "jet_FT_EFF_extrapolation_from_charm_1up_global_effSF_" + btaggingWP);
  addScaleFactor(btag_extrapolation_from_charm_up, "jet_FT_EFF_extrapolation_from_charm_1up_global_ineffSF_" + btaggingWP);
  btag_sys |= btag_extrapolation_from_charm_up;
  Condition btag_extrapolation_from_charm_down = registerVariation("FT_EFF_extrapolation_from_charm_1down");
  addScaleFactor(btag_extrapolation_from_charm_down, "jet_FT_EFF_extrapolation_from_charm_1down_global_effSF_" + btaggingWP);
  addScaleFactor(btag_extrapolation_from_charm_down, "jet_FT_EFF_extrapolation_from_charm_1down_global_ineffSF_" + btaggingWP);
  btag_sys |= btag_extrapolation_from_charm_down;
  
  // -- Nominal scale factor 
  addScaleFactor(none, btag_sys, "jet_NOMINAL_global_effSF_" + btaggingWP);
  addScaleFactor(none, btag_sys, "jet_NOMINAL_global_ineffSF_" + btaggingWP);


  /*
  // Top theory uncertainty: 0, systematic variations: 2x2
  */
  bool isTTBar = false;
  if (!this->fSample->getTag("~isTTBar", isTTBar)) {
    ERROR("tag isTTBar missing");
  }
  if ( isTTBar ) {
    // -- ISR
    //Condition ttbar_ISR_up = registerVariation("TTbar_ISR_1up");
    //addScaleFactor(ttbar_ISR_up, "pmg_truth_weight_ISRHi");
    Condition ttbar_ISR_down = registerVariation("TTbar_ISR_1down");
    addScaleFactor(ttbar_ISR_down, "pmg_truth_weight_ISRLo");

    // -- FSR
    Condition ttbar_FSR_up = registerVariation("TTbar_FSR_1up");
    addScaleFactor(ttbar_FSR_up, "pmg_truth_weight_FSRHi");
    Condition ttbar_FSR_down = registerVariation("TTbar_FSR_1down");
    addScaleFactor(ttbar_FSR_down, "pmg_truth_weight_FSRLo");
  }
}

//______________________________________________________________________________________________
bool ScaleFactor::initializeSelf() {
  if (!LepHadObservable::initializeSelf()) {
      ERROR("Initialization of LepHadObservable failed.");
      return false;
  }
  
  int sum = 0; 
  fSysName = this->fSample->replaceInTextRecursive("$(variation)","~");
  for (unsigned int i = 0; i < variations.size(); ++i) {
    if (fSysName.EndsWith(variations[i].first)) {
      variation = variations[i].second;
      ++sum;
    }
  }
  if ( 0 == sum) {
    variation = nominal;
    ++sum;
  }
   

  if (1 != sum) {
    ERROR("%s triggers %d variations !", fSysName, sum);
    throw std::runtime_error("Strange systematic:" + fSysName); 
  }

  for (unsigned int i = 0; i < branches.size(); i++) {
    Condition requirement = std::get<0>(branches[i]);
    Condition veto = std::get<1>(branches[i]);
    TString name = std::get<2>(branches[i]);
    std::get<3>(branches[i]) = NULL;

    // remove those, which are already impossible due to variation
    if ( (requirement & staticConditionsMask & ~variation).any() ) { continue; }
    if ( (veto & variation).any() ) { continue; }

    std::get<3>(branches[i]) = new TTreeFormula(name, name, this->fTree);
  }

  return true;
}



bool ScaleFactor::finalizeSelf(){

  for (unsigned int i = 0; i < branches.size(); i++) {
    TTreeFormula* formula = std::get<3>(branches[i]);
    if (formula != NULL) {
      delete formula;
      formula = NULL;
    }
  }

  return true;
}



Condition ScaleFactor::registerVariation(TString name) {
  Condition variation;
  variation.set(nextBitPosition);
  staticConditionsMask.set(nextBitPosition);
  nextBitPosition++;

  std::pair<TString, Condition> pair(name, variation);
  variations.push_back(pair);

  return variation;
}



void ScaleFactor::addScaleFactor(Condition requirement, TString branch) {
  addScaleFactor(requirement, none, branch);
}



void ScaleFactor::addScaleFactor(Condition requirement, Condition veto, TString branch) {
  std::tuple<Condition, Condition, TString, TTreeFormula*> sf;

  std::get<0>(sf) = requirement;
  std::get<1>(sf) = veto;
  std::get<2>(sf) = branch;
  std::get<3>(sf) = NULL;

  branches.push_back(sf);
}



// get the name of tau ID WP 
TString ScaleFactor::getTauIDWPName(const TString& name) const {
  TString result = "";
  if (name == "rnn_loose") {
    result = "RNNloose";
  }
  else if (name == "rnn_medium") {
    result = "RNNmedium";
  }
  else if (name == "rnn_tight") {
    result = "RNNtight";
  }
  else if (name == "bdt_loose") {
    result = "BDTloose";
  }
  else if (name == "bdt_medium") {
    result = "BDTmedium";
  }
  else if (name == "bdt_tight") {
    result = "BDTtight";
  }
  else {
    throw std::runtime_error("Unsupported TauID WP: " + name);
  }

  return result;
}



TObjArray* ScaleFactor::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();

  for (unsigned int i = 0; i < branches.size(); i++) {
    TString name = std::get<2>(branches[i]);
    bnames->Add(new TObjString(name.Data()));
  }

  return bnames;
}



double ScaleFactor::getValue() const {

  double scaleFac = 1.;

  Condition status(variation);

  if (is2015())     { status |= y2015; }
  
  if (isHighPt())   { status |= highpt ;}
  if (isMuon())     { status |= muon; }
  if (isElectron()) { status |= electron; }
  
  if (isTauID())    { status |= tauid; }
  if (isLepISO())   { status |= lepiso; }
  
  if (m_verbose) {
    VERBOSEclass("******************************************");
  }
    
  // apply branches
  for (unsigned int i = 0; i < branches.size(); i++) {
    Condition requirement = std::get<0>(branches[i]);
    Condition veto = std::get<1>(branches[i]);
    
    // some requirements are not met
    if ((requirement & ~status).any()) { continue; }

    // some vetos are triggered
    if ((veto & status ).any()) { continue; }

    // skip unexpected pu weight (observed in bbH2500 sample)
    TString name = std::get<2>(branches[i]);
    TTreeFormula* formula = std::get<3>(branches[i]);
    if (name == "NOMINAL_pileup_combined_weight") {
      if (fabs(formula->EvalInstance()) > 10000 ) {
        ERRORclass("unexpected pileup weight: %f", formula->EvalInstance());
        continue;
      }
    }
    
    if (m_verbose) { 
      VERBOSEclass("%s: %f", name.Data(), formula->EvalInstance());
    }

    scaleFac *= formula->EvalInstance();
  }
  return scaleFac;
}
