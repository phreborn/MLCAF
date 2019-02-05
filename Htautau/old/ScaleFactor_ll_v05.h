//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __ScaleFactor_ll_v05__
#define __ScaleFactor_ll_v05__
#include "QFramework/TQTreeObservable.h"
#include "Htautau2015/EventSelection_leplep_default.h"
#include "Htautau2015/EventSelection_leplep_fake.h"

#include "TTreeFormula.h"

class ScaleFactor_ll_v05 : public TQTreeObservable {
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
  TTreeFormula* leptons_id_loose = NULL;
  TTreeFormula* leptons_id_medium = NULL;
  TTreeFormula* leptons_id_tight = NULL;
  TTreeFormula* leptons_iso_wp = NULL;
  // ---- to be deleted
  TTreeFormula* leptons_NOMINAL_effSF_RecoLoose  = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_RecoMedium = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_RecoTight  = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_IsoLoose = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_IsoTight = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_IsoGradientLoose = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_IsoGradient = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_offline_LooseAndBLayerLLH_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_offline_MediumLLH_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_offline_TightLLH_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04 = NULL;
  TTreeFormula* leptons_NOMINAL_effSF_offline_RecoTrk_2015_13TeV_rel20p0_25ns_v04 = NULL;
  /// end --- to be deleted
 
  TTreeFormula* muon_ID_effSF = NULL;
  TTreeFormula* muon_ISO_effSF = NULL;
  
  TTreeFormula* el_ID_effSF = NULL;
  TTreeFormula* el_ISO_effSF = NULL;
  TTreeFormula* el_Track_effSF = NULL;

  bool el_looseID  = false;
  bool el_mediumID = false;
  bool el_tightID  = false;

  bool el_looseISO = false;
  bool el_tightISO = false;
  bool el_gradlooseISO = false;
  bool el_gradISO = false;

  int idwp_e = -1;
  int isowp_e = -1;
  int lepIndex = -1;
  
  bool mu_looseID  = false;
  bool mu_mediumID = false;
  bool mu_tightID  = false;

  bool mu_looseISO = false;
  bool mu_tightISO = false;
  bool mu_gradlooseISO = false;
  bool mu_gradISO = false;

  int idwp_m = -1;
  int isowp_m = -1;

  TString muon_ID_effSF_name="";
  TString muon_ISO_effSF_name  = "";
  TString el_Track_effSF_name="";
  TString el_ID_effSF_name="";
  TString el_ISO_effSF_name="";
  

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  ScaleFactor_ll_v05();
  ScaleFactor_ll_v05(const TString& expression);
  virtual ~ScaleFactor_ll_v05();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(ScaleFactor_ll_v05, 1);


};
#endif
