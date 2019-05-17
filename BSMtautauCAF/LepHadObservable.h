//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __LEPHADOBSERVABLE__
#define __LEPHADOBSERVABLE__
#include "QFramework/TQTreeObservable.h"

#include "TTreeFormula.h"
#include "TMath.h"

class LepHadObservable : public TQTreeObservable {
protected:
  // put here any data members your class might need
public:
  virtual TObjArray* getBranchNames() const override;

protected:
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;
protected:
  TString fExpression = "";

 // limit is the number of the last run of that year:
  const long LIMIT_2015 = 284484;
  const long LIMIT_2016 = 311563;
  const long LIMIT_2017 = 341649;
  const long LIMIT_2018 = 364292;

  bool _isData = false;
  bool _isMC = false;
  bool _isFake = false;
  bool _isSherpa = false;

  bool _use2015 = true;
  bool _use2016 = true;
  bool _use2017 = true;
  bool _use2018 = true;
  bool _useSLT = true;
  bool _useTLT = true;

  TString _weightvariation;
  bool _pileup_low = false;
  bool _pileup_high = false;
  bool _pileup = false;

  TTreeFormula* x_run_number = NULL;

  TTreeFormula* tau_0_pt = NULL;
  TTreeFormula* tau_0_jet_bdt_medium = NULL;
  TTreeFormula* lep_0_pt = NULL;
  TTreeFormula* tau_0_phi = NULL;
  TTreeFormula* lep_0_phi = NULL;
  TTreeFormula* met_reco_et = NULL;
  TTreeFormula* met_reco_etx = NULL;
  TTreeFormula* met_reco_ety = NULL;
  TTreeFormula* met_reco_phi = NULL;
  TTreeFormula* tau_0_n_charged_tracks = NULL;
  TTreeFormula* n_bjets = NULL;

  TTreeFormula* lep_0_iso_Gradient = NULL;
  TTreeFormula* lep_0_iso_FCTightTrackOnly = NULL;
  TTreeFormula* lep_0_iso_FCTight = NULL;

  TTreeFormula* n_electrons = NULL;
  TTreeFormula* n_muons = NULL;
  TTreeFormula* lep_0 = NULL;
  TTreeFormula* lep_0_eta = NULL;

  TTreeFormula* lephad_met_lep0_cos_dphi = NULL;
  TTreeFormula* lephad_met_lep1_cos_dphi = NULL;
  TTreeFormula* lephad_mt_lep0_met = NULL;
  TTreeFormula* lephad_mt_lep1_met = NULL;
  TTreeFormula* lephad_dphi = NULL;


  TString var = "";

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  LepHadObservable();
  LepHadObservable(const TString& expression);

  bool isData() const;
  bool isMC() const;
  bool isFake() const;
  bool isSherpa() const;

  bool is2015() const;
  bool is2016() const;
  bool is2017() const;
  bool is2018() const;
  bool isTauID() const;
  bool isTLT() const;
  bool isSLT() const;

  bool isMuon() const;
  bool isElectron() const;
  bool isHighPt() const;
  bool isHighPt2() const;

  virtual ~LepHadObservable();
public:
  virtual bool parseExpression(const TString& expr);
  virtual void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  // ClassDef(LepHadObservable, 0);
};
#endif
