//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __HIGGSPT__
#define __HIGGSPT__
#include "BSMtautauCAF/LepHadObservable.h"

class HiggsPt : public LepHadObservable {

  public:
    
    ClassDefOverride(HiggsPt, 1);
    
    HiggsPt();
    HiggsPt(const TString& name);
    ~HiggsPt();
    virtual double getValue() const override;
    virtual TObjArray* getBranchNames() const override;
  
  protected:
    virtual bool initializeSelf() override;
    virtual bool finalizeSelf() override;

};
#endif
