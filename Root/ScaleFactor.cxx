#include "Htautau/ScaleFactor.h"
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


ScaleFactor::ScaleFactor(const TString& expression): LepHadObservable(expression) {
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  ////////////////////////////////////////////////////////////////////////////////
  // Z samples' kfactors

 //Condition  LPX_KFACTOR_ALPHAS_1down_lpx_kfactor      = registerVariation("LPX_KFACTOR_ALPHAS_1down_lpx_kfactor");
 //Condition  LPX_KFACTOR_ALPHAS_1up_lpx_kfactor        = registerVariation("LPX_KFACTOR_ALPHAS_1up_lpx_kfactor");
 //Condition  LPX_KFACTOR_BEAM_ENERGY_1down_lpx_kfactor = registerVariation("LPX_KFACTOR_BEAM_ENERGY_1down_lpx_kfactor");
 //Condition  LPX_KFACTOR_BEAM_ENERGY_1up_lpx_kfactor   = registerVariation("LPX_KFACTOR_BEAM_ENERGY_1up_lpx_kfactor");
 //Condition  LPX_KFACTOR_CHOICE_HERAPDF20_lpx_kfactor  = registerVariation("LPX_KFACTOR_CHOICE_HERAPDF20_lpx_kfactor");
 //Condition  LPX_KFACTOR_CHOICE_NNPDF30_lpx_kfactor    = registerVariation("LPX_KFACTOR_CHOICE_NNPDF30_lpx_kfactor");
 //Condition  LPX_KFACTOR_PDF_1down_lpx_kfactor         = registerVariation("LPX_KFACTOR_PDF_1down_lpx_kfactor");
 //Condition  LPX_KFACTOR_PDF_1up_lpx_kfactor           = registerVariation("LPX_KFACTOR_PDF_1up_lpx_kfactor");
 //Condition  LPX_KFACTOR_PDF_EV1_lpx_kfactor           = registerVariation("LPX_KFACTOR_PDF_EV1_lpx_kfactor");
 //Condition  LPX_KFACTOR_PDF_EV2_lpx_kfactor           = registerVariation("LPX_KFACTOR_PDF_EV2_lpx_kfactor");
 //Condition  LPX_KFACTOR_PDF_EV3_lpx_kfactor           = registerVariation("LPX_KFACTOR_PDF_EV3_lpx_kfactor");
 //Condition  LPX_KFACTOR_PDF_EV4_lpx_kfactor           = registerVariation("LPX_KFACTOR_PDF_EV4_lpx_kfactor");
 //Condition  LPX_KFACTOR_PDF_EV5_lpx_kfactor           = registerVariation("LPX_KFACTOR_PDF_EV5_lpx_kfactor");
 //Condition  LPX_KFACTOR_PDF_EV6_lpx_kfactor           = registerVariation("LPX_KFACTOR_PDF_EV6_lpx_kfactor");
 //Condition  LPX_KFACTOR_PDF_EV7_lpx_kfactor           = registerVariation("LPX_KFACTOR_PDF_EV7_lpx_kfactor");
 //Condition  LPX_KFACTOR_PDF_EW_1down_lpx_kfactor      = registerVariation("LPX_KFACTOR_PDF_EW_1down_lpx_kfactor");
 //Condition  LPX_KFACTOR_PDF_EW_1up_lpx_kfactor        = registerVariation("LPX_KFACTOR_PDF_EW_1up_lpx_kfactor");
 //Condition  LPX_KFACTOR_PI_1down_lpx_kfactor          = registerVariation("LPX_KFACTOR_PI_1down_lpx_kfactor");
 //Condition  LPX_KFACTOR_PI_1up_lpx_kfactor            = registerVariation("LPX_KFACTOR_PI_1up_lpx_kfactor");
 //Condition  LPX_KFACTOR_REDCHOICE_NNPDF30_lpx_kfactor = registerVariation("LPX_KFACTOR_REDCHOICE_NNPDF30_lpx_kfactor");
 //Condition  LPX_KFACTOR_SCALE_W_1down_lpx_kfactor     = registerVariation("LPX_KFACTOR_SCALE_W_1down_lpx_kfactor");
 //Condition  LPX_KFACTOR_SCALE_W_1up_lpx_kfactor       = registerVariation("LPX_KFACTOR_SCALE_W_1up_lpx_kfactor");
 //Condition  LPX_KFACTOR_SCALE_Z_1down_lpx_kfactor     = registerVariation("LPX_KFACTOR_SCALE_Z_1down_lpx_kfactor");
 //Condition  LPX_KFACTOR_SCALE_Z_1up_lpx_kfactor       = registerVariation("LPX_KFACTOR_SCALE_Z_1up_lpx_kfactor");

 //addScaleFactor( isZ,
 //                LPX_KFACTOR_ALPHAS_1down_lpx_kfactor |
 //                LPX_KFACTOR_ALPHAS_1up_lpx_kfactor |
 //                LPX_KFACTOR_BEAM_ENERGY_1down_lpx_kfactor |
 //                LPX_KFACTOR_BEAM_ENERGY_1up_lpx_kfactor |
 //                LPX_KFACTOR_CHOICE_HERAPDF20_lpx_kfactor |
 //                LPX_KFACTOR_CHOICE_NNPDF30_lpx_kfactor |
 //                LPX_KFACTOR_PDF_1down_lpx_kfactor |
 //                LPX_KFACTOR_PDF_1up_lpx_kfactor |
 //                LPX_KFACTOR_PDF_EV1_lpx_kfactor |
 //                LPX_KFACTOR_PDF_EV2_lpx_kfactor |
 //                LPX_KFACTOR_PDF_EV3_lpx_kfactor |
 //                LPX_KFACTOR_PDF_EV4_lpx_kfactor |
 //                LPX_KFACTOR_PDF_EV5_lpx_kfactor |
 //                LPX_KFACTOR_PDF_EV6_lpx_kfactor |
 //                LPX_KFACTOR_PDF_EV7_lpx_kfactor |
 //                LPX_KFACTOR_PDF_EW_1down_lpx_kfactor |
 //                LPX_KFACTOR_PDF_EW_1up_lpx_kfactor |
 //                LPX_KFACTOR_PI_1down_lpx_kfactor |
 //                LPX_KFACTOR_PI_1up_lpx_kfactor |
 //                LPX_KFACTOR_REDCHOICE_NNPDF30_lpx_kfactor |
 //                LPX_KFACTOR_SCALE_W_1down_lpx_kfactor |
 //                LPX_KFACTOR_SCALE_W_1up_lpx_kfactor |
 //                LPX_KFACTOR_SCALE_Z_1down_lpx_kfactor |
 //                LPX_KFACTOR_SCALE_Z_1up_lpx_kfactor,  "NOMINAL_lpx_kfactor");

 //addScaleFactor(isZ | LPX_KFACTOR_ALPHAS_1down_lpx_kfactor,      "LPX_KFACTOR_ALPHAS_1down_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_ALPHAS_1up_lpx_kfactor,        "LPX_KFACTOR_ALPHAS_1up_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_BEAM_ENERGY_1down_lpx_kfactor, "LPX_KFACTOR_BEAM_ENERGY_1down_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_BEAM_ENERGY_1up_lpx_kfactor,   "LPX_KFACTOR_BEAM_ENERGY_1up_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_CHOICE_HERAPDF20_lpx_kfactor,  "LPX_KFACTOR_CHOICE_HERAPDF20_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_CHOICE_NNPDF30_lpx_kfactor,    "LPX_KFACTOR_CHOICE_NNPDF30_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_PDF_1down_lpx_kfactor,         "LPX_KFACTOR_PDF_1down_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_PDF_1up_lpx_kfactor,           "LPX_KFACTOR_PDF_1up_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_PDF_EV1_lpx_kfactor,           "LPX_KFACTOR_PDF_EV1_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_PDF_EV2_lpx_kfactor,           "LPX_KFACTOR_PDF_EV2_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_PDF_EV3_lpx_kfactor,           "LPX_KFACTOR_PDF_EV3_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_PDF_EV4_lpx_kfactor,           "LPX_KFACTOR_PDF_EV4_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_PDF_EV5_lpx_kfactor,           "LPX_KFACTOR_PDF_EV5_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_PDF_EV6_lpx_kfactor,           "LPX_KFACTOR_PDF_EV6_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_PDF_EV7_lpx_kfactor,           "LPX_KFACTOR_PDF_EV7_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_PDF_EW_1down_lpx_kfactor,      "LPX_KFACTOR_PDF_EW_1down_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_PDF_EW_1up_lpx_kfactor,        "LPX_KFACTOR_PDF_EW_1up_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_PI_1down_lpx_kfactor,          "LPX_KFACTOR_PI_1down_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_PI_1up_lpx_kfactor,            "LPX_KFACTOR_PI_1up_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_REDCHOICE_NNPDF30_lpx_kfactor, "LPX_KFACTOR_REDCHOICE_NNPDF30_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_SCALE_W_1down_lpx_kfactor,     "LPX_KFACTOR_SCALE_W_1down_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_SCALE_W_1up_lpx_kfactor,       "LPX_KFACTOR_SCALE_W_1up_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_SCALE_Z_1down_lpx_kfactor,     "LPX_KFACTOR_SCALE_Z_1down_lpx_kfactor");
 //addScaleFactor(isZ | LPX_KFACTOR_SCALE_Z_1up_lpx_kfactor,       "LPX_KFACTOR_SCALE_Z_1up_lpx_kfactor");

  ////////////////////////////////////////////////////////////////////////////////
  // muon slt efficiency
  Condition mu_eff_trigstat_low = registerVariation("mu_eff_trigstat_low");
  Condition mu_eff_trigstat_high = registerVariation("mu_eff_trigstat_high");
  Condition mu_eff_trigsys_low = registerVariation("mu_eff_trigsys_low");
  Condition mu_eff_trigsys_high = registerVariation("mu_eff_trigsys_high");

  // muon slt efficiency 2015
  addScaleFactor(muon | slt | y2015,
    highpt | mu_eff_trigstat_low | mu_eff_trigstat_high | mu_eff_trigsys_low | mu_eff_trigsys_high,
    "lep_0_NOMINAL_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoNone");

  addScaleFactor(muon | slt | y2015 | mu_eff_trigstat_low,
    "lep_0_MUON_EFF_TrigStatUncertainty_1down_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoNone");

  addScaleFactor(muon | slt | y2015 | mu_eff_trigstat_high,
    "lep_0_MUON_EFF_TrigStatUncertainty_1up_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoNone");

  addScaleFactor(muon | slt | y2015 | mu_eff_trigsys_low,
    "lep_0_MUON_EFF_TrigSystUncertainty_1down_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoNone");

  addScaleFactor(muon | slt | y2015 | mu_eff_trigsys_high,
    "lep_0_MUON_EFF_TrigSystUncertainty_1up_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoNone");

  // muon slt efficient 2016
  addScaleFactor(muon | slt | y2016,
    highpt | mu_eff_trigstat_low | mu_eff_trigstat_high | mu_eff_trigsys_low | mu_eff_trigsys_high,
    "lep_0_NOMINAL_MuEffSF_HLT_mu26_ivarmedium_QualMedium_IsoNone");

  addScaleFactor(muon | slt | y2016 | mu_eff_trigstat_low,
    "lep_0_MUON_EFF_TrigStatUncertainty_1down_MuEffSF_HLT_mu26_ivarmedium_QualMedium_IsoNone");

  addScaleFactor(muon | slt | y2016 | mu_eff_trigstat_high,
    "lep_0_MUON_EFF_TrigStatUncertainty_1up_MuEffSF_HLT_mu26_ivarmedium_QualMedium_IsoNone");

  addScaleFactor(muon | slt | y2016 | mu_eff_trigsys_low,
     "lep_0_MUON_EFF_TrigSystUncertainty_1down_MuEffSF_HLT_mu26_ivarmedium_QualMedium_IsoNone");

  addScaleFactor(muon | slt | y2016 | mu_eff_trigsys_high,
    "lep_0_MUON_EFF_TrigSystUncertainty_1up_MuEffSF_HLT_mu26_ivarmedium_QualMedium_IsoNone");

  // muon slt efficiency high pt
   addScaleFactor(muon | slt | highpt,
    mu_eff_trigstat_low | mu_eff_trigstat_high | mu_eff_trigsys_low | mu_eff_trigsys_high,
    "lep_0_NOMINAL_MuEffSF_HLT_mu50_QualMedium_IsoNone");

  addScaleFactor(muon | slt | highpt | mu_eff_trigstat_low,
    "lep_0_MUON_EFF_TrigStatUncertainty_1down_MuEffSF_HLT_mu50_QualMedium_IsoNone");

  addScaleFactor(muon | slt | highpt | mu_eff_trigstat_high,
    "lep_0_MUON_EFF_TrigStatUncertainty_1up_MuEffSF_HLT_mu50_QualMedium_IsoNone");

  addScaleFactor(muon | slt | highpt | mu_eff_trigsys_low,
     "lep_0_MUON_EFF_TrigSystUncertainty_1down_MuEffSF_HLT_mu50_QualMedium_IsoNone");

  addScaleFactor(muon | slt | highpt | mu_eff_trigsys_high,
    "lep_0_MUON_EFF_TrigSystUncertainty_1up_MuEffSF_HLT_mu50_QualMedium_IsoNone");

/*  ////////////////////////////////////////////////////////////////////////////////
  // tau tlt efficiency
  Condition tau_trigger_statdata_low = registerVariation("tau_trigger_statdata_low");
  Condition tau_trigger_statdata_high = registerVariation("tau_trigger_statdata_high");
  Condition tau_trigger_statmc_low = registerVariation("tau_trigger_statmc_low");
  Condition tau_trigger_statmc_high = registerVariation("tau_trigger_statmc_high");
  Condition tau_trigger_syst_low = registerVariation("tau_trigger_syst_low");
  Condition tau_trigger_syst_high = registerVariation("tau_trigger_syst_high");
  Condition tau_trigger_total2016_low = registerVariation("tau_trigger_total2016_low");
  Condition tau_trigger_total2016_high = registerVariation("tau_trigger_total2016_high");

  // tau tlt efficiency 2015
  addScaleFactor(tlt | y2015,
    tau_trigger_statdata_low | tau_trigger_statdata_high | tau_trigger_statmc_low | tau_trigger_statmc_high | tau_trigger_syst_low | tau_trigger_syst_high,
    "tau_0_NOMINAL_TauEffSF_HLT_tau25_medium1_tracktwo_JETIDBDTMEDIUM");

  addScaleFactor(tlt | y2015 | tau_trigger_statdata_low,
    "tau_0_TAUS_TRUEHADTAU_EFF_TRIGGER_STATDATA2015_1down_TauEffSF_HLT_tau25_medium1_tracktwo_JETIDBDTMEDIUM");

  addScaleFactor(tlt | y2015 | tau_trigger_statdata_high,
    "tau_0_TAUS_TRUEHADTAU_EFF_TRIGGER_STATDATA2015_1up_TauEffSF_HLT_tau25_medium1_tracktwo_JETIDBDTMEDIUM");

  addScaleFactor(tlt | y2015 | tau_trigger_statmc_low,
    "tau_0_TAUS_TRUEHADTAU_EFF_TRIGGER_STATMC2015_1down_TauEffSF_HLT_tau25_medium1_tracktwo_JETIDBDTMEDIUM");

  addScaleFactor(tlt | y2015 | tau_trigger_statmc_high,
    "tau_0_TAUS_TRUEHADTAU_EFF_TRIGGER_STATMC2015_1up_TauEffSF_HLT_tau25_medium1_tracktwo_JETIDBDTMEDIUM");

  addScaleFactor(tlt | y2015 | tau_trigger_syst_low,
    "tau_0_TAUS_TRUEHADTAU_EFF_TRIGGER_SYST2015_1down_TauEffSF_HLT_tau25_medium1_tracktwo_JETIDBDTMEDIUM");

  addScaleFactor(tlt | y2015 | tau_trigger_syst_high,
    "tau_0_TAUS_TRUEHADTAU_EFF_TRIGGER_SYST2015_1up_TauEffSF_HLT_tau25_medium1_tracktwo_JETIDBDTMEDIUM");

  // tau tlt efficiency 2016
  addScaleFactor(tlt | y2016,
    tau_trigger_total2016_low | tau_trigger_total2016_high,
    "tau_0_NOMINAL_TauEffSF_HLT_tau25_medium1_tracktwo_JETIDBDTMEDIUM");

  addScaleFactor(tlt | y2016 | tau_trigger_total2016_low,
    "tau_0_TAUS_TRUEHADTAU_EFF_TRIGGER_TOTAL2016_1down_TauEffSF_HLT_tau25_medium1_tracktwo_JETIDBDTMEDIUM");

  addScaleFactor(tlt | y2016 | tau_trigger_total2016_high,
    "tau_0_TAUS_TRUEHADTAU_EFF_TRIGGER_TOTAL2016_1up_TauEffSF_HLT_tau25_medium1_tracktwo_JETIDBDTMEDIUM");


*/  ////////////////////////////////////////////////////////////////////////////////
  // electron slt efficiency
  Condition el_eff_trigger_low = registerVariation("el_eff_trigger_low");
  Condition el_eff_trigger_high = registerVariation("el_eff_trigger_high");

  addScaleFactor(electron | slt,
    el_eff_trigger_low | el_eff_trigger_high,
    "lep_0_NOMINAL_EleEffSF_SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_2017_e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0_MediumLLH_d0z0_v13_isolGradient");

  addScaleFactor(electron | slt | el_eff_trigger_low,
    "lep_0_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR_1down_EleEffSF_SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0_MediumLLH_d0z0_v13_isolGradient");

  addScaleFactor(electron | slt | el_eff_trigger_high,
    "lep_0_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR_1up_EleEffSF_SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_e26_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0_MediumLLH_d0z0_v13_isolGradient");


  ////////////////////////////////////////////////////////////////////////////////
  // electron id efficiency
  Condition el_eff_id_low = registerVariation("el_eff_id_low");
  Condition el_eff_id_high = registerVariation("el_eff_id_high");

  addScaleFactor(electron,
    el_eff_id_low | el_eff_id_high,
    "lep_0_NOMINAL_EleEffSF_offline_MediumLLH_d0z0_v13");

  addScaleFactor(electron | el_eff_id_low,
    "lep_0_EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR_1down_EleEffSF_offline_MediumLLH_d0z0_v13");

  addScaleFactor(electron | el_eff_id_high,
    "lep_0_EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR_1up_EleEffSF_offline_MediumLLH_d0z0_v13");

  ////////////////////////////////////////////////////////////////////////////////
  // electron reco efficiency
  Condition el_eff_reco_low = registerVariation("el_eff_reco_low");
  Condition el_eff_reco_high = registerVariation("el_eff_reco_high");

  addScaleFactor(electron,
    el_eff_reco_low | el_eff_reco_high,
    "lep_0_NOMINAL_EleEffSF_offline_RecoTrk");

  addScaleFactor(electron | el_eff_reco_low,
    "lep_0_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR_1down_EleEffSF_offline_RecoTrk");

  addScaleFactor(electron | el_eff_reco_high,
    "lep_0_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR_1up_EleEffSF_offline_RecoTrk");

  ////////////////////////////////////////////////////////////////////////////////
  // electron isolation
  Condition el_eff_iso_low = registerVariation("el_eff_iso_low");
  Condition el_eff_iso_high = registerVariation("el_eff_iso_high");

  addScaleFactor(electron,
    el_eff_iso_low | el_eff_iso_high,
    "lep_0_NOMINAL_EleEffSF_Isolation_MediumLLH_d0z0_v13_isolGradient");

  addScaleFactor(electron | el_eff_iso_low,
    "lep_0_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR_1down_EleEffSF_Isolation_MediumLLH_d0z0_v13_isolGradient");

  addScaleFactor(electron | el_eff_iso_high,
    "lep_0_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR_1up_EleEffSF_Isolation_MediumLLH_d0z0_v13_isolGradient");

  ////////////////////////////////////////////////////////////////////////////////
  // muon reco efficiency
  Condition mu_eff_stat_low = registerVariation("mu_eff_stat_low");
  Condition mu_eff_stat_high = registerVariation("mu_eff_stat_high");
  Condition mu_eff_statlowpt_low = registerVariation("mu_eff_statlowpt_low");
  Condition mu_eff_statlowpt_high = registerVariation("mu_eff_statlowpt_high");
  Condition mu_eff_sys_low = registerVariation("mu_eff_sys_low");
  Condition mu_eff_sys_high = registerVariation("mu_eff_sys_high");
  Condition mu_eff_syslowpt_low = registerVariation("mu_eff_syslowpt_low");
  Condition mu_eff_syslowpt_high = registerVariation("mu_eff_syslowpt_high");

  addScaleFactor(muon,
    mu_eff_stat_low | mu_eff_stat_high | mu_eff_statlowpt_low | mu_eff_statlowpt_high | mu_eff_sys_low | mu_eff_sys_high | mu_eff_syslowpt_low | mu_eff_syslowpt_high,
    "lep_0_NOMINAL_MuEffSF_Reco_QualMedium");

  addScaleFactor(muon | mu_eff_stat_low,
    "lep_0_MUON_EFF_STAT_1down_MuEffSF_Reco_QualMedium");

  addScaleFactor(muon | mu_eff_stat_high,
    "lep_0_MUON_EFF_STAT_1up_MuEffSF_Reco_QualMedium");

  addScaleFactor(muon | mu_eff_statlowpt_low,
    "lep_0_MUON_EFF_STAT_LOWPT_1down_MuEffSF_Reco_QualMedium");

  addScaleFactor(muon | mu_eff_statlowpt_high,
    "lep_0_MUON_EFF_STAT_LOWPT_1up_MuEffSF_Reco_QualMedium");

  addScaleFactor(muon | mu_eff_sys_low,
    "lep_0_MUON_EFF_SYS_1down_MuEffSF_Reco_QualMedium");

  addScaleFactor(muon | mu_eff_sys_high,
    "lep_0_MUON_EFF_SYS_1up_MuEffSF_Reco_QualMedium");

  addScaleFactor(muon | mu_eff_syslowpt_low,
    "lep_0_MUON_EFF_SYS_LOWPT_1down_MuEffSF_Reco_QualMedium");

  addScaleFactor(muon | mu_eff_syslowpt_high,
    "lep_0_MUON_EFF_SYS_LOWPT_1up_MuEffSF_Reco_QualMedium");

  ////////////////////////////////////////////////////////////////////////////////
  // muon isolation efficient
  Condition mu_eff_isostat_low = registerVariation("mu_eff_isostat_low");
  Condition mu_eff_isostat_high = registerVariation("mu_eff_isostat_high");
  Condition mu_eff_isosys_low = registerVariation("mu_eff_isosys_low");
  Condition mu_eff_isosys_high = registerVariation("mu_eff_isosys_high");

  addScaleFactor(muon,
   mu_eff_isostat_low | mu_eff_isostat_high | mu_eff_isosys_low | mu_eff_isosys_high,
   "lep_0_NOMINAL_MuEffSF_IsoGradient");

  addScaleFactor(muon | mu_eff_isostat_low,
   "lep_0_MUON_ISO_STAT_1down_MuEffSF_IsoGradient");

  addScaleFactor(muon | mu_eff_isostat_high,
   "lep_0_MUON_ISO_STAT_1up_MuEffSF_IsoGradient");

  addScaleFactor(muon | mu_eff_isosys_low,
   "lep_0_MUON_ISO_SYS_1down_MuEffSF_IsoGradient");

  addScaleFactor(muon | mu_eff_isosys_high,
   "lep_0_MUON_ISO_SYS_1up_MuEffSF_IsoGradient");

  ////////////////////////////////////////////////////////////////////////////////
  // muon ttva
  Condition mu_eff_ttvastat_low = registerVariation("mu_eff_ttvastat_low");
  Condition mu_eff_ttvastat_high = registerVariation("mu_eff_ttvastat_high");
  Condition mu_eff_ttvasys_low = registerVariation("mu_eff_ttvasys_low");
  Condition mu_eff_ttvasys_high = registerVariation("mu_eff_ttvasys_high");

  addScaleFactor(muon,
    mu_eff_ttvastat_low | mu_eff_ttvastat_high | mu_eff_ttvasys_low | mu_eff_ttvasys_high,
    "lep_0_NOMINAL_MuEffSF_TTVA");

  addScaleFactor(muon | mu_eff_ttvastat_low,
    "lep_0_MUON_TTVA_STAT_1down_MuEffSF_TTVA");

  addScaleFactor(muon | mu_eff_ttvastat_high,
    "lep_0_MUON_TTVA_STAT_1up_MuEffSF_TTVA");

  addScaleFactor(muon | mu_eff_ttvasys_low,
    "lep_0_MUON_TTVA_SYS_1down_MuEffSF_TTVA");

  addScaleFactor(muon | mu_eff_ttvasys_high,
    "lep_0_MUON_TTVA_SYS_1up_MuEffSF_TTVA");

  ////////////////////////////////////////////////////////////////////////////////
  // tau reco efficiency
  Condition tau_eff_reco_total_low = registerVariation("tau_eff_reco_total_low");
  Condition tau_eff_reco_total_high = registerVariation("tau_eff_reco_total_high");
  Condition tau_eff_reco_highpt_low = registerVariation("tau_eff_reco_highpt_low");
  Condition tau_eff_reco_highpt_high = registerVariation("tau_eff_reco_highpt_high");

  addScaleFactor(none,
    tau_eff_reco_total_low | tau_eff_reco_total_high | tau_eff_reco_highpt_low | tau_eff_reco_highpt_high,
    "tau_0_NOMINAL_TauEffSF_selection");

  addScaleFactor(tau_eff_reco_total_low,
    "tau_0_TAUS_TRUEHADTAU_EFF_RECO_TOTAL_1down_TauEffSF_selection");

  addScaleFactor(tau_eff_reco_total_high,
    "tau_0_TAUS_TRUEHADTAU_EFF_RECO_TOTAL_1up_TauEffSF_selection");

  addScaleFactor(tau_eff_reco_highpt_low,
    "tau_0_TAUS_TRUEHADTAU_EFF_RECO_HIGHPT_1down_TauEffSF_selection");

  addScaleFactor(tau_eff_reco_highpt_high,
    "tau_0_TAUS_TRUEHADTAU_EFF_RECO_HIGHPT_1up_TauEffSF_selection");


  ////////////////////////////////////////////////////////////////////////////////
  // tau electron overlap removal
  Condition tau_eff_eleolr_trueele_low = registerVariation("tau_eff_eleolr_trueelectron_low");
  Condition tau_eff_eleolr_trueele_high = registerVariation("tau_eff_eleolr_trueelectron_high");

  addScaleFactor(none,
    tau_eff_eleolr_trueele_low | tau_eff_eleolr_trueele_high,
    "tau_0_NOMINAL_TauEffSF_selection");

  addScaleFactor(tau_eff_eleolr_trueele_low,
    "tau_0_TAUS_TRUEELECTRON_EFF_ELEOLR_TOTAL_1down_TauEffSF_selection");

  addScaleFactor(tau_eff_eleolr_trueele_high,
    "tau_0_TAUS_TRUEELECTRON_EFF_ELEOLR_TOTAL_1up_TauEffSF_selection");

  Condition tau_eff_eleolr_truehadtau_low = registerVariation("tau_eff_eleolr_truehadtau_low");
  Condition tau_eff_eleolr_truehadtau_high = registerVariation("tau_eff_eleolr_truehadtau_high");

  addScaleFactor(none,
    tau_eff_eleolr_truehadtau_low | tau_eff_eleolr_truehadtau_high,
    "tau_0_NOMINAL_TauEffSF_selection");

  addScaleFactor(none | tau_eff_eleolr_truehadtau_low,
    "tau_0_TAUS_TRUEHADTAU_EFF_ELEOLR_TOTAL_1down_TauEffSF_selection");

  addScaleFactor(none | tau_eff_eleolr_truehadtau_high,
    "tau_0_TAUS_TRUEHADTAU_EFF_ELEOLR_TOTAL_1up_TauEffSF_selection");

  ////////////////////////////////////////////////////////////////////////////////
  // tau jetid efficiency
  Condition tau_eff_jetid_total_low = registerVariation("tau_eff_jetid_total_low");
  Condition tau_eff_jetid_total_high = registerVariation("tau_eff_jetid_total_high");
  Condition tau_eff_jetid_highpt_low = registerVariation("tau_eff_jetid_highpt_low");
  Condition tau_eff_jetid_highpt_high = registerVariation("tau_eff_jetid_highpt_high");

  addScaleFactor(tauid,
    tau_eff_jetid_total_low | tau_eff_jetid_total_high | tau_eff_jetid_highpt_low | tau_eff_jetid_highpt_high,
    "tau_0_NOMINAL_TauEffSF_JetBDTmedium");

  addScaleFactor(tau_eff_jetid_total_low,
    "tau_0_TAUS_TRUEHADTAU_EFF_JETID_TOTAL_1down_TauEffSF_JetBDTmedium");

  addScaleFactor(tau_eff_jetid_total_high,
    "tau_0_TAUS_TRUEHADTAU_EFF_JETID_TOTAL_1up_TauEffSF_JetBDTmedium");

  addScaleFactor(tau_eff_jetid_highpt_low,
    "tau_0_TAUS_TRUEHADTAU_EFF_JETID_HIGHPT_1down_TauEffSF_JetBDTmedium");

  addScaleFactor(tau_eff_jetid_highpt_high,
    "tau_0_TAUS_TRUEHADTAU_EFF_JETID_HIGHPT_1up_TauEffSF_JetBDTmedium");

  ////////////////////////////////////////////////////////////////////////////////
  // btag
  Condition btag_all;

  // b
  const int n_btag_b = 3;
  Condition btag_b_low[n_btag_b];
  Condition btag_b_high[n_btag_b];

  for (int i = 0; i < n_btag_b; i++) {
    btag_b_low[i] = registerVariation(TString::Format("btag_b_%d_low", i));
    btag_b_high[i] = registerVariation(TString::Format("btag_b_%d_high", i));
    btag_all |= btag_b_low[i];
    btag_all |= btag_b_high[i];

    addScaleFactor(btag_b_low[i], TString::Format("jet_FT_EFF_Eigen_B_%d_1down_global_effSF_MVX", i));
    addScaleFactor(btag_b_low[i], TString::Format("jet_FT_EFF_Eigen_B_%d_1down_global_ineffSF_MVX", i));
    addScaleFactor(btag_b_high[i], TString::Format("jet_FT_EFF_Eigen_B_%d_1up_global_effSF_MVX", i));
    addScaleFactor(btag_b_high[i], TString::Format("jet_FT_EFF_Eigen_B_%d_1up_global_ineffSF_MVX", i));
  }

  // c
  const int n_btag_c = 4;
  Condition btag_c_low[n_btag_c];
  Condition btag_c_high[n_btag_c];

  for (int i = 0; i < n_btag_c; i++) {
    btag_c_low[i] = registerVariation(TString::Format("btag_c_%d_low", i));
    btag_c_high[i] = registerVariation(TString::Format("btag_c_%d_high", i));
    btag_all |= btag_c_low[i];
    btag_all |= btag_c_high[i];

    addScaleFactor(btag_c_low[i], TString::Format("jet_FT_EFF_Eigen_C_%d_1down_global_effSF_MVX", i));
    addScaleFactor(btag_c_low[i], TString::Format("jet_FT_EFF_Eigen_C_%d_1down_global_ineffSF_MVX", i));
    addScaleFactor(btag_c_high[i], TString::Format("jet_FT_EFF_Eigen_C_%d_1up_global_effSF_MVX", i));
    addScaleFactor(btag_c_high[i], TString::Format("jet_FT_EFF_Eigen_C_%d_1up_global_ineffSF_MVX", i));
  }

  // light
  const int n_btag_light = 5;
  Condition btag_light_low[n_btag_light];
  Condition btag_light_high[n_btag_light];

  for (int i = 0; i < n_btag_light; i++) {
    btag_light_low[i] = registerVariation(TString::Format("btag_light_%d_low", i));
    btag_light_high[i] = registerVariation(TString::Format("btag_light_%d_high", i));
    btag_all |= btag_light_low[i];
    btag_all |= btag_light_high[i];

    addScaleFactor(btag_light_low[i], TString::Format("jet_FT_EFF_Eigen_Light_%d_1down_global_effSF_MVX", i));
    addScaleFactor(btag_light_low[i], TString::Format("jet_FT_EFF_Eigen_Light_%d_1down_global_ineffSF_MVX", i));
    addScaleFactor(btag_light_high[i], TString::Format("jet_FT_EFF_Eigen_Light_%d_1up_global_effSF_MVX", i));
    addScaleFactor(btag_light_high[i], TString::Format("jet_FT_EFF_Eigen_Light_%d_1up_global_ineffSF_MVX", i));
  }

  // extrapolation
  Condition btag_extrapolation_low = registerVariation("btag_extrapolation_low");
  Condition btag_extrapolation_high = registerVariation("btag_extrapolation_high");
  btag_all |= btag_extrapolation_low;
  btag_all |= btag_extrapolation_high;

  addScaleFactor(btag_extrapolation_low, "jet_FT_EFF_extrapolation_1down_global_effSF_MVX");
  addScaleFactor(btag_extrapolation_low, "jet_FT_EFF_extrapolation_1down_global_ineffSF_MVX");

  addScaleFactor(btag_extrapolation_high, "jet_FT_EFF_extrapolation_1up_global_effSF_MVX");
  addScaleFactor(btag_extrapolation_high, "jet_FT_EFF_extrapolation_1up_global_ineffSF_MVX");

  // extrapolation from charm
  Condition btag_extrapolation_from_charm_low = registerVariation("btag_extrapolation_from_charm_low");
  Condition btag_extrapolation_from_charm_high = registerVariation("btag_extrapolation_from_charm_high");
  btag_all |= btag_extrapolation_from_charm_low;
  btag_all |= btag_extrapolation_from_charm_high;

  addScaleFactor(btag_extrapolation_from_charm_low, "jet_FT_EFF_extrapolation_from_charm_1down_global_effSF_MVX");
  addScaleFactor(btag_extrapolation_from_charm_low, "jet_FT_EFF_extrapolation_from_charm_1down_global_ineffSF_MVX");

  addScaleFactor(btag_extrapolation_from_charm_high, "jet_FT_EFF_extrapolation_from_charm_1up_global_effSF_MVX");
  addScaleFactor(btag_extrapolation_from_charm_high, "jet_FT_EFF_extrapolation_from_charm_1up_global_ineffSF_MVX");

  // btag all
  addScaleFactor(none, btag_all, "jet_NOMINAL_global_effSF_MV2c10");
  addScaleFactor(none, btag_all, "jet_NOMINAL_global_ineffSF_MV2c10");

  ////////////////////////////////////////////////////////////////////////////////
  // jet jvt efficiency
  Condition jet_jvteff_low = registerVariation("jet_jvteff_low");
  Condition jet_jvteff_high = registerVariation("jet_jvteff_high");

  addScaleFactor(none, jet_jvteff_low | jet_jvteff_high, "jet_NOMINAL_central_jets_global_effSF_JVT");
  addScaleFactor(jet_jvteff_low, "jet_JET_JvtEfficiency_1down_central_jets_global_effSF_JVT");
  addScaleFactor(jet_jvteff_high, "jet_JET_JvtEfficiency_1up_central_jets_global_effSF_JVT");

  Condition jet_jvtineff_low = registerVariation("jet_jvtineff_low");
  Condition jet_jvtineff_high = registerVariation("jet_jvtineff_high");

  addScaleFactor(none, jet_jvtineff_low | jet_jvtineff_high, "jet_NOMINAL_central_jets_global_ineffSF_JVT");
  addScaleFactor(jet_jvtineff_low, "jet_JET_JvtEfficiency_1down_central_jets_global_ineffSF_JVT");
  addScaleFactor(jet_jvtineff_high, "jet_JET_JvtEfficiency_1up_central_jets_global_ineffSF_JVT");

  ////////////////////////////////////////////////////////////////////////////////
  // pileup
  Condition pu_prw_low = registerVariation("pu_prw_low");
  Condition pu_prw_high = registerVariation("pu_prw_high");

  addScaleFactor(none, pu_prw_low | pu_prw_high, "NOMINAL_pileup_combined_weight");

  addScaleFactor(pu_prw_low, "PRW_DATASF_1down_pileup_combined_weight");
  addScaleFactor(pu_prw_high, "PRW_DATASF_1up_pileup_combined_weight");

  ////////////////////////////////////////////////////////////////////////////////

  // luminosity scaling
  //addScaleFactor(y2015, &scale2015);
  //addScaleFactor(y2016, &scale2016);

  ////////////////////////////////////////////////////////////////////////////////
  // mc weight
  addScaleFactor(none, "weight_mc");


  ////////////////////////////////////////////////////////////////////////////////
  // fail safe
  //addScaleFactor(none, muon | electron, &zero);
  //addScaleFactor(none, y2015 | y2016, &zero);
  //addScaleFactor(none, slt | tlt, &zero);

  ////////////////////////////////////////////////////////////////////////////////
  // pileup
  //TFile* pileup_weights_file = TFile::Open("input/pileup_weights.root");
  //fac = (TH2*) pileup_weights_file->Get("fac");
  //ren = (TH2*) pileup_weights_file->Get("ren");
}

//______________________________________________________________________________________________
bool ScaleFactor::parseExpression(const TString& expr) {

  if (expr == "ScaleFactor" || expr == "ScaleFactor_nominal") {
    variation = nominal;
    return true;
  }

  for (unsigned int i = 0; i < variations.size(); i++) {
    if (expr.EndsWith(variations[i].first)) {
      variation = variations[i].second;
      return true;
    }
  }


  return false;
}

//______________________________________________________________________________________________
bool ScaleFactor::initializeSelf() {
  if (!LepHadObservable::initializeSelf()) {
      ERROR("Initialization of LepHadObservable failed.");
      return false;
  }

  this->fSample->getTag("~scale2016", scale2016);
  this->fSample->getTag("~scale2015", scale2015);

  this->fSample->getTag("~isZtt", isZtt);
  this->fSample->getTag("~isZll", isZll);

  // These flags do not change on a sample-to-sample basis, they are constant
  // until initializeSelf is called again.
  staticConditionsMask |= sherpa;

  Condition staticConditions = variation;
  if (isSherpa()) {
      staticConditions |= sherpa;
  }

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

  event_number = new TTreeFormula("event_number", "event_number",  this->fTree);

  return true;
}

//______________________________________________________________________________________________

bool ScaleFactor::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

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
void ScaleFactor::addScaleFactor(Condition requirement, const double* factor) {
  addScaleFactor(requirement, none, factor);
}

//______________________________________________________________________________________________
void ScaleFactor::addScaleFactor(Condition requirement, Condition veto, const double* factor) {
  std::tuple<Condition, Condition, const double*> sf;

  std::get<0>(sf) = requirement;
  std::get<1>(sf) = veto;
  std::get<2>(sf) = factor;

  factors.push_back(sf);
}

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

  bnames->Add(new TObjString("event_number"));

  return bnames;
}

//______________________________________________________________________________________________

double ScaleFactor::getValue() const {
  // in the rest of this function, you should retrieve the data and calculate your return value
  // here is the place where most of your custom code should go
  // a couple of comments should guide you through the process
  // when writing your code, please keep in mind that this code can be executed several times on every event
  // make your code efficient. catch all possible problems. when in doubt, contact experts!

  // here, you should calculate your return value
  // of course, you can use other data members of your observable at any time
  /* example block for TTreeFormula method:
  const double retval = this->fFormula->Eval(0.);
  */
  /* exmple block for TTree::SetBranchAddress method:
  const double retval = this->fBranch1 + this->fBranch2;
  */

  double scaleFac = 1.;

  Condition status(variation);

  if (is2017())     { status |= y2017; }
  if (is2016())     { status |= y2016; }
  if (is2015())     { status |= y2015; }
  if (isSLT())      { status |= slt; }
  if (isTauID())    { status |= tauid; }
  if (isMuon())     { status |= muon; }
  if (isElectron()) { status |= electron; }
  if (isSherpa())   { status |= sherpa; }
  if (isHighPt())   { status |= highpt ;}
  if (isZtt || isZll) { status |= isZ;}

  // apply branches
  for (unsigned int i = 0; i < branches.size(); i++) {
    Condition requirement = std::get<0>(branches[i]);
    Condition veto = std::get<1>(branches[i]);

    // some requirements are not met
    if ((requirement & ~status).any()) { continue; }
    // some vetos are triggered
    if ((veto & status ).any()) { continue; }

    TTreeFormula* formula = std::get<3>(branches[i]);
    scaleFac *= formula->EvalInstance();
  }


  // apply constant factors
  for (unsigned int i = 0; i < factors.size(); i++) {
    Condition requirement = std::get<0>(factors[i]);
    Condition veto = std::get<1>(factors[i]);

    // some requirements are not met
    if ((requirement & ~status).any()) { continue; }
    // some vetos are triggered
    if ((veto & status ).any()) { continue; }

    scaleFac *= (*std::get<2>(factors[i]));
  }

  DEBUGclass("returning");

  return scaleFac;
}

//______________________________________________________________________________________________
