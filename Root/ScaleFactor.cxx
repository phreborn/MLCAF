#include "BSMtautauCAF/ScaleFactor.h"
#include <limits>
#include <iostream>

#include "TAxis.h"
#include "TFile.h"

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

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

  ////////////////////////////////////////////////////////////////////////////////
  /// Electron related
  ////////////////////////////////////////////////////////////////////////////////
  // electron slt efficiency lepiso ???
  addScaleFactor(electron | lepiso | nominal,
    "lep_0_NOMINAL_EleEffSF_SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_2018_e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0_MediumLLH_d0z0_v13_isolGradient");
  
  Condition el_eff_trigger_low = registerVariation("el_eff_trigger_low");
  Condition el_eff_trigger_high = registerVariation("el_eff_trigger_high");
  addScaleFactor(electron | lepiso | el_eff_trigger_low,
    "lep_0_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR_1down_EleEffSF_SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_2018_e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0_MediumLLH_d0z0_v13_isolGradient");
  addScaleFactor(electron | lepiso | el_eff_trigger_high,
    "lep_0_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR_1up_EleEffSF_SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_2018_e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0_MediumLLH_d0z0_v13_isolGradient");
  
  // electron reco efficiency
  addScaleFactor(electron | nominal, "lep_0_NOMINAL_EleEffSF_offline_RecoTrk");
  
  Condition el_eff_reco_low = registerVariation("el_eff_reco_low");
  Condition el_eff_reco_high = registerVariation("el_eff_reco_high");
  addScaleFactor(electron | el_eff_reco_low, "lep_0_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR_1down_EleEffSF_offline_RecoTrk");
  addScaleFactor(electron | el_eff_reco_high, "lep_0_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR_1up_EleEffSF_offline_RecoTrk");
  
  // electron id efficiency
  addScaleFactor(electron | nominal, "lep_0_NOMINAL_EleEffSF_offline_MediumLLH_d0z0_v13");
  
  Condition el_eff_id_low = registerVariation("el_eff_id_low");
  Condition el_eff_id_high = registerVariation("el_eff_id_high");
  addScaleFactor(electron | el_eff_id_low, "lep_0_EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR_1down_EleEffSF_offline_MediumLLH_d0z0_v13");
  addScaleFactor(electron | el_eff_id_high, "lep_0_EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR_1up_EleEffSF_offline_MediumLLH_d0z0_v13");

  // electron isolation
  addScaleFactor(electron | lepiso | nominal, "lep_0_NOMINAL_EleEffSF_Isolation_MediumLLH_d0z0_v13_Gradient");
  
  Condition el_eff_iso_low = registerVariation("el_eff_iso_low");
  Condition el_eff_iso_high = registerVariation("el_eff_iso_high");
  addScaleFactor(electron | lepiso | el_eff_iso_low, "lep_0_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR_1down_EleEffSF_Isolation_MediumLLH_d0z0_v13_Gradient");
  addScaleFactor(electron | lepiso | el_eff_iso_high, "lep_0_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR_1up_EleEffSF_Isolation_MediumLLH_d0z0_v13_Gradient");

  ////////////////////////////////////////////////////////////////////////////////
  /// Muon related
  ////////////////////////////////////////////////////////////////////////////////
  // muon slt efficiency 
  // 2015
  addScaleFactor(muon | y2015 | nominal, highpt, 
    "lep_0_NOMINAL_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoNone");
  // 2016 - 2018
  addScaleFactor(muon | nominal, highpt | y2015, 
    "lep_0_NOMINAL_MuEffSF_HLT_mu26_ivarmedium_QualMedium_IsoNone");
  // high pt 
  addScaleFactor(muon | highpt | nominal, 
    "lep_0_NOMINAL_MuEffSF_HLT_mu50_QualMedium_IsoNone");

  Condition mu_eff_trigstat_low = registerVariation("mu_eff_trigstat_low");
  Condition mu_eff_trigstat_high = registerVariation("mu_eff_trigstat_high");
  Condition mu_eff_trigsys_low = registerVariation("mu_eff_trigsys_low");
  Condition mu_eff_trigsys_high = registerVariation("mu_eff_trigsys_high");
  
  // 2015 
  addScaleFactor(muon | y2015 | mu_eff_trigstat_low, highpt, 
    "lep_0_MUON_EFF_TrigStatUncertainty_1down_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoNone");
  addScaleFactor(muon | y2015 | mu_eff_trigstat_high,  highpt,
    "lep_0_MUON_EFF_TrigStatUncertainty_1up_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoNone");
  addScaleFactor(muon | y2015 | mu_eff_trigsys_low, highpt,
    "lep_0_MUON_EFF_TrigSystUncertainty_1down_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoNone");
  addScaleFactor(muon | y2015 | mu_eff_trigsys_high, highpt,
    "lep_0_MUON_EFF_TrigSystUncertainty_1up_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoNone");
  // 2016 - 2018 
  addScaleFactor(muon | mu_eff_trigstat_low,  highpt | y2015, 
    "lep_0_MUON_EFF_TrigStatnty_1down_MuEffSF_HLT_mu26_ivarmedium_QualMedium_IsoNone");
  addScaleFactor(muon | mu_eff_trigstat_high, highpt | y2015,
    "lep_0_MUON_EFF_TrigStatnty_1up_MuEffSF_HLT_mu26_ivarmedium_QualMedium_IsoNone");
  addScaleFactor(muon | mu_eff_trigsys_low,   highpt | y2015,
    "lep_0_MUON_EFF_TrigSystnty_1down_MuEffSF_HLT_mu26_ivarmedium_QualMedium_IsoNone");
  addScaleFactor(muon | mu_eff_trigsys_high,  highpt | y2015,
    "lep_0_MUON_EFF_TrigSystUncertainty_1up_MuEffSF_HLT_mu26_ivarmedium_QualMedium_IsoNone");
  // high pt 
  addScaleFactor(muon | highpt | mu_eff_trigstat_low,
    "lep_0_MUON_EFF_TrigStatUncertainty_1down_MuEffSF_HLT_mu50_QualMedium_IsoNone");
  addScaleFactor(muon | highpt | mu_eff_trigstat_high,
    "lep_0_MUON_EFF_TrigStatUncertainty_1up_MuEffSF_HLT_mu50_QualMedium_IsoNone");
  addScaleFactor(muon | highpt | mu_eff_trigsys_low,
     "lep_0_MUON_EFF_TrigSystUncertainty_1down_MuEffSF_HLT_mu50_QualMedium_IsoNone");
  addScaleFactor(muon | highpt | mu_eff_trigsys_high,
    "lep_0_MUON_EFF_TrigSystUncertainty_1up_MuEffSF_HLT_mu50_QualMedium_IsoNone");

  // muon reco efficiency
  addScaleFactor(muon | nominal , "lep_0_NOMINAL_MuEffSF_Reco_QualMedium");
  
  Condition mu_eff_stat_low = registerVariation("mu_eff_stat_low");
  addScaleFactor(muon | mu_eff_stat_low, "lep_0_MUON_EFF_RECO_STAT_1down_MuEffSF_Reco_QualMedium");
  Condition mu_eff_stat_high = registerVariation("mu_eff_stat_high");
  addScaleFactor(muon | mu_eff_stat_high, "lep_0_MUON_EFF_RECO_STAT_1up_MuEffSF_Reco_QualMedium");
  Condition mu_eff_statlowpt_low = registerVariation("mu_eff_statlowpt_low");
  addScaleFactor(muon | mu_eff_statlowpt_low, "lep_0_MUON_EFF_RECO_STAT_LOWPT_1down_MuEffSF_Reco_QualMedium");
  Condition mu_eff_statlowpt_high = registerVariation("mu_eff_statlowpt_high");
  addScaleFactor(muon | mu_eff_statlowpt_high, "lep_0_MUON_EFF_RECO_STAT_LOWPT_1up_MuEffSF_Reco_QualMedium");
  Condition mu_eff_sys_low = registerVariation("mu_eff_sys_low");
  addScaleFactor(muon | mu_eff_sys_low, "lep_0_MUON_EFF_RECO_SYS_1down_MuEffSF_Reco_QualMedium");
  Condition mu_eff_sys_high = registerVariation("mu_eff_sys_high");
  addScaleFactor(muon | mu_eff_sys_high, "lep_0_MUON_EFF_RECO_SYS_1up_MuEffSF_Reco_QualMedium");
  Condition mu_eff_syslowpt_low = registerVariation("mu_eff_syslowpt_low");
  addScaleFactor(muon | mu_eff_syslowpt_low, "lep_0_MUON_EFF_RECO_SYS_LOWPT_1down_MuEffSF_Reco_QualMedium");
  Condition mu_eff_syslowpt_high = registerVariation("mu_eff_syslowpt_high");
  addScaleFactor(muon | mu_eff_syslowpt_high, "lep_0_MUON_EFF_RECO_SYS_LOWPT_1up_MuEffSF_Reco_QualMedium");
  
  // muon isolation efficient
  addScaleFactor(muon | lepiso | nominal, "lep_0_NOMINAL_MuEffSF_IsoFCTight_FixedRad");
  
  Condition mu_eff_isostat_low = registerVariation("mu_eff_isostat_low");
  addScaleFactor(muon | lepiso | mu_eff_isostat_low, "lep_0_MUON_EFF_ISO_STAT_1down_MuEffSF_IsoFCTight_FixedRad");
  Condition mu_eff_isostat_high = registerVariation("mu_eff_isostat_high");
  addScaleFactor(muon | lepiso | mu_eff_isostat_high, "lep_0_MUON_EFF_ISO_STAT_1up_MuEffSF_IsoFCTight_FixedRad");
  Condition mu_eff_isosys_low = registerVariation("mu_eff_isosys_low");
  addScaleFactor(muon | lepiso | mu_eff_isosys_low, "lep_0_MUON_EFF_ISO_SYS_1down_MuEffSF_IsoFCTight_FixedRad");
  Condition mu_eff_isosys_high = registerVariation("mu_eff_isosys_high");
  addScaleFactor(muon | lepiso | mu_eff_isosys_high, "lep_0_MUON_EFF_ISO_SYS_1up_MuEffSF_IsoFCTight_FixedRad");
  
  // muon ttva
  addScaleFactor(muon | nominal, "lep_0_NOMINAL_MuEffSF_TTVA");
  
  Condition mu_eff_ttvastat_low = registerVariation("mu_eff_ttvastat_low");
  addScaleFactor(muon | mu_eff_ttvastat_low, "lep_0_MUON_EFF_TTVA_STAT_1down_MuEffSF_TTVA");
  Condition mu_eff_ttvastat_high = registerVariation("mu_eff_ttvastat_high");
  addScaleFactor(muon | mu_eff_ttvastat_high, "lep_0_MUON_EFF_TTVA_STAT_1up_MuEffSF_TTVA");
  Condition mu_eff_ttvasys_low = registerVariation("mu_eff_ttvasys_low");
  addScaleFactor(muon | mu_eff_ttvasys_low, "lep_0_MUON_EFF_TTVA_SYS_1down_MuEffSF_TTVA");
  Condition mu_eff_ttvasys_high = registerVariation("mu_eff_ttvasys_high");
  addScaleFactor(muon | mu_eff_ttvasys_high, "lep_0_MUON_EFF_TTVA_SYS_1up_MuEffSF_TTVA");
  
  ////////////////////////////////////////////////////////////////////////////////
  /// Tau Related
  ////////////////////////////////////////////////////////////////////////////////
  // tau reco efficiency
  addScaleFactor(nominal, "tau_0_NOMINAL_TauEffSF_selection");

  Condition tau_eff_reco_total_low = registerVariation("tau_eff_reco_total_low");
  addScaleFactor(tau_eff_reco_total_low, "tau_0_TAUS_TRUEHADTAU_EFF_RECO_TOTAL_1down_TauEffSF_selection");
  Condition tau_eff_reco_total_high = registerVariation("tau_eff_reco_total_high");
  addScaleFactor(tau_eff_reco_total_high, "tau_0_TAUS_TRUEHADTAU_EFF_RECO_TOTAL_1up_TauEffSF_selection");
  Condition tau_eff_reco_highpt_low = registerVariation("tau_eff_reco_highpt_low");
  addScaleFactor(tau_eff_reco_highpt_low, "tau_0_TAUS_TRUEHADTAU_EFF_RECO_HIGHPT_1down_TauEffSF_selection");
  Condition tau_eff_reco_highpt_high = registerVariation("tau_eff_reco_highpt_high");
  addScaleFactor(tau_eff_reco_highpt_high, "tau_0_TAUS_TRUEHADTAU_EFF_RECO_HIGHPT_1up_TauEffSF_selection");

  // tau jetid efficiency
  addScaleFactor(tauid | nominal, "tau_0_NOMINAL_TauEffSF_JetBDTmedium");
  
  Condition tau_eff_jetid_total_low = registerVariation("tau_eff_jetid_total_low");
  addScaleFactor(tauid | tau_eff_jetid_total_low, "tau_0_TAUS_TRUEHADTAU_EFF_JETID_SYST_1down_TauEffSF_JetBDTmedium");
  Condition tau_eff_jetid_total_high = registerVariation("tau_eff_jetid_total_high");
  addScaleFactor(tauid | tau_eff_jetid_total_high, "tau_0_TAUS_TRUEHADTAU_EFF_JETID_SYST_1up_TauEffSF_JetBDTmedium");
  Condition tau_eff_jetid_highpt_low = registerVariation("tau_eff_jetid_highpt_low");
  addScaleFactor(tauid | tau_eff_jetid_highpt_low, "tau_0_TAUS_TRUEHADTAU_EFF_JETID_HIGHPT_1down_TauEffSF_JetBDTmedium");
  Condition tau_eff_jetid_highpt_high = registerVariation("tau_eff_jetid_highpt_high");
  addScaleFactor(tauid | tau_eff_jetid_highpt_high, "tau_0_TAUS_TRUEHADTAU_EFF_JETID_HIGHPT_1up_TauEffSF_JetBDTmedium");
  
  // tau electron overlap removal ?????????
  Condition tau_eff_eleolr_trueele_low = registerVariation("tau_eff_eleolr_trueelectron_low");
  addScaleFactor(tau_eff_eleolr_trueele_low, "tau_0_TAUS_TRUEELECTRON_EFF_ELEOLR_SYST_1down_TauEffSF_selection");
  Condition tau_eff_eleolr_trueele_high = registerVariation("tau_eff_eleolr_trueelectron_high");
  addScaleFactor(tau_eff_eleolr_trueele_high, "tau_0_TAUS_TRUEELECTRON_EFF_ELEOLR_SYST_1up_TauEffSF_selection");
  Condition tau_eff_eleolr_truehadtau_low = registerVariation("tau_eff_eleolr_truehadtau_low");
  addScaleFactor(tau_eff_eleolr_truehadtau_low, "tau_0_TAUS_TRUEHADTAU_EFF_ELEOLR_TOTAL_1down_TauEffSF_selection");
  Condition tau_eff_eleolr_truehadtau_high = registerVariation("tau_eff_eleolr_truehadtau_high");
  addScaleFactor(tau_eff_eleolr_truehadtau_high, "tau_0_TAUS_TRUEHADTAU_EFF_ELEOLR_TOTAL_1up_TauEffSF_selection");

  ///////////////////////////////////////////////////////////////////////////////
  /// Jet Related
  ///////////////////////////////////////////////////////////////////////////////
  // jet jvt efficiency
  addScaleFactor(nominal, "jet_NOMINAL_central_jets_global_effSF_JVT");
  
  Condition jet_jvteff_low = registerVariation("jet_jvteff_low");
  addScaleFactor(jet_jvteff_low, "jet_JET_JvtEfficiency_1down_central_jets_global_effSF_JVT");
  Condition jet_jvteff_high = registerVariation("jet_jvteff_high");
  addScaleFactor(jet_jvteff_high, "jet_JET_JvtEfficiency_1up_central_jets_global_effSF_JVT");
 
  // jet jvt ineff 
  addScaleFactor(nominal, "jet_NOMINAL_central_jets_global_ineffSF_JVT");
  
  Condition jet_jvtineff_low = registerVariation("jet_jvtineff_low");
  addScaleFactor(jet_jvtineff_low, "jet_JET_JvtEfficiency_1down_central_jets_global_ineffSF_JVT");
  Condition jet_jvtineff_high = registerVariation("jet_jvtineff_high");
  addScaleFactor(jet_jvtineff_high, "jet_JET_JvtEfficiency_1up_central_jets_global_ineffSF_JVT");

  ////////////////////////////////////////////////////////////////////////////////
  /// pileup
  ////////////////////////////////////////////////////////////////////////////////
  addScaleFactor(nominal, "NOMINAL_pileup_combined_weight");

  Condition pu_prw_low = registerVariation("pu_prw_low");
  addScaleFactor(pu_prw_low, "PRW_DATASF_1down_pileup_combined_weight");
  Condition pu_prw_high = registerVariation("pu_prw_high");
  addScaleFactor(pu_prw_high, "PRW_DATASF_1up_pileup_combined_weight");
  
  ////////////////////////////////////////////////////////////////////////////////
  // btag
  ////////////////////////////////////////////////////////////////////////////////
  /// eff and inff should be anti ?????
  addScaleFactor(nominal, "jet_NOMINAL_global_effSF_MV2c10");
  addScaleFactor(nominal, "jet_NOMINAL_global_ineffSF_MV2c10");

  // b
  const int N_BTAG_B = 3;
  Condition btag_b_low[N_BTAG_B];
  Condition btag_b_high[N_BTAG_B];

  for (int i = 0; i < N_BTAG_B; i++) {
    btag_b_low[i] = registerVariation(TString::Format("btag_b_%d_low", i));
    btag_b_high[i] = registerVariation(TString::Format("btag_b_%d_high", i));

    addScaleFactor(btag_b_low[i], TString::Format("jet_FT_EFF_Eigen_B_%d_1down_global_effSF_MV2c10", i));
    addScaleFactor(btag_b_low[i], TString::Format("jet_FT_EFF_Eigen_B_%d_1down_global_ineffSF_MV2c10", i));
    addScaleFactor(btag_b_high[i], TString::Format("jet_FT_EFF_Eigen_B_%d_1up_global_effSF_MV2c10", i));
    addScaleFactor(btag_b_high[i], TString::Format("jet_FT_EFF_Eigen_B_%d_1up_global_ineffSF_MV2c10", i));
  }

  // c
  const int N_BTAG_C = 4;
  Condition btag_c_low[N_BTAG_C];
  Condition btag_c_high[N_BTAG_C];

  for (int i = 0; i < N_BTAG_C; i++) {
    btag_c_low[i] = registerVariation(TString::Format("btag_c_%d_low", i));
    btag_c_high[i] = registerVariation(TString::Format("btag_c_%d_high", i));

    addScaleFactor(btag_c_low[i], TString::Format("jet_FT_EFF_Eigen_C_%d_1down_global_effSF_MV2c10", i));
    addScaleFactor(btag_c_low[i], TString::Format("jet_FT_EFF_Eigen_C_%d_1down_global_ineffSF_MV2c10", i));
    addScaleFactor(btag_c_high[i], TString::Format("jet_FT_EFF_Eigen_C_%d_1up_global_effSF_MV2c10", i));
    addScaleFactor(btag_c_high[i], TString::Format("jet_FT_EFF_Eigen_C_%d_1up_global_ineffSF_MV2c10", i));
  }

  // light
  const int N_BTAG_LIGHT = 5;
  Condition btag_light_low[N_BTAG_LIGHT];
  Condition btag_light_high[N_BTAG_LIGHT];

  for (int i = 0; i < N_BTAG_LIGHT; i++) {
    btag_light_low[i] = registerVariation(TString::Format("btag_light_%d_low", i));
    btag_light_high[i] = registerVariation(TString::Format("btag_light_%d_high", i));

    addScaleFactor(btag_light_low[i], TString::Format("jet_FT_EFF_Eigen_Light_%d_1down_global_effSF_MV2c10", i));
    addScaleFactor(btag_light_low[i], TString::Format("jet_FT_EFF_Eigen_Light_%d_1down_global_ineffSF_MV2c10", i));
    addScaleFactor(btag_light_high[i], TString::Format("jet_FT_EFF_Eigen_Light_%d_1up_global_effSF_MV2c10", i));
    addScaleFactor(btag_light_high[i], TString::Format("jet_FT_EFF_Eigen_Light_%d_1up_global_ineffSF_MV2c10", i));
  }

  // extrapolation
  Condition btag_extrapolation_low = registerVariation("btag_extrapolation_low");
  Condition btag_extrapolation_high = registerVariation("btag_extrapolation_high");
  
  addScaleFactor(btag_extrapolation_low, "jet_FT_EFF_extrapolation_1down_global_effSF_MV2c10");
  addScaleFactor(btag_extrapolation_high, "jet_FT_EFF_extrapolation_1up_global_effSF_MV2c10");
  addScaleFactor(btag_extrapolation_low, "jet_FT_EFF_extrapolation_1down_global_ineffSF_MV2c10");
  addScaleFactor(btag_extrapolation_high, "jet_FT_EFF_extrapolation_1up_global_ineffSF_MV2c10");

  // extrapolation from charm
  Condition btag_extrapolation_from_charm_low = registerVariation("btag_extrapolation_from_charm_low");
  Condition btag_extrapolation_from_charm_high = registerVariation("btag_extrapolation_from_charm_high");

  addScaleFactor(btag_extrapolation_from_charm_low, "jet_FT_EFF_extrapolation_from_charm_1down_global_effSF_MV2c10");
  addScaleFactor(btag_extrapolation_from_charm_low, "jet_FT_EFF_extrapolation_from_charm_1down_global_ineffSF_MV2c10");
  addScaleFactor(btag_extrapolation_from_charm_high, "jet_FT_EFF_extrapolation_from_charm_1up_global_effSF_MV2c10");
  addScaleFactor(btag_extrapolation_from_charm_high, "jet_FT_EFF_extrapolation_from_charm_1up_global_ineffSF_MV2c10");

  ////////////////////////////////////////////////////////////////////////////////
  // mc weight
  ////////////////////////////////////////////////////////////////////////////////
  addScaleFactor(none, "weight_mc");
}

//______________________________________________________________________________________________
bool ScaleFactor::initializeSelf() {
  if (!LepHadObservable::initializeSelf()) {
      ERROR("Initialization of LepHadObservable failed.");
      return false;
  }

  if (fExpression == "ScaleFactor_nominal") {
     variation = nominal;
  }
  
  for (unsigned int i = 0; i < variations.size(); i++) {
    if (fExpression.EndsWith(variations[i].first)) {
        variation = variations[i].second;
    }
  }

  // These flags do not change on a sample-to-sample basis, they are constant
  // until initializeSelf is called again.

  Condition staticConditions = variation;

  for (unsigned int i = 0; i < branches.size(); i++) {
    Condition requirement = std::get<0>(branches[i]);
    Condition veto = std::get<1>(branches[i]);

    std::get<3>(branches[i]) = NULL;

    // remove those, which are already impossible due to variation
    if ((requirement & staticConditionsMask & ~staticConditions).any()) { continue; }
    if ((veto & staticConditions).any()) { continue; }

    TString name = std::get<2>(branches[i]);
    std::get<3>(branches[i]) = new TTreeFormula(name, name, this->fTree);
  }

  return true;
}

//______________________________________________________________________________________________

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

//______________________________________________________________________________________________
Condition ScaleFactor::registerVariation(TString name) {
  Condition variation;
  variation.set(nextBitPosition);
  staticConditionsMask.set(nextBitPosition);
  nextBitPosition++;


  std::pair<TString, Condition> pair(name, variation);
  variations.push_back(pair);

  return variation;
}

//______________________________________________________________________________________________
void ScaleFactor::addScaleFactor(Condition requirement, TString branch) {
  addScaleFactor(requirement, none, branch);
}

//______________________________________________________________________________________________
void ScaleFactor::addScaleFactor(Condition requirement, Condition veto, TString branch) {
  std::tuple<Condition, Condition, TString, TTreeFormula*> sf;

  std::get<0>(sf) = requirement;
  std::get<1>(sf) = veto;
  std::get<2>(sf) = branch;
  std::get<3>(sf) = NULL;

  branches.push_back(sf);
}


//______________________________________________________________________________________________
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

//______________________________________________________________________________________________

double ScaleFactor::getValue() const {

  double scaleFac = 1.;

  Condition status(variation);

  if (is2015())     { status |= y2015; }
  
  if (isHighPt())   { status |= highpt ;}
  if (isMuon())     { status |= muon; }
  if (isElectron()) { status |= electron; }
  
  if (isTauID())    { status |= tauid; }
  if (isLepISO())   { status |= lepiso; }

  // apply branches
  for (unsigned int i = 0; i < branches.size(); i++) {
    Condition requirement = std::get<0>(branches[i]);
    Condition veto = std::get<1>(branches[i]);

    // some requirements are not met
    if ((requirement & ~status).any()) { continue; }
    // some vetos are triggered
    if ((veto & status ).any()) { continue; }

    TTreeFormula* formula = std::get<3>(branches[i]);

    // skip unexpected pu weight (observed in bbH2500 sample)
    if (std::get<2>(branches[i]) == "NOMINAL_pileup_combined_weight") {
      if (fabs(formula->EvalInstance()) > 10000 ) {
        std::cout << "ERROR: unexpected pileup weight: " << formula->EvalInstance() << std::endl;
        continue;
      }
    }
    scaleFac *= formula->EvalInstance();
  }
  DEBUGclass("returning");
  return scaleFac;
}
