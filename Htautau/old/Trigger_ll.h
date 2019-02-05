//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __Trigger_ll__
#define __Trigger_ll__
#include "QFramework/TQTreeObservable.h"

#include "TTreeFormula.h"

class Trigger_ll : public TQTreeObservable {
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

  TTreeFormula* lep_0 = NULL;
  TTreeFormula* lep_1 = NULL;
  TTreeFormula* lep_0_pt = NULL;
  TTreeFormula* lep_1_pt = NULL;
  TTreeFormula* lep_0_HLT_e24_lhmedium_L1EM18VH = NULL;
  TTreeFormula* lep_0_HLT_e60_lhmedium = NULL;
  TTreeFormula* lep_0_HLT_e120_lhloose = NULL;
  TTreeFormula* lep_0_HLT_e24_lhmedium_L1EM20VH = NULL;
  TTreeFormula* lep_0_HLT_mu20_iloose_L1MU15 = NULL;
  TTreeFormula* lep_0_HLT_mu50 = NULL;
  TTreeFormula* lep_1_HLT_e24_lhmedium_L1EM18VH = NULL;
  TTreeFormula* lep_1_HLT_e60_lhmedium = NULL;
  TTreeFormula* lep_1_HLT_e120_lhloose = NULL;
  TTreeFormula* lep_1_HLT_e24_lhmedium_L1EM20VH = NULL;
  TTreeFormula* lep_1_HLT_mu20_iloose_L1MU15 = NULL;
  TTreeFormula* lep_1_HLT_mu50 = NULL;
  TTreeFormula* HLT_e17_loose_mu14 = NULL;
  TTreeFormula* HLT_mu18_mu8noL1 = NULL;
  TTreeFormula* HLT_2e12_lhloose_L12EM10VH = NULL;

  bool isData = false;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  Trigger_ll();
  Trigger_ll(const TString& expression);
  virtual ~Trigger_ll();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(Trigger_ll, 1);


};
#endif
