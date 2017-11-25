#include "CAFExample/HWWTriggerMatchingObs.h"
#include <limits>
#include <algorithm> // std::fill_n

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

#include "xAODEventInfo/EventInfo.h"

ClassImp(HWWTriggerMatchingObs)


bool HWWTriggerMatchingObs::initializeSelf() {
  // this->mCandName = "H";
  TString CandName = "";
  if(!this->fSample->getTagString("~cand",CandName)) return false;
  this->mCandName = "Event"+CandName;
  return true;
}

// DEBUG function
TString HWWTriggerMatchingObs::dumpTrigMatch(const xAOD::CompositeParticle* Evt, const HWWTrigConfig* trigConf, const xAOD::EventInfo* evtInfo) const {
  // dump all trig match info   
  const bool isMC = evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION);
  DEBUGclass("Inside dumpTrigMatch");

    
  for (size_t iPart=0; iPart<Evt->nParts(); ++iPart ) {
    const xAOD::IParticle* part = Evt->part(iPart);
    if (part->type() == xAOD::Type::Muon) {
      // loop over single electron triggers
      for(const auto& trigger: (isMC ? trigConf->trigSingleEl_MC: trigConf->trigSingleEl_Data)) {
        std::cout << "Muon " << trigger << " : " << part->auxdata<char>(std::string(m_trigmatch_prefix + trigger)) << std::endl; 
      }
    }
  }

  for (size_t iPart=0; iPart<Evt->nParts(); ++iPart ) {
    const xAOD::IParticle* part = Evt->part(iPart);
    if (part->type() == xAOD::Type::Electron) {
      // loop over single electron triggers
      for(const auto& trigger: (isMC ? trigConf->trigSingleEl_MC: trigConf->trigSingleEl_Data)) {
        std::cout << "Electron " << trigger << " : " << part->auxdata<char>(std::string(m_trigmatch_prefix + trigger)) << std::endl;
      }
    }
  }
  return ""; // return dummy string
}

//______________________________________________________________________________________________

HWWTriggerMatchingObs::HWWTriggerMatchingObs(){
  // default constructor
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

HWWTriggerMatchingObs::~HWWTriggerMatchingObs(){
  // default destructor
  DEBUGclass("destructor called");
} 

#define XAOD_STANDALONE 1
// put here any EDM includes you might need, e.g.
//#include "xAODParticleEvent/CompositeParticleContainer.h"


//______________________________________________________________________________________________
bool HWWTriggerMatchingObs::isMatchedSingleMuEvent(const xAOD::CompositeParticle* Evt, const xAOD::EventInfo* evtInfo) const {
  // return true if this event has muon matched to one of single-muon triggers
   
  // there could be more than one muon, so store matching variable in a bool
  bool matched(false);
  // loop over particles
  for (size_t iPart=0; iPart<Evt->nParts(); ++iPart ) {
    const xAOD::IParticle* part = Evt->part(iPart);
    if (part->type() == xAOD::Type::Muon) {
      matched |= HWWTrigBase::isMatchedSingleMuParticle(part, evtInfo);
    }
  }

  return matched;
}

//______________________________________________________________________________________________
bool HWWTriggerMatchingObs::isMatchedSingleElEvent(const xAOD::CompositeParticle* Evt, const xAOD::EventInfo* evtInfo) const {
  // return true if this event has electron matched to one of single-muon triggers
   
  // there could be more than one electron, so store matching variable in a bool
  bool matched(false);
  // loop over particles
  for (size_t iPart=0; iPart<Evt->nParts(); ++iPart ) {
    const xAOD::IParticle* part = Evt->part(iPart);
    if (part->type() == xAOD::Type::Electron) {
      matched |= HWWTrigBase::isMatchedSingleElParticle(part, evtInfo);
    }
  }

  return matched;
}


//______________________________________________________________________________________________
bool HWWTriggerMatchingObs::isMatchedSingleTriggersOnly(const xAOD::CompositeParticle *Evt, const xAOD::EventInfo* evtInfo) const {

  return (isMatchedSingleElEvent(Evt, evtInfo) || isMatchedSingleMuEvent(Evt, evtInfo));

}


//______________________________________________________________________________________________
bool HWWTriggerMatchingObs::isMatchedIncludingDilep(const xAOD::CompositeParticle *Evt, const HWWTrigConfig* trigConf, const xAOD::EventInfo* evtInfo) const {
  // is any event particle matched to any of the triggers?

  // compute first single-lepton triggers
  if (isMatchedSingleTriggersOnly(Evt, evtInfo)) return true;
  
  // if not matched to any of the single lepton triggers, try to match to the dilepton triggers 
  // slightly more complicated since we have to keep track of the two legs

  // get trigger list for this event
  const std::vector<TString>& triggers = evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION) ? trigConf->trigDilep_MC : trigConf->trigDilep_Data;

  unsigned int nDilepTriggers = triggers.size();
  // arrays of bools holding matched-to-dilep-leg. Initialize to false
  bool* matchedElectronLeg = new bool[nDilepTriggers]; std::fill_n(matchedElectronLeg, nDilepTriggers, false); 
  bool* matchedMuonLeg = new bool[nDilepTriggers];     std::fill_n(matchedMuonLeg, nDilepTriggers, false); 

  
  // loop over triggers
  // TString trigger;
  for (unsigned int iDilep(0); iDilep < nDilepTriggers; iDilep++) {
    // trigger = triggers[iDilep];
    // loop over particles in part() container (particles passing final object selection)
    // fill matchedElectronLeg and matchedMuonLeg depending on type
    for (size_t iPart=0; iPart<Evt->nParts(); ++iPart ) {
      const xAOD::IParticle* part = Evt->part(iPart);
      // Electron
      if (part->type() == xAOD::Type::Electron) {
        // the pt is event-level cut, check that first
        if (part->pt() > trigConf->ptcut_dilep_elleg) {
          matchedElectronLeg[iDilep] = HWWTrigBase::isMatchedDilepLegParticle(part, this->m_trigmatch_prefix + triggers[iDilep]);
        }
      } else if (part->type() == xAOD::Type::Muon) { // Muon
        if (part->pt() > trigConf->ptcut_dilep_muleg) {
          matchedMuonLeg[iDilep] = HWWTrigBase::isMatchedDilepLegParticle(part, this->m_trigmatch_prefix + triggers[iDilep]);
        }
      }
    }
  }

  // loop over arrays, if two matched found at same index, we have a match
  bool matched(false);
  for (unsigned int iDilep(0); iDilep < nDilepTriggers; ++iDilep) {
    if (matchedElectronLeg[iDilep] && matchedMuonLeg[iDilep]) matched = true;
  }

  // clean up
  delete matchedElectronLeg;
  delete matchedMuonLeg; 

  return matched;
}

//______________________________________________________________________________________________
double HWWTriggerMatchingObs::getValue() const {
  // value retrieval function, called on every event for every cut and histogram
  DEBUGclass("entering function");

  // the TQEventObservable only works in ASG_RELEASE RootCore, hence
  // we encapsulate the implementation in an ifdef/ifndef block
  #ifndef ASG_RELEASE
  #warning "using plain ROOT compilation scheme - please add '-DASG_RELEASE' to your packages 'Makefile.RootCore'"
  return std::numeric_limits<double>::quiet_NaN();
  #else 
  // in the rest of this function, you should retrieve the data and calculate your return value
  // here is the place where most of your custom code should go
  // a couple of comments should guide you through the process
  // when writing your code, please keep in mind that this code can be executed several times on every event
  // make your code efficient. catch all possible problems. when in doubt, contact experts!
  
  if (!this->fEvent->retrieve(this->mCand,this->mCandName.Data()).isSuccess()){
    DEBUGclass("Failed to retrieve event candidate!");//" %s", this->mCandName.Data()).Data());
    return 0.;
  }
  // get the event candidate
  const xAOD::CompositeParticle *Evt = this->mCand->at(0);

  const xAOD::EventInfo* evtInfo = NULL;
  if (!this->fEvent->retrieve(evtInfo,"EventInfo").isSuccess()) {
    throw std::runtime_error("HWWTriggerMatchingObs :: Failed to retrieve event info!");
  }

  // get trigger config for this event (needed to know if dilepton triggers are used)
  const HWWTrigConfig* trigConfig = HWWTrigBase::getTrigConfig(evtInfo);
  if (!trigConfig) throw std::runtime_error("In HWWTriggerMatchingObs :: couldn't retrieve HWWTrigConfig object. Are you sure you passed this observable a list of such objects?");

  DEBUGclass(dumpTrigMatch(Evt, trigConfig, evtInfo).Data());
  bool isMatched = trigConfig->m_useDilepTriggers ? isMatchedIncludingDilep(Evt, trigConfig, evtInfo) : isMatchedSingleTriggersOnly(Evt, evtInfo); 

  DEBUGclass("returning %d", isMatched);
  return isMatched;  
  #endif
}
//______________________________________________________________________________________________

HWWTriggerMatchingObs::HWWTriggerMatchingObs(const TString& name, const std::vector<HWWTrigConfig*>& trigConfigs) :
                                              // const bool matchElectronOnly, const bool matchMuonOnly):
TQEventObservable(name),
HWWTrigBase(trigConfigs)
{
  // constructor with name argument
  DEBUGclass("constructor called with '%s'",name.Data());
}
