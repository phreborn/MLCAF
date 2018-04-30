//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __HWWLEPTONIDOBSERVABLE__
#define __HWWLEPTONIDOBSERVABLE__
#include "CAFxAODUtils/TQEventObservable.h"
#include "CAFExample/HWWLeptonIDHelper.h"
#include "xAODParticleEvent/CompositeParticleContainer.h"

// which lepton to check and what to check for
enum HWWLepIDModeOfRunning{
  LeadLepID,
  SubleadLepID,
  OtherLepID,
  LeadLepAntiID,
  SubleadLepAntiID,
  OtherLepAntiID
};

class HWWLeptonIDObservable : public TQEventObservable {

private:

  // LeptonIDHelper for anti-id and id selections
  const HWW::HWWLeptonIDHelper* fLeptonIDHelper = nullptr;

  /** mode of running, which lepton to check on **/
  HWWLepIDModeOfRunning fHWWLepIDModeOfRunning;

  const unsigned int fIndexLeading;
  const unsigned int fIndexSubleading;
  const unsigned int fIndexOtherLepton;

protected:
  // put here data members you wish to retrieve
  // be careful to declare them as follows:
  // mutable ClassName const * varname = 0
  // the "mutable" keyword ensures that this member can be changed also by const functions
  // the "const" keyword ensures that const containers can be retrieved
  // for example, use
  mutable xAOD::CompositeParticleContainer const * mCand = 0;




public:
  virtual double getValue() const override;
  virtual bool initializeSelf() override;
  TString mCandName = "";
  // getClone override (so we don't have to rely on root streamer)
  TQObservable* getClone() const override;

public:
  // default constructor
  HWWLeptonIDObservable();
  // copy constructor
  HWWLeptonIDObservable(const HWWLeptonIDObservable& obs);
  // nominal constructor
  HWWLeptonIDObservable(const TString& name, const HWW::HWWLeptonIDHelper* lepIDHelper, const int mode_of_running,
                          const unsigned int indexLeadLep = 0, const unsigned int indexSubleadLep = 1,
                           const unsigned int indexOtherLepton = 0);
  virtual ~HWWLeptonIDObservable();
  ClassDefOverride(HWWLeptonIDObservable, 1);


};
#endif
