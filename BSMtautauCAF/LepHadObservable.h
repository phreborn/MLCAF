//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __LEPHADOBSERVABLE__
#define __LEPHADOBSERVABLE__
#include "QFramework/TQTreeObservable.h"

#include "TTreeFormula.h"
#include "TMath.h"
#include <bitset>
    
typedef std::bitset<128> Condition;

class LepHadObservable : public TQTreeObservable {
  
public:
  
  LepHadObservable();
  LepHadObservable(const TString& expression);
  virtual ~LepHadObservable() = default;
  
  virtual TObjArray* getBranchNames() const override;
  
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;
  

  bool isData() const;
  bool isMC() const;

  bool is2015() const;
  bool is2016() const;
  bool is2017() const;
  bool is2018() const;

  unsigned int bjetCount() const;

  bool isSLT() const;

  bool isMuon() const;
  bool isElectron() const;
  bool isTTBar() const;
  bool isSTop() const;
  bool isZ2BJET() const;
  bool isZ1BJET() const;
  bool isZ1CJET() const;
  bool isZ1LJET() const;
  bool isTauID() const;
  bool isLepISO() const;

  bool isHighPt() const;

  float TransverseMass(float pt1, float pt2, float dphi) const;

protected:
  
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;
  
  TString fExpression = "";

  // limit is the number of the last run of that year:
  const long LIMIT_2015 = 284484;
  const long LIMIT_2016 = 311563;
  const long LIMIT_2017 = 341649;
  const long LIMIT_2018 = 364292;

  bool m_isData = false;
  bool m_isMC = false;
  bool m_isTTBar = false;
  bool m_isSTop = false;
  bool m_isZ2BJET = false;
  bool m_isZ1BJET = false;
  bool m_isZ1CJET = false;
  bool m_isZ1LJET = false;

  bool m_verbose = false;

  TTreeFormula* n_bjets = nullptr;
  TTreeFormula* lep_0_iso_electron = nullptr;
  TTreeFormula* lep_0_iso_muon = nullptr;
  TTreeFormula* tau_0_jet_id = nullptr;
  
  TTreeFormula* x_run_number = nullptr;
  TTreeFormula* mc_channel_number = nullptr;
  
  TTreeFormula* n_electrons = nullptr;
  TTreeFormula* n_muons = nullptr;
  TTreeFormula* lep_0 = nullptr;
  TTreeFormula* lep_0_pt = nullptr;
  TTreeFormula* lep_0_eta = nullptr;
  TTreeFormula* lep_0_phi = nullptr;
  TTreeFormula* tau_0_n_charged_tracks = nullptr;
  TTreeFormula* tau_0_pt = nullptr;
  TTreeFormula* tau_0_eta = nullptr;
  TTreeFormula* tau_0_phi = nullptr;
  TTreeFormula* jet_0_pt = nullptr;
  TTreeFormula* bjet_0_pt = nullptr;
  TTreeFormula* bjet_0_phi = nullptr;
  TTreeFormula* jets_scalar_sum_pt = nullptr;
  TTreeFormula* lephad_qxq = nullptr;
  TTreeFormula* lephad_dphi = nullptr;
  TTreeFormula* met_reco_et = nullptr;
  TTreeFormula* met_reco_etx = nullptr;
  TTreeFormula* met_reco_ety = nullptr;
  TTreeFormula* met_reco_phi = nullptr;
  TTreeFormula* lephad_met_lep0_cos_dphi = nullptr;
  TTreeFormula* lephad_met_lep1_cos_dphi = nullptr;
  TTreeFormula* lephad_mt_lep0_met = nullptr;
  TTreeFormula* lephad_mt_lep1_met = nullptr;
};

#endif
