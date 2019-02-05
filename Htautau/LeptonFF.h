//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __LEPTONFF__
#define __LEPTONFF__
#include "QFramework/TQTreeObservable.h"

#include "TFile.h"
#include "TTreeFormula.h"

class LeptonFF : public TQTreeObservable {
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

  TTreeFormula* lep_0     = NULL;
  TTreeFormula* lep_0_pt  = NULL;
  TTreeFormula* lep_0_eta = NULL;
  TTreeFormula* n_bjets   = NULL;

  TH1D *   h_ff_flCR_ehad_bveto_fl = 0;
  TH1D *   h_ff_flCR_ehad_btag_fl  = 0;

  TH1D *   h_ff_flCR_muhad_lowPt_bveto_fl  = 0;
  TH1D *   h_ff_flCR_muhad_highPt_bveto_fl = 0;
  TH1D *   h_ff_flCR_muhad_lowPt_btag_fl   = 0;
  TH1D *   h_ff_flCR_muhad_highPt_btag_fl  = 0;


public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  LeptonFF();
  LeptonFF(const TString& expression);
  virtual ~LeptonFF();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(LeptonFF, 1);


};
#endif
