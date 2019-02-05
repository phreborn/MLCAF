//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __DPHIDISTREWEIGHT__
#define __DPHIDISTREWEIGHT__
#include "QFramework/TQTreeObservable.h"

#include "TFile.h"
#include "TTreeFormula.h"

class dPhiDistReweight : public TQTreeObservable {
protected:
  // put here any data members your class might need
 
public:
  virtual double getValue() const override;
  virtual TObjArray* getBranchNames() const override;
protected:
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;
protected:
  TString fExpression = "";

  TString fSysName = "";

  TTreeFormula* NOMINAL_pileup_random_run_number     = NULL;
  TTreeFormula* run_number = NULL;
  TTreeFormula* tau_0_phi = NULL;
  TTreeFormula* met_reco_phi = NULL;

  TTreeFormula* tau_0_pt = NULL;
  TTreeFormula* lephad_qxq = NULL;
  TTreeFormula* lephad_mt_lep0_met = NULL;
  TTreeFormula* tau_0_n_tracks = NULL;
  TTreeFormula* lep_0 = NULL;
  TTreeFormula* n_bjets = NULL;
  
  TH1D * h_dphi_distcor  = 0;

  std::vector<TFile*> fileList;


public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  dPhiDistReweight();
  dPhiDistReweight(const TString& expression);
  virtual ~dPhiDistReweight();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(dPhiDistReweight, 1);

};
#endif
