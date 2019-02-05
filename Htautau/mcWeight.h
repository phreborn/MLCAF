//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __MCWEIGHT__
#define __MCWEIGHT__
#include "QFramework/TQTreeObservable.h"

#include "TTreeFormula.h"

class mcWeight : public TQTreeObservable {
protected:
  // put here any data members your class might need

public:
  virtual double getValue() const override;
  virtual TObjArray* getBranchNames() const override;
protected:
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;
  TTreeFormula* weight_mc = NULL;
  TTreeFormula* NOMINAL_pileup_combined_weight = NULL;
public:
  mcWeight();
  mcWeight(const TString& name);
  virtual ~mcWeight();
  ClassDefOverride(mcWeight, 1);


};
#endif
