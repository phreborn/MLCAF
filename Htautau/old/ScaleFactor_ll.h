//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __ScaleFactor_ll__
#define __ScaleFactor_ll__
#include "QFramework/TQTreeObservable.h"

#include "TTreeFormula.h"

class ScaleFactor_ll : public TQTreeObservable {
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
  TTreeFormula* lep_0_NOMINAL_MU_RECO_MEDIUM = NULL;
  TTreeFormula* lep_0_NOMINAL_MU_RECO_LOOSE = NULL;
  TTreeFormula* lep_0_NOMINAL_MU_RECO_TIGHT = NULL;
  TTreeFormula* lep_0_NOMINAL_MU_ISO_LOOSE = NULL; 
  TTreeFormula* lep_0_NOMINAL_EL_RECO = NULL;
  TTreeFormula* lep_0_NOMINAL_EL_ID_MEDIUM = NULL;
  TTreeFormula* lep_0_NOMINAL_EL_ID_LOOSE = NULL;
  TTreeFormula* lep_0_NOMINAL_EL_ID_TIGHT = NULL;
  TTreeFormula* lep_0_NOMINAL_EL_ISO_LOOSE = NULL;
  TTreeFormula* lep_1_NOMINAL_MU_RECO_MEDIUM = NULL;
  TTreeFormula* lep_1_NOMINAL_MU_RECO_TIGHT = NULL;
  TTreeFormula* lep_1_NOMINAL_MU_RECO_LOOSE = NULL;
  TTreeFormula* lep_1_NOMINAL_MU_ISO_LOOSE = NULL;
  TTreeFormula* lep_1_NOMINAL_EL_RECO = NULL;
  TTreeFormula* lep_1_NOMINAL_EL_ID_MEDIUM = NULL;
  TTreeFormula* lep_1_NOMINAL_EL_ID_TIGHT = NULL;
  TTreeFormula* lep_1_NOMINAL_EL_ID_LOOSE = NULL;
  TTreeFormula* lep_1_NOMINAL_EL_ISO_LOOSE = NULL;

  bool isMedMed = false;
  bool isTightTight = false;
  bool isTightLoose = false;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  ScaleFactor_ll();
  ScaleFactor_ll(const TString& expression);
  virtual ~ScaleFactor_ll();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(ScaleFactor_ll, 1);


};
#endif
