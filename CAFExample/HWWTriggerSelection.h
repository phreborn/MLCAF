//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __HWWTRIGGERSELECTION__
#define __HWWTRIGGERSELECTION__
#include "CAFxAODUtils/TQEventObservable.h"
#include "CAFExample/HWWTrigBase.h"
#include "CAFExample/HWWTrigConfig.h"

class HWWTriggerSelection : public TQEventObservable, HWWTrigBase {
protected:
  // put here data members you wish to retrieve
  // be careful to declare them as follows:
  // mutable ClassName const * varname = 0
  // the "mutable" keyword ensures that this member can be changed also by const functions
  // the "const" keyword ensures that const containers can be retrieved
  // for example, use
  // mutable CompositeParticleContainer const * mCand = 0;

public:
  virtual double getValue() const override;
public:
  HWWTriggerSelection();
  HWWTriggerSelection(const TString& name, const std::vector<HWWTrigConfig*>& trigConfigs);
  virtual ~HWWTriggerSelection();
  ClassDefOverride(HWWTriggerSelection, 1);


};
#endif
