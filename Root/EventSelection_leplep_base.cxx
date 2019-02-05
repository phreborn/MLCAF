#include "Htautau/EventSelection_leplep_base.h"
#include "Htautau/EventSelection_leplep_base_static.h"
#include <limits>
#include <algorithm>
#include <vector>
#include <string>
#include <chrono>
#include "QFramework/TQIterator.h"

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(EventSelection_leplep_basis)

//______________________________________________________________________________________________
EventSelection_leplep_basis::EventSelection_leplep_basis(const TString& expression, int systematic, int flag):EventSelection(expression,systematic,flag){
}
//______________________________________________________________________________________________
EventSelection_leplep_basis::~EventSelection_leplep_basis() {
  // default destructor
}

bool EventSelection_leplep_basis::finalize(){
    EventSelection::finalize();

    delete m_leptons_cluster_eta;
    delete m_leptons_cluster_eta_be2;
    delete m_leptons_iso_wp;
    delete m_leptons_id_loose;
    delete m_leptons_id_medium;
    delete m_leptons_id_tight;

    delete m_taus_n_tracks;

    delete leptons_HLT_e24_lhmedium_L1EM20VH;
    delete leptons_HLT_e60_lhmedium;
    delete leptons_HLT_e120_lhloose;
    delete leptons_HLT_mu20_iloose_L1MU15;
    delete leptons_HLT_mu50;
    delete HLT_e24_lhmedium_L1EM20VH;
    delete leptons_HLT_2e12_lhloose_L12EM10VH;
    delete leptons_HLT_mu18_mu8noL1;
    delete leptons_HLT_e17_loose_mu14;
    delete HLT_e60_lhmedium;
    delete HLT_e120_lhloose;
    delete HLT_mu20_iloose_L1MU15;
    delete HLT_mu50;
    delete HLT_e17_loose_mu14;
    delete HLT_mu18_mu8noL1;
    delete HLT_2e12_lhloose_L12EM10VH;
    delete leptons_HLT_e24_lhtight_nod0_ivarloose;
    delete leptons_HLT_e60_lhmedium_nod0;
    delete leptons_HLT_e140_lhloose_nod0 ;
    delete leptons_HLT_mu24_ivarmedium;
    delete leptons_HLT_mu20_mu8noL1;
    delete leptons_HLT_e17_lhloose_nod0_mu14;
    delete leptons_HLT_2e17_lhvloose_nod0;
    delete leptons_HLT_2e15_lhvloose_nod0_L12EM13VH;

    if (!m_isData || m_isBoth) {
        delete mu_ID_effSF;
        delete mu_ISO_effSF;

        delete el_ID_effSF;
        delete el_ISO_effSF;
        delete el_Track_effSF;

        delete jets_JVT_effSF;
        delete jets_MVX_effSF;
        delete jets_MVX_ineffSF;

        delete tw_mu14;
        delete tw_mu20ORmu50;
        delete tw_mu18;
        delete tw_mu8noL1;
	delete tw_singleE_2015_2016;
	delete tw_singleMu_2016;
	delete tw_2e12_2015_2e15_2016;
	delete tw_2e12_2015_2e17_2016;
	delete tw_mu20_2016;
	delete tw_e17_2015_e17_2016;
    }
    return true;
}

bool EventSelection_leplep_basis::add_particle_branches()  {
    EventSelection::add_particle_branches();
    additional_branches.push_back("leptons_cluster_eta");
    additional_branches.push_back("leptons_cluster_eta_be2");
    additional_branches.push_back("leptons_iso_wp");
    additional_branches.push_back("leptons_id_loose");
    additional_branches.push_back("leptons_id_medium");
    additional_branches.push_back("leptons_id_tight");
    additional_branches.push_back("leptons_trk_d0");
    additional_branches.push_back("leptons_trk_d0_sig");
    additional_branches.push_back("taus_n_tracks");
    return true;
}

bool EventSelection_leplep_basis::connect_particle_branches()  {
    EventSelection::connect_particle_branches();
    m_leptons_cluster_eta     = new TTreeFormula( "leptons_cluster_eta"     , "leptons_cluster_eta"     , this->fTree);
    m_leptons_cluster_eta_be2 = new TTreeFormula( "leptons_cluster_eta_be2" , "leptons_cluster_eta_be2" , this->fTree);
    m_leptons_iso_wp          = new TTreeFormula( "leptons_iso_wp"          , "leptons_iso_wp"          , this->fTree);
    m_leptons_id_loose        = new TTreeFormula( "leptons_id_loose"        , "leptons_id_loose"        , this->fTree);
    m_leptons_id_medium       = new TTreeFormula( "leptons_id_medium"       , "leptons_id_medium"       , this->fTree);
    m_leptons_id_tight        = new TTreeFormula( "leptons_id_tight"        , "leptons_id_tight"        , this->fTree);
    m_leptons_trk_d0          = new TTreeFormula( "leptons_trk_d0"          , "leptons_trk_d0"          , this->fTree);
    m_leptons_trk_d0_sig      = new TTreeFormula( "leptons_trk_d0_sig"      , "leptons_trk_d0_sig"      , this->fTree);

    m_taus_n_tracks           = new TTreeFormula( "taus_n_tracks"           , "taus_n_tracks"           , this->fTree);


    return true;
}

bool EventSelection_leplep_basis::add_trigger_branches() {
    EventSelection::add_trigger_branches();
    additional_branches.push_back("HLT_e24_lhmedium_L1EM20VH");
    additional_branches.push_back("HLT_e60_lhmedium");
    additional_branches.push_back("HLT_e120_lhloose");
    additional_branches.push_back("HLT_mu20_iloose_L1MU15");
    additional_branches.push_back("HLT_mu50");
    additional_branches.push_back("leptons_HLT_e24_lhmedium_L1EM20VH");
    additional_branches.push_back("leptons_HLT_e60_lhmedium");
    additional_branches.push_back("leptons_HLT_e120_lhloose");
    additional_branches.push_back("leptons_HLT_mu20_iloose_L1MU15");
    additional_branches.push_back("leptons_HLT_mu50");
    additional_branches.push_back("leptons_HLT_2e12_lhloose_L12EM10VH");
    additional_branches.push_back("leptons_HLT_mu18_mu8noL1");
    additional_branches.push_back("leptons_HLT_e17_loose_mu14");
    additional_branches.push_back("HLT_e17_loose_mu14");
    additional_branches.push_back("HLT_mu18_mu8noL1");
    additional_branches.push_back("HLT_2e12_lhloose_L12EM10VH");
    additional_branches.push_back("leptons_HLT_e24_lhtight_nod0_ivarloose");
    additional_branches.push_back("leptons_HLT_e60_lhmedium_nod0");
    additional_branches.push_back("leptons_HLT_e140_lhloose_nod0");
    additional_branches.push_back("leptons_HLT_mu24_ivarmedium");
    additional_branches.push_back("leptons_HLT_mu20_mu8noL1");
    additional_branches.push_back("leptons_HLT_e17_lhloose_nod0_mu14");
    additional_branches.push_back("leptons_HLT_2e17_lhvloose_nod0");
    additional_branches.push_back("leptons_HLT_2e15_lhvloose_nod0_L12EM13VH");
    additional_branches.push_back("HLT_e24_lhtight_nod0_ivarloose");
    additional_branches.push_back("HLT_e60_lhmedium_nod0");
    additional_branches.push_back("HLT_e140_lhloose_nod0");
    additional_branches.push_back("HLT_mu24_ivarmedium");
    additional_branches.push_back("HLT_2e15_lhvloose_nod0_L12EM13VH");
    additional_branches.push_back("HLT_2e17_lhvloose_nod0");
    additional_branches.push_back("HLT_mu20_mu8noL1");
    additional_branches.push_back("HLT_e17_lhloose_nod0_mu14");

    return true;
}

bool EventSelection_leplep_basis::connect_trigger_branches() {
    EventSelection::connect_trigger_branches();

    leptons_HLT_e24_lhmedium_L1EM20VH = new TTreeFormula( "leptons_HLT_e24_lhmedium_L1EM20VH" , "leptons_HLT_e24_lhmedium_L1EM20VH" , this->fTree);

    leptons_HLT_e60_lhmedium          = new TTreeFormula( "leptons_HLT_e60_lhmedium"          , "leptons_HLT_e60_lhmedium"          , this->fTree);
    leptons_HLT_e120_lhloose          = new TTreeFormula( "leptons_HLT_e120_lhloose"          , "leptons_HLT_e120_lhloose"          , this->fTree);
    leptons_HLT_mu20_iloose_L1MU15    = new TTreeFormula( "leptons_HLT_mu20_iloose_L1MU15"    , "leptons_HLT_mu20_iloose_L1MU15"    , this->fTree);
    leptons_HLT_mu50                  = new TTreeFormula( "leptons_HLT_mu50"                  , "leptons_HLT_mu50"                  , this->fTree);

    HLT_e24_lhmedium_L1EM20VH = new TTreeFormula("HLT_e24_lhmedium_L1EM20VH", "HLT_e24_lhmedium_L1EM20VH", this->fTree);
    HLT_e60_lhmedium                   = new TTreeFormula("HLT_e60_lhmedium"                    , "HLT_e60_lhmedium"                   , this->fTree);
    HLT_e120_lhloose                   = new TTreeFormula("HLT_e120_lhloose"                    , "HLT_e120_lhloose"                   , this->fTree);
    HLT_mu20_iloose_L1MU15             = new TTreeFormula("HLT_mu20_iloose_L1MU15"              , "HLT_mu20_iloose_L1MU15"             , this->fTree);
    HLT_mu50                           = new TTreeFormula("HLT_mu50"                            , "HLT_mu50"                           , this->fTree);
    leptons_HLT_e17_loose_mu14         = new TTreeFormula( "leptons_HLT_e17_loose_mu14"         , "leptons_HLT_e17_loose_mu14"         , this->fTree);
    leptons_HLT_mu18_mu8noL1           = new TTreeFormula( "leptons_HLT_mu18_mu8noL1"           , "leptons_HLT_mu18_mu8noL1"           , this->fTree);
    leptons_HLT_2e12_lhloose_L12EM10VH = new TTreeFormula( "leptons_HLT_2e12_lhloose_L12EM10VH" , "leptons_HLT_2e12_lhloose_L12EM10VH" , this->fTree);
    HLT_e17_loose_mu14                 = new TTreeFormula( "HLT_e17_loose_mu14"                 , "HLT_e17_loose_mu14"                 , this->fTree);
    HLT_mu18_mu8noL1                   = new TTreeFormula( "HLT_mu18_mu8noL1"                   , "HLT_mu18_mu8noL1"                   , this->fTree);
    HLT_2e12_lhloose_L12EM10VH         = new TTreeFormula( "HLT_2e12_lhloose_L12EM10VH"         , "HLT_2e12_lhloose_L12EM10VH"         , this->fTree);
    leptons_HLT_e24_lhtight_nod0_ivarloose = new TTreeFormula("leptons_HLT_e24_lhtight_nod0_ivarloose", "leptons_HLT_e24_lhtight_nod0_ivarloose", this->fTree);
    leptons_HLT_e60_lhmedium_nod0          = new TTreeFormula("leptons_HLT_e60_lhmedium_nod0", "leptons_HLT_e60_lhmedium_nod0", this->fTree);
    leptons_HLT_e140_lhloose_nod0          = new TTreeFormula("leptons_HLT_e140_lhloose_nod0", "leptons_HLT_e140_lhloose_nod0", this->fTree);
    leptons_HLT_mu24_ivarmedium              = new TTreeFormula("leptons_HLT_mu24_ivarmedium", "leptons_HLT_mu24_ivarmedium", this->fTree);
    leptons_HLT_mu20_mu8noL1                 = new TTreeFormula("leptons_HLT_mu20_mu8noL1", "leptons_HLT_mu20_mu8noL1", this->fTree);
    leptons_HLT_e17_lhloose_nod0_mu14        = new TTreeFormula("leptons_HLT_e17_lhloose_nod0_mu14", "leptons_HLT_e17_lhloose_nod0_mu14", this->fTree);
    leptons_HLT_2e17_lhvloose_nod0           = new TTreeFormula("leptons_HLT_2e17_lhvloose_nod0", "leptons_HLT_2e17_lhvloose_nod0", this->fTree);
    leptons_HLT_2e15_lhvloose_nod0_L12EM13VH = new TTreeFormula("leptons_HLT_2e15_lhvloose_nod0_L12EM13VH", "leptons_HLT_2e15_lhvloose_nod0_L12EM13VH", this->fTree);
    HLT_e24_lhtight_nod0_ivarloose           = new TTreeFormula("HLT_e24_lhtight_nod0_ivarloose", "HLT_e24_lhtight_nod0_ivarloose", this->fTree);
    HLT_2e15_lhvloose_nod0_L12EM13VH         = new TTreeFormula("HLT_2e15_lhvloose_nod0_L12EM13VH", "HLT_2e15_lhvloose_nod0_L12EM13VH", this->fTree);
    HLT_2e17_lhvloose_nod0                   = new TTreeFormula("HLT_2e17_lhvloose_nod0", "HLT_2e17_lhvloose_nod0", this->fTree);
    HLT_e60_lhmedium_nod0                    = new TTreeFormula("HLT_e60_lhmedium_nod0", "HLT_e60_lhmedium_nod0", this->fTree);
    HLT_e140_lhloose_nod0                    = new TTreeFormula("HLT_e140_lhloose_nod0", "HLT_e140_lhloose_nod0", this->fTree);
    HLT_mu24_ivarmedium                      = new TTreeFormula("HLT_mu24_ivarmedium", "HLT_mu24_ivarmedium", this->fTree);
    HLT_mu20_mu8noL1                         = new TTreeFormula("HLT_mu20_mu8noL1", "HLT_mu20_mu8noL1", this->fTree);
    HLT_e17_lhloose_nod0_mu14                = new TTreeFormula("HLT_e17_lhloose_nod0_mu14", "HLT_e17_lhloose_nod0_mu14", this->fTree);

    return true;
}

bool EventSelection_leplep_basis::add_lepton_sf_brachnes() {
    EventSelection::add_lepton_sf_brachnes();
    mu_ID_effSF_name    = "leptons_NOMINAL_MuEffSF_Reco_QualMedium";
    mu_ISO_effSF_name   = "leptons_NOMINAL_MuEffSF_IsoGradient";
    el_ID_effSF_name    = "leptons_NOMINAL_effSF_offline_MediumLLH_v11";
    el_ISO_effSF_name   = "leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v11_isolGradient";
    el_Track_effSF_name = "leptons_NOMINAL_effSF_offline_RecoTrk";

    if ( m_systematic == getSystematic ( "MUON_EFF_STAT_1down"                    )  ) mu_ID_effSF_name    = "leptons_MUON_EFF_STAT_1down_MuEffSF_Reco_QualMedium"                                                                             ;
    if ( m_systematic == getSystematic ( "MUON_EFF_STAT_1up"                      )  ) mu_ID_effSF_name    = "leptons_MUON_EFF_STAT_1up_MuEffSF_Reco_QualMedium"                                                                               ;
    if ( m_systematic == getSystematic ( "MUON_EFF_SYS_1down"                     )  ) mu_ID_effSF_name    = "leptons_MUON_EFF_SYS_1down_MuEffSF_Reco_QualMedium"                                                                              ;
    if ( m_systematic == getSystematic ( "MUON_EFF_SYS_1up"                       )  ) mu_ID_effSF_name    = "leptons_MUON_EFF_SYS_1up_MuEffSF_Reco_QualMedium"                                                                                ;
    if ( m_systematic == getSystematic ( "MUON_ISO_STAT_1down"                    )  ) mu_ISO_effSF_name   = "leptons_MUON_ISO_STAT_1down_MuEffSF_IsoGradient"                                                                            ;
    if ( m_systematic == getSystematic ( "MUON_ISO_STAT_1up"                      )  ) mu_ISO_effSF_name   = "leptons_MUON_ISO_STAT_1up_MuEffSF_IsoGradient"                                                                              ;
    if ( m_systematic == getSystematic ( "MUON_ISO_SYS_1down"                     )  ) mu_ISO_effSF_name   = "leptons_MUON_ISO_SYS_1down_MuEffSF_IsoGradient"                                                                             ;
    if ( m_systematic == getSystematic ( "MUON_ISO_SYS_1up"                       )  ) mu_ISO_effSF_name   = "leptons_MUON_ISO_SYS_1up_MuEffSF_IsoGradient"                                                                               ;
    if ( m_systematic == getSystematic ( "MUON_EFF_STAT_LOWPT_1down"              )  ) mu_ID_effSF_name    = "leptons_MUON_EFF_STAT_LOWPT_1down_MuEffSF_Reco_QualMedium"                                                                       ;
    if ( m_systematic == getSystematic ( "MUON_EFF_STAT_LOWPT_1up"                )  ) mu_ID_effSF_name    = "leptons_MUON_EFF_STAT_LOWPT_1up_MuEffSF_Reco_QualMedium"                                                                         ;
    if ( m_systematic == getSystematic ( "MUON_EFF_SYS_LOWPT_1down"               )  ) mu_ID_effSF_name    = "leptons_MUON_EFF_SYS_LOWPT_1down_MuEffSF_Reco_QualMedium"                                                                        ;
    if ( m_systematic == getSystematic ( "MUON_EFF_SYS_LOWPT_1up"                )  ) mu_ID_effSF_name    = "leptons_MUON_EFF_SYS_LOWPT_1up_MuEffSF_Reco_QualMedium"                                                                          ;
    /*
    mu_ttva_effSF_name="leptons_NOMINAL_MU_TTVA";
    if                                           ( m_systematic == -5 )  mu_ttva_effSF_name    = "leptons_MUON_TTVA_iSTAT_1down_MU_TTVA"                                                                                  ;
    if                                           ( m_systematic == 5  )  mu_ttva_effSF_name    = "leptons_MUON_TTVA_STAT_1up_MU_TTVA"                                                                                     ;
    if                                           ( m_systematic == -6 )  mu_ttva_effSF_name    = "leptons_MUON_TTVA_SYS_1down_MU_TTVA"                                                                                    ;
    if                                           ( m_systematic == 6  )  mu_ttva_effSF_name    = "leptons_MUON_TTVA_SYS_1up_MU_TTVA"                                                                                      ;
    */
    if ( m_systematic == getSystematic ( "EL_EFF_ID_TotalCorrUncertainty_1down"   )  ) el_ID_effSF_name    = "leptons_EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR_1down_effSF_offline_MediumLLH_v11"             ;
    if ( m_systematic == getSystematic ( "EL_EFF_ID_TotalCorrUncertainty_1up"     )  ) el_ID_effSF_name    = "leptons_EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR_1up_effSF_offline_MediumLLH_v11"               ;
    if ( m_systematic == getSystematic ( "EL_EFF_Iso_TotalCorrUncertainty_1down"  )  ) el_ISO_effSF_name   = "leptons_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR_1down_effSF_Isolation_MediumLLH_d0z0_v11_isolGradient" ;
    if ( m_systematic == getSystematic ( "EL_EFF_Iso_TotalCorrUncertainty_1up"    )  ) el_ISO_effSF_name   = "leptons_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR_1up_effSF_Isolation_MediumLLH_d0z0_v11_isolGradient"   ;
    if ( m_systematic == getSystematic ( "EL_EFF_Reco_TotalCorrUncertainty_1down" )  ) el_Track_effSF_name = "leptons_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR_1down_effSF_offline_RecoTrk"                 ;
    if ( m_systematic == getSystematic ( "EL_EFF_Reco_TotalCorrUncertainty_1up"   )  ) el_Track_effSF_name = "leptons_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR_1up_effSF_offline_RecoTrk"                 ;

    additional_branches.push_back(mu_ID_effSF_name);
    additional_branches.push_back(mu_ISO_effSF_name);
    additional_branches.push_back(el_ID_effSF_name);
    additional_branches.push_back(el_ISO_effSF_name);
    additional_branches.push_back(el_Track_effSF_name);
    return true;
}

bool EventSelection_leplep_basis::add_jet_sf_brachnes() {
    EventSelection::add_jet_sf_brachnes();
    jets_JVT_effSF_name   = "jets_NOMINAL_effSF_JVT";
    jets_effSF_MVX_name   = "jets_NOMINAL_effSF_MVX";
    jets_ineffSF_MVX_name = "jets_NOMINAL_ineffSF_MVX";

    if (m_systematic == getSystematic("JET_EFF_JVT_up")  )  jets_JVT_effSF_name="jets_JvtEfficiencyUp_effSF_JVT"   ;
    if (m_systematic == getSystematic("JET_EFF_JVT_down"))  jets_JVT_effSF_name="jets_JvtEfficiencyDown_effSF_JVT" ;

    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_B_0_1down" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_B_0_1down_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_B_0_1down_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_B_0_1up" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_B_0_1up_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_B_0_1up_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_B_1_1down" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_B_1_1down_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_B_1_1down_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_B_1_1up" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_B_1_1up_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_B_1_1up_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_B_2_1down" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_B_2_1down_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_B_2_1down_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_B_2_1up" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_B_2_1up_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_B_2_1up_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_C_0_1down" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_C_0_1down_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_C_0_1down_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_C_0_1up" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_C_0_1up_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_C_0_1up_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_C_1_1down" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_C_1_1down_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_C_1_1down_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_C_1_1up" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_C_1_1up_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_C_1_1up_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_C_2_1down" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_C_2_1down_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_C_2_1down_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_C_2_1up" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_C_2_1up_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_C_2_1up_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_C_3_1down" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_C_3_1down_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_C_3_1down_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_C_3_1up" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_C_3_1up_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_C_3_1up_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_Light_0_1down" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_Light_0_1down_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_Light_0_1down_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_Light_0_1up" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_Light_0_1up_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_Light_0_1up_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_Light_1_1down" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_Light_1_1down_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_Light_1_1down_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_Light_1_1up" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_Light_1_1up_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_Light_1_1up_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_Light_2_1down" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_Light_2_1down_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_Light_2_1down_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_Light_2_1up" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_Light_2_1up_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_Light_2_1up_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_Light_3_1down" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_Light_3_1down_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_Light_3_1down_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_Light_3_1up" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_Light_3_1up_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_Light_3_1up_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_Light_4_1down" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_Light_4_1down_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_Light_4_1down_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_Eigen_Light_4_1up" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_Eigen_Light_4_1up_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_Eigen_Light_4_1up_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_extrapolation_1down" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_extrapolation_1down_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_extrapolation_1down_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_extrapolation_1up" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_extrapolation_1up_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_extrapolation_1up_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_extrapolation_from_charm_1down" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_extrapolation_from_charm_1down_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_extrapolation_from_charm_1down_ineffSF_MVX" ;
    }
    if (m_systematic == getSystematic( "jets_FT_EFF_extrapolation_from_charm_1up" )) {
        jets_effSF_MVX_name=           "jets_FT_EFF_extrapolation_from_charm_1up_effSF_MVX" ;
        jets_ineffSF_MVX_name=         "jets_FT_EFF_extrapolation_from_charm_1up_ineffSF_MVX" ;
    }

    additional_branches.push_back(jets_JVT_effSF_name);
    additional_branches.push_back(jets_effSF_MVX_name);
    additional_branches.push_back(jets_ineffSF_MVX_name);
    return true;
}

bool EventSelection_leplep_basis::connect_lepton_sf_brachnes() {
    EventSelection::connect_lepton_sf_brachnes();
    if (!m_isData || m_isBoth) {
        mu_ID_effSF    = new TTreeFormula ("mu_ID_effSF"    , mu_ID_effSF_name    , this->fTree);
        mu_ISO_effSF   = new TTreeFormula ("mu_ISO_effSF"   , mu_ISO_effSF_name   , this->fTree);

        el_ID_effSF    = new TTreeFormula ("el_ID_effSF"    , el_ID_effSF_name    , this->fTree);
        el_ISO_effSF   = new TTreeFormula ("el_ISO_effSF"   , el_ISO_effSF_name   , this->fTree);
        el_Track_effSF = new TTreeFormula ("el_Track_effSF" , el_Track_effSF_name , this->fTree);
        std::cout << "using the following lepton sf" << std::endl;
        std::cout << mu_ID_effSF_name    << std::endl;
        std::cout << mu_ISO_effSF_name   << std::endl;
	//
        std::cout << el_ID_effSF_name    << std::endl;
        std::cout << el_ISO_effSF_name   << std::endl;
        std::cout << el_Track_effSF_name << std::endl;
    }
    return true;
}

bool EventSelection_leplep_basis::connect_jet_sf_brachnes() {
    EventSelection::connect_jet_sf_brachnes();
    if (!m_isData || m_isBoth) {
      jets_JVT_effSF   = new TTreeFormula ("jets_JVT_effSF"   , jets_JVT_effSF_name   , this->fTree);
      jets_MVX_effSF   = new TTreeFormula ("jets_MVX_effSF"   , jets_effSF_MVX_name   , this->fTree);
      jets_MVX_ineffSF = new TTreeFormula ("jets_MVX_ineffSF" , jets_ineffSF_MVX_name , this->fTree);
        std::cout << "using the following jet sf" << std::endl;
        std::cout <<  jets_JVT_effSF_name    << std::endl;
        std::cout <<  jets_effSF_MVX_name    << std::endl;
        std::cout <<  jets_ineffSF_MVX_name  << std::endl;
    }

    return true;
}

bool EventSelection_leplep_basis::add_trigger_sf_brachnes() {
    EventSelection::add_trigger_sf_brachnes();
    tw_mu14_name           = "leptons_NOMINAL_MuEffSF_HLT_mu14_QualMedium_IsoGradient";
    tw_mu20ORmu50_name     = "leptons_NOMINAL_MuEffSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_QualMedium_IsoGradient";
    tw_mu18_name           = "leptons_NOMINAL_MuEffSF_HLT_mu18_QualMedium_IsoGradient";
    tw_mu8noL1_name        = "leptons_NOMINAL_MuEffSF_HLT_mu8noL1_QualMedium_IsoGradient";
    tw_singleE_2015_2016_name   = "leptons_NOMINAL_effSF_SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_e24_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0_MediumLLH_d0z0_v11_isolGradient"; // single E trigger for 2015 and 2016
    tw_singleMu_2016_name       = "leptons_NOMINAL_MuEffSF_HLT_mu24_imedium_OR_HLT_mu50_QualMedium_IsoGradient";
    tw_2e12_2015_2e15_2016_name = "leptons_NOMINAL_effSF_DI_E_2015_e12_lhloose_L1EM10VH_2016_e15_lhvloose_nod0_L1EM13VH_MediumLLH_d0z0_v11_isolGradient"; // di E for 2015 and 2016
    tw_2e12_2015_2e17_2016_name = "leptons_NOMINAL_effSF_DI_E_2015_e12_lhloose_L1EM10VH_2016_e17_lhvloose_nod0_MediumLLH_d0z0_v11_isolGradient";
    tw_mu20_2016_name           = "leptons_NOMINAL_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoGradient";
    tw_e17_2015_e17_2016_name   = "leptons_NOMINAL_effSF_MULTI_L_2015_e17_lhloose_2016_e17_lhloose_nod0_MediumLLH_d0z0_v11_isolGradient"; // multi L for 2015 and 2016

    if (m_systematic       == getSystematic("MUON_EFF_TrigStatUncertainty_1down")) {
           tw_mu14_name           = "leptons_MUON_EFF_TrigStatUncertainty_1down_MuEffSF_HLT_mu14_QualMedium_IsoGradient";
           tw_mu20ORmu50_name     = "leptons_MUON_EFF_TrigStatUncertainty_1down_MuEffSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_QualMedium_IsoGradient";
           tw_mu18_name           = "leptons_MUON_EFF_TrigStatUncertainty_1down_MuEffSF_HLT_mu18_QualMedium_IsoGradient";
           tw_mu8noL1_name        = "leptons_MUON_EFF_TrigStatUncertainty_1down_MuEffSF_HLT_mu8noL1_QualMedium_IsoGradient";
	   tw_singleMu_2016_name  = "leptons_MUON_EFF_TrigStatUncertainty_1down_MuEffSF_HLT_mu24_imedium_OR_HLT_mu50_QualMedium_IsoGradient";
	   tw_mu20_2016_name      = "leptons_MUON_EFF_TrigStatUncertainty_1down_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoGradient";
    }
    if (m_systematic       == getSystematic("MUON_EFF_TrigStatUncertainty_1up")) {
           tw_mu14_name           = "leptons_MUON_EFF_TrigStatUncertainty_1up_MuEffSF_HLT_mu14_QualMedium_IsoGradient";
	   tw_mu20ORmu50_name     = "leptons_MUON_EFF_TrigStatUncertainty_1up_MuEffSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_QualMedium_IsoGradient";
	   tw_mu18_name           = "leptons_MUON_EFF_TrigStatUncertainty_1up_MuEffSF_HLT_mu18_QualMedium_IsoGradient";
	   tw_mu8noL1_name        = "leptons_MUON_EFF_TrigStatUncertainty_1up_MuEffSF_HLT_mu8noL1_QualMedium_IsoGradient";
	   tw_singleMu_2016_name  = "leptons_MUON_EFF_TrigStatUncertainty_1up_MuEffSF_HLT_mu24_imedium_OR_HLT_mu50_QualMedium_IsoGradient";
           tw_mu20_2016_name      = "leptons_MUON_EFF_TrigStatUncertainty_1up_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoGradient";
    }
    if (m_systematic       == getSystematic("MUON_EFF_TrigSystUncertainty_1down")) {
           tw_mu14_name           = "leptons_MUON_EFF_TrigSystUncertainty_1down_MuEffSF_HLT_mu14_QualMedium_IsoGradient";
	   tw_mu20ORmu50_name     = "leptons_MUON_EFF_TrigSystUncertainty_1down_MuEffSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_QualMedium_IsoGradient";
	   tw_mu18_name           = "leptons_MUON_EFF_TrigSystUncertainty_1down_MuEffSF_HLT_mu18_QualMedium_IsoGradient";
	   tw_mu8noL1_name        = "leptons_MUON_EFF_TrigSystUncertainty_1down_MuEffSF_HLT_mu8noL1_QualMedium_IsoGradient";
	   tw_singleMu_2016_name  = "leptons_MUON_EFF_TrigSystUncertainty_1down_MuEffSF_HLT_mu24_imedium_OR_HLT_mu50_QualMedium_IsoGradient";
           tw_mu20_2016_name      = "leptons_MUON_EFF_TrigSystUncertainty_1down_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoGradient";
    }
    if (m_systematic       == getSystematic("MUON_EFF_TrigSystUncertainty_1up")) {
           tw_mu14_name           = "leptons_MUON_EFF_TrigSystUncertainty_1up_MuEffSF_HLT_mu14_QualMedium_IsoGradient";
	   tw_mu20ORmu50_name     = "leptons_MUON_EFF_TrigSystUncertainty_1up_MuEffSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_QualMedium_IsoGradient";
	   tw_mu18_name           = "leptons_MUON_EFF_TrigSystUncertainty_1up_MuEffSF_HLT_mu18_QualMedium_IsoGradient";
	   tw_mu8noL1_name        = "leptons_MUON_EFF_TrigSystUncertainty_1up_MuEffSF_HLT_mu8noL1_QualMedium_IsoGradient";
	   tw_singleMu_2016_name  = "leptons_MUON_EFF_TrigSystUncertainty_1up_MuEffSF_HLT_mu24_imedium_OR_HLT_mu50_QualMedium_IsoGradient";
           tw_mu20_2016_name      = "leptons_MUON_EFF_TrigSystUncertainty_1up_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoGradient";
    }
    if (m_systematic       == getSystematic("EL_EFF_Trigger_TotalCorrUncertainty_1down")) {
      tw_singleE_2015_2016_name = "leptons_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR_1down_effSF_SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_e24_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0_MediumLLH_d0z0_v11_isolGradient";
      tw_2e12_2015_2e15_2016_name = "leptons_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR_1down_effSF_DI_E_2015_e12_lhloose_L1EM10VH_2016_e15_lhvloose_nod0_L1EM13VH_MediumLLH_d0z0_v11_isolGradient";
      tw_2e12_2015_2e17_2016_name = "leptons_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR_1down_effSF_DI_E_2015_e12_lhloose_L1EM10VH_2016_e17_lhvloose_nod0_MediumLLH_d0z0_v11_isolGradient";
      tw_e17_2015_e17_2016_name  = "leptons_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR_1down_effSF_MULTI_L_2015_e17_lhloose_2016_e17_lhloose_nod0_MediumLLH_d0z0_v11_isolGradient";
    }
    if (m_systematic       == getSystematic("EL_EFF_Trigger_TotalCorrUncertainty_1up")) {
      tw_singleE_2015_2016_name = "leptons_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR_1up_effSF_SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_e24_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0_MediumLLH_d0z0_v11_isolGradient";
      tw_2e12_2015_2e15_2016_name = "leptons_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR_1up_effSF_DI_E_2015_e12_lhloose_L1EM10VH_2016_e15_lhvloose_nod0_L1EM13VH_MediumLLH_d0z0_v11_isolGradient";
      tw_2e12_2015_2e17_2016_name = "leptons_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR_1up_effSF_DI_E_2015_e12_lhloose_L1EM10VH_2016_e17_lhvloose_nod0_MediumLLH_d0z0_v11_isolGradient";
      tw_e17_2015_e17_2016_name  = "leptons_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR_1up_effSF_MULTI_L_2015_e17_lhloose_2016_e17_lhloose_nod0_MediumLLH_d0z0_v11_isolGradient";
    }

    additional_branches.push_back(tw_mu14_name);
    additional_branches.push_back(tw_singleE_2015_2016_name);
    additional_branches.push_back(tw_singleMu_2016_name);
    additional_branches.push_back(tw_mu20ORmu50_name);
    additional_branches.push_back(tw_mu18_name);
    additional_branches.push_back(tw_mu8noL1_name);
    additional_branches.push_back(tw_2e12_2015_2e15_2016_name);
    additional_branches.push_back(tw_2e12_2015_2e17_2016_name);
    additional_branches.push_back(tw_mu20_2016_name);
    additional_branches.push_back(tw_e17_2015_e17_2016_name);
    return true;
}
bool EventSelection_leplep_basis::connect_trigger_sf_brachnes() {
    EventSelection::connect_trigger_sf_brachnes();
    if (!m_isData || m_isBoth) {
        std::cout << "using the following trigger sf" << std::endl;
        std::cout <<  tw_mu14_name                << std::endl;
        std::cout <<  tw_mu20ORmu50_name          << std::endl;
        std::cout <<  tw_mu18_name                << std::endl;
        std::cout <<  tw_mu8noL1_name             << std::endl;
        std::cout <<  tw_singleE_2015_2016_name   << std::endl;
        std::cout <<  tw_singleMu_2016_name       << std::endl;
        std::cout <<  tw_2e12_2015_2e15_2016_name << std::endl;
        std::cout <<  tw_2e12_2015_2e17_2016_name << std::endl;
        std::cout <<  tw_mu20_2016_name           << std::endl;
        std::cout <<  tw_e17_2015_e17_2016_name   << std::endl;
        tw_mu14           = new TTreeFormula ("tw_mu14"           , tw_mu14_name           , this->fTree);
        tw_mu20ORmu50     = new TTreeFormula ("tw_mu20ORmu50"     , tw_mu20ORmu50_name     , this->fTree);
        tw_mu18           = new TTreeFormula ("tw_mu18"           , tw_mu18_name           , this->fTree);
        tw_mu8noL1        = new TTreeFormula ("tw_mu8noL1"        , tw_mu8noL1_name        , this->fTree);
	tw_singleE_2015_2016   = new TTreeFormula("tw_singleE_2015_2016", tw_singleE_2015_2016_name, this->fTree);
	tw_singleMu_2016       = new TTreeFormula("tw_singleMu_2016", tw_singleMu_2016_name, this->fTree);
	tw_2e12_2015_2e15_2016 = new TTreeFormula("tw_2e12_2015_2e15_2016", tw_2e12_2015_2e15_2016_name, this->fTree);
	tw_2e12_2015_2e17_2016 = new TTreeFormula("tw_2e12_2015_2e17_2016", tw_2e12_2015_2e17_2016_name, this->fTree);
	tw_mu20_2016           = new TTreeFormula("tw_mu20_2016", tw_mu20_2016_name, this->fTree);
	tw_e17_2015_e17_2016   = new TTreeFormula("tw_e17_2015_e17_2016", tw_e17_2015_e17_2016_name, this->fTree);
    }
    return true;
}

//______________________________________________________________________________________________


bool EventSelection_leplep_basis::obtain_trigger_sf() {

  //std::cout << "-------" << std::endl;
    //debug=true;


    int RRN =current_run_number;

    TriggerWeight= 1.00;
    float TriggerWeight_l0= 1.00;
    float TriggerWeight_l1= 1.00;
    isTriggered_data = false;
    isTriggered_mc = false;
    TriggerType = 0;
    lep_0_pt=-1;
    lep_1_pt=-1;
    lep_idx0=-1;
    lep_idx1=-1;

    // for efficiency meausurement
    specialTriggerWeight= 1.00;
    specialisTriggered_data = false;
    specialisTriggered_mc = false;
    specialTriggerType = 0;

    if (leptons_selected_idx.size()>=2) {
      lep_0_pt=leptons[leptons_selected_idx[0]].Pt();
      lep_1_pt=leptons[leptons_selected_idx[1]].Pt();
      lep_idx0=leptons_selected_idx[0];
      lep_idx1=leptons_selected_idx[1];
      if (debug) {
	std::cout << "lep index for 2l "<< lep_0_pt << " " << lep_1_pt << " idx " << lep_idx0 << " " << lep_idx1 << std::endl;
      }
    }

    double th_singleMu = 1000*1000.;
    double th_singleE  = 1000*1000.;
    double th_diE      = 1000*1000.;
    double th_eMu_e    = 1000*1000.;
    double th_diMu_0   = 1000*1000.;
    double th_diMu_1   = 1000*1000.;
    double th_eMu_m    = 1000*1000.;


    //std::cout<< "random_run_number:"<< RRN << std::endl;
    //std::cout<< "lepton0pt"<< lep_0_pt << "lepton1pt:" << lep_1_pt << std::endl;

    // 2015 dataset
    if(is15){
      bool singleE  =(HLT_e24_lhmedium_L1EM20VH->EvalInstance() || HLT_e60_lhmedium->EvalInstance() || HLT_e120_lhloose->EvalInstance());
      bool singleMu =(HLT_mu20_iloose_L1MU15->EvalInstance() || HLT_mu50->EvalInstance());
      bool diE      = HLT_2e12_lhloose_L12EM10VH->EvalInstance();
      bool diMu     = HLT_mu18_mu8noL1->EvalInstance();
      bool eMu      = HLT_e17_loose_mu14->EvalInstance();

      th_singleMu = 21*1000.;
      th_singleE  = 25*1000.;
      th_diE      = 15*1000.;
      th_eMu_e    = 18*1000.;
      th_diMu_0   = 19*1000.;
      th_diMu_1   = 10*1000.;
      th_eMu_m    = 15*1000.;

      if (mus_selected_idx.size()==2 && els_selected_idx.size()==0){ //mm
	if(mus_selected_idx[0] == leptons_selected_idx[0] && mus_selected_idx[1] == leptons_selected_idx[1]){
	  if (lep_0_pt >= th_singleMu && singleMu==1 && (leptons_HLT_mu20_iloose_L1MU15->EvalInstance(lep_idx0)==1 || leptons_HLT_mu50->EvalInstance(lep_idx0)==1)){
            isTriggered_data = true;
            isTriggered_mc = true;
	    TriggerType = 10;
            if (!m_isData || m_isBoth) TriggerWeight_l0 *= tw_mu20ORmu50->EvalInstance(lep_idx0);
            if (debug) {
	      std::cout << "mm triggered data/mc tw_mu20ORmu50 weight " << TriggerWeight_l0 << std::endl;
            }
	  }
	  else if (lep_0_pt>=th_diMu_0 && lep_0_pt<th_singleMu && lep_1_pt >=th_diMu_1 && diMu==1 && leptons_HLT_mu18_mu8noL1->EvalInstance(lep_idx0)==1 && leptons_HLT_mu18_mu8noL1->EvalInstance(lep_idx1)==1){
            isTriggered_data = true;
            isTriggered_mc = true;
	    TriggerType = 12;
            if (!m_isData || m_isBoth) TriggerWeight_l0 *= tw_mu18->EvalInstance(lep_idx0);
            if (!m_isData || m_isBoth) TriggerWeight_l1 *= tw_mu8noL1->EvalInstance(lep_idx1);
            if (debug) {
	      std::cout << "mm triggered data/mc tw_mu8noL1 tw_mu18 weight " << TriggerWeight_l0 << " " << TriggerWeight_l1 << std::endl;
            }
	  }
	}
      }
      else if (els_selected_idx.size()==2 && mus_selected_idx.size()==0){ // ee
	if (lep_0_pt >= th_singleE && singleE==1 && (leptons_HLT_e24_lhmedium_L1EM20VH->EvalInstance(lep_idx0)==1 || leptons_HLT_e60_lhmedium->EvalInstance(lep_idx0)==1 || leptons_HLT_e120_lhloose->EvalInstance(lep_idx0)==1)){
	  isTriggered_mc = true;
	  isTriggered_data = true;
	  TriggerType = 20;
	  if (!m_isData || m_isBoth) TriggerWeight_l0 *= tw_singleE_2015_2016->EvalInstance(lep_idx0);
	  if (debug) {
	    std::cout << "mm triggered data/mc tw_e24ORe60ORe120 weight " << TriggerWeight_l0 << std::endl;
	  }
	}
	else if (lep_0_pt< th_singleE && lep_0_pt >= th_diE && lep_1_pt >= th_diE && diE==1 && leptons_HLT_2e12_lhloose_L12EM10VH->EvalInstance(lep_idx0)==1 && leptons_HLT_2e12_lhloose_L12EM10VH->EvalInstance(lep_idx1)==1){
	  isTriggered_mc = true;
	  isTriggered_data = true;
	  TriggerType = 22;
	  if (!m_isData || m_isBoth) TriggerWeight_l0 *= tw_2e12_2015_2e15_2016->EvalInstance(lep_idx0);
	  if (!m_isData || m_isBoth) TriggerWeight_l1 *= tw_2e12_2015_2e15_2016->EvalInstance(lep_idx1);
	  if (debug) {
	    std::cout << "mm triggered data/mc tw_2e12 weight " << TriggerWeight_l0 << " " << TriggerWeight_l1  <<   std::endl;
	  }
	}
      }
      else if (leptons_selected_idx.size() ==2 && mus_selected_idx[0]==leptons_selected_idx[0]){ //me
	if (lep_0_pt >= th_singleMu && lep_1_pt < th_singleE && singleMu==1 && (leptons_HLT_mu20_iloose_L1MU15->EvalInstance(lep_idx0)==1 || leptons_HLT_mu50->EvalInstance(lep_idx0)==1)){
	  isTriggered_mc = true;
	  isTriggered_data = true;
	  TriggerType = 10;
	  if (!m_isData || m_isBoth) TriggerWeight_l0 *= tw_mu20ORmu50->EvalInstance(lep_idx0);
	  if (debug) {
	    std::cout << "mm triggered data/mc tw_mu20ORmu50 weight " << TriggerWeight_l0 << std::endl;
	  }
	}
	else if (lep_1_pt >= th_singleE && singleE == 1 && (leptons_HLT_e24_lhmedium_L1EM20VH->EvalInstance(lep_idx1)==1 || leptons_HLT_e60_lhmedium->EvalInstance(lep_idx1)==1 || leptons_HLT_e120_lhloose->EvalInstance(lep_idx1)==1)) {
	  isTriggered_mc = true;
	  isTriggered_data = true;
	  TriggerType = 21;
	  if (!m_isData || m_isBoth) TriggerWeight_l1 *= tw_singleE_2015_2016->EvalInstance(lep_idx1);
	  if (debug) {
	    std::cout << "mm triggered data/mc tw_e24ORe60ORe120 weight " << TriggerWeight_l1 << std::endl;
	  }
	}
	else if (lep_1_pt < th_singleE && lep_1_pt >= th_eMu_e && lep_0_pt < th_singleMu && lep_0_pt >= th_eMu_m && eMu==1 && leptons_HLT_e17_loose_mu14->EvalInstance(lep_idx1)==1){
	  isTriggered_mc = true;
	  isTriggered_data = true;
	  TriggerType = 211;
	  if (!m_isData || m_isBoth) TriggerWeight_l1 *= tw_e17_2015_e17_2016->EvalInstance(lep_idx1);
	  if (!m_isData || m_isBoth) TriggerWeight_l0 *= tw_mu14->EvalInstance(lep_idx0);
	  if (debug) {
	    std::cout << "mm triggereddata/mc tw_e17 tw_mu14 weight " << TriggerWeight_l0 <<  " "  << TriggerWeight_l1 << std::endl;
	  }
	}
      }
      else if (leptons_selected_idx.size() ==2 && els_selected_idx[0]==leptons_selected_idx[0]) { //em
	if (lep_0_pt >= th_singleE && singleE==1 && (leptons_HLT_e24_lhmedium_L1EM20VH->EvalInstance(lep_idx0)==1 || leptons_HLT_e60_lhmedium->EvalInstance(lep_idx0)==1 || leptons_HLT_e120_lhloose->EvalInstance(lep_idx0)==1)){
	  isTriggered_mc = true;
	  isTriggered_data = true;
	  TriggerType = 20;
	  if (!m_isData || m_isBoth) TriggerWeight_l0 *= tw_singleE_2015_2016->EvalInstance(lep_idx0);
	  if (debug) {
	    std::cout << "mm triggered data/mc tw_e24ORe60ORe120 weight " << TriggerWeight_l0 << std::endl;
	  }
	}
	else if (lep_0_pt < th_singleE && lep_1_pt >=th_singleMu && singleMu==1 && (leptons_HLT_mu20_iloose_L1MU15->EvalInstance(lep_idx1)==1 || leptons_HLT_mu50->EvalInstance(lep_idx1)==1)){
	  isTriggered_mc = true;
	  isTriggered_data = true;
	  TriggerType = 11;
	  if (!m_isData || m_isBoth) TriggerWeight_l1 *= tw_mu20ORmu50->EvalInstance(lep_idx1);
	  if (debug) {
	    std::cout << "mm triggered data/mc tw_mu20ORmu50 weight " << TriggerWeight_l1 << std::endl;
	  }
	}
	else if (lep_0_pt < th_singleE && lep_0_pt >= th_eMu_e && lep_1_pt < th_singleMu && lep_1_pt >= th_eMu_m && eMu==1 && leptons_HLT_e17_loose_mu14->EvalInstance(lep_idx0)==1){
	  isTriggered_mc = true;
	  isTriggered_data = true;
	  TriggerType = 211;
	  if (!m_isData || m_isBoth) TriggerWeight_l0 *= tw_e17_2015_e17_2016->EvalInstance(lep_idx0);
	  if (!m_isData || m_isBoth) TriggerWeight_l1 *= tw_mu14->EvalInstance(lep_idx1);
	  if (debug) {
	    std::cout << "mm triggered data/mc tw_e17 tw_mu14 weight " << TriggerWeight_l0 << " " << TriggerWeight_l1 << std::endl;
	  }
	}
      }
    } // end 2015 dataset
     // 2016 dataset
    if(is16){
      // std::cout << "Run for 2016 dataset" << std::endl;
      bool singleE  = 0;
      bool singleMu = 0;
      bool diE      = 0;
      bool diMu     = 0;
      bool eMu      = 0;

      if(RRN==298687){
	singleE=(HLT_e24_lhtight_nod0_ivarloose->EvalInstance() ||HLT_e24_lhmedium_L1EM20VH->EvalInstance()  || HLT_e60_lhmedium_nod0->EvalInstance() || HLT_e140_lhloose_nod0->EvalInstance());
      }
      else {
	singleE=(HLT_e24_lhtight_nod0_ivarloose->EvalInstance() || HLT_e60_lhmedium_nod0->EvalInstance() || HLT_e140_lhloose_nod0->EvalInstance());
      }
      singleMu = (leptons_HLT_mu24_ivarmedium->EvalInstance() || HLT_mu50->EvalInstance());
      if(RRN==300540){
	diE = HLT_2e17_lhvloose_nod0->EvalInstance();
      }
      else {
	diE = HLT_2e15_lhvloose_nod0_L12EM13VH->EvalInstance();
      }
      diMu = HLT_mu20_mu8noL1->EvalInstance();
      eMu = HLT_e17_lhloose_nod0_mu14->EvalInstance();

      th_singleMu = 26.*1000.;
      th_singleE  = 25*1000.;
      th_diE      = 16*1000.;
      th_eMu_e    = 18*1000.;
      th_diMu_0   = 21*1000.;
      th_diMu_1   = 10*1000.;
      th_eMu_m    = 15*1000.;

      if (mus_selected_idx.size()==2 && els_selected_idx.size()==0){ //mm
	if (lep_0_pt >= th_singleMu && singleMu==1 && (leptons_HLT_mu24_ivarmedium->EvalInstance(lep_idx0)==1 || leptons_HLT_mu50->EvalInstance(lep_idx0)==1)){
	  isTriggered_data = true;
	  isTriggered_mc = true;
	  TriggerType = 10;
	  if (!m_isData || m_isBoth) TriggerWeight_l0 *= tw_singleMu_2016->EvalInstance(lep_idx0);
	}
	else if (lep_0_pt>=th_diMu_0 && lep_0_pt<th_singleMu && lep_1_pt>=th_diMu_1 && diMu==1 && leptons_HLT_mu20_mu8noL1->EvalInstance(lep_idx0)==1 && leptons_HLT_mu20_mu8noL1->EvalInstance(lep_idx1)==1){
	  isTriggered_data = true;
	  isTriggered_mc = true;
	  TriggerType = 12;
	  if (!m_isData || m_isBoth) TriggerWeight_l0 *= tw_mu20_2016->EvalInstance(lep_idx0);
	  if (!m_isData || m_isBoth) TriggerWeight_l1 *= tw_mu8noL1->EvalInstance(lep_idx1);
	}
      }

      else if (els_selected_idx.size()==2 && mus_selected_idx.size()==0){ // ee
	if (RRN==298687 && lep_0_pt >= th_singleE && singleE==1 && (leptons_HLT_e24_lhtight_nod0_ivarloose->EvalInstance(lep_idx0)==1 || leptons_HLT_e24_lhmedium_L1EM20VH->EvalInstance(lep_idx0)==1 || leptons_HLT_e60_lhmedium_nod0->EvalInstance(lep_idx0)==1 || leptons_HLT_e140_lhloose_nod0->EvalInstance(lep_idx0)==1)){
	  isTriggered_data = true;
	  isTriggered_mc = true;
	  TriggerType = 20;
	  if (!m_isData || m_isBoth) TriggerWeight_l0 *= tw_singleE_2015_2016->EvalInstance(lep_idx0);
	}
	else if (RRN!=298687 && lep_0_pt >= th_singleE && singleE==1 && (leptons_HLT_e24_lhtight_nod0_ivarloose->EvalInstance(lep_idx0)==1 || leptons_HLT_e60_lhmedium_nod0->EvalInstance(lep_idx0)==1 || leptons_HLT_e140_lhloose_nod0->EvalInstance(lep_idx0)==1)){
	  isTriggered_data = true;
	  isTriggered_mc = true;
	  TriggerType = 20;
	  if (!m_isData || m_isBoth) TriggerWeight_l0 *= tw_singleE_2015_2016->EvalInstance(lep_idx0);
	}
	else if (RRN==300540 && lep_0_pt<th_singleE && lep_0_pt >= 18*1000. && lep_1_pt >= 18*1000. && diE==1 && leptons_HLT_2e17_lhvloose_nod0->EvalInstance(lep_idx0)==1 && leptons_HLT_2e17_lhvloose_nod0->EvalInstance(lep_idx1)==1){
	  isTriggered_data = true;
	  isTriggered_mc = true;
	  TriggerType = 22;
	  if (!m_isData || m_isBoth) TriggerWeight_l0 *= tw_2e12_2015_2e17_2016->EvalInstance(lep_idx0);
	  if (!m_isData || m_isBoth) TriggerWeight_l1 *= tw_2e12_2015_2e17_2016->EvalInstance(lep_idx1);
	}
	else if (RRN!=300540 && lep_0_pt<th_singleE && lep_0_pt >= th_diE && lep_1_pt >= th_diE && diE==1 && leptons_HLT_2e15_lhvloose_nod0_L12EM13VH->EvalInstance(lep_idx0)==1 && leptons_HLT_2e15_lhvloose_nod0_L12EM13VH->EvalInstance(lep_idx1)==1){
          isTriggered_data = true;
	  isTriggered_mc = true;
          TriggerType = 22;
          if (!m_isData || m_isBoth) TriggerWeight_l0 *= tw_2e12_2015_2e15_2016->EvalInstance(lep_idx0);
          if (!m_isData || m_isBoth) TriggerWeight_l1 *= tw_2e12_2015_2e15_2016->EvalInstance(lep_idx1);
        }
      }

      else if (leptons_selected_idx.size() ==2 && mus_selected_idx[0]==leptons_selected_idx[0]){ //me
	if (lep_0_pt>=th_singleMu && lep_1_pt<th_singleE && singleMu==1 && (leptons_HLT_mu24_ivarmedium->EvalInstance(lep_idx0)==1 || leptons_HLT_mu50->EvalInstance(lep_idx0)==1)){
	  isTriggered_mc = true;
	  isTriggered_data = true;
	  TriggerType = 10;
	  if (!m_isData || m_isBoth) TriggerWeight_l0 *= tw_singleMu_2016->EvalInstance(lep_idx0);
	}
	else if (RRN==298687 && lep_1_pt>=th_singleE && singleE == 1 && (leptons_HLT_e24_lhtight_nod0_ivarloose->EvalInstance(lep_idx1)==1 || leptons_HLT_e24_lhmedium_L1EM20VH->EvalInstance(lep_idx1)==1 || leptons_HLT_e60_lhmedium_nod0->EvalInstance(lep_idx1)==1 || leptons_HLT_e140_lhloose_nod0->EvalInstance(lep_idx1)==1)) {
	  isTriggered_mc = true;
	  isTriggered_data = true;
	  TriggerType = 21;
	  if (!m_isData || m_isBoth) TriggerWeight_l1 *= tw_singleE_2015_2016->EvalInstance(lep_idx1);
	}
	else if (RRN!=298687 && lep_1_pt>=th_singleE && singleE == 1 && (leptons_HLT_e24_lhtight_nod0_ivarloose->EvalInstance(lep_idx1)==1 || leptons_HLT_e60_lhmedium_nod0->EvalInstance(lep_idx1)==1 || leptons_HLT_e140_lhloose_nod0->EvalInstance(lep_idx1)==1)) {
          isTriggered_mc = true;
	  isTriggered_data = true;
          TriggerType = 21;
          if (!m_isData || m_isBoth) TriggerWeight_l1 *= tw_singleE_2015_2016->EvalInstance(lep_idx1);
        }
	else if (lep_1_pt<th_singleE && lep_1_pt>=th_eMu_e && lep_0_pt<th_singleMu && lep_0_pt>=th_eMu_m && eMu==1 && leptons_HLT_e17_lhloose_nod0_mu14->EvalInstance(lep_idx1)==1){
	  isTriggered_mc = true;
	  isTriggered_data = true;
	  TriggerType = 211;
	  if (!m_isData || m_isBoth) TriggerWeight_l1 *= tw_e17_2015_e17_2016->EvalInstance(lep_idx1);
	  if (!m_isData || m_isBoth) TriggerWeight_l0 *= tw_mu14->EvalInstance(lep_idx0);
	}

      }

      else if (leptons_selected_idx.size() ==2 && els_selected_idx[0]==leptons_selected_idx[0]) { // em
	if (RRN!=298687 && lep_0_pt>=th_singleE && singleE==1 && (leptons_HLT_e24_lhtight_nod0_ivarloose->EvalInstance(lep_idx0)==1 || leptons_HLT_e60_lhmedium_nod0->EvalInstance(lep_idx0)==1 || leptons_HLT_e140_lhloose_nod0->EvalInstance(lep_idx0)==1)){
	  isTriggered_mc = true;
	  isTriggered_data = true;
	  TriggerType = 20;
	  if (!m_isData || m_isBoth) TriggerWeight_l0 *= tw_singleE_2015_2016->EvalInstance(lep_idx0);
	}
	else if (RRN==298687 && lep_0_pt>=th_singleE && singleE==1 && (leptons_HLT_e24_lhtight_nod0_ivarloose->EvalInstance(lep_idx0)==1 || leptons_HLT_e24_lhmedium_L1EM20VH->EvalInstance(lep_idx0) || leptons_HLT_e60_lhmedium_nod0->EvalInstance(lep_idx0)==1 || leptons_HLT_e140_lhloose_nod0->EvalInstance(lep_idx0)==1)){
	  isTriggered_mc = true;
	  isTriggered_data = true;
	  TriggerType = 20;
	  if (!m_isData || m_isBoth) TriggerWeight_l0 *= tw_singleE_2015_2016->EvalInstance(lep_idx0);
	}
	else if (lep_0_pt<th_singleE && lep_1_pt>=th_singleMu && singleMu==1 && (leptons_HLT_mu24_ivarmedium->EvalInstance(lep_idx1)==1 || leptons_HLT_mu50->EvalInstance(lep_idx1)==1)){
	  isTriggered_mc = true;
	  isTriggered_data = true;
	  TriggerType = 11;
	  if (!m_isData || m_isBoth) TriggerWeight_l1 *= tw_singleMu_2016->EvalInstance(lep_idx1);
	}
	else if (lep_0_pt<th_singleE && lep_0_pt>=th_eMu_e && lep_1_pt<th_singleMu && lep_1_pt>=th_eMu_m && eMu==1 && leptons_HLT_e17_lhloose_nod0_mu14->EvalInstance(lep_idx0)==1){
	  isTriggered_mc = true;
	  isTriggered_data = true;
	  TriggerType = 211;
	  if (!m_isData || m_isBoth) TriggerWeight_l0 *= tw_e17_2015_e17_2016->EvalInstance(lep_idx0);
	  if (!m_isData || m_isBoth) TriggerWeight_l1 *= tw_mu14->EvalInstance(lep_idx1);
	}
      }
    }

    if (isTemplateFake) TriggerWeight_l1=1.0;
    TriggerWeight=TriggerWeight_l0*TriggerWeight_l1;

    //std::cout << "isTriggerde_mc " << isTriggered_mc << std::endl;

    return true;

}

bool EventSelection_leplep_basis::obtain_lepton_sf() {
    LeptonWeight =1.0;
    LeptonWeight_tight =1.0;
    LeptonWeight_lep0_tight =1.0;
    LeptonWeight_lep1_tight =1.0;
    if (!m_isData || m_isBoth) {
        if (leptons_selected_idx.size()>=2) {
            for ( auto el_idx: els_selected_idx) {
                if (isTemplateFake && el_idx == leptons_selected_idx[1] ) {
                    LeptonWeight *= 1.0;
                } else if(el_idx == leptons_selected_idx[0] || el_idx == leptons_selected_idx[1]){
                    LeptonWeight *= el_ID_effSF->EvalInstance(el_idx);
                    LeptonWeight *= el_ISO_effSF->EvalInstance(el_idx);
                    LeptonWeight *= el_Track_effSF->EvalInstance(el_idx);
//                    std::cout << "el_Track_effSF " << el_Track_effSF->EvalInstance(el_idx) << " " << el_idx << std::endl;
                }
            }
            for ( auto mu_idx: mus_selected_idx) {
                if (isTemplateFake && mu_idx == leptons_selected_idx[1]) {
                    LeptonWeight *= 1.0;
                } else if(mu_idx == leptons_selected_idx[0] || mu_idx == leptons_selected_idx[1]){
                    LeptonWeight *= mu_ID_effSF->EvalInstance(mu_idx);
		    LeptonWeight *= mu_ISO_effSF->EvalInstance(mu_idx);
		    // v06:
		    // MU ISO SF buggy! Set to 1 atm for 2016 ad 2015
		    //if(is15){
		    //  LeptonWeight *= mu_ISO_effSF->EvalInstance(mu_idx);
		    //}
		    //if(is16){
		    //  LeptonWeight *= 1.;
		    //}
                }
            }
        }
    }


    return true;
}

bool EventSelection_leplep_basis::obtain_jet_sf(){
    JVTweight=1.0;
    MVXweight=1.0;
    isBtagged = false;
    //std::cout << "In jet SF" << std::endl;
    for ( auto jet_idx: jets_selected_idx) {
        if (!m_isData || m_isBoth) JVTweight *= jets_JVT_effSF->EvalInstance(jet_idx);
        int mvx_tagged = m_jets_mvx_tagged->EvalInstance(jet_idx);
        if(m_jets_pt->EvalInstance(jet_idx) >= 25*1000. && fabs(m_jets_eta->EvalInstance(jet_idx)) <= 2.5 && mvx_tagged != 0){
            isBtagged = true;
            if (!m_isData || m_isBoth) MVXweight *= jets_MVX_effSF->EvalInstance(jet_idx);
        }
        else {
            if (!m_isData || m_isBoth) MVXweight *= jets_MVX_ineffSF->EvalInstance(jet_idx);
        }
    }
    if (m_isData)  {
        MVXweight=1.0;
        JVTweight=1.0;
    }

    //std::cout << "JVT weight: " << JVTweight << std::endl;
    return true;
}


bool EventSelection_leplep_basis::initialise_branches() {
    EventSelection::initialise_branches();
    m_leptons_id_loose->GetNdata();
    m_leptons_id_medium->GetNdata();
    m_leptons_id_tight->GetNdata();
    m_leptons_iso_wp->GetNdata();
    m_taus_n_tracks->GetNdata();
    m_leptons_cluster_eta->GetNdata();
    m_leptons_cluster_eta_be2->GetNdata();
    m_leptons_trk_d0->GetNdata();
    m_leptons_trk_d0_sig->GetNdata();
    if (!m_isData || m_isBoth) {
        mu_ID_effSF->GetNdata();
        mu_ISO_effSF->GetNdata();
        el_ID_effSF->GetNdata();
        el_ISO_effSF->GetNdata();
        el_Track_effSF->GetNdata();
        jets_JVT_effSF->GetNdata();
        jets_MVX_effSF->GetNdata();
        jets_MVX_ineffSF->GetNdata();
        tw_mu14->GetNdata();
        tw_mu20ORmu50->GetNdata();
        tw_mu18->GetNdata();
        tw_mu8noL1->GetNdata();
	tw_singleE_2015_2016->GetNdata();
	tw_singleMu_2016->GetNdata();
	tw_2e12_2015_2e15_2016->GetNdata();
	tw_2e12_2015_2e17_2016->GetNdata();
	tw_mu20_2016->GetNdata();
	tw_e17_2015_e17_2016->GetNdata();
    }

    leptons_HLT_e24_lhmedium_L1EM20VH->GetNdata();
    leptons_HLT_e60_lhmedium->GetNdata();
    leptons_HLT_e120_lhloose->GetNdata();
    leptons_HLT_mu20_iloose_L1MU15->GetNdata();
    leptons_HLT_mu50->GetNdata();
    leptons_HLT_2e12_lhloose_L12EM10VH->GetNdata();
    leptons_HLT_mu18_mu8noL1 ->GetNdata();
    leptons_HLT_e17_loose_mu14->GetNdata();
    leptons_HLT_e24_lhtight_nod0_ivarloose->GetNdata();
    leptons_HLT_e60_lhmedium_nod0->GetNdata();
    leptons_HLT_e140_lhloose_nod0->GetNdata();
    leptons_HLT_mu20_mu8noL1->GetNdata();
    leptons_HLT_mu24_ivarmedium->GetNdata();
    leptons_HLT_e17_lhloose_nod0_mu14->GetNdata();
    leptons_HLT_2e17_lhvloose_nod0->GetNdata();
    leptons_HLT_2e15_lhvloose_nod0_L12EM13VH->GetNdata();

    return true;
}

bool EventSelection_leplep_basis::selection_objects() {
    EventSelection::selection_objects();
    prepare_selection(mus, all_mus_selected);
    prepare_selection(els, tau_ov_els_selected);
    for (size_t i=0; i<els.size(); i++) {
        if (els[i].Pt()>15*1000 && m_leptons_id_medium->EvalInstance(els_idx[i]) ==1){
            tau_ov_els_selected[i]=true;
        } else {
            tau_ov_els_selected[i]=false;
        }
    }
    if (debug) {
        std::cout << "AA tau ov e ";
        printVectors(tau_ov_els_selected);
    }
    return true;
}

bool EventSelection_leplep_basis::el_selection(int el_idx) const {
  bool result= (m_leptons_pt->EvalInstance(el_idx)>=15*1000 && fabs(m_leptons_cluster_eta->EvalInstance(el_idx))<=2.47 && fabs(m_leptons_cluster_eta_be2->EvalInstance(el_idx))<=2.47 && m_leptons_id_medium->EvalInstance(el_idx)==1 && ((int)m_leptons_iso_wp->EvalInstance(el_idx)%100000)/10000 > 0);
  if (isTemplateFake) {
      if (el_idx<2) result=true;
  }
    if (!result && debug) {
      std::cout << "e fail " << el_idx << " " <<  m_leptons_pt->EvalInstance(el_idx) << " " << m_leptons_cluster_eta->EvalInstance(el_idx) << " "  <<  m_leptons_id_medium->EvalInstance(el_idx) << " "<< m_leptons_iso_wp->EvalInstance(el_idx) <<std::endl;
    }
    return result;
}

bool EventSelection_leplep_basis::mu_selection(int mu_idx) const {
  bool result= (m_leptons_pt->EvalInstance(mu_idx)>=10*1000 && fabs(m_leptons_eta->EvalInstance(mu_idx))<=2.47 && m_leptons_id_medium->EvalInstance(mu_idx)==1 && ((int)m_leptons_iso_wp->EvalInstance(mu_idx)%100000)/10000 > 0);
  if (isTemplateFake) {
      if (mu_idx<2) result=true;
  }
    if (!result && debug) {
      std::cout << "m fail " << mu_idx << " " <<  m_leptons_pt->EvalInstance(mu_idx) << " " << m_leptons_eta->EvalInstance(mu_idx) << " "  <<  m_leptons_id_medium->EvalInstance(mu_idx) << " " << m_leptons_iso_wp->EvalInstance(mu_idx) <<std::endl;
    }
    return result;
}

bool EventSelection_leplep_basis::tau_selection(int tau_idx) const {
    int taus_n_tracks=m_taus_n_tracks->EvalInstance(tau_idx);
    double taus_eta=m_taus_eta->EvalInstance(tau_idx);
    bool result= (m_taus_pt->EvalInstance(tau_idx) >20*1000  && (taus_n_tracks == 1 || taus_n_tracks  == 3) && (taus_eta < 2.5 && (taus_eta<1.37 || taus_eta>1.52)));
    if (!result && debug) {
       std::cout << "tau fail " << tau_idx << " " <<  m_leptons_pt->EvalInstance(tau_idx) << " " << m_leptons_eta->EvalInstance(tau_idx) << " "  <<  m_taus_n_tracks->EvalInstance(tau_idx) << std::endl;
    }
    return result;
}

bool EventSelection_leplep_basis::jet_selection(int jet_idx) const {
    (void) jet_idx;
    return true;
}

void EventSelection_leplep_basis::removeoverlap() {

  // [1] (selected) electron must not overlap with selected muons
  OVR_DeltaR(mus,mus_selected,els,els_selected,0.2);
  // [2] taus must not overlap with any muon in the ntuple
  OVR_DeltaR(mus,all_mus_selected,taus,taus_selected,0.2);
  // [3] taus must not overlap with medium electrons with pT > 15 GeV
  OVR_DeltaR(els,tau_ov_els_selected,taus,taus_selected,0.2);
  // [4] jets must not overlap with selected muons, electrons and taus
  OVR_DeltaR(mus,mus_selected,jets,jets_selected,0.2);
  OVR_DeltaR(els,els_selected,jets,jets_selected,0.2);
  OVR_DeltaR(taus,taus_selected,jets,jets_selected,0.2);

}

bool EventSelection_leplep_basis::calculate_variables() {
    EventSelection::calculate_variables();
    calculate_VBF_cat();
    calculate_VBF_cat_ZttCR();
    calculate_boosted_cat();
    calculate_boosted_cat_ZttCR();
    return true;
}

bool EventSelection_leplep_basis::calculate_lepton_variables(){
    EventSelection::calculate_lepton_variables();
    m_leplep_d0_l0=-999;
    m_leplep_d0_l1=-999;
    m_leplep_d0sig_l0=-999;
    m_leplep_d0sig_l1=-999;
    if (leptons_selected_idx.size()>0) {
        m_leplep_d0_l0=m_leptons_trk_d0->EvalInstance(leptons_selected_idx[0]);
        m_leplep_d0sig_l0=m_leptons_trk_d0_sig->EvalInstance(leptons_selected_idx[0]);
    }
    if (leptons_selected_idx.size()>1) {
        m_leplep_d0_l1=m_leptons_trk_d0->EvalInstance(leptons_selected_idx[1]);
        m_leplep_d0sig_l1=m_leptons_trk_d0_sig->EvalInstance(leptons_selected_idx[1]);
    }
    //std::cout << "lepton idx ";
    //for (auto idx: leptons_selected_idx) {
    //    std::cout << idx << " ";
    //}
    //std::cout << "lepton idx " << std::endl;
    return true;
}

bool EventSelection_leplep_basis::calculate_VBF_cat() {
    m_VBF_cat = false;
    //std::cout << "VBF " << m_category_2jetVBF->EvalInstance() << " "<< jets_selected_vector.size() << std::endl;
    if (!(jets_selected_vector.size()>=2)) return true;
    //std::cout << "VBF " << m_category_2jetVBF->EvalInstance() << " "<< jets_selected_vector[1].Pt() << std::endl;
    if (!(jets_selected_vector[0].Pt()>40 * 1000 )) return true;
    if (!(jets_selected_vector[1].Pt()>30 * 1000 )) return true;
    //std::cout << "VBF " << m_category_2jetVBF->EvalInstance() << " "<< m_jet_deta<< std::endl;
    if (!(m_jet_deta >= 3 )) return true;
    //std::cout << "VBF " << m_category_2jetVBF->EvalInstance() << " "<< m_jet_mjj<< std::endl;
    if (!(m_jet_mjj >=400*1000)) return true;
    //std::cout << "VBF " << m_category_2jetVBF->EvalInstance() << " "<< m_bveto<< std::endl;
    if (isBtagged) return true;
    //std::cout << "VBF " << m_category_2jetVBF->EvalInstance() << " "<< m_lepton_centrality<< std::endl;
    if (!(m_lepton_centrality)) return true;
    //std::cout << "VBF " << m_category_2jetVBF->EvalInstance() << " "<< m_central_jet_veto<< std::endl;
    //if (!(m_central_jet_veto)) return true;
    m_VBF_cat=true;
    //m_category_2jetVBF->GetNdata();
    // std::cout << "VBF " << m_category_2jetVBF->EvalInstance() << m_VBF_cat << std::endl;
    //if (m_category_2jetVBF->EvalInstance() == 1 ) {
    //    std::cout << "VBF " << m_VBF_cat << std::endl;
    //}
    return true;
}

bool EventSelection_leplep_basis::calculate_VBF_cat_ZttCR() {
    m_VBF_cat_ZttCR = false;
    //std::cout << "VBF " << m_category_2jetVBF->EvalInstance() << " "<< jets_selected_vector.size() << std::endl;
    if (!(jets_selected_vector.size()>=2)) return true;
    //std::cout << "VBF " << m_category_2jetVBF->EvalInstance() << " "<< jets_selected_vector[1].Pt() << std::endl;
    if (!(jets_selected_vector[0].Pt()>40 * 1000 )) return true;
    if (!(jets_selected_vector[1].Pt()>30 * 1000 )) return true;
    //std::cout << "VBF " << m_category_2jetVBF->EvalInstance() << " "<< m_jet_deta<< std::endl;
    if (!(m_jet_deta >= 3 )) return true;
    //std::cout << "VBF " << m_category_2jetVBF->EvalInstance() << " "<< m_jet_mjj<< std::endl;
    if (!(m_jet_mjj >=300*1000)) return true;
    //std::cout << "VBF " << m_category_2jetVBF->EvalInstance() << " "<< m_bveto<< std::endl;
    if (isBtagged) return true;
    //std::cout << "VBF " << m_category_2jetVBF->EvalInstance() << " "<< m_lepton_centrality<< std::endl;
    if (!(m_lepton_centrality)) return true;
    //std::cout << "VBF " << m_category_2jetVBF->EvalInstance() << " "<< m_central_jet_veto<< std::endl;
    //if (!(m_central_jet_veto)) return true;
    m_VBF_cat_ZttCR=true;
    //m_category_2jetVBF->GetNdata();
    // std::cout << "VBF " << m_category_2jetVBF->EvalInstance() << m_VBF_cat << std::endl;
    //if (m_category_2jetVBF->EvalInstance() == 1 ) {
    //    std::cout << "VBF " << m_VBF_cat << std::endl;
    //}
    return true;
}

bool EventSelection_leplep_basis::calculate_boosted_cat() {
    m_boosted_cat=false;
    if (m_VBF_cat) return true;
    if (m_higgs_pt<100*1000) return true;
    m_boosted_cat=true;
    return true;
}

bool EventSelection_leplep_basis::calculate_boosted_cat_ZttCR() {
    m_boosted_cat_ZttCR=false;
    if (m_VBF_cat) return true;
    if (m_leplep_pt_ll<100*1000) return true;
    m_boosted_cat_ZttCR=true;
    return true;
}
