//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __MTTOT__
#define __MTTOT__
#include "BSMtautauCAF/LepHadObservable.h"

class mTtot : public LepHadObservable {
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

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  mTtot();
  mTtot(const TString& expression);
  virtual ~mTtot();
  ClassDefOverride(mTtot, 1);


};
#endif
