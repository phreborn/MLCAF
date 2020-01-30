//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __JETFAKES__
#define __JETFAKES__

#include "BSMtautauCAF/LepHadObservable.h"

class JetFakes : public LepHadObservable {

  public:
    
    ClassDef(JetFakes, 1);
    
    JetFakes();
    JetFakes(const TString& expression);
    ~JetFakes();
    
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

    std::map<TString, TH1F*> m_FF_hist;
};
#endif
