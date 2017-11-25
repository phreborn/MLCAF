//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __HWWFAKEFLAVORZJETS__
#define __HWWFAKEFLAVORZJETS__
#include "CAFxAODUtils/TQEventObservable.h"
#include "xAODParticleEvent/CompositeParticleContainer.h"

#include "CAFExample/HWWFakeFlavorDefs.h"

using namespace HWWFakeFlavor;

class HWWFakeFlavorZjets : public TQEventObservable {
private:
  FakeFlavor getFlavourMCTruthClassifier(const xAOD::IParticle* fakeCandidate, const bool isFakeE, const bool isFakeM) const;
  FakeFlavorRun1 getFlavourRun1(const xAOD::IParticle* fakeCandidate) const;
protected:
  // put here data members you wish to retrieve
  // be careful to declare them as follows:
  // mutable ClassName const * varname = 0
  // the "mutable" keyword ensures that this member can be changed also by const functions
  // the "const" keyword ensures that const containers can be retrieved
  // for example, use
  // mutable CompositeParticleContainer const * mCand = 0;

  mutable int feventFakeFlavor = FakeFlavor::NotClassified; //!
  mutable Long64_t fCachedEntry = -1; //!

  // mutable xAOD::CompositeParticleContainer const * eeCand = 0;
  // mutable xAOD::CompositeParticleContainer const * emCand = 0;
  // mutable xAOD::CompositeParticleContainer const * meCand = 0;
  mutable xAOD::CompositeParticleContainer const * mCand = 0;

  bool makeFlavorCache() const;

public:
  virtual bool initializeSelf() override;
  virtual double getValue() const override;
  const FakeClassifierMode mMode = FakeClassifierMode::MCTruthClassifier;
  const FakeIndex mIndex = FakeIndex::Other;
  TString mCandName = "";
public:
  HWWFakeFlavorZjets();
  HWWFakeFlavorZjets(const TString& name, const int classifierMode=0, const int fakeIndex=3);
  virtual ~HWWFakeFlavorZjets();
  ClassDefOverride(HWWFakeFlavorZjets, 1);

};
#endif
