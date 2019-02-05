//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __VPTREWEIGHT__
#define __VPTREWEIGHT__
#include "QFramework/TQTreeObservable.h"
#include "TTreeFormula.h"

class VpTReweight : public TQTreeObservable {
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

  TTreeFormula* lep_0_pt = NULL;
  TTreeFormula* lep_0_phi = NULL;
  TTreeFormula* met_reco_etx = NULL;
  TTreeFormula* met_reco_ety = NULL;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  VpTReweight();
  VpTReweight(const TString& expression);
  virtual ~VpTReweight();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(VpTReweight, 1);


};
#endif
