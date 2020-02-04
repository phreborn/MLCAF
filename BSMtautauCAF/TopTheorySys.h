//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __TopTheorySys__
#define __TopTheorySys__

#include "BSMtautauCAF/LepHadObservable.h"

class TopTheorySys : public LepHadObservable {

  public:
    ClassDef(TopTheorySys, 1);
    
    TopTheorySys();
    TopTheorySys(const TString& expression);
    ~TopTheorySys();
    
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
    TH1F* m_hSys = 0;

    TTreeFormula* pmg_truth_weight_ISRHi = NULL;
    TTreeFormula* pmg_truth_weight_ISRLo = NULL;
    TTreeFormula* pmg_truth_weight_FSRHi = NULL;
    TTreeFormula* pmg_truth_weight_FSRLo = NULL;
};
#endif
