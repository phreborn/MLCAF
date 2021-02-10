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
    virtual ~TruthTauSelector();
  
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

    TTreeFormula* tau_0_matched_isHadTau = NULL;
    TTreeFormula* tau_0_matched_isEle    = NULL;
    TTreeFormula* tau_0_matched_isMuon   = NULL;
    TTreeFormula* tau_0_matched_classifierParticleType  = NULL;

};
#endif

