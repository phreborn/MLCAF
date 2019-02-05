#ifndef __EventSelection_leplep_basis__
#define __EventSelection_leplep_basis__
#include "QFramework/TQAlgorithm.h"
#include "QFramework/TQSample.h"

#include "TLorentzVector.h"
#include "TTreeFormula.h"
#include "Htautau/EventSelection.h"
#include <vector>

class EventSelection_leplep_basis : public EventSelection {
public:
//  virtual int getJetIdx(int nr);
//  virtual int getElIdx(int nr);
//  virtual int getMuIdx(int nr);
//  virtual int getLeptonIdx(int nr);
//  virtual int getTauIdx(int nr);
//  virtual int getNJet();
//  virtual int getNEl();
//  virtual int getNMu();
//  virtual int getNLepton();
//  virtual int getNTau();
//  virtual double getTriggerWeight();
//  virtual double getScaleFactor();
//  virtual bool getTriggered_MC();
//  virtual bool getTriggered_data();
  virtual bool finalize();
protected:
  int lep_idx0=-1;
  int lep_idx1=-1;
  double lep_0_pt,lep_1_pt;


  TTreeFormula *m_leptons_cluster_eta;
  TTreeFormula *m_leptons_cluster_eta_be2;
  TTreeFormula *m_leptons_iso_wp;
  TTreeFormula *m_leptons_id_loose;
  TTreeFormula *m_leptons_id_medium;
  TTreeFormula *m_leptons_id_tight;
  TTreeFormula *m_leptons_trk_d0;
  TTreeFormula *m_leptons_trk_d0_sig;
  TTreeFormula *m_taus_n_tracks;

  //TTreeFormula *leptons_HLT_e24_lhmedium_L1EM18VH;
  TTreeFormula *leptons_HLT_e60_lhmedium;
  TTreeFormula *leptons_HLT_e120_lhloose;
  TTreeFormula *leptons_HLT_e24_lhmedium_L1EM20VH;
  TTreeFormula *leptons_HLT_mu20_iloose_L1MU15;
  TTreeFormula *leptons_HLT_mu50;
  TTreeFormula *HLT_e24_lhmedium_L1EM20VH;
  //TTreeFormula *HLT_e24_lhmedium_L1EM18VH;
  TTreeFormula *HLT_e60_lhmedium;
  TTreeFormula *HLT_e120_lhloose;
  TTreeFormula *HLT_mu20_iloose_L1MU15;
  TTreeFormula *HLT_mu50;
  TTreeFormula *leptons_HLT_e17_loose_mu14;
  TTreeFormula *leptons_HLT_mu18_mu8noL1;
  TTreeFormula *leptons_HLT_2e12_lhloose_L12EM10VH;
  TTreeFormula *HLT_e17_loose_mu14;
  TTreeFormula *HLT_mu18_mu8noL1;
  TTreeFormula *HLT_2e12_lhloose_L12EM10VH;

  TTreeFormula* HLT_e24_lhtight_nod0_ivarloose;
  TTreeFormula* HLT_2e15_lhvloose_nod0_L12EM13VH;
  TTreeFormula* HLT_2e17_lhvloose_nod0;
  TTreeFormula* HLT_e60_lhmedium_nod0;
  TTreeFormula* HLT_e140_lhloose_nod0;
  TTreeFormula* HLT_e24_lhmedium_nod0_L1EM20VH;
  TTreeFormula* HLT_mu24_ivarmedium;
  TTreeFormula* HLT_mu20_mu8noL1;
  TTreeFormula* HLT_e17_lhloose_nod0_mu14;
  TTreeFormula* leptons_HLT_e24_lhtight_nod0_ivarloose;
  TTreeFormula* leptons_HLT_e60_lhmedium_nod0;
  TTreeFormula* leptons_HLT_e140_lhloose_nod0;
  TTreeFormula* leptons_HLT_e24_lhmedium_nod0_L1EM20VH;
  TTreeFormula* leptons_HLT_mu24_ivarmedium;
  TTreeFormula* leptons_HLT_mu20_mu8noL1;
  TTreeFormula* leptons_HLT_e17_lhloose_nod0_mu14;
  TTreeFormula* leptons_HLT_2e17_lhvloose_nod0;
  TTreeFormula* leptons_HLT_2e15_lhvloose_nod0_L12EM13VH;

  TTreeFormula* mu_ID_effSF;
  TTreeFormula* mu_ISO_effSF;

  TTreeFormula* el_ID_effSF;
  TTreeFormula* el_ISO_effSF;
  TTreeFormula* el_Track_effSF;

  TTreeFormula* jets_JVT_effSF;
  TTreeFormula* jets_MVX_effSF;
  TTreeFormula* jets_MVX_ineffSF;

  TTreeFormula* tw_mu14;
  TTreeFormula* tw_e17;
  TTreeFormula* tw_2e12;
  TTreeFormula* tw_mu20ORmu50;
  TTreeFormula* tw_mu18;
  TTreeFormula* tw_mu8noL1;
  TTreeFormula* tw_e24ORe60ORe120;
  TTreeFormula* tw_singleE_2015_2016;
  TTreeFormula* tw_singleMu_2016;
  TTreeFormula* tw_2e12_2015_2e15_2016;
  TTreeFormula* tw_2e12_2015_2e17_2016;
  TTreeFormula* tw_mu20_2016;
  TTreeFormula* tw_e17_2015_e17_2016;

  TString mu_ID_effSF_name;
  TString mu_ISO_effSF_name;

  TString el_ID_effSF_name;
  TString el_ISO_effSF_name;
  TString el_Track_effSF_name;

  TString jets_JVT_effSF_name;
  TString jets_effSF_MVX_name;
  TString jets_ineffSF_MVX_name;

  TString tw_mu14_name;
  TString tw_e17_name;
  TString tw_2e12_name;
  TString tw_mu20ORmu50_name;
  TString tw_mu18_name;
  TString tw_mu8noL1_name;
  TString tw_e24ORe60ORe120_name;
  TString tw_singleE_2015_2016_name;
  TString tw_singleMu_2016_name;
  TString tw_2e12_2015_2e15_2016_name;
  TString tw_2e12_2015_2e17_2016_name;
  TString tw_mu20_2016_name;
  TString tw_e17_2015_e17_2016_name;

//  static std::vector < int > jets_selected_idx_leplep_basis;
//  static std::vector < int > leptons_selected_idx_leplep_basis;
//  static std::vector < int > els_selected_idx_leplep_basis;
//  static std::vector < int > mus_selected_idx_leplep_basis;
//  static std::vector < int > taus_selected_idx_leplep_basis;
//
//  static double TriggerWeight_leplep_basis;
//  static double LeptonWeight_leplep_basis;
//  static bool isTriggered_mc_leplep_basis;
//  static bool isTriggered_data_leplep_basis;

  virtual bool add_particle_branches();
  virtual bool add_trigger_branches();
  virtual bool add_trigger_sf_brachnes();
  virtual bool add_lepton_sf_brachnes();
  virtual bool add_jet_sf_brachnes();
  virtual bool connect_particle_branches();
  virtual bool connect_trigger_branches();
  virtual bool connect_trigger_sf_brachnes();
  virtual bool connect_lepton_sf_brachnes();
  virtual bool connect_jet_sf_brachnes();

  virtual bool initialise_branches();

  virtual bool selection_objects();

  virtual bool el_selection(int el_idx) const;
  virtual bool mu_selection(int mu_idx) const;
  virtual bool tau_selection(int tau_idx) const;
  virtual bool jet_selection(int jet_idx) const;

  std::vector < bool > tau_ov_els_selected;
  std::vector < bool > all_mus_selected;

  virtual void removeoverlap();

  virtual bool obtain_trigger_sf();
  virtual bool obtain_lepton_sf();
  virtual bool obtain_jet_sf();

  virtual bool calculate_variables();
  virtual bool calculate_lepton_variables();
  virtual bool calculate_VBF_cat();
  virtual bool calculate_VBF_cat_ZttCR();
  virtual bool calculate_boosted_cat();
  virtual bool calculate_boosted_cat_ZttCR();

//  virtual bool finalise_selection();

public:
  EventSelection_leplep_basis(const TString& expression="", int systematic=-1, int flag =-1);
  virtual ~EventSelection_leplep_basis();
  ClassDef(EventSelection_leplep_basis, 1);


};

template < class subbase >
class EventSelection_leplep_base : public EventSelection_leplep_basis {
    public:
        EventSelection_leplep_base(const TString& expression, int systematic, int flag):EventSelection_leplep_basis(expression,systematic,flag){};
    protected:
        static std::vector < int > jets_selected_idx_leplep_base;
        static std::vector < TLorentzVector > jets_selected_vector_leplep_base;
        static std::vector < int > leptons_selected_idx_leplep_base;
        static std::vector < TLorentzVector > leptons_selected_vector_leplep_base;
        static std::vector < int > els_selected_idx_leplep_base;
        static std::vector < int > mus_selected_idx_leplep_base;
        static std::vector < int > taus_selected_idx_leplep_base;
        static std::vector < bool > leptons_is_selected_tight_leplep_base;
        static double TriggerWeight_leplep_base;
        static double LeptonWeight_leplep_base;
        static double LeptonWeight_tight_leplep_base;
        static double LeptonWeight_lep0_tight_leplep_base;
        static double LeptonWeight_lep1_tight_leplep_base;
        static double JVTweight_leplep_base;
        static double MVXweight_leplep_base;
        static bool isBtagged_leplep_base;
        static bool isTriggered_mc_leplep_base;
        static bool isTriggered_data_leplep_base;
        static int TriggerType_leplep_base;
        static std::vector < TLorentzVector > jets_leplep_base;
        static std::vector < TLorentzVector > leptons_leplep_base;
        static std::vector < TLorentzVector > els_leplep_base;
        static std::vector < TLorentzVector > mus_leplep_base;
        static std::vector < TLorentzVector > taus_leplep_base;
        static double m_sphericity_leplep_base;
        static std::vector < TLorentzVector > m_hpto_vectors_leplep_base;

	static bool specialisTriggered_mc_leplep_base;
        static bool specialisTriggered_data_leplep_base;
        static int specialTriggerType_leplep_base;
	static double specialTriggerWeight_leplep_base;

        static std::vector < double > m_lep_pt_leplep_base;
        static std::vector < double > m_lep_eta_leplep_base;
        static std::vector < double > m_lepjet_dRmin_leplep_base;
        static double m_leplep_mvis_leplep_base;
        static double m_leplep_mt_leplep_base;
        static double m_leplep_sign_leplep_base;
        static double m_lep_x0_leplep_base;
        static double m_lep_x1_leplep_base;
        static double m_lep_coll_m_leplep_base;
        static double m_leplep_pt_ll_leplep_base;
        static double m_leplep_pt_tautau_leplep_base;
        static double m_leplep_coll_pt_leplep_base;
        static double m_leplep_mmc_maxw_leplep_base;
        static double m_leplep_mmc_mlm_leplep_base;
        static double m_leplep_mmc_mlnu3p_leplep_base;
        static double m_leplep_sumpt_leplep_base;
        static double m_leplep_dphi_leplep_base;
        static double m_leplep_dphil0m_leplep_base;
        static double m_leplep_dphil1m_leplep_base;
        static double m_leplep_detall_leplep_base;
        static double m_leplep_mll_leplep_base;
        static double m_leplep_mcollasym_leplep_base;

        static double m_jet_mjj_leplep_base;
        static double m_jet0_pt_leplep_base;
        static double m_jet1_pt_leplep_base;
        static double m_jet_deta_leplep_base;
        static double m_jet_centrality_leplep_base;
        static double m_hpto_leplep_base;
        static double m_hpto_etx_leplep_base;
        static double m_hpto_ety_leplep_base;
        static double m_hpto_phi_leplep_base;
        static bool m_lep0_ismatched_leplep_base;
        static bool m_lep1_ismatched_leplep_base;

        static double m_hpto_x0_leplep_base;
        static double m_hpto_x1_leplep_base;
        static double m_hpto_coll_m_leplep_base;
        static double m_higgs_pt_leplep_base;

        static int m_leplep_nJetPt25_leplep_base;
        static int m_leplep_nJetEta2p4Pt25_leplep_base;
        static double m_leplep_mtLep0_leplep_base;
        static double m_leplep_mtLep1_leplep_base;

        static double m_leplep_pt_lep0met_leplep_base;
        static double m_leplep_pt_lep1met_leplep_base;

        static double m_leplep_dphilep0met_leplep_base;
        static double m_leplep_dphilep1met_leplep_base;

        static double m_leplep_d0_l0_leplep_base;
        static double m_leplep_d0_l1_leplep_base;
        static double m_leplep_d0sig_l0_leplep_base;
        static double m_leplep_d0sig_l1_leplep_base;

        static bool m_lepton_centrality_leplep_base;
        static bool m_central_jet_veto_leplep_base;

        static bool m_VBF_cat_leplep_base;
        static bool m_VBF_cat_ZttCR_leplep_base;
        static bool m_boosted_cat_leplep_base;
        static bool m_boosted_cat_ZttCR_leplep_base;

	static long current_run_number_leplep_base;

        bool finalise_selection(){
            jets_selected_idx_leplep_base         = jets_selected_idx;
            leptons_selected_idx_leplep_base      = leptons_selected_idx;
            leptons_selected_vector_leplep_base   = leptons_selected_vector;
            els_selected_idx_leplep_base          = els_selected_idx;
            mus_selected_idx_leplep_base          = mus_selected_idx;
            taus_selected_idx_leplep_base         = taus_selected_idx;

            TriggerWeight_leplep_base             = TriggerWeight;
            LeptonWeight_leplep_base              = LeptonWeight;
            LeptonWeight_tight_leplep_base        = LeptonWeight_tight;
            LeptonWeight_lep0_tight_leplep_base   = LeptonWeight_lep0_tight;
            LeptonWeight_lep1_tight_leplep_base   = LeptonWeight_lep1_tight;
            JVTweight_leplep_base                 = JVTweight;
            MVXweight_leplep_base                 = MVXweight;
            isBtagged_leplep_base                 = isBtagged;
            isTriggered_mc_leplep_base            = isTriggered_mc;
            isTriggered_data_leplep_base          = isTriggered_data;
            TriggerType_leplep_base               = TriggerType;

            specialTriggerWeight_leplep_base      = specialTriggerWeight;
            specialisTriggered_mc_leplep_base     = specialisTriggered_mc;
            specialisTriggered_data_leplep_base   = specialisTriggered_data;
            specialTriggerType_leplep_base        = specialTriggerType;

            jets_leplep_base                      = jets;
            leptons_leplep_base                   = leptons;
            els_leplep_base                       = els;
            mus_leplep_base                       = mus;
            taus_leplep_base                      = taus;


            m_sphericity_leplep_base              = m_sphericity;
            m_hpto_vectors_leplep_base            = m_hpto_vectors;
            m_leplep_mvis_leplep_base             = m_leplep_mvis;
            m_leplep_mt_leplep_base               = m_leplep_mt;
            m_leplep_sign_leplep_base             = m_leplep_sign;
            m_lep_x0_leplep_base                  = m_lep_x0;
            m_lep_x1_leplep_base                  = m_lep_x1;
            m_lep_coll_m_leplep_base              = m_lep_coll_m;
            m_leplep_pt_ll_leplep_base            = m_leplep_pt_ll;
            m_leplep_pt_tautau_leplep_base        = m_leplep_pt_tautau;
            m_leplep_coll_pt_leplep_base          = m_leplep_coll_pt;
            m_leplep_mmc_maxw_leplep_base         = m_leplep_mmc_maxw;
            m_leplep_mmc_mlm_leplep_base          = m_leplep_mmc_mlm;
            m_leplep_mmc_mlnu3p_leplep_base       = m_leplep_mmc_mlnu3p;
            m_leplep_sumpt_leplep_base            = m_leplep_sumpt;
            m_leplep_dphi_leplep_base             = m_leplep_dphi;
            m_leplep_dphil0m_leplep_base          = m_leplep_dphil0m;
            m_leplep_dphil1m_leplep_base          = m_leplep_dphil1m;
            m_leplep_detall_leplep_base           = m_leplep_detall;
            m_leplep_mll_leplep_base              = m_leplep_mll;
            m_leplep_mcollasym_leplep_base        = m_leplep_mcollasym;
            m_jet_mjj_leplep_base                 = m_jet_mjj;
            m_jet0_pt_leplep_base                 = m_jet0_pt;
            m_jet1_pt_leplep_base                 = m_jet1_pt;
            m_jet_deta_leplep_base                = m_jet_deta;
            m_jet_centrality_leplep_base          = m_jet_centrality;
            m_hpto_leplep_base                    = m_hpto;
            m_hpto_etx_leplep_base                = m_hpto_etx;
            m_hpto_ety_leplep_base                = m_hpto_ety;
            m_hpto_phi_leplep_base                = m_hpto_phi;
            m_hpto_x0_leplep_base                 = m_hpto_x0;
            m_hpto_x1_leplep_base                 = m_hpto_x1;
            m_hpto_coll_m_leplep_base             = m_hpto_coll_m;
            m_higgs_pt_leplep_base                = m_higgs_pt;
            m_lepton_centrality_leplep_base       = m_lepton_centrality;
            m_central_jet_veto_leplep_base        = m_central_jet_veto;
            m_VBF_cat_leplep_base                 = m_VBF_cat;
            m_VBF_cat_ZttCR_leplep_base                 = m_VBF_cat_ZttCR;
            m_boosted_cat_leplep_base             = m_boosted_cat;
            m_boosted_cat_ZttCR_leplep_base       = m_boosted_cat_ZttCR;
            m_lep0_ismatched_leplep_base          = m_lep0_ismatched;
            m_lep1_ismatched_leplep_base          = m_lep1_ismatched;
            leptons_is_selected_tight_leplep_base = leptons_is_selected_tight;
            m_lep_pt_leplep_base                  = m_lep_pt;
            m_lep_eta_leplep_base                 = m_lep_eta;
            m_lepjet_dRmin_leplep_base            = m_lepjet_dRmin;

            m_leplep_mtLep0_leplep_base           = m_leplep_mtLep0;
            m_leplep_mtLep1_leplep_base           = m_leplep_mtLep1;
            m_leplep_nJetPt25_leplep_base         = m_leplep_nJetPt25;
            m_leplep_nJetEta2p4Pt25_leplep_base   = m_leplep_nJetEta2p4Pt25;
            m_leplep_dphilep0met_leplep_base      = m_leplep_dphilep0met;
            m_leplep_dphilep1met_leplep_base      = m_leplep_dphilep1met;

            m_leplep_pt_lep0met_leplep_base       = m_leplep_pt_lep0met;
            m_leplep_pt_lep1met_leplep_base       = m_leplep_pt_lep1met;

            m_leplep_d0_l0_leplep_base    = m_leplep_d0_l0;
            m_leplep_d0_l1_leplep_base    = m_leplep_d0_l1;

            m_leplep_d0sig_l0_leplep_base = m_leplep_d0sig_l0;
            m_leplep_d0sig_l1_leplep_base = m_leplep_d0sig_l1;

	    current_run_number_leplep_base = current_run_number;

            return true;
        }
    public:
        int getJetIdx(int nr) {
            if (nr <0 || nr >= (int) jets_selected_idx_leplep_base.size()) return -1;
            else return jets_selected_idx_leplep_base[nr];
        }
        int getElIdx(int nr) {
            if (nr <0 || nr >= (int) els_selected_idx_leplep_base.size()) return -1;
            else return els_selected_idx_leplep_base[nr];
        }
        int getMuIdx(int nr) {
            if (nr <0 || nr >= (int) mus_selected_idx_leplep_base.size()) return -1;
            else return mus_selected_idx_leplep_base[nr];
        }
        int getLeptonIdx(int nr) {
	  //if(leptons_selected_idx_leplep_base.size()>1){
	  //  if(leptons_selected_idx_leplep_base[0]!=0 || leptons_selected_idx_leplep_base[1]!=1){
	  //    //std::cout << "In getleptonIdx with " << current_run_number << " " << current_event_number<< std::endl;
	  //  std::cout << "ACHTUNG:: In selected lepton idx:" << leptons_selected_idx_leplep_base[0] << " " << leptons_selected_idx_leplep_base[1] << std::endl;
	  //  }
	  //}
            if (nr <0 || nr >= (int) leptons_selected_idx_leplep_base.size()) return -1;
            else return leptons_selected_idx_leplep_base[nr];
        }
        int getTauIdx(int nr) {
            if (nr <0 || nr >= (int) taus_selected_idx_leplep_base.size()) return -1;
            else return taus_selected_idx_leplep_base[nr];
        }
        int getNJet() {
            return jets_selected_idx_leplep_base.size();
        }
        int getNEl() {
            return els_selected_idx_leplep_base.size();
        }
        int getNMu() {
            return mus_selected_idx_leplep_base.size();
        }
        int getNLepton() {
            return leptons_selected_idx_leplep_base.size();
        }
        int getNTau() {
            return taus_selected_idx_leplep_base.size();
        }
        bool getLepTight(int nr) {
            if (nr <0 || nr >= (int) leptons_is_selected_tight_leplep_base.size()) return 0;
            else return leptons_is_selected_tight_leplep_base[nr];
        }
        double getTriggerWeight(){
            return TriggerWeight_leplep_base;
        }
	double getSpecialTriggerWeight(){
	  return specialTriggerWeight_leplep_base;
	}
        double getScaleFactor(){
            return LeptonWeight_leplep_base;
        }
        double getJVTWeight(){
            return JVTweight_leplep_base;
        }
        double getMVXWeight(){
            return MVXweight_leplep_base;
        }
        bool getBtagged(){
            return isBtagged_leplep_base;
        }
        bool getTriggered_MC(){

            return isTriggered_mc_leplep_base;
        }
        bool getTriggered_data(){
            return isTriggered_data_leplep_base;
        }
        int getTriggerType(){
            return TriggerType_leplep_base;
        }
	bool getSpecialTriggered_MC(){
	  return specialisTriggered_mc_leplep_base;
        }
        bool getSpecialTriggered_data(){
	  return specialisTriggered_data_leplep_base;
        }
	int getSpecialTriggerType(){
	  return specialTriggerType_leplep_base;
	}
        std::vector < TLorentzVector > getJets(){
            return jets_leplep_base;
        }
        std::vector < TLorentzVector > getLeptons(){
            return leptons_leplep_base;
        }
        std::vector < TLorentzVector > getEls(){
            return els_leplep_base;
        }
        std::vector < TLorentzVector > getMus(){
            return mus_leplep_base;
        }
        std::vector < TLorentzVector > getTaus(){
            return taus_leplep_base;
        }
        double getSphericity() {
            return m_sphericity_leplep_base;
        }
        std::vector < TLorentzVector > getHPTO_vectors() {
            return m_hpto_vectors_leplep_base;
        }
        double getDRminLepJet(int nr){
            if (nr <0 || nr >= (int) m_lepjet_dRmin_leplep_base.size()) return -1;
            else return m_lepjet_dRmin_leplep_base[nr];
        }
        double getMvis(){
            return m_leplep_mvis_leplep_base;
        }
        double getMt(){
            return m_leplep_mt_leplep_base;
        }
        double getMMC_maxw(){
            return m_leplep_mmc_maxw_leplep_base;
        }
        double getMMC_mlm(){
            return m_leplep_mmc_mlm_leplep_base;
        }
        double getMMC_mlnu3p(){
            return m_leplep_mmc_mlnu3p_leplep_base;
        }
        double getLepLepSign(){
            return m_leplep_sign_leplep_base;
        }
        double getLepX0CollApp(){
            return m_lep_x0_leplep_base;
        }
        double getLepX1CollApp(){
            return m_lep_x1_leplep_base;
        }
        double getLepMCollApp(){
            return m_lep_coll_m_leplep_base;
        }
        double getPtLL() {
            return m_leplep_pt_ll_leplep_base;
        }
        double getPtTauTau() {
            return m_leplep_pt_tautau_leplep_base;
        }
        double getPtCollPt() {
            return m_leplep_coll_pt_leplep_base;
        }
        double getSumPtLep(){
            return m_leplep_sumpt_leplep_base;
        }
        double getDphiLL(){
            return m_leplep_dphi_leplep_base;
        }
        double getMCollASym(){
            return m_leplep_mcollasym_leplep_base;
        }
        double getDphiL0MET(){
            return m_leplep_dphil0m_leplep_base;
        }
        double getDphiL1MET(){
            return m_leplep_dphil1m_leplep_base;
        }
        double getDEtaLL(){
            return m_leplep_detall_leplep_base;
        }
        double getMLL(){
            return m_leplep_mll_leplep_base;
        }
        double getLepPt(int nr){
            if (nr <0 || nr >= (int) m_lep_pt_leplep_base.size()) return -1;
            else return m_lep_pt_leplep_base[nr];
        }
        double getLepEta(int nr) {
            if (nr <0 || nr >= (int) m_lep_eta_leplep_base.size()) return -9999.;
            else return m_lep_eta_leplep_base[nr];
        }
        bool getLep0Match(){
            return m_lep0_ismatched_leplep_base;
        }
        bool getLep1Match(){
            return m_lep1_ismatched_leplep_base;
        }
        double getJet_mjj(){
            return m_jet_mjj_leplep_base;
        }
        double getJet0Pt(){
            return m_jet0_pt_leplep_base;
        }
        double getJet1Pt(){
            return m_jet1_pt_leplep_base;
        }
        double getJet_deta(){
            return m_jet_deta_leplep_base;
        }
        double getJet_centrality(){
            return m_jet_centrality_leplep_base;
        }
        double getHPTO(){
            return m_hpto_leplep_base;
        }
        double getHPTO_etx(){
            return m_hpto_etx_leplep_base;
        }
        double getHPTO_ety(){
            return m_hpto_ety_leplep_base;
        }
        double getHPTO_phi(){
            return m_hpto_phi_leplep_base;
        }

        double getHPTO_x0() {
            return m_hpto_x0_leplep_base;
        }
        double getHPTO_x1() {
            return m_hpto_x1_leplep_base;
        }
        double gethpto_coll_m() {
            return m_hpto_coll_m_leplep_base;
        }
        double getHiggs_pt() {
            return m_higgs_pt_leplep_base;
        }

        int getNJetPt25() {
            return m_leplep_nJetPt25_leplep_base;
        }

        int getNJetEta2p4Pt25() {
            return m_leplep_nJetEta2p4Pt25_leplep_base;
        }

        double getMtLep0() {
            return m_leplep_mtLep0_leplep_base;
        }
        double getMtLep1() {
            return m_leplep_mtLep1_leplep_base;
        }

        double getPtLep0MET(){
            return m_leplep_pt_lep0met_leplep_base;
        }

        double getPtLep1MET(){
            return m_leplep_pt_lep1met_leplep_base;
        }

        double getDphiLep0MET(){
            return m_leplep_dphilep0met_leplep_base;
        }
        double getDphiLep1MET(){
            return m_leplep_dphilep1met_leplep_base;
        }

        double getd0l0(){
            return m_leplep_d0_l0_leplep_base;
        }

        double getd0l1(){
            return m_leplep_d0_l1_leplep_base;
        }

        double getd0sigl0(){
            return m_leplep_d0sig_l0_leplep_base;
        }

        double getd0sigl1(){
            return m_leplep_d0sig_l1_leplep_base;
        }

        bool getLepton_centrality() {
            return m_lepton_centrality_leplep_base;
        }
        bool getCentral_jet_veto() {
            return m_central_jet_veto_leplep_base;
        }

        bool getVBF_cat() {
            return m_VBF_cat_leplep_base;
        }
        bool getVBF_cat_ZttCR() {
            return m_VBF_cat_ZttCR_leplep_base;
        }
        bool getboosted_cat() {
            return m_boosted_cat_leplep_base;
        }
        bool getboosted_cat_ZttCR() {
            return m_boosted_cat_ZttCR_leplep_base;
        }

	long getRunNumber() {
	  return current_run_number_leplep_base;
	}

};
#endif
