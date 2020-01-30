//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __JETFAKESREWEIGHT__
#define __JETFAKESREWEIGHT__

#include "BSMtautauCAF/LepHadObservable.h"

class JetFakesReweight : public LepHadObservable {

  public:
    ClassDef(JetFakesReweight, 1);
    
    JetFakesReweight();
    JetFakesReweight(const TString& expression);
    ~JetFakesReweight();
    
    virtual bool hasExpression() const override;
    virtual const TString& getExpression() const override;
    virtual void setExpression(const TString& expr) override;

    virtual double getValue() const override;
    virtual TObjArray* getBranchNames() const override;

  protected:
    virtual bool initializeSelf() override;
    virtual bool finalizeSelf() override;

    TString fExpression = "";
    TString fSysName = "";
    TDirectory* m_histoDir = 0;

    std::map<TString, TH1F*> m_SF_hist;
};
#endif
