//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __TOPCOR__
#define __TOPCOR__
#include "QFramework/TQTreeObservable.h"

#include "TFile.h"
#include "TTreeFormula.h"

class topCor : public TQTreeObservable {
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
  TTreeFormula* n_bjets   = NULL;


public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  topCor();
  topCor(const TString& expression);
  virtual ~topCor();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(topCor, 1);

};
#endif
