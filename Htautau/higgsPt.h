//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __HIGGSPT__
#define __HIGGSPT__
#include "Htautau/LepHadObservable.h"

class higgsPt : public LepHadObservable {
protected:
  // put here any data members your class might need

public:
  virtual double getValue() const override;
  virtual TObjArray* getBranchNames() const override;
protected:
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;
public:
  higgsPt();
  higgsPt(const TString& name);
  virtual ~higgsPt();
  ClassDefOverride(higgsPt, 1);


};
#endif
