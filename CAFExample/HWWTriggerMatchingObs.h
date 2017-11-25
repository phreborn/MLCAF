//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __HWWTRIGGERMATCHINGOBS__
#define __HWWTRIGGERMATCHINGOBS__
#include "CAFxAODUtils/TQEventObservable.h"

#include "CAFExample/HWWTrigConfig.h"
#include "CAFExample/HWWTrigBase.h"

#ifndef __CINT__
#define XAOD_STANDALONE 1
// put here any EDM includes you might need, e.g.
#include "xAODParticleEvent/CompositeParticleContainer.h"
#else
// put here forward declares for the classes you might need, e.g.
class CompositeParticle;
class CompositeParticleContainer;
#endif

class HWWTriggerMatchingObs : public TQEventObservable, public HWWTrigBase {
protected:
  // put here data members you wish to retrieve
  // be careful to declare them as follows:
  // mutable ClassName const * varname = 0
  // the "mutable" keyword ensures that this member can be changed also by const functions
  // the "const" keyword ensures that const containers can be retrieved
  // for example, use
  mutable xAOD::CompositeParticleContainer const * mCand = 0;
  TString mCandName = "";
  virtual bool initializeSelf() override;

public:
  virtual double getValue() const override;
  
  
  // const TString fTrigMatchPrefix;

public:
  HWWTriggerMatchingObs();
  HWWTriggerMatchingObs(const TString& name, const std::vector<HWWTrigConfig*>& triggerConfigs);
  virtual ~HWWTriggerMatchingObs();
  ClassDefOverride(HWWTriggerMatchingObs, 1);

  // bool isMatchedDilepLegParticle(const xAOD::IParticle* part, const TString& trigmatch_expression) const;
  // bool isMatchedSingleMuParticle(const xAOD::IParticle* muon, const HWWTrigConfig* trigConf, const xAOD::EventInfo* evtInfo) const;
  // bool isMatchedSingleElParticle(const xAOD::IParticle* electron, const HWWTrigConfig* trigConf, const xAOD::EventInfo* evtInfo) const;

private:
  // does this event have a trigger-matched particle (given dilep triggers are used)?
  bool isMatchedIncludingDilep(const xAOD::CompositeParticle *Evt, const HWWTrigConfig* trigConf, const xAOD::EventInfo* evtInfo) const;
  // does this event have a trigger-matched particle (given only triggers are used)?
  bool isMatchedSingleTriggersOnly(const xAOD::CompositeParticle *Evt, const xAOD::EventInfo* evtInfo) const;
  // helper function: does this event have single-electron trigger-matched electron?
  bool isMatchedSingleElEvent(const xAOD::CompositeParticle* Evt, const xAOD::EventInfo* evtInfo) const;
  // helper function: does this event have single-muon trigger-matched muon?
  bool isMatchedSingleMuEvent(const xAOD::CompositeParticle* Evt, const xAOD::EventInfo* evtInfo) const;
  
  TString dumpTrigMatch(const xAOD::CompositeParticle* Evt, const HWWTrigConfig* trigConf, const xAOD::EventInfo* evtInfo) const;

};
#endif
