#include "Htautau/EventSelection_leplep_fake.h"
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

ClassImp(EventSelection_leplep_fake)

//______________________________________________________________________________________________
EventSelection_leplep_fake::EventSelection_leplep_fake(const TString& expression, int systematic, int flag):EventSelection_leplep_base(expression,systematic,flag){
}
//______________________________________________________________________________________________
EventSelection_leplep_fake::~EventSelection_leplep_fake() {
  // default destructor
}


bool EventSelection_leplep_fake::add_lepton_sf_brachnes() {
  EventSelection_leplep_base < EventSelection_leplep_fake >::add_lepton_sf_brachnes();
    mu_ID_effSF_name    = "leptons_NOMINAL_MuEffSF_Reco_QualMedium";
    mu_ISO_effSF_name   = "leptons_NOMINAL_MuEffSF_IsoGradient"; // don't apply
    el_ID_effSF_name    = "leptons_NOMINAL_effSF_offline_LooseAndBLayerLLH_v11";
    el_ISO_effSF_name   = "leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v11_isolGradient"; // don't apply!!
    el_Track_effSF_name = "leptons_NOMINAL_effSF_offline_RecoTrk";


    additional_branches.push_back(mu_ID_effSF_name);
    additional_branches.push_back(mu_ISO_effSF_name);
    additional_branches.push_back(el_ID_effSF_name);
    additional_branches.push_back(el_ISO_effSF_name);
    additional_branches.push_back(el_Track_effSF_name);
    return true;
}


bool EventSelection_leplep_fake::add_trigger_sf_brachnes() {
  EventSelection_leplep_base < EventSelection_leplep_fake >::add_trigger_sf_brachnes();

  tw_mu14_name           = "leptons_NOMINAL_MuEffSF_HLT_mu14_QualMedium_IsoGradient";
  tw_mu20ORmu50_name     = "leptons_NOMINAL_MuEffSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_QualMedium_IsoGradient";
  tw_mu18_name           = "leptons_NOMINAL_MuEffSF_HLT_mu18_QualMedium_IsoGradient";
  tw_mu8noL1_name        = "leptons_NOMINAL_MuEffSF_HLT_mu8noL1_QualMedium_IsoGradient";
  tw_singleE_2015_2016_name   = "leptons_NOMINAL_effSF_SINGLE_E_2015_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_2016_e24_lhtight_nod0_ivarloose_OR_e60_lhmedium_nod0_OR_e140_lhloose_nod0_LooseAndBLayerLLH_d0z0_v11"; // single E trigger for 2015 and 2016
  tw_singleMu_2016_name       = "leptons_NOMINAL_MuEffSF_HLT_mu24_imedium_OR_HLT_mu50_QualMedium_IsoGradient";
  tw_2e12_2015_2e15_2016_name = "leptons_NOMINAL_effSF_DI_E_2015_e12_lhloose_L1EM10VH_2016_e15_lhvloose_nod0_L1EM13VH_LooseAndBLayerLLH_d0z0_v11"; // di E for 2015 and 2016
  tw_2e12_2015_2e17_2016_name = "leptons_NOMINAL_effSF_DI_E_2015_e12_lhloose_L1EM10VH_2016_e17_lhvloose_nod0_LooseAndBLayerLLH_d0z0_v11"; // di E for 2015 and 2016
  tw_mu20_2016_name           = "leptons_NOMINAL_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoGradient";
  tw_e17_2015_e17_2016_name   = "leptons_NOMINAL_effSF_MULTI_L_2015_e17_lhloose_2016_e17_lhloose_nod0_LooseAndBLayerLLH_d0z0_v11"; // multi L for 2015 and 2016


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

//______________________________________________________________________________________________


bool EventSelection_leplep_fake::el_selection(int el_idx) const {
  bool result= (m_leptons_pt->EvalInstance(el_idx)>=15*1000 && fabs(m_leptons_cluster_eta->EvalInstance(el_idx))<=2.47 && fabs(m_leptons_cluster_eta_be2->EvalInstance(el_idx))<=2.47 && m_leptons_id_loose->EvalInstance(el_idx)==1);
    if (!result && debug) {
      std::cout << "e fail " << el_idx << " " <<  m_leptons_pt->EvalInstance(el_idx) << " " << m_leptons_cluster_eta->EvalInstance(el_idx) << " "  <<  m_leptons_id_loose->EvalInstance(el_idx) << " "<< m_leptons_iso_wp->EvalInstance(el_idx) <<std::endl;
    }
    return result;
}

bool EventSelection_leplep_fake::mu_selection(int mu_idx) const {
  bool result= (m_leptons_pt->EvalInstance(mu_idx)>=10*1000 && fabs(m_leptons_eta->EvalInstance(mu_idx))<=2.47 && m_leptons_id_medium->EvalInstance(mu_idx)==1);
    if (!result && debug) {
      std::cout << "m fail " << mu_idx << " " <<  m_leptons_pt->EvalInstance(mu_idx) << " " << m_leptons_eta->EvalInstance(mu_idx) << " "  <<  m_leptons_id_medium->EvalInstance(mu_idx) << " " << m_leptons_iso_wp->EvalInstance(mu_idx) <<std::endl;
    }
    return result;
}

bool EventSelection_leplep_fake::tau_selection(int tau_idx) const {
    int taus_n_tracks=m_taus_n_tracks->EvalInstance(tau_idx);
    double taus_eta=m_taus_eta->EvalInstance(tau_idx);
    bool result= (m_taus_pt->EvalInstance(tau_idx) >20*1000  && (taus_n_tracks == 1 || taus_n_tracks  == 3) && (taus_eta < 2.5 && (taus_eta<1.37 || taus_eta>1.52)));
    if (!result && debug) {
       std::cout << "tau fail " << tau_idx << " " <<  m_leptons_pt->EvalInstance(tau_idx) << " " << m_leptons_eta->EvalInstance(tau_idx) << " "  <<  m_taus_n_tracks->EvalInstance(tau_idx) << std::endl;
    }
    return result;
}

bool EventSelection_leplep_fake::jet_selection(int jet_idx) const {
    (void) jet_idx;
    return true;
}

bool EventSelection_leplep_fake::obtain_lepton_sf() {

  LeptonWeight =1.0; // both loose
  //LeptonWeight_tight = 1.0; // both tight
  //LeptonWeight_lep0_loose = 1.0; // lead lep is loose
  //LeptonWeight_lep1_loose = 1.0; // sublead lep is loose
  //LeptonWeight_lep0_tight = 1.0; // lead lep is tight
  //LeptonWeight_lep1_tight = 1.0; // sublead lep is tight

  if (!m_isData || m_isBoth) {
    if (leptons_selected_idx.size()>=2) {
      for ( auto el_idx: els_selected_idx) {
	//std::cout << "In electron loop" << std::endl;
	if(el_idx == leptons_selected_idx[0] || el_idx == leptons_selected_idx[1]){
	  //std::cout << "-- have selected electron" << std::endl;
	  LeptonWeight *= el_ID_effSF->EvalInstance(el_idx);
	  LeptonWeight *= el_Track_effSF->EvalInstance(el_idx);
	}
	//if(m_leptons_id_tight->EvalInstance(el_idx)== 1 && ((int)m_leptons_iso_wp->EvalInstance(el_idx) % 100000)/10000 > 0){
	//  //std::cout << "-- it is also tight" << std::endl;
	//  LeptonWeight_tight *= el_ID_effSF_tight->EvalInstance(el_idx);
	//  LeptonWeight_tight *= el_ISO_effSF->EvalInstance(el_idx);
	//  LeptonWeight_tight *= el_Track_effSF_tight->EvalInstance(el_idx);
	//}
      }
      for ( auto mu_idx: mus_selected_idx) {
	//std::cout << "In muon loop" << std::endl;
	if(mu_idx == leptons_selected_idx[0] || mu_idx == leptons_selected_idx[1]){
	  LeptonWeight *= mu_ID_effSF->EvalInstance(mu_idx);
	  //std::cout << "-- have selected muon" << std::endl;
	  //if(m_leptons_id_tight->EvalInstance(mu_idx)== 1 && ((int)m_leptons_iso_wp->EvalInstance(mu_idx) % 100000)/10000 > 0){
	  //  //std::cout << "-- it is also tight" <<std::endl;
	  //  LeptonWeight_tight *= mu_ID_effSF->EvalInstance(mu_idx);
	  //  LeptonWeight_tight *= mu_ISO_effSF->EvalInstance(mu_idx);
	  //}
	}
      }
    }
  }

      //std::cout << "now check leptons separately:" << std::endl;

   //if(els_selected_idx[0]==leptons_selected_idx[0]){ // lep0 is electron
   //	//std::cout << "-- have leading electron" << std::endl;
   //	el_idx = els_selected_idx[0];
   //	if(m_leptons_id_tight->EvalInstance(el_idx)== 1 && ((int)m_leptons_iso_wp->EvalInstance(el_idx) % 100000)/10000 > 0){
   //	  //std::cout << "-- it is also tight" <<std::endl;
   //    LeptonWeight_lep0_tight *= el_ID_effSF_tight->EvalInstance(el_idx);
   //    LeptonWeight_lep0_tight *= el_ISO_effSF->EvalInstance(el_idx);
   //    LeptonWeight_lep0_tight *= el_Track_effSF_tight->EvalInstance(el_idx);
   //  }
   //}
   //if(els_selected_idx[0]==leptons_selected_idx[1]){ // lep1 is electron
   //	std::cout << "-- have subleading electron" << std::endl;
   //	el_idx = els_selected_idx[0];
   //  if(m_leptons_id_tight->EvalInstance(el_idx)== 1 && ((int)m_leptons_iso_wp->EvalInstance(el_idx) % 100000)/10000 > 0){
   //	  std::cout << "-- it is also tight" <<std::endl;
   //    LeptonWeight_lep1_tight *= el_ID_effSF_tight->EvalInstance(el_idx);
   //    LeptonWeight_lep1_tight *= el_ISO_effSF->EvalInstance(el_idx);
   //    LeptonWeight_lep1_tight *= el_Track_effSF_tight->EvalInstance(el_idx);
   //  }
   //}
   //if(mus_selected_idx[0]==leptons_selected_idx[0]){ // lep0 is muon
   //	std::cout << "-- have leading muon" << std::endl;
   //	mu_idx = mus_selected_idx[0];
   //  if(m_leptons_id_tight->EvalInstance(mu_idx)== 1 && ((int)m_leptons_iso_wp->EvalInstance(mu_idx) % 100000)/10000 > 0){
   //	  std::cout << "-- it is also tight" <<std::endl;
   //	  LeptonWeight_lep0_tight *= mu_ID_effSF->EvalInstance(mu_idx);
   //	  LeptonWeight_lep0_tight *= mu_ISO_effSF->EvalInstance(mu_idx);
   //  }
   //}
   //if(mus_selected_idx[0]==leptons_selected_idx[1]){ // lep1 is muon
   //	  std::cout << "-- have subleading muon" << std::endl;
   //	mu_idx = mus_selected_idx[0];
   //  if(m_leptons_id_tight->EvalInstance(mu_idx)== 1 && ((int)m_leptons_iso_wp->EvalInstance(mu_idx) % 100000)/10000 > 0){
   //	  std::cout << "-- it is also tight" <<std::endl;
   //    LeptonWeight_lep1_tight *= mu_ID_effSF->EvalInstance(mu_idx);
   //    LeptonWeight_lep1_tight *= mu_ISO_effSF->EvalInstance(mu_idx);
   //  }
   //}
   //
  //}

  //std::cout << "Lepton Weight: " << LeptonWeight << std::endl;
  //std::cout << "Lepton Weight_tight" << LeptonWeight_tight << std::endl;
  //std::cout << "Lepton Weight_lep0_tight" << LeptonWeight_lep0_tight << std::endl;
  //std::cout << "Lepton Weight_lep1_tight" << LeptonWeight_lep1_tight << std::endl;
  //std::cout << "Lepton Weight_lep0_tight*Lepton Weight_lep1_tight" << LeptonWeight_lep0_tight*LeptonWeight_lep1_tight << std::endl;

  return true;
}

bool EventSelection_leplep_fake::calculate_variables() {
  EventSelection_leplep_base < EventSelection_leplep_fake >::calculate_variables();

  for(int i=0; i<leptons_selected_idx.size(); i++){
    if(m_leptons_id_medium->EvalInstance(leptons_selected_idx[i])== 1 && ((int)m_leptons_iso_wp->EvalInstance(leptons_selected_idx[i]) % 100000)/10000 > 0){
      leptons_is_selected_tight[i]=true;
    }
  }

  return true;
}

bool EventSelection_leplep_fake::obtain_trigger_sf() {
  EventSelection_leplep_base < EventSelection_leplep_fake >::obtain_trigger_sf();

  // 2015 dataset
  if(m_flag==15){
    bool singleE  =(HLT_e24_lhmedium_L1EM20VH->EvalInstance() || HLT_e60_lhmedium->EvalInstance() || HLT_e120_lhloose->EvalInstance());
    bool singleMu =(HLT_mu20_iloose_L1MU15->EvalInstance() || HLT_mu50->EvalInstance());
    bool diE      = HLT_2e12_lhloose_L12EM10VH->EvalInstance();
    bool diMu     = HLT_mu18_mu8noL1->EvalInstance();
    bool eMu      = HLT_e17_loose_mu14->EvalInstance();
    if (mus_selected_idx.size()==2 && els_selected_idx.size()==0){ //mm
      if(mus_selected_idx[0] == leptons_selected_idx[0] && mus_selected_idx[1] == leptons_selected_idx[1]){
	if (lep_0_pt >= 22*1000. && singleMu==1 && (leptons_HLT_mu20_iloose_L1MU15->EvalInstance(lep_idx0)==1 || leptons_HLT_mu50->EvalInstance(lep_idx0)==1)){
	  specialisTriggered_data = true;
	  specialisTriggered_mc = true;
	  specialTriggerType = 10;
	  if (!m_isData || m_isBoth) specialTriggerWeight *= tw_mu20ORmu50->EvalInstance(lep_idx0);
	  if (debug) {
	    std::cout << "mm triggered data/mc tw_mu20ORmu50 weight " << specialTriggerWeight << std::endl;
	  }
	}
	if (lep_0_pt>=20*1000. && lep_1_pt/1000 >=10. && diMu==1 && leptons_HLT_mu18_mu8noL1->EvalInstance(lep_idx0)==1 && leptons_HLT_mu18_mu8noL1->EvalInstance(lep_idx1)==1){
	  specialisTriggered_data = true;
	  specialisTriggered_mc = true;
	  specialTriggerType = 12;
	  if (!m_isData || m_isBoth) specialTriggerWeight *= tw_mu18->EvalInstance(lep_idx0);
	  if (!m_isData || m_isBoth) specialTriggerWeight *= tw_mu8noL1->EvalInstance(lep_idx1);
	  if (debug) {
	    std::cout << "mm triggered data/mc tw_mu8noL1 tw_mu18 weight " << specialTriggerWeight << std::endl;
	  }
	}
      }
    }
    else if (els_selected_idx.size()==2 && mus_selected_idx.size()==0){ // ee
      if (lep_0_pt >= 26*1000 && singleE==1 && (leptons_HLT_e24_lhmedium_L1EM20VH->EvalInstance(lep_idx0)==1 || leptons_HLT_e60_lhmedium->EvalInstance(lep_idx0)==1 || leptons_HLT_e120_lhloose->EvalInstance(lep_idx0)==1)){
	specialisTriggered_mc = true;
	specialisTriggered_data = true;
	specialTriggerType = 20;
	if (!m_isData || m_isBoth) specialTriggerWeight *= tw_singleE_2015_2016->EvalInstance(lep_idx0);
	if (debug) {
	  std::cout << "mm triggered data/mc tw_e24ORe60ORe120 weight " << specialTriggerWeight << std::endl;
	}
      }
      if (lep_0_pt >= 15000 && lep_1_pt >= 15000 && diE==1 && leptons_HLT_2e12_lhloose_L12EM10VH->EvalInstance(lep_idx0)==1 && leptons_HLT_2e12_lhloose_L12EM10VH->EvalInstance(lep_idx1)==1){
	specialisTriggered_mc = true;
	specialisTriggered_data = true;
	specialTriggerType = 22;
	if (!m_isData || m_isBoth) specialTriggerWeight *= tw_2e12_2015_2e15_2016->EvalInstance(lep_idx0);
	if (!m_isData || m_isBoth) specialTriggerWeight *= tw_2e12_2015_2e15_2016->EvalInstance(lep_idx1);
	if (debug) {
	  std::cout << "mm triggered data/mc tw_2e12 weight " << specialTriggerWeight << std::endl;
	}
      }
    }
    else if (leptons_selected_idx.size() ==2 && mus_selected_idx[0]==leptons_selected_idx[0]){ //me
      if (lep_0_pt >= 22 * 1000 && lep_1_pt < 26 * 1000 && singleMu==1 && (leptons_HLT_mu20_iloose_L1MU15->EvalInstance(lep_idx0)==1 || leptons_HLT_mu50->EvalInstance(lep_idx0)==1)){
	specialisTriggered_mc = true;
	specialisTriggered_data = true;
	specialTriggerType = 10;
	if (!m_isData || m_isBoth) specialTriggerWeight *= tw_mu20ORmu50->EvalInstance(lep_idx0);
	if (debug) {
	  std::cout << "mm triggered data/mc tw_mu20ORmu50 weight " << specialTriggerWeight << std::endl;
	}
      }
      if (lep_1_pt >= 26 * 1000 && singleE == 1 && (leptons_HLT_e24_lhmedium_L1EM20VH->EvalInstance(lep_idx1)==1 || leptons_HLT_e60_lhmedium->EvalInstance(lep_idx1)==1 || leptons_HLT_e120_lhloose->EvalInstance(lep_idx1)==1)) {
	specialisTriggered_mc = true;
	specialisTriggered_data = true;
	specialTriggerType = 21;
	if (!m_isData || m_isBoth) specialTriggerWeight *= tw_singleE_2015_2016->EvalInstance(lep_idx1);
	if (debug) {
	  std::cout << "mm triggered data/mc tw_e24ORe60ORe120 weight " << specialTriggerWeight << std::endl;
	}
      }
      if (lep_1_pt >= 19 * 1000 && lep_0_pt >= 16 * 1000 && eMu==1 && leptons_HLT_e17_loose_mu14->EvalInstance(lep_idx1)==1){
	specialisTriggered_mc = true;
	specialisTriggered_data = true;
	specialTriggerType = 211;
	if (!m_isData || m_isBoth) specialTriggerWeight *= tw_e17_2015_e17_2016->EvalInstance(lep_idx1);
	if (!m_isData || m_isBoth) specialTriggerWeight *= tw_mu14->EvalInstance(lep_idx0);
	if (debug) {
	  std::cout << "mm triggereddata/mc tw_e17 tw_mu14 weight " << specialTriggerWeight << std::endl;
	}
      }
    }
    else if (leptons_selected_idx.size() ==2 && els_selected_idx[0]==leptons_selected_idx[0]) { //em
      if (lep_0_pt >= 26 * 1000 && singleE==1 && (leptons_HLT_e24_lhmedium_L1EM20VH->EvalInstance(lep_idx0)==1 || leptons_HLT_e60_lhmedium->EvalInstance(lep_idx0)==1 || leptons_HLT_e120_lhloose->EvalInstance(lep_idx0)==1)){
	specialisTriggered_mc = true;
	specialisTriggered_data = true;
	specialTriggerType = 20;
	if (!m_isData || m_isBoth) specialTriggerWeight *= tw_singleE_2015_2016->EvalInstance(lep_idx0);
	if (debug) {
	  std::cout << "mm triggered data/mc tw_e24ORe60ORe120 weight " << specialTriggerWeight << std::endl;
	}
      }
      if (lep_1_pt >=22 * 1000 && singleMu==1 && (leptons_HLT_mu20_iloose_L1MU15->EvalInstance(lep_idx1)==1 || leptons_HLT_mu50->EvalInstance(lep_idx1)==1)){
	specialisTriggered_mc = true;
	specialisTriggered_data = true;
	specialTriggerType = 11;
	if (!m_isData || m_isBoth) specialTriggerWeight *= tw_mu20ORmu50->EvalInstance(lep_idx1);
	if (debug) {
	  std::cout << "mm triggered data/mc tw_mu20ORmu50 weight " << specialTriggerWeight << std::endl;
	}
      }
      if (lep_0_pt >= 19 * 1000 && lep_1_pt >= 16 * 1000 && eMu==1 && leptons_HLT_e17_loose_mu14->EvalInstance(lep_idx0)==1){
	specialisTriggered_mc = true;
	specialisTriggered_data = true;
	specialTriggerType = 211;
	if (!m_isData || m_isBoth) specialTriggerWeight *= tw_e17_2015_e17_2016->EvalInstance(lep_idx0);
	if (!m_isData || m_isBoth) specialTriggerWeight *= tw_mu14->EvalInstance(lep_idx1);
	if (debug) {
	  std::cout << "mm triggered data/mc tw_e17 tw_mu14 weight " << specialTriggerWeight << std::endl;
	}
      }
    }
  } //end 2015 dataset

  return true;

}
