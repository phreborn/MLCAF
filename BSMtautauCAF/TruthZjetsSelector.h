//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __TruthZjetsSelector__
#define __TruthZjetsSelector__
#include "BSMtautauCAF/LepHadObservable.h"

#include "TTreeFormula.h"

class TruthZjetsSelector : public LepHadObservable {
  public:

    ClassDef(TruthZjetsSelector, 1);
  
    TruthZjetsSelector();
    TruthZjetsSelector(const TString& expression);
    virtual ~TruthZjetsSelector() = default;
  
    virtual bool hasExpression() const override;
    virtual const TString& getExpression() const override;
    virtual void setExpression(const TString& expr) override;
    virtual double getValue() const override;
    virtual TObjArray* getBranchNames() const override;

  protected:
    virtual bool initializeSelf() override;
    virtual bool finalizeSelf() override;
    TString fExpression = "";
    TString fOptionName = "";

    TTreeFormula* selected_jet_0_origin = nullptr;
    TTreeFormula* selected_jet_1_origin = nullptr;
};
#endif

