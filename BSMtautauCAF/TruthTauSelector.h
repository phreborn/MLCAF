//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __TruthTauSelector__
#define __TruthTauSelector__
#include "BSMtautauCAF/LepHadObservable.h"

#include "TTreeFormula.h"

class TruthTauSelector : public LepHadObservable {
  public:

    ClassDef(TruthTauSelector, 1);
  
    TruthTauSelector();
    TruthTauSelector(const TString& expression);
    virtual ~TruthTauSelector() = default;
  
    virtual bool hasExpression() const override;
    virtual const TString& getExpression() const override;
    virtual void setExpression(const TString& expr) override;
    virtual double getValue() const override;
    virtual TObjArray* getBranchNames() const override;

  protected:
    virtual bool initializeSelf() override;
    virtual bool finalizeSelf() override;
    TString fExpression = "";
    TString fOptionName = "";

    TTreeFormula* tau_0_truth_isHadTau = nullptr;
    TTreeFormula* tau_0_truth_isEle    = nullptr;
    TTreeFormula* tau_0_truth_isMuon   = nullptr;
    TTreeFormula* tau_0_truth_classifierParticleType  = nullptr;
};
#endif
