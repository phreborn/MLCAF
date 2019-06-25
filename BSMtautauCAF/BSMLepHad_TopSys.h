//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __BSMLepHad_TopSys__
#define __BSMLepHad_TopSys__
#include "QFramework/TQTreeObservable.h"
#include "BSMtautauCAF/LepHadObservable.h"
#include "TTreeFormula.h"

class BSMLepHad_TopSys : public LepHadObservable {
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
  TString fSysName = "";

  TTreeFormula* pmg_truth_weight_ISRHi = NULL;
  TTreeFormula* pmg_truth_weight_ISRLo = NULL;
  TTreeFormula* pmg_truth_weight_FSRHi = NULL;
  TTreeFormula* pmg_truth_weight_FSRLo = NULL;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  BSMLepHad_TopSys();
  BSMLepHad_TopSys(const TString& expression);
  virtual ~BSMLepHad_TopSys();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(BSMLepHad_TopSys, 1);


};
#endif
