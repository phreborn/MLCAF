//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __INVMTAUJET__
#define __INVMTAUJET__
#include "BSMtautauCAF/LepHadObservable.h"

class InvMTauJet : public LepHadObservable {
  
  public:
  
    ClassDefOverride(InvMTauJet, 1);
    
    InvMTauJet();
    InvMTauJet(const TString& expression);
    ~InvMTauJet();

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
