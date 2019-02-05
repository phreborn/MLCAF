//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __DphiLL_ll_v05__
#define __DphiLL_ll_v05__
#include "QFramework/TQTreeObservable.h"
#include "Htautau2015/EventSelection_leplep_default.h"

#include "TTreeFormula.h"

class DphiLL_ll_v05 : public TQTreeObservable {
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
  TTreeFormula* dilep_dphi = NULL;
  EventSelection_leplep_default * EVS;


public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  DphiLL_ll_v05();
  DphiLL_ll_v05(const TString& expression);
  virtual ~DphiLL_ll_v05();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(DphiLL_ll_v05, 1);


};
#endif
