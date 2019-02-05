#ifndef __EventSelection__
#define __EventSelection__
#include "QFramework/TQAlgorithm.h"
#include "QFramework/TQSample.h"

#include "TLorentzVector.h"
#include "TTreeFormula.h"
#include <vector>

class EventSelection : public TQAlgorithm {
public:
//  virtual double getValue() const override;
  virtual bool initialize(TQSample * sample);
  virtual bool finalize();
  virtual bool execute();
  virtual bool cleanup();
  virtual TObjArray* getBranchNames() const;

  virtual bool provideSystematicMap(const std::map < TString, int > &map);
  virtual int getSystematic(const TString &systematic);
  
protected:
 
  TQSample* fSample = NULL;
  TQToken* fTreeToken = NULL;
  TTree* fTree = NULL;

  int m_systematic;
  int m_flag;
  bool is15=false;
  bool is16=false;
  bool isTemplateFake=false;
  long current_event_number=-1;
  long current_run_number=-1;
  std::map < TString, int > m_systematicMap;
  std::vector < bool > jets_selected;
  std::vector < bool > els_selected;
  std::vector < bool > mus_selected;
  std::vector < bool > taus_selected;
  long event_number; 
  long run_number;
  std::vector < int > els_idx;
  std::vector < int > mus_idx;
  std::vector < int > jets_selected_idx;
  std::vector < int > leptons_selected_idx;
  std::vector < int > els_selected_idx;
  std::vector < int > mus_selected_idx;
  std::vector < int > taus_selected_idx;
  bool debug=false;

  double TriggerWeight;
  double LeptonWeight;
  double LeptonWeight_tight;
  double LeptonWeight_lep0_tight;
  double LeptonWeight_lep1_tight;
  double JVTweight;
  double MVXweight;
  bool isBtagged;
  bool isTriggered_mc;
  bool isTriggered_data;
  int TriggerType;

  double specialTriggerWeight;
  bool specialisTriggered_mc;
  bool specialisTriggered_data;
  int specialTriggerType;

//  TString fExpression = "";

  TTreeFormula *m_event_number;
  TTreeFormula *m_run_number;

  TTreeFormula *m_jets_pt;
  TTreeFormula *m_jets_eta;
  TTreeFormula *m_jets_phi;
  TTreeFormula *m_jets_m;
  TTreeFormula *m_jets_mvx_tagged;
  
  TTreeFormula *m_leptons;
  TTreeFormula *m_leptons_pt;
  TTreeFormula *m_leptons_eta;
  TTreeFormula *m_leptons_phi;
  TTreeFormula *m_leptons_m;
  TTreeFormula *m_leptons_q;


  TTreeFormula *m_lep_matched_lep;
  TTreeFormula *m_lep_matched_lep_pdgId;
  TTreeFormula *m_lep_matched_lep_mother_pdgId;
  TTreeFormula *m_lep_matched_lep_origin;
  TTreeFormula *m_lep_matched_lep_type;


  TTreeFormula *m_taus_pt;
  TTreeFormula *m_taus_eta;
  TTreeFormula *m_taus_phi;
  TTreeFormula *m_taus_m;
  
  TTreeFormula *m_met_et;
  TTreeFormula *m_met_etx;
  TTreeFormula *m_met_ety;
  TTreeFormula *m_met_phi;

  TTreeFormula *m_dilep_mt_lep0_met;
  TTreeFormula *m_dilep_met_lep0_cos_dphi;
  TTreeFormula *m_dilep_met_lep1_cos_dphi;
  TTreeFormula *m_dilep_deta;
  TTreeFormula *m_dilep_mmc_maxw_m;
  TTreeFormula *m_dilep_mmc_mlm_m;
  TTreeFormula *m_dilep_mmc_mlnu3p_m;
  TTreeFormula *m_dilep_coll_approx_x0;
  TTreeFormula *m_dilep_coll_approx_x1;
  TTreeFormula *m_dilep_coll_approx_m;
  //TTreeFormula *m_lep_lep_met_pt;
  //TTreeFormula * m_category_2jetVBF;
  //TTreeFormula * m_category_boosted;

  std::vector < TString > additional_branches;

  bool m_isData;
  bool m_isBoth;

  double m_sphericity=-999.0;
  std::vector < TLorentzVector > m_hpto_vectors;

  double m_leplep_mvis=-999.0;
  double m_leplep_mt=-999.0;
  double m_leplep_mmc_maxw = -999.0;
  double m_leplep_mmc_mlm = -999.0;
  double m_leplep_mmc_mlnu3p = -999.0;
  double m_leplep_sumpt=-999.0;
  double m_leplep_dphi=-999.0;
  double m_leplep_dphil0m=-999.0;
  double m_leplep_dphil1m=-999.0;
  double m_leplep_detall=-999.0;
  double m_leplep_mll=-999.0;
  double m_leplep_mcollasym=-999.0;
  std::vector < double > m_lep_pt;
  std::vector < double > m_lep_eta;
  //double m_lep0_pt=-999.0;
  //double m_lep1_pt=-999.0;
  double m_leplep_pt_ll = -999;
  double m_leplep_pt_tautau = -999;
  double m_leplep_coll_pt = -999;
  double m_lep_x0=-999.0;
  double m_lep_x1=-999.0;
  double m_lep_coll_m=-999.0;
  double m_leplep_sign=-999.0;
  double m_jet_mjj=-999.0;
  double m_jet0_pt=-999.0;
  double m_jet1_pt=-999.0;
  double m_jet_deta=-999.0;
  double m_jet_centrality=-999.0;
  double m_hpto=-999.0;
  double m_hpto_etx=-999.0;
  double m_hpto_ety=-999.0;
  double m_hpto_phi=-999.0;
  double m_hpto_x0=-999.0;
  double m_hpto_x1=-999.0;
  double m_hpto_coll_m=-999.0;
  double m_higgs_pt=-999.0;

  double m_leplep_d0_l0 = -999;
  double m_leplep_d0_l1 = -999;

  double m_leplep_d0sig_l0 = -999;
  double m_leplep_d0sig_l1 = -999;

  double m_leplep_mtLep0=-999.0;
  double m_leplep_mtLep1=-999.0;

  double m_leplep_pt_lep0met=-999.0;
  double m_leplep_pt_lep1met=-999.0;

  int m_leplep_nJetPt25=-999;
  int m_leplep_nJetEta2p4Pt25=-999;
  
  double m_leplep_dphilep0met=-999.0;
  double m_leplep_dphilep1met=-999.0;

  std::vector < double > m_lepjet_dRmin;
  std::vector < bool > leptons_is_selected_tight;

  bool m_lep0_ismatched;
  bool m_lep1_ismatched;

  bool m_lepton_centrality=false;
  bool m_central_jet_veto=false;

  bool m_VBF_cat=false;
  bool m_VBF_cat_ZttCR=false;
  bool m_boosted_cat=false;
  bool m_boosted_cat_ZttCR=false;

  std::vector < TLorentzVector > jets;
  std::vector < TLorentzVector > leptons;
  std::vector < TLorentzVector > els;
  std::vector < TLorentzVector > mus;
  std::vector < TLorentzVector > taus;

  std::vector < TLorentzVector > jets_selected_vector;
  std::vector < TLorentzVector > leptons_selected_vector;
  std::vector < TLorentzVector > els_selected_vector;
  std::vector < TLorentzVector > mus_selected_vector;
  std::vector < TLorentzVector > taus_selected_vector;

  virtual std::vector< TLorentzVector > buildVector ( TTreeFormula *pts , TTreeFormula *etas, TTreeFormula *phis, TTreeFormula *ms) const;
  virtual void OVR_DeltaR (const std::vector < TLorentzVector > &vec1, const std::vector <bool> &select1, const std::vector < TLorentzVector > &vec2, std::vector <bool> &select2, double DeltaR) const;

  virtual bool add_particle_branches();
  virtual bool add_trigger_branches();
  virtual bool add_lepton_sf_brachnes();
  virtual bool add_trigger_sf_brachnes();
  virtual bool add_jet_sf_brachnes();
  virtual bool connect_particle_branches();
  virtual bool connect_trigger_branches();
  virtual bool connect_lepton_sf_brachnes();
  virtual bool connect_trigger_sf_brachnes();
  virtual bool connect_jet_sf_brachnes();

  virtual bool initialise_branches();

  virtual bool create_objects();
  virtual bool selection_objects();
  virtual bool output_objects();
  virtual bool obtain_trigger_sf();
  virtual bool obtain_lepton_sf();
  virtual bool obtain_jet_sf();
  virtual bool finalise_selection();
  virtual bool calculate_variables();

  virtual bool calculate_hpto();
  virtual bool calculate_lepton_variables();
  virtual bool calculate_jet_centrality();
  virtual bool calculate_jet_variables();
  virtual bool calculate_hpto_variables();
  virtual bool calculate_sphericity();
  virtual bool calculate_lepton_centrality();
  virtual bool calculate_central_jet_veto();
  virtual bool calculate_higgs_pt();
  virtual bool calculate_collinear (const TLorentzVector& k1, const TLorentzVector& k2, Double_t met_etx, Double_t met_ety, Double_t &mass, Double_t &x1, Double_t &x2, Double_t &pt1, Double_t &pt2);

  virtual bool massCollinear(const TLorentzVector& k1, const TLorentzVector& k2, Double_t met_etx, Double_t met_ety, Double_t &mass, Double_t &x1, Double_t &x2);

  virtual bool el_selection(int el_idx) const;
  virtual bool mu_selection(int mu_idx) const;
  virtual bool tau_selection(int tau_idx) const;
  virtual bool jet_selection(int jet_idx) const;
  
  virtual void prepare_selection(const std::vector < TLorentzVector > &vector, std::vector < bool > &selection) const;
  
  virtual void objectselection(const std::vector < TLorentzVector > &vector, std::vector < bool > &selection, const std::vector < int > * proxy, bool (EventSelection::*selector) (int) const) const;

  virtual void convertSelectionToIndex(const std::vector < bool > &selection, const std::vector < int > * proxy ,std::vector < int > &selection_idx) const;

  virtual std::vector < int > sortobbjects( const std::vector < int > &selection_idx, TTreeFormula * obs) const;
 
  virtual void removeoverlap();
 
  void printVectors (const std::vector < TLorentzVector > &vectors, const std::vector < int > *proxy=NULL ) const;
  void printVectors (const std::vector < int > &vectors) const;
  void printVectors (const std::vector < double > &vectors) const;
  void printVectors (const std::vector < bool > &vectors) const;

  std::vector < TLorentzVector > getSelectedVector (std::vector < TLorentzVector > vector, std::vector < int > selected_idx);
  
public:
//  virtual bool hasExpression() const override;
//  virtual const TString& getExpression() const override;
//  virtual void setExpression(const TString& expr) override;

  EventSelection(const TString& expression="", int systematic=-1, int flag=-1);
  virtual ~EventSelection();
public:
//  bool parseExpression(const TString& expr);
//  void clearParsedExpression();

//  virtual TString getActiveExpression() const override;

  ClassDef(EventSelection, 1);};


#endif
