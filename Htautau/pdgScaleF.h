//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __PDGSCALEF__
#define __PDGSCALEF__
#include "QFramework/TQTreeObservable.h"

#include "TFile.h"
#include "TTreeFormula.h"

class pdgScaleF : public TQTreeObservable {
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

  TTreeFormula* tau_0_n_tracks = NULL;
  TTreeFormula* tau_0_truth_pdgId = NULL;

  TH1F *   h_ratio_1p = 0;
  TH1F *   h_ratio_3p = 0;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  pdgScaleF();
  pdgScaleF(const TString& expression);
  virtual ~pdgScaleF();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(pdgScaleF, 1);

};
#endif
