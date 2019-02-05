//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __TemplateFake_weight_ll__
#define __TemplateFake_weight_ll__
#include "QFramework/TQTreeObservable.h"

#include "TTreeFormula.h"

class TemplateFake_weight_ll : public TQTreeObservable {
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
  TTreeFormula* fake_weight = NULL;
  TTreeFormula* sherpa_weight = NULL;
  int m_systematic=0;
  TString fake_weight_name="";
  bool m_isSherpa;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  TemplateFake_weight_ll();
  TemplateFake_weight_ll(const TString& expression, int systematic=0);
  virtual ~TemplateFake_weight_ll();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(TemplateFake_weight_ll, 1);


};
#endif
