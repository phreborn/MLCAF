#include "CAFExample/HWWTriggerSelection.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(HWWTriggerSelection)

//______________________________________________________________________________________________

HWWTriggerSelection::HWWTriggerSelection(){
  // default constructor
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

HWWTriggerSelection::~HWWTriggerSelection(){
  // default destructor
  DEBUGclass("destructor called");
} 

#define XAOD_STANDALONE 1
// put here any EDM includes you might need, e.g.
//#include "xAODParticleEvent/CompositeParticleContainer.h"

//______________________________________________________________________________________________

double HWWTriggerSelection::getValue() const {
  // value retrieval function, called on every event for every cut and histogram
  DEBUGclass("entering function");

  // the TQEventObservable only works in ASG_RELEASE RootCore, hence
  // we encapsulate the implementation in an ifdef/ifndef block
  #ifndef ASG_RELEASE
  #warning "using plain ROOT compilation scheme - please add '-DASG_RELEASE' to your packages 'Makefile.RootCore'"
  return std::numeric_limits<double>::quiet_NaN();
  #else 
  
  const xAOD::EventInfo* evtInfo = NULL;
  this->retrieve(evtInfo,"EventInfo");

  const double retval = static_cast<double>(HWWTrigBase::passAnyTrigger(evtInfo));
  DEBUGclass("returning %f", retval);
  return retval;
  #endif
}
//______________________________________________________________________________________________

HWWTriggerSelection::HWWTriggerSelection(const TString& name, const std::vector<HWWTrigConfig*>& trigConfigs):
TQEventObservable(name), 
HWWTrigBase(trigConfigs)
{
  // constructor with name argument
  DEBUGclass("constructor called with '%s'",name.Data());
}
