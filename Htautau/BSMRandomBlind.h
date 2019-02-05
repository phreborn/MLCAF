//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __BSMRANDOMBLIND__
#define __BSMRANDOMBLIND__
#include "QFramework/TQTreeObservable.h"

#include "TTreeFormula.h"
#include "TRandom3.h"

class BSMRandomBlind : public TQTreeObservable {
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

  TString fOptionName = "";

  TTreeFormula* event_number = NULL;

  TRandom3 * rRandomGenerator = NULL;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  BSMRandomBlind();
  BSMRandomBlind(const TString& expression);
  virtual ~BSMRandomBlind();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(BSMRandomBlind, 1);

};
#endif
