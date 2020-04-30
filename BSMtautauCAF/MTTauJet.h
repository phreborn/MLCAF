//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __MTTAUJET__
#define __MTTAUJET__
#include "BSMtautauCAF/LepHadObservable.h"

class MTTauJet : public LepHadObservable {
  
  public:
  
    ClassDefOverride(MTTauJet, 1);
    
    MTTauJet();
    MTTauJet(const TString& expression);
    ~MTTauJet();

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
