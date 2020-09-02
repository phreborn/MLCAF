//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __QCDJETFAKETAU__
#define __QCDJETFAKETAU__

#include "BSMtautauCAF/LepHadObservable.h"

class QCDJetFakeTau : public LepHadObservable {

  public:
    ClassDef(QCDJetFakeTau, 1);
  
    QCDJetFakeTau();
    QCDJetFakeTau(const TString& expression);
    ~QCDJetFakeTau();
  
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
