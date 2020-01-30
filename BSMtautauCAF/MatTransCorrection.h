//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __MATTRANSCORRECTION__
#define __MATTRANSCORRECTION__

#include "BSMtautauCAF/LepHadObservable.h"
#include "TGraphAsymmErrors.h"

class MatTransCorrection : public LepHadObservable {

  public:
    ClassDef(MatTransCorrection, 1);
  
    MatTransCorrection();
    MatTransCorrection(const TString& expression);
    ~MatTransCorrection();

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

    std::map<TString, TF1*> m_SF_fun;
    std::map<TString, TGraphAsymmErrors*> m_SF_graph;
};
#endif
