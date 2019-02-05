//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __SF_JVT_ll_v05__
#define __SF_JVT_ll_v05__
#include "QFramework/TQTreeObservable.h"
#include "Htautau2015/EventSelection_leplep_default.h"

#include "TTreeFormula.h"

class SF_JVT_ll_v05 : public TQTreeObservable {
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
  TTreeFormula* jets_effSF_JVT = NULL;
  TString jets_effSF_JVT_name = "";

  int m_systematic=0;

  EventSelection_leplep_default * EVS;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  SF_JVT_ll_v05();
  SF_JVT_ll_v05(const TString& expression, int systematic=0);
  virtual ~SF_JVT_ll_v05();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(SF_JVT_ll_v05, 1);


};
#endif
