//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __SF_MVX_ll_v05__
#define __SF_MVX_ll_v05__
#include "QFramework/TQTreeObservable.h"
#include "Htautau2015/EventSelection_leplep_default.h"

#include "TTreeFormula.h"

class SF_MVX_ll_v05 : public TQTreeObservable {
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
  TTreeFormula* jets_effSF_MVX = NULL;
  TTreeFormula* jets_ineffSF_MVX = NULL;
  TTreeFormula* jets_pt = NULL;
  TTreeFormula* jets_eta = NULL;
  TTreeFormula* jets_mvx_tagged = NULL;
  int m_systematic=0;
  TString jets_effSF_MVX_name="";
  TString jets_ineffSF_MVX_name="";
  EventSelection_leplep_default* EVS;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  SF_MVX_ll_v05();
  SF_MVX_ll_v05(const TString& expression, int systematic);
  virtual ~SF_MVX_ll_v05();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(SF_MVX_ll_v05, 1);


};
#endif
