//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __BSMTRIGGERDECISION__
#define __BSMTRIGGERDECISION__

#include "BSMtautauCAF/LepHadObservable.h"

class BSMTriggerDecision : public LepHadObservable {
protected:
  // put here any data members your class might need
 
public:
  virtual double getValue() const override;
  virtual TObjArray* getBranchNames() const override;
protected:
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;
protected:
  TString fExpression = "";
  TString fOptionName = "";

  //* 2015 trigger
  TTreeFormula* HLT_e24_lhmedium_L1EM20VH = NULL;
  TTreeFormula* eleTrigMatch_0_HLT_e24_lhmedium_L1EM20VH = NULL;

  TTreeFormula* HLT_e60_lhmedium = NULL;
  TTreeFormula* eleTrigMatch_0_HLT_e60_lhmedium = NULL;

  //* 2016 trigger
  TTreeFormula* HLT_e26_lhtight_nod0_ivarloose = NULL;
  TTreeFormula* eleTrigMatch_0_HLT_e26_lhtight_nod0_ivarloose = NULL;

  TTreeFormula* HLT_e60_lhmedium_nod0 = NULL;
  TTreeFormula* eleTrigMatch_0_HLT_e60_lhmedium_nod0 = NULL;

  //* 2015 trigger
  TTreeFormula* HLT_e120_lhloose = NULL;
  TTreeFormula* eleTrigMatch_0_HLT_e120_lhloose = NULL;

  //* 2016 trigger
  TTreeFormula* HLT_e140_lhloose_nod0 = NULL;
  TTreeFormula* eleTrigMatch_0_HLT_e140_lhloose_nod0 = NULL;

  //* 2015 trigger
  TTreeFormula* HLT_mu20_iloose_L1MU15               = NULL;
  TTreeFormula* muTrigMatch_0_HLT_mu20_iloose_L1MU15 = NULL;

  //* 2016 trigger
  TTreeFormula* HLT_mu26_ivarmedium               = NULL;
  TTreeFormula* muTrigMatch_0_HLT_mu26_ivarmedium = NULL;

  TTreeFormula* HLT_mu50               = NULL;
  TTreeFormula* muTrigMatch_0_HLT_mu50 = NULL;

  //* 2017 and 2018 triggers should be the same as 2016

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  BSMTriggerDecision();
  BSMTriggerDecision(const TString& expression);
  virtual ~BSMTriggerDecision();
public:


  ClassDef(BSMTriggerDecision, 1);

};
#endif
