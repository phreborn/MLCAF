#include "Htautau/EventSelection_leplep_tight.h"
#include <limits>
#include <algorithm>
#include <vector>
#include <string>
#include <chrono>
#include "QFramework/TQIterator.h"
#include "Htautau/EventSelection_leplep_base_static.h"
// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
//

ClassImp(EventSelection_leplep_tight)

//______________________________________________________________________________________________
EventSelection_leplep_tight::EventSelection_leplep_tight(const TString& expression, int systematic, int flag):EventSelection_leplep_base(expression,systematic,flag){
}
//______________________________________________________________________________________________
EventSelection_leplep_tight::~EventSelection_leplep_tight() {
  // default destructor
}


bool EventSelection_leplep_tight::add_lepton_sf_brachnes() {
  EventSelection_leplep_base < EventSelection_leplep_tight >::add_lepton_sf_brachnes();
    mu_ID_effSF_name    = "leptons_NOMINAL_effSF_RecoTight";
    mu_ISO_effSF_name   = "leptons_NOMINAL_effSF_IsoGradient";
    el_ID_effSF_name    = "leptons_NOMINAL_effSF_offline_TightLLH_2015_13TeV_rel20p0_25ns_v04";
    el_ISO_effSF_name   = "leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04";
    el_Track_effSF_name = "leptons_NOMINAL_effSF_offline_RecoTrk_2015_13TeV_rel20p0_25ns_v04";

    switch (m_systematic) {
        case -1  : mu_ID_effSF_name    = "leptons_MUON_EFF_STAT_1down_effSF_RecoTight"       ; break ;
        case 1   : mu_ID_effSF_name    = "leptons_MUON_EFF_STAT_1up_effSF_RecoTight"         ; break ;
        case -2  : mu_ID_effSF_name    = "leptons_MUON_EFF_STAT_LOWPT_1down_effSF_RecoTight" ; break ;
        case 2   : mu_ID_effSF_name    = "leptons_MUON_EFF_STAT_LOWPT_1up_effSF_RecoTight"   ; break ;
        case -3  : mu_ID_effSF_name    = "leptons_MUON_EFF_SYS_1down_effSF_RecoTight"        ; break ;
        case 3   : mu_ID_effSF_name    = "leptons_MUON_EFF_SYS_1up_effSF_RecoTight"          ; break ;
        case -4  : mu_ID_effSF_name    = "leptons_MUON_EFF_SYS_LOWPT_1down_effSF_RecoTight"  ; break ;
        case 4   : mu_ID_effSF_name    = "leptons_MUON_EFF_SYS_LOWPT_1up_effSF_RecoTight"    ; break ;
        case -10 : mu_ISO_effSF_name   = "leptons_MUON_ISO_STAT_1down_effSF_IsoGradient" ; break ;
        case 10  : mu_ISO_effSF_name   = "leptons_MUON_ISO_STAT_1up_effSF_IsoGradient"   ; break ;
        case -11 : mu_ISO_effSF_name   = "leptons_MUON_ISO_SYS_1down_effSF_IsoGradient"  ; break ;
        case 11  : mu_ISO_effSF_name   = "leptons_MUON_ISO_SYS_1up_effSF_IsoGradient"    ; break ;
        case -20 : el_ID_effSF_name    = "leptons_EL_EFF_ID_TotalCorrUncertainty_1down_effSF_offline_TightLLH_2015_13TeV_rel20p0_25ns_v04"; break;
        case 20  : el_ID_effSF_name    = "leptons_EL_EFF_ID_TotalCorrUncertainty_1up_effSF_offline_TightLLH_2015_13TeV_rel20p0_25ns_v04"; break;
        case -30 : el_ISO_effSF_name   = "leptons_EL_EFF_Iso_TotalCorrUncertainty_1down_effSF_Isolation_TightLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04"; break;
        case 30  : el_ISO_effSF_name   = "leptons_EL_EFF_Iso_TotalCorrUncertainty_1up_effSF_Isolation_TightLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04"; break;
        case -40 : el_Track_effSF_name = "leptons_EL_EFF_Reco_TotalCorrUncertainty_1down_effSF_offline_RecoTrk_2015_13TeV_rel20p0_25ns_v04"; break;
        case 40  : el_Track_effSF_name = "leptons_EL_EFF_Reco_TotalCorrUncertainty_1up_effSF_offline_RecoTrk_2015_13TeV_rel20p0_25ns_v04"; break;
    }
    additional_branches.push_back(mu_ID_effSF_name);
    additional_branches.push_back(mu_ISO_effSF_name);
    additional_branches.push_back(el_ID_effSF_name);
    additional_branches.push_back(el_ISO_effSF_name);
    additional_branches.push_back(el_Track_effSF_name);
    return true;
}


bool EventSelection_leplep_tight::add_trigger_sf_brachnes() {
  EventSelection_leplep_base < EventSelection_leplep_tight >::add_trigger_sf_brachnes();
    tw_mu14_name           = "leptons_NOMINAL_HLT_mu14_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE";
    tw_e17_name            = "leptons_NOMINAL_effSF_e17_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04";
    tw_2e12_name           = "leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04";
    tw_mu20ORmu50_name     = "leptons_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE";
    tw_mu18_name           = "leptons_NOMINAL_HLT_mu18_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE";
    tw_mu8noL1_name        = "leptons_NOMINAL_HLT_mu8noL1_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE";
    tw_e24ORe60ORe120_name = "leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04";

    switch (m_systematic) {
        case -100: tw_mu14_name           = "leptons_MUON_EFF_TrigStatUncertainty_1down_HLT_mu14_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE";
                   tw_mu20ORmu50_name     = "leptons_MUON_EFF_TrigStatUncertainty_1down_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE";
                   tw_mu18_name           = "leptons_MUON_EFF_TrigStatUncertainty_1down_HLT_mu18_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE";
                   tw_mu8noL1_name        = "leptons_MUON_EFF_TrigStatUncertainty_1down_HLT_mu8noL1_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE"; break;
        case  100: tw_mu14_name           = "leptons_MUON_EFF_TrigStatUncertainty_1up_HLT_mu14_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE";
                   tw_mu20ORmu50_name     = "leptons_MUON_EFF_TrigStatUncertainty_1up_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE";
                   tw_mu18_name           = "leptons_MUON_EFF_TrigStatUncertainty_1up_HLT_mu18_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE";
                   tw_mu8noL1_name        = "leptons_MUON_EFF_TrigStatUncertainty_1up_HLT_mu8noL1_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE"; break;
        case -101: tw_mu14_name           = "leptons_MUON_EFF_TrigSystUncertainty_1down_HLT_mu14_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE";
                   tw_mu20ORmu50_name     = "leptons_MUON_EFF_TrigSystUncertainty_1down_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE";
                   tw_mu18_name           = "leptons_MUON_EFF_TrigSystUncertainty_1down_HLT_mu18_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE";
                   tw_mu8noL1_name        = "leptons_MUON_EFF_TrigSystUncertainty_1down_HLT_mu8noL1_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE"; break;
        case  101: tw_mu14_name           = "leptons_MUON_EFF_TrigSystUncertainty_1up_HLT_mu14_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE";
                   tw_mu20ORmu50_name     = "leptons_MUON_EFF_TrigSystUncertainty_1up_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE";
                   tw_mu18_name           = "leptons_MUON_EFF_TrigSystUncertainty_1up_HLT_mu18_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE";
                   tw_mu8noL1_name        = "leptons_MUON_EFF_TrigSystUncertainty_1up_HLT_mu8noL1_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE"; break;
        case -200: tw_e17_name            = "leptons_EL_EFF_Trigger_TotalCorrUncertainty_1down_effSF_e17_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04";
                   tw_2e12_name           = "leptons_EL_EFF_Trigger_TotalCorrUncertainty_1down_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04";
                   tw_e24ORe60ORe120_name = "leptons_EL_EFF_Trigger_TotalCorrUncertainty_1down_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04";
        case  200: tw_e17_name            = "leptons_EL_EFF_Trigger_TotalCorrUncertainty_1up_effSF_e17_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04";
                   tw_2e12_name           = "leptons_EL_EFF_Trigger_TotalCorrUncertainty_1up_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04";
                   tw_e24ORe60ORe120_name = "leptons_EL_EFF_Trigger_TotalCorrUncertainty_1up_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04";
    }

    additional_branches.push_back(tw_mu14_name);
    additional_branches.push_back(tw_e17_name);
    additional_branches.push_back(tw_2e12_name);
    additional_branches.push_back(tw_mu20ORmu50_name);
    additional_branches.push_back(tw_mu18_name);
    additional_branches.push_back(tw_mu8noL1_name);
    additional_branches.push_back(tw_e24ORe60ORe120_name);
    return true;
}

//______________________________________________________________________________________________


bool EventSelection_leplep_tight::el_selection(int el_idx) const {
  bool result= (m_leptons_pt->EvalInstance(el_idx)>=15*1000 && fabs(m_leptons_cluster_eta->EvalInstance(el_idx))<=2.47 && fabs(m_leptons_cluster_eta_be2->EvalInstance(el_idx))<=2.47 && m_leptons_id_tight->EvalInstance(el_idx)==1 && ((int)m_leptons_iso_wp->EvalInstance(el_idx) % 100000)/10000 > 0);
    if (!result && debug) {
      std::cout << "e fail " << el_idx << " " <<  m_leptons_pt->EvalInstance(el_idx) << " " << m_leptons_cluster_eta->EvalInstance(el_idx) << " "  <<  m_leptons_id_medium->EvalInstance(el_idx) << " "<< m_leptons_iso_wp->EvalInstance(el_idx) <<std::endl;
    }
    return result;
}

bool EventSelection_leplep_tight::mu_selection(int mu_idx) const {
  bool result= (m_leptons_pt->EvalInstance(mu_idx)>=10*1000 && fabs(m_leptons_eta->EvalInstance(mu_idx))<=2.47 && m_leptons_id_tight->EvalInstance(mu_idx)==1 && ((int)m_leptons_iso_wp->EvalInstance(mu_idx) % 100000)/10000 > 0);
    if (!result && debug) {
      std::cout << "m fail " << mu_idx << " " <<  m_leptons_pt->EvalInstance(mu_idx) << " " << m_leptons_eta->EvalInstance(mu_idx) << " "  <<  m_leptons_id_medium->EvalInstance(mu_idx) << " " << m_leptons_iso_wp->EvalInstance(mu_idx) <<std::endl;
    }
    return result;
}

bool EventSelection_leplep_tight::tau_selection(int tau_idx) const {
    int taus_n_tracks=m_taus_n_tracks->EvalInstance(tau_idx);
    double taus_eta=m_taus_eta->EvalInstance(tau_idx);
    bool result= (m_taus_pt->EvalInstance(tau_idx) >20*1000  && (taus_n_tracks == 1 || taus_n_tracks  == 3) && (taus_eta < 2.5 && (taus_eta<1.37 || taus_eta>1.52)));
    if (!result && debug) {
       std::cout << "tau fail " << tau_idx << " " <<  m_leptons_pt->EvalInstance(tau_idx) << " " << m_leptons_eta->EvalInstance(tau_idx) << " "  <<  m_taus_n_tracks->EvalInstance(tau_idx) << std::endl;
    }
    return result;
}

bool EventSelection_leplep_tight::jet_selection(int jet_idx) const {
    (void) jet_idx;
    return true;
}
























