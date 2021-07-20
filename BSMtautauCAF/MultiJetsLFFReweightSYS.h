//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __MultiJetsLFFReweightSYS__
#define __MultiJetsLFFReweightSYS__

#include "BSMtautauCAF/LepHadObservable.h"

class MultiJetsLFFReweightSYS : public LepHadObservable {

  public:

    ClassDef(MultiJetsLFFReweightSYS, 1);
  
    MultiJetsLFFReweightSYS();
    MultiJetsLFFReweightSYS(const TString& expression);
    ~MultiJetsLFFReweightSYS();

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
