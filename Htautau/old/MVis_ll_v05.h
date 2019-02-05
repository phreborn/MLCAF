//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __MVis_ll_v05__
#define __MVis_ll_v05__
#include "QFramework/TQTreeObservable.h"
#include "Htautau2015/EventSelection_leplep_default.h"
#include "Htautau2015/EventSelection_leplep_fake.h"

#include "TTreeFormula.h"

class MVis_ll_v05 : public TQTreeObservable {
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
  TTreeFormula* leptons_eta = NULL;
  TTreeFormula* leptons_phi = NULL;
  TTreeFormula* leptons_m = NULL;
  TTreeFormula* dilep_vis_mass = NULL;
  EventSelection_leplep_default * EVS;
  EventSelection_leplep_fake * EVS_fake;

  bool useFakeSelec = false;


public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  MVis_ll_v05();
  MVis_ll_v05(const TString& expression);
  virtual ~MVis_ll_v05();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(MVis_ll_v05, 1);


};
#endif
