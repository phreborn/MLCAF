//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __EXTRAPOLATIONSYS__
#define __EXTRAPOLATIONSYS__

#include "BSMtautauCAF/LepHadObservable.h"

class ExtrapolationSys : public LepHadObservable {

  public:
    ClassDef(ExtrapolationSys, 1);
    
    ExtrapolationSys();
    ExtrapolationSys(const TString& expression);
    ~ExtrapolationSys();
    
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
