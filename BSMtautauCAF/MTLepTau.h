//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __MTLEPTAU__
#define __MTLEPTAU__
#include "BSMtautauCAF/LepHadObservable.h"

class MTLepTau : public LepHadObservable {
  
  public:
  
    ClassDefOverride(MTLepTau, 1);
    
    MTLepTau();
    MTLepTau(const TString& expression);
    ~MTLepTau();

    virtual bool hasExpression() const override;
    virtual const TString& getExpression() const override;
    virtual void setExpression(const TString& expr) override;
    virtual double getValue() const override;
    virtual TObjArray* getBranchNames() const override;
  
  protected:
    virtual bool initializeSelf() override;
    virtual bool finalizeSelf() override;
    TString fExpression = "";

};
#endif
