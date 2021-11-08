//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __MultiJetsSF__
#define __MultiJetsSF__

#include "BSMtautauCAF/LepHadObservable.h"

class MultiJetsSF : public LepHadObservable {

  public:

    ClassDef(MultiJetsSF, 1);
  
    MultiJetsSF();
    MultiJetsSF(const TString& expression);
    ~MultiJetsSF();

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
