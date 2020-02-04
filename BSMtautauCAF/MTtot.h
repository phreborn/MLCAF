//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __MTTOT__
#define __MTTOT__
#include "BSMtautauCAF/LepHadObservable.h"

class MTtot : public LepHadObservable {
  
  public:
  
    ClassDefOverride(MTtot, 1);
    
    MTtot();
    MTtot(const TString& expression);
    ~MTtot();

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
