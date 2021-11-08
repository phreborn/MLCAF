//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __MULTIJETSTFF__
#define __MULTIJETSTFF__

#include "BSMtautauCAF/LepHadObservable.h"

class MultiJetsTFF : public LepHadObservable {

  public:
    ClassDef(MultiJetsTFF, 1);
  
    MultiJetsTFF();
    MultiJetsTFF(const TString& expression);
    ~MultiJetsTFF();
  
    virtual double getValue() const override;
    virtual TObjArray* getBranchNames() const override;
    virtual bool hasExpression() const override;
    virtual const TString& getExpression() const override;
    virtual void setExpression(const TString& expr) override;

  protected:
    virtual bool initializeSelf() override;
    virtual bool finalizeSelf() override;

    TString fExpression = "";
    TString fSysName = "";
    TDirectory* m_histoDir = 0;

    std::map<TString, TH1F*> m_FF_hist;
};
#endif
