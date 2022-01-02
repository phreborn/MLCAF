//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __TOPRESIDUALSYS__
#define __TOPRESIDUALSYS__

#include "BSMtautauCAF/LepHadObservable.h"

class TopResidualSys : public LepHadObservable {

  public:
    ClassDef(TopResidualSys, 1);
    
    TopResidualSys();
    TopResidualSys(const TString& expression);
    ~TopResidualSys();
    
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
