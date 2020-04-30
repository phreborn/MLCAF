//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __SUMOFPT__
#define __SUMOFPT__
#include "BSMtautauCAF/LepHadObservable.h"

class SumOfPt : public LepHadObservable {
  
  public:
  
    ClassDefOverride(SumOfPt, 1);
    
    SumOfPt();
    SumOfPt(const TString& expression);
    ~SumOfPt();

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
