//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __TOPREWEIGHTLQ__
#define __TOPREWEIGHTLQ__

#include "BSMtautauCAF/LepHadObservable.h"

class TopReweightLQ : public LepHadObservable {

  public:
    ClassDef(TopReweightLQ, 1);
  
    TopReweightLQ();
    TopReweightLQ(const TString& expression);
    ~TopReweightLQ();

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

    std::map<TString, TH1F*> m_SF_hist;

};
#endif
