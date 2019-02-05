//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __btagSelector__
#define __btagSelector__
#include "QFramework/TQTreeObservable.h"

#include "TTreeFormula.h"

class btagSelector : public TQTreeObservable {
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

  std::vector<double>  *vjetPt =0 ;
  std::vector<double>  *vjetMv2c20 =0;


public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  btagSelector();
  btagSelector(const TString& expression);
  virtual ~btagSelector();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(btagSelector, 1);


};
#endif
