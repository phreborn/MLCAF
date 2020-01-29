//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __TruthSelector__
#define __TruthSelector__
#include "BSMtautauCAF/LepHadObservable.h"

#include "TTreeFormula.h"

class TruthSelector : public LepHadObservable {
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
  TString fOptionName = "";

  TTreeFormula* tau_0_truth_isHadTau = NULL;
  TTreeFormula* tau_0_truth_isEle    = NULL;
  TTreeFormula* tau_0_truth_isMuon   = NULL;
  TTreeFormula* tau_0_truth_pdgId    = NULL;
  TTreeFormula* tau_0_truth_classifierParticleType  = NULL;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  TruthSelector();
  TruthSelector(const TString& expression);
  virtual ~TruthSelector();
public:


  ClassDef(TruthSelector, 1);


};
#endif
