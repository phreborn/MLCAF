//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __HWWDRMINLLOTHERL__
#define __HWWDRMINLLOTHERL__
#include "CAFxAODUtils/TQEventObservable.h"

#ifndef __CINT__
#ifdef ASG_RELEASE
#include "xAODParticleEvent/CompositeParticleContainer.h"
#endif
#endif

class IParticle;

class HWWDRMinllOtherl : public TQEventObservable {
protected:
  // put here data members you wish to retrieve
  // be careful to declare them as follows:
  // mutable ClassName const * varname = 0
  // the "mutable" keyword ensures that this member can be changed also by const functions
  // the "const" keyword ensures that const containers can be retrieved
  // for example, use
  // mutable CompositeParticleContainer const * mCand = 0;

  TString mCandName = "";

#ifndef __CINT__
#ifdef ASG_RELEASE

mutable xAOD::CompositeParticleContainer const * mCand = 0;

#endif
#endif

public:
  virtual double getValue() const override;
  virtual bool initializeSelf() override;
public:
  HWWDRMinllOtherl();
  HWWDRMinllOtherl(const TString& name);
  virtual ~HWWDRMinllOtherl();
  ClassDefOverride(HWWDRMinllOtherl, 1);


};
#endif
