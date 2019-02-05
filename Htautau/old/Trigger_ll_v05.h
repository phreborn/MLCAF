//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __Trigger_ll_v05__
#define __Trigger_ll_v05__
#include "QFramework/TQTreeObservable.h"
#include "Htautau2015/EventSelection_leplep_default.h"
#include "Htautau2015/EventSelection_leplep_fake.h"

#include "TTreeFormula.h"

class Trigger_ll_v05 : public TQTreeObservable {
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

  TTreeFormula* leptons = NULL;
  TTreeFormula* leptons_pt = NULL;
  TTreeFormula* leptons_HLT_e24_lhmedium_L1EM18VH = NULL;
  TTreeFormula* leptons_HLT_e60_lhmedium = NULL;
  TTreeFormula* leptons_HLT_e120_lhloose = NULL;
  TTreeFormula* leptons_HLT_e24_lhmedium_L1EM20VH = NULL;
  TTreeFormula* leptons_HLT_mu20_iloose_L1MU15 = NULL;
  TTreeFormula* leptons_HLT_mu50 = NULL;
  TTreeFormula* HLT_e17_loose_mu14 = NULL;
  TTreeFormula* HLT_mu18_mu8noL1 = NULL;
  TTreeFormula* HLT_2e12_lhloose_L12EM10VH = NULL;
  EventSelection_leplep_default * EVS;
  EventSelection_leplep_fake * EVS_fake;

  bool isData = false;
  bool isTrigType = false;

  bool useFakeSelec = false;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  Trigger_ll_v05();
  Trigger_ll_v05(const TString& expression);
  virtual ~Trigger_ll_v05();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(Trigger_ll_v05, 1);


};
#endif
