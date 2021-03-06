//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __MTLEPJET__
#define __MTLEPJET__
#include "BSMtautauCAF/LepHadObservable.h"

class MTLepJet : public LepHadObservable {
  
  public:
  
    ClassDefOverride(MTLepJet, 1);
    
    MTLepJet();
    MTLepJet(const TString& expression);
    ~MTLepJet();

    virtual bool hasExpression() const override;
    virtual const TString& getExpression() const override;
    virtual void setExpression(const TString& expr) override;
    virtual double getValue() const override;
    virtual TObjArray* getBranchNames() const override;
  
  protected:
    virtual bool initializeSelf() override;
    virtual bool finalizeSelf() override;
    TString fExpression = "";

    TTreeFormula* lepjet_dphi = nullptr;

};
#endif
