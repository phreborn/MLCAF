#ifndef __OverlapRemovalAlg_leplep__
#define __OverlapRemovalAlg_leplep__
#include "QFramework/TQAlgorithm.h"
#include "QFramework/TQSample.h"

#include "TLorentzVector.h"
#include "TTreeFormula.h"
#include <vector>

class OverlapRemovalAlg_leplep : public TQAlgorithm {
public:
//  virtual double getValue() const override;
  virtual bool initialize(TQSample * sample);
  virtual bool finalize();
  virtual bool execute();
  virtual bool cleanup();
  virtual TObjArray* getBranchNames() const;
  virtual int getJetIdx(int nr);
  virtual int getElIdx(int nr);
  virtual int getMuIdx(int nr);
  virtual int getLeptonIdx(int nr);
  virtual int getTauIdx(int nr);
  virtual int getNJet();
  virtual int getNEl();
  virtual int getNMu();
  virtual int getNLepton();
  virtual int getNTau();
  
protected:
 
  TQSample* fSample = NULL;
  TQToken* fTreeToken = NULL;
  TTree* fTree = NULL;

  static std::vector < bool > jets_selected;
  static std::vector < bool > els_selected;
  static std::vector < bool > mus_selected;
  static std::vector < bool > taus_selected;
  static long event_number; 
  static long run_number; 
  static std::vector < int > els_idx;
  static std::vector < int > mus_idx;
  static std::vector < int > jets_selected_idx;
  static std::vector < int > leptons_selected_idx;
  static std::vector < int > els_selected_idx;
  static std::vector < int > mus_selected_idx;
  static std::vector < int > taus_selected_idx;
  static bool debug;

//  TString fExpression = "";

  TTreeFormula *m_event_number;
  TTreeFormula *m_run_number;

  TTreeFormula *m_jets_pt;
  TTreeFormula *m_jets_eta;
  TTreeFormula *m_jets_phi;
  TTreeFormula *m_jets_m;
  
  TTreeFormula *m_leptons;
  TTreeFormula *m_leptons_pt;
  TTreeFormula *m_leptons_eta;
  TTreeFormula *m_leptons_cluster_eta;
  TTreeFormula *m_leptons_cluster_eta_be2;
  TTreeFormula *m_leptons_phi;
  TTreeFormula *m_leptons_m;
  TTreeFormula *m_leptons_iso_wp;
  TTreeFormula *m_leptons_id_loose;
  TTreeFormula *m_leptons_id_medium;
  TTreeFormula *m_leptons_id_tight;

  TTreeFormula *m_taus_pt;
  TTreeFormula *m_taus_eta;
  TTreeFormula *m_taus_phi;
  TTreeFormula *m_taus_m;
  TTreeFormula *m_taus_n_tracks;

  virtual std::vector< TLorentzVector > buildVector ( TTreeFormula *pts , TTreeFormula *etas, TTreeFormula *phis, TTreeFormula *ms) const;
  virtual void OVR_DeltaR (const std::vector < TLorentzVector > &vec1, const std::vector <bool> &select1, const std::vector < TLorentzVector > &vec2, std::vector <bool> &select2, double DeltaR) const;
  //Alena:
  virtual void OVR_DeltaR_anyMu (const std::vector < TLorentzVector > &vec1, const std::vector <bool> &select1, const std::vector < TLorentzVector > &vec2, std::vector <bool> &select2, double DeltaR) const;
  virtual void OVR_DeltaR_El (const std::vector < TLorentzVector > &vec1, const std::vector <bool> &select1, const std::vector < TLorentzVector > &vec2, std::vector <bool> &select2, double DeltaR) const;
 
  virtual void prepare_selection(const std::vector < TLorentzVector > &vector, std::vector < bool > &selection) const;
  
  virtual bool el_selection(int el_idx) const;
  virtual bool mu_selection(int mu_idx) const;
  virtual bool tau_selection(int tau_idx) const;
  virtual bool jet_selection(int jet_idx) const;
  
  virtual void objectselection(const std::vector < TLorentzVector > &vector, std::vector < bool > &selection, const std::vector < int > * proxy, bool (OverlapRemovalAlg_leplep::*selector) (int) const) const ;

  virtual void convertSelectionToIndex(const std::vector < bool > &selection, const std::vector < int > * proxy ,std::vector < int > &selection_idx) const;

  virtual std::vector < int > sortobbjects( const std::vector < int > &selection_idx, TTreeFormula * obs) const;
 
  virtual void removeoverlap(const std::vector <TLorentzVector> &els , std::vector < bool > &els_selected          , 
          const std::vector <TLorentzVector> &mus                            , std::vector < bool > &mus_selected          , 
          const std::vector <TLorentzVector> &taus                           , std::vector < bool > &taus_selected         , 
          const std::vector <TLorentzVector> &jets                           , std::vector < bool > &jets_selected) const;
 
  void printVectors (const std::vector < TLorentzVector > &vectors, const std::vector < int > *proxy=NULL ) const;
  void printVectors (const std::vector < int > &vectors) const;
  void printVectors (const std::vector < double > &vectors) const;
  void printVectors (const std::vector < bool > &vectors) const;
  
  bool jetIndexMode    = false;
  bool elIndexMode     = false;
  bool muIndexMode     = false;
  bool tauIndexMode    = false;
  bool leptonIndexMode = false;

  bool jetNMode    = false;
  bool elNMode     = false;
  bool muNMode     = false;
  bool tauNMode    = false;
  bool leptonNMode = false;

  int jetIndex    = -1;
  int elIndex     = -1;
  int muIndex     = -1;
  int tauIndex    = -1;
  int leptonIndex = -1;

public:
//  virtual bool hasExpression() const override;
//  virtual const TString& getExpression() const override;
//  virtual void setExpression(const TString& expr) override;

  OverlapRemovalAlg_leplep();
  virtual ~OverlapRemovalAlg_leplep();
public:
//  bool parseExpression(const TString& expr);
//  void clearParsedExpression();

//  virtual TString getActiveExpression() const override;

  ClassDef(OverlapRemovalAlg_leplep, 1);


};
#endif
