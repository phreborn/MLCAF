//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __TriggerWeight_ll_v05__
#define __TriggerWeight_ll_v05__
#include "QFramework/TQTreeObservable.h"
#include "Htautau2015/EventSelection_leplep_default.h"
#include "Htautau2015/EventSelection_leplep_fake.h"

#include "TTreeFormula.h"

class TriggerWeight_ll_v05 : public TQTreeObservable {
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
  EventSelection_leplep_default * EVS;
  EventSelection_leplep_fake * EVS_fake;

  bool useFakeSelec = false;

  TTreeFormula* leptons = NULL;
  TTreeFormula* leptons_pt = NULL;
  TTreeFormula* leptons_id_loose = NULL;
  TTreeFormula* leptons_id_medium = NULL;
  TTreeFormula* leptons_id_tight = NULL;
  TTreeFormula* leptons_iso_wp = NULL;
  TTreeFormula* leptons_HLT_e24_lhmedium_L1EM18VH = NULL;
  TTreeFormula* leptons_HLT_e60_lhmedium = NULL;
  TTreeFormula* leptons_HLT_e120_lhloose = NULL;
  TTreeFormula* leptons_HLT_e24_lhmedium_L1EM20VH = NULL;
  TTreeFormula* leptons_HLT_mu20_iloose_L1MU15 = NULL;
  TTreeFormula* leptons_HLT_mu50 = NULL;
  TTreeFormula* HLT_e17_loose_mu14 = NULL;
  TTreeFormula* HLT_mu18_mu8noL1 = NULL;
  TTreeFormula* HLT_2e12_lhloose_L12EM10VH = NULL;

  TTreeFormula* leptons_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE = NULL;
  TTreeFormula* leptons_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE = NULL;
  TTreeFormula* leptons_NOMINAL_HLT_mu18_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE = NULL;
  TTreeFormula* leptons_NOMINAL_HLT_mu18_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE = NULL;
  TTreeFormula* leptons_NOMINAL_HLT_mu8noL1_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE = NULL;
  TTreeFormula* leptons_NOMINAL_HLT_mu8noL1_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE = NULL;
  TTreeFormula* leptons_NOMINAL_HLT_mu14_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE = NULL;
  TTreeFormula* leptons_NOMINAL_HLT_mu14_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_e17_lhloose_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_e17_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_e17_lhloose_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04 = NULL;


public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  TriggerWeight_ll_v05();
  TriggerWeight_ll_v05(const TString& expression);
  virtual ~TriggerWeight_ll_v05();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(TriggerWeight_ll_v05, 1);


};
#endif
