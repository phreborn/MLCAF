//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __TOPEXTRAPOLATIONSYS__
#define __TOPEXTRAPOLATIONSYS__

#include "BSMtautauCAF/LepHadObservable.h"

class TopExtrapolationSys : public LepHadObservable {

  public:
    ClassDef(TopExtrapolationSys, 1);
    
    TopExtrapolationSys();
    TopExtrapolationSys(const TString& expression);
    ~TopExtrapolationSys();
    
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
