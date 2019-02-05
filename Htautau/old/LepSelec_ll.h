//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __LepSelec_ll__
#define __LepSelec_ll__
#include "QFramework/TQTreeObservable.h"

#include "TTreeFormula.h"

class LepSelec_ll : public TQTreeObservable {
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
  TTreeFormula* lep_0_eta = NULL;
  TTreeFormula* lep_1_eta = NULL;
  TTreeFormula* lep_0_cluster_eta = NULL;
  TTreeFormula* lep_1_cluster_eta = NULL;
  TTreeFormula* lep_0_id_medium = NULL;
  TTreeFormula* lep_1_id_medium = NULL;
  TTreeFormula* lep_0_id_loose = NULL;
  TTreeFormula* lep_1_id_loose = NULL;
  TTreeFormula* lep_0_id_tight = NULL;
  TTreeFormula* lep_1_id_tight = NULL;
  TTreeFormula* lep_0_iso_wp = NULL;
  TTreeFormula* lep_1_iso_wp = NULL;

  bool isMedMed = false;
  bool isTightTight = false;
  bool isTightLoose = false;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  LepSelec_ll();
  LepSelec_ll(const TString& expression);
  virtual ~LepSelec_ll();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(LepSelec_ll, 1);


};
#endif
