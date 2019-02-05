//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __BSMTRIGGERWEIGHT__
#define __BSMTRIGGERWEIGHT__
#include "QFramework/TQTreeObservable.h"

#include "TTreeFormula.h"

class BSMTriggerWeight : public TQTreeObservable {
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

  TString fSysName = "";

  TTreeFormula* NOMINAL_pileup_random_run_number = NULL;

  TTreeFormula* lep_0    = NULL;
  TTreeFormula* lep_0_pt = NULL;

  //* 2015 trigger
  TTreeFormula* HLT_e24_lhmedium_L1EM20VH = NULL;
  TTreeFormula* eleTrigMatch_0_HLT_e24_lhmedium_L1EM20VH = NULL;

  //* 2016 trigger
  TTreeFormula* HLT_e24_lhtight_nod0_ivarloose = NULL;
  TTreeFormula* eleTrigMatch_0_HLT_e24_lhtight_nod0_ivarloose = NULL;

  TTreeFormula* HLT_e60_lhmedium                = NULL;
  TTreeFormula* eleTrigMatch_0_HLT_e60_lhmedium = NULL;

  //* 2015 trigger
  TTreeFormula* HLT_e120_lhloose = NULL;
  TTreeFormula* eleTrigMatch_0_HLT_e120_lhloose = NULL;

  //* 2016 trigger
  TTreeFormula* HLT_e140_lhloose_nod0                = NULL;
  TTreeFormula* eleTrigMatch_0_HLT_e140_lhloose_nod0 = NULL;

  //* 2015 trigger
  TTreeFormula* HLT_mu20_iloose_L1MU15               = NULL;
  TTreeFormula* muTrigMatch_0_HLT_mu20_iloose_L1MU15 = NULL;

  //* 2016 trigger
  TTreeFormula* HLT_mu26_ivarmedium               = NULL;
  TTreeFormula* muTrigMatch_0_HLT_mu26_ivarmedium = NULL;

  TTreeFormula* HLT_mu50                             = NULL;
  TTreeFormula* muTrigMatch_0_HLT_mu50               = NULL;

  TTreeFormula* lep_0_NOMINAL_MuEffSF_HLT_mu50_QualMedium_IsoNone            = NULL;
  TTreeFormula* lep_0_NOMINAL_MuEffSF_HLT_mu26_ivarmedium_QualMedium_IsoNone = NULL;
  TTreeFormula* lep_0_NOMINAL_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoNone = NULL;

  //** 

  TTreeFormula* lep_0_MUON_EFF_TrigStatUncertainty_1up_MuEffSF_HLT_mu50_QualMedium_IsoNone = NULL;
  TTreeFormula* lep_0_MUON_EFF_TrigStatUncertainty_1up_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoNone = NULL;
  TTreeFormula* lep_0_MUON_EFF_TrigStatUncertainty_1up_MuEffSF_HLT_mu26_ivarmedium_QualMedium_IsoNone = NULL;

  TTreeFormula* lep_0_MUON_EFF_TrigStatUncertainty_1down_MuEffSF_HLT_mu50_QualMedium_IsoNone = NULL;
  TTreeFormula* lep_0_MUON_EFF_TrigStatUncertainty_1down_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoNone = NULL;                            
  TTreeFormula* lep_0_MUON_EFF_TrigStatUncertainty_1down_MuEffSF_HLT_mu26_ivarmedium_QualMedium_IsoNone = NULL;

  TTreeFormula* lep_0_MUON_EFF_TrigSystUncertainty_1up_MuEffSF_HLT_mu50_QualMedium_IsoNone = NULL;
  TTreeFormula* lep_0_MUON_EFF_TrigSystUncertainty_1up_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoNone = NULL;
  TTreeFormula* lep_0_MUON_EFF_TrigSystUncertainty_1up_MuEffSF_HLT_mu26_ivarmedium_QualMedium_IsoNone = NULL;

  TTreeFormula* lep_0_MUON_EFF_TrigSystUncertainty_1down_MuEffSF_HLT_mu50_QualMedium_IsoNone = NULL;
  TTreeFormula* lep_0_MUON_EFF_TrigSystUncertainty_1down_MuEffSF_HLT_mu20_iloose_L1MU15_QualMedium_IsoNone = NULL;
  TTreeFormula* lep_0_MUON_EFF_TrigSystUncertainty_1down_MuEffSF_HLT_mu26_ivarmedium_QualMedium_IsoNone = NULL;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  BSMTriggerWeight();
  BSMTriggerWeight(const TString& expression);
  virtual ~BSMTriggerWeight();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(BSMTriggerWeight, 1);

};
#endif
