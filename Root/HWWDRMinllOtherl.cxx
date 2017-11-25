#include "CAFExample/HWWDRMinllOtherl.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"


// This observable was created to calculate in FakeZjet samples the DR between the fake (3rd) lepton
// and the closer of the two leading leptons

// Motivation: In mm-e events, there is an unexpected tail of gamma fakes in low Mll.
// Hypothesis: These gamma fakes come from muon breaking radiation and as such
//             should be quite close in DR to one of the muons



ClassImp(HWWDRMinllOtherl)

//______________________________________________________________________________________________

HWWDRMinllOtherl::HWWDRMinllOtherl(){
  // default constructor
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

HWWDRMinllOtherl::~HWWDRMinllOtherl(){
  // default destructor
  DEBUGclass("destructor called");
} 

#define XAOD_STANDALONE 1
// put here any EDM includes you might need, e.g.
//#include "xAODParticleEvent/CompositeParticleContainer.h"

//______________________________________________________________________________________________

double HWWDRMinllOtherl::getValue() const {
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
  
  // first, you can retrieve the data members you needwith the 'retrieve' method
  // as arguments to this function, pass the member pointer to the container as well as the container name
  /* example block:
  xAOD::CompositeParticleContainer* cont = NULL;
  this->retrieve(cont, "EECands");
  */

  // after you have retrieved your data members, you can proceed to calculate the return value
  
  // probably, you first have to retrieve an element from the container
  /* example block:
  const CompositeParticle* p = cont->at(0);
  */

  // in the end, you should calculate your return value
  // of course, you can use other data members of your observable at any time
  /* exmple block:
  const double retval = p->electron(0)->passSelection(this->fExpression.Data());
  */

  // Retrieve CompositeParticle container
  if(!this->fEvent->retrieve(this->mCand, this->mCandName.Data()).isSuccess()) {
    DEBUGclass("failed to retrieve candidates!");
    return false;
  }

  DEBUGclass("retrieved candidates! %s",this->mCandName.Data());

  DEBUGclass(" this->mCand->size(): %i",this->mCand->size());

  // Retrieve event candidate
  const xAOD::CompositeParticle *Evt = this->mCand->at(0);

  const xAOD::IParticle *Lep0 = Evt->part(0);
  const xAOD::IParticle *Lep1 = Evt->part(1);

  const xAOD::IParticle *OtherLep = Evt->otherPart(0);

  double DRLep0OtherLep = (OtherLep->p4()).DeltaR(Lep0->p4());
  double DRLep1OtherLep = (OtherLep->p4()).DeltaR(Lep1->p4());

  double DRmin = -99;

  if (DRLep0OtherLep < DRLep1OtherLep) {
    DRmin = DRLep0OtherLep;
  } else {
    DRmin = DRLep1OtherLep;
  }
  
  DEBUGclass("returning");
  return DRmin;
  #endif
}
//______________________________________________________________________________________________

bool HWWDRMinllOtherl::initializeSelf() {

  // called once per sample (input file) so that the observable knows the name of the event candidate
  // will be EventEM or EventME in the case of DF analysis (depending on the current channel)

  TString CandName = "";
  if(!this->fSample->getTagString("~cand",CandName)) return false;
  this->mCandName = "Event"+CandName;

  return true;
}

//______________________________________________________________________________________________

HWWDRMinllOtherl::HWWDRMinllOtherl(const TString& name):
TQEventObservable(name)
{
  // constructor with name argument
  DEBUGclass("constructor called with '%s'",name.Data());
}
