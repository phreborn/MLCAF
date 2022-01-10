//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __TruthTauSelectorFakeComposition__
#define __TruthTauSelectorFakeComposition__
#include "BSMtautauCAF/LepHadObservable.h"

#include "TTreeFormula.h"

class TruthTauSelectorFakeComposition : public LepHadObservable {
  public:

    ClassDef(TruthTauSelectorFakeComposition, 1);
  
    TruthTauSelectorFakeComposition();
    TruthTauSelectorFakeComposition(const TString& expression);
    virtual ~TruthTauSelectorFakeComposition() = default;
  
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

    TTreeFormula* tau_0_matched_isHadTau = nullptr;
    TTreeFormula* tau_0_matched_isEle    = nullptr;
    TTreeFormula* tau_0_matched_isMuon   = nullptr;
    TTreeFormula* tau_0_matched_classifierParticleType  = nullptr;
    TTreeFormula* tau_0_matched_isJet   = nullptr;
    TTreeFormula* tau_0_matched_pdgId   = nullptr;

};
#endif

