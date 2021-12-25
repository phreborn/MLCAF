//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __TruthLepSelector__
#define __TruthLepSelector__
#include "BSMtautauCAF/LepHadObservable.h"

#include "TTreeFormula.h"

class TruthLepSelector : public LepHadObservable {
  public:

    ClassDef(TruthLepSelector, 1);
  
    TruthLepSelector();
    TruthLepSelector(const TString& expression);
    virtual ~TruthLepSelector() = default;
  
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

    TTreeFormula* lep_0_matched_isHad = nullptr;
    TTreeFormula* lep_0_matched_pdgId    = nullptr;
    TTreeFormula* lep_0_matched_classifierParticleType  = nullptr;
};
#endif

