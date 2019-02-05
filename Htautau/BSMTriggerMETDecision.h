//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __BSMTRIGGERMETDECISION__
#define __BSMTRIGGERMETDECISION__
#include "QFramework/TQTreeObservable.h"

#include "TTreeFormula.h"

class BSMTriggerMETDecision : public TQTreeObservable {
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

  TTreeFormula* run_number = NULL;
  TTreeFormula* NOMINAL_pileup_random_run_number = NULL;

  TTreeFormula* lep_0        = NULL;
  TTreeFormula* lep_0_pt     = NULL;
  TTreeFormula* lep_0_phi    = NULL;
  TTreeFormula* met_reco_et  = NULL;
  TTreeFormula* met_reco_phi = NULL;

  //* 2015 trigger
  TTreeFormula* HLT_xe70                = NULL;
  TTreeFormula* HLT_xe70_mht            = NULL;
  TTreeFormula* HLT_xe70_tc_lcw         = NULL;

  //* 2016 trigger
  TTreeFormula* HLT_xe80_tc_lcw_L1XE50  = NULL;
  TTreeFormula* HLT_xe90_mht_L1XE50     = NULL;
  TTreeFormula* HLT_xe100_mht_L1XE50    = NULL;
  TTreeFormula* HLT_xe110_mht_L1XE50    = NULL;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  BSMTriggerMETDecision();
  BSMTriggerMETDecision(const TString& expression);
  virtual ~BSMTriggerMETDecision();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(BSMTriggerMETDecision, 1);

};
#endif
