//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __TRIGGERSF__
#define __TRIGGERSF__
#include "QFramework/TQTreeObservable.h"

#include "TTreeFormula.h"

class TriggerSF : public TQTreeObservable {
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

  TTreeFormula* jet_0_pt = NULL;
  TTreeFormula* jet_0_eta = NULL;
  TTreeFormula* tau_0_pt = NULL;
  TTreeFormula* lep_0_pt = NULL;

  TTreeFormula* n_muons = NULL;
  TTreeFormula* n_electrons = NULL;

  TTreeFormula* tau_0_NOMINAL_effSF_HLT_tau25_medium1_tracktwo_JETIDBDTMEDIUM  = NULL;
  TTreeFormula* lep_0_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04  = NULL;
  TTreeFormula* lep_0_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04  = NULL;
  
  TTreeFormula* lep_0_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE = NULL;
  TTreeFormula* lep_0_NOMINAL_HLT_mu14_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE = NULL;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  TriggerSF();
  TriggerSF(const TString& expression);
  virtual ~TriggerSF();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(TriggerSF, 1);


};
#endif
