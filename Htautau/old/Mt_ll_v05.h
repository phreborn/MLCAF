//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __Mt_ll_v05__
#define __Mt_ll_v05__
#include "QFramework/TQTreeObservable.h"
#include "Htautau2015/EventSelection_leplep_default.h"
#include "Htautau2015/EventSelection_leplep_fake.h"

#include "TTreeFormula.h"

class Mt_ll_v05 : public TQTreeObservable {
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
  TTreeFormula* dilep_mt_lep0_met = NULL;
  EventSelection_leplep_default * EVS;
  EventSelection_leplep_fake * EVS_fake;

  bool useFakeSelec = false;


public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  Mt_ll_v05();
  Mt_ll_v05(const TString& expression);
  virtual ~Mt_ll_v05();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(Mt_ll_v05, 1);


};
#endif
