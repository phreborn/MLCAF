//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __LEPTONFAKESREWEIGHT__
#define __LEPTONFAKESREWEIGHT__

#include "BSMtautauCAF/LepHadObservable.h"

class LeptonFakesReweight : public LepHadObservable {

  public:

    ClassDef(LeptonFakesReweight, 1);
  
    LeptonFakesReweight();
    LeptonFakesReweight(const TString& expression);
    ~LeptonFakesReweight();

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

    bool fileLoaded = false;
    std::map<TString, TH1F*> m_SF_hist;
};
#endif
