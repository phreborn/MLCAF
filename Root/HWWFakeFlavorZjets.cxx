#include "CAFExample/HWWFakeFlavorZjets.h"
#include <limits>
#include "MCTruthClassifier/MCTruthClassifierDefs.h"
#include <iostream>
using namespace std;

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

using namespace HWWFakeFlavor;

ClassImp(HWWFakeFlavorZjets)

//______________________________________________________________________________________________

HWWFakeFlavorZjets::HWWFakeFlavorZjets(){
  // default constructor
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

HWWFakeFlavorZjets::~HWWFakeFlavorZjets(){
  // default destructor
  DEBUGclass("destructor called");
}

#define XAOD_STANDALONE 1
// put here any EDM includes you might need, e.g.
//#include "xAODParticleEvent/CompositeParticleContainer.h"


//______________________________________________________________________________________________
bool HWWFakeFlavorZjets::initializeSelf() {
  TString CandName = "";
  if(!this->fSample->getTagString("~cand",CandName)) return false;
  this->mCandName = "Event"+CandName;
  return true;
}

//______________________________________________________________________________________________
bool HWWFakeFlavorZjets::makeFlavorCache() const {

  DEBUGclass("makeFlavorCache called for instance with expression '%s'",this->GetName());
#ifndef ASG_RELEASE
  //TEvent observables can only be used with xAOD libraries
  return false;
#else
  if (this->fCachedEntry == this->getCurrentEntry()) return true; //already up-to-date, nothing to do here

  // Reset template assignment of event
  this->feventFakeFlavor = FakeFlavor::NotClassified;

  // Determine if this is data from sample tag
  bool isData;
  if(!this->fSample->getTagBool("~isData",isData)) return false;

  // Fake Flavor only available for MC!
  if (isData) {
    return true; // feventFakeFlavor remains FakeFlavor::NotClassified
  }

  // get event candidate
  if(!this->fEvent->retrieve(this->mCand, this->mCandName.Data()).isSuccess()){
    DEBUGclass("failed to retrieve candidates!");
    return 0;
  }
  // DEBUGclass("retrieve candidates! %s",this->mCandName.Data());
  const xAOD::CompositeParticle *evtCand = this->mCand->at(0);
  // DEBUGclass(" this->mCand->size() %i",this->mCand->size());

  if(this->mCand->size()==0) return false;

  // Determine flavor of candidate leptons from sample tags
  bool isLeadE;
  if(!this->fSample->getTagBool("~isLeadE",isLeadE)) {
    ERROR("Couldn't retrieve lepton flavor tag!");
    return FakeFlavor::NotClassified;
  }

  bool isLeadM;
  if(!this->fSample->getTagBool("~isLeadM",isLeadM)) {
    ERROR("Couldn't retrieve lepton flavor tag!");
    return FakeFlavor::NotClassified;
  }

  bool isSubE;
  if(!this->fSample->getTagBool("~isSubE",isSubE)) {
    ERROR("Couldn't retrieve lepton flavor tag!");
    return FakeFlavor::NotClassified;
  }

  bool isSubM;
  if(!this->fSample->getTagBool("~isSubM",isSubM)) {
    ERROR("Couldn't retrieve lepton flavor tag!");
    return FakeFlavor::NotClassified;
  }

  // Classify event (fake-e or fake-mu) and get fake candidate,
  // depending on index

  bool isFakeE = false;
  bool isFakeM = false;
  const xAOD::IParticle* fakeCandidate = 0;

  if (mIndex == FakeIndex::Leading) {

    isFakeE = isLeadE;
    isFakeM = isLeadM;
    fakeCandidate = evtCand->part(0);

  } else if (mIndex == FakeIndex::Subleading) {

    isFakeE = isSubE;
    isFakeM = isSubM;
    fakeCandidate = evtCand->part(1);

  } else if (mIndex == FakeIndex::Other) {

    isFakeE = (evtCand->nOtherElectrons() > 0);
    isFakeM = (evtCand->nOtherMuons() > 0);
    fakeCandidate = evtCand->otherPart(0);

  }

  //Assign a flavour to the event
  if         (mMode == FakeClassifierMode::MCTruthClassifier) this->feventFakeFlavor = getFlavourMCTruthClassifier(fakeCandidate, isFakeE, isFakeM);
  else if    (mMode == FakeClassifierMode::Run1)              this->feventFakeFlavor = getFlavourRun1(fakeCandidate);

  this->fCachedEntry = this->getCurrentEntry();
  DEBUGclass("Created new set of cached values in instance '%s'",this->GetName());

  return true;
#endif

}

//______________________________________________________________________________________________
FakeFlavor HWWFakeFlavorZjets::getFlavourMCTruthClassifier(const xAOD::IParticle* fakeCandidate, const bool isFakeE, const bool isFakeM) const {
  // get fake flavour with MCTruthClassifier
  //Get the fake candidate origin information
  int fake_truthType   = -1;
  int fake_truthOrigin = -1;
  int fake_firstEgMotherPdgId = -999; //Default PDG-ID value
  int fake_charge = 0;

  if (isFakeE){
    fake_truthType = fakeCandidate->auxdata<int>("firstEgMotherTruthType");
    fake_truthOrigin = fakeCandidate->auxdata<int>("firstEgMotherTruthOrigin");
    fake_firstEgMotherPdgId = fakeCandidate->auxdata<int>("firstEgMotherPdgId");

    const xAOD::Electron* electronFake = static_cast<const xAOD::Electron*>(fakeCandidate);
    fake_charge = electronFake->charge();
  }

  if (isFakeM){
    fake_truthType   = fakeCandidate->auxdata<int>("hwwTruthType");
    fake_truthOrigin = fakeCandidate->auxdata<int>("hwwTruthOrigin");

    const xAOD::Muon* muonFake = static_cast<const xAOD::Muon*>(fakeCandidate);
    fake_charge = muonFake->charge();
  }

  //---------------------------------------------//
  //      Now classify the fake candidate        //
  //---------------------------------------------//

  //Check if it's prompt
  bool prompt = false;
  bool chargeFlip = false;
  bool promptIsolated = false;

  if ( (fake_truthType == MCTruthPartClassifier::ParticleType::IsoElectron || fake_truthType == MCTruthPartClassifier::ParticleType::IsoMuon)
        && (fake_truthOrigin == MCTruthPartClassifier::ParticleOrigin::Higgs || fake_truthOrigin == MCTruthPartClassifier::ParticleOrigin::WBoson ||
	    fake_truthOrigin == MCTruthPartClassifier::ParticleOrigin::ZBoson || fake_truthOrigin == MCTruthPartClassifier::ParticleOrigin::DiBoson) ) {

    prompt = true;

    if (isFakeE) {
      if ( fake_firstEgMotherPdgId*fake_charge > 0 ) {
        chargeFlip = true;
      }
    }

    if (!chargeFlip) {
      promptIsolated = true;
    }
  }

  //If it's non-prompt, then classify fake type
  bool HFb = false;
  bool HFc = false;
  bool LFgamma = false;
  bool pi0 = false;
  bool Kaon = false;
  bool LFrest = false;
  bool NonDefined = false;

  if (!prompt) {

    switch (fake_truthOrigin){

      //Check for HFb;
    case MCTruthPartClassifier::ParticleOrigin::BottomMeson  :
    case MCTruthPartClassifier::ParticleOrigin::BBbarMeson   :
    case MCTruthPartClassifier::ParticleOrigin::BottomBaryon :
      HFb = true;
      break;

      // Check for HFc
    case MCTruthPartClassifier::ParticleOrigin::CharmedMeson  :
    case MCTruthPartClassifier::ParticleOrigin::CCbarMeson    :
    case MCTruthPartClassifier::ParticleOrigin::CharmedBaryon :
      HFc = true;
      break;

      // Check for LFgamma
    case MCTruthPartClassifier::ParticleOrigin::WBoson     :
      // There were events in W->mv which had fakes coming from
      // an isolated photon originating from the W boson
      if (fake_truthType == MCTruthPartClassifier::ParticleType::IsoPhoton){
	      LFgamma = true;
      }
      break;

    case MCTruthPartClassifier::ParticleOrigin::SinglePhot :
    case MCTruthPartClassifier::ParticleOrigin::PhotonConv :
    case MCTruthPartClassifier::ParticleOrigin::ElMagProc  :
    case MCTruthPartClassifier::ParticleOrigin::DalitzDec  :
    case MCTruthPartClassifier::ParticleOrigin::UndrPhot   :
    case MCTruthPartClassifier::ParticleOrigin::BremPhot   :
    case MCTruthPartClassifier::ParticleOrigin::ISRPhot    :
    case MCTruthPartClassifier::ParticleOrigin::FSRPhot    :
      LFgamma = true;
      break;

      // check for pi0
      // Used to be in LFgamma category, but
      // separate out now because the suspicion is that
      // these fall into light flavor category in Run1Scheme
    case MCTruthPartClassifier::ParticleOrigin::PiZero     :
      pi0 = true;
      break;

      // check for Kaon
    case MCTruthPartClassifier::ParticleOrigin::KaonDecay :
      Kaon = true;
      break;

      // Check for LFrest
    case MCTruthPartClassifier::ParticleOrigin::LightMeson   :
    case MCTruthPartClassifier::ParticleOrigin::LightBaryon  :
    case MCTruthPartClassifier::ParticleOrigin::PionDecay    :
    case MCTruthPartClassifier::ParticleOrigin::TauLep       :
    case MCTruthPartClassifier::ParticleOrigin::StrangeMeson :
    case MCTruthPartClassifier::ParticleOrigin::StrangeBaryon:
      LFrest = true;
      break;

      // Check for NonDefined origin
    case MCTruthPartClassifier::ParticleOrigin::NonDefined :
      NonDefined = true;
      break;

    default :
      std::cout << "Warning - Fakable object was non-prompt, but fake type was not assigned! Truth type/origin: " << fake_truthType << "/" << fake_truthOrigin << std::endl;
    }
  }

  //Assign a flavour to the event
  FakeFlavor eventFlavor = FakeFlavor::NotClassified;
  if (promptIsolated) eventFlavor = FakeFlavor::Prompt;
  else if (chargeFlip) eventFlavor = FakeFlavor::ChargeFlip;

  else if (isFakeE && HFb) eventFlavor = FakeFlavor::EL_HFb;
  else if (isFakeM && HFb) eventFlavor = FakeFlavor::MU_HFb;

  else if (isFakeE && HFc) eventFlavor = FakeFlavor::EL_HFc;
  else if (isFakeM && HFc) eventFlavor = FakeFlavor::MU_HFc;

  else if (isFakeE && LFgamma) eventFlavor = FakeFlavor::EL_LFgamma;
  else if (isFakeE && pi0)     eventFlavor = FakeFlavor::EL_pi0;

  else if (isFakeE && Kaon) eventFlavor = FakeFlavor::EL_Kaon;
  else if (isFakeM && Kaon) eventFlavor = FakeFlavor::MU_Kaon;

  else if (isFakeE && LFrest) eventFlavor = FakeFlavor::EL_LFrest;
  else if (isFakeM && LFrest) eventFlavor = FakeFlavor::MU_LFrest;

  else if (isFakeE && NonDefined) eventFlavor = FakeFlavor::EL_NonDefined_Origin;
  else if (isFakeM && NonDefined) eventFlavor = FakeFlavor::MU_NonDefined_Origin;

  else std::cout << "Warning - Fake Flavor not assigned to event! eventFlavor remains FakeFlavor::NotClassified." << std::endl;


  return eventFlavor;

}
//______________________________________________________________________________________________
FakeFlavorRun1 HWWFakeFlavorZjets::getFlavourRun1(const xAOD::IParticle* fakeCandidate) const {
  /**  get fake flavour with s method from run1 (implemented by Javier) **/
  FakeFlavorRun1 fakeFlavor = FakeFlavorRun1::notClassified;
  const int flavourTag = fakeCandidate->auxdata<int>("flavourTag");
  if (flavourTag >= 1 && flavourTag <= 10) return static_cast<FakeFlavorRun1>(flavourTag); // if value is sensible, return
  return fakeFlavor;
  // if (flavourTag == 1)      fakeFlavor = FakeFlavorRun1::bottomLeptonic;
  // else if (flavourTag == 2) fakeFlavor = FakeFlavorRun1::bottomHadronic;
  //            =  1,
  // bottomHadronic           =  2,
  // charmLeptonic            =  3,
  // charmHadronic            =  4,
  // strangeLeptonic          =  5,
  // strangeHadronic          =  6,
  // lightLeptonic           =  7,
  // lightHadronic           =  8,
  // otherLeptonic           =  9,
  // otherHadronic           =  10


}
//______________________________________________________________________________________________

double HWWFakeFlavorZjets::getValue() const {
  // value retrieval function, called on every event for every cut and histogram
  DEBUGclass("entering function");

  // the TQEventObservable only works in ASG_RELEASE RootCore, hence
  // we encapsulate the implementation in an ifdef/ifndef block
  #ifndef ASG_RELEASE
  #warning "using plain ROOT compilation scheme - please add '-DASG_RELEASE' to your packages 'Makefile.RootCore'"
  return std::numeric_limits<double>::quiet_NaN();
  #else 

  // If this is the first time getValue is called on the event,
  if (this->fCachedEntry != this->getCurrentEntry()) {
    // Find the fake flavor of the event
    if (!this->makeFlavorCache()) {
      ERROR("Failed to classify event!");
      return std::numeric_limits<double>::quiet_NaN();
    }
  }
  
  DEBUGclass("returning");
  return static_cast<double>(this->feventFakeFlavor);
  #endif
}

HWWFakeFlavorZjets::HWWFakeFlavorZjets(const TString& name, const int classifierMode, const int fakeIndex):
TQEventObservable(name),
mMode(static_cast<FakeClassifierMode>(classifierMode)),
mIndex(static_cast<FakeIndex>(fakeIndex))
{
  // constructor with name argument
  DEBUGclass("constructor called with '%s'",name.Data());
  TString str_mode;
  TString str_index;

  if (mMode == FakeClassifierMode::MCTruthClassifier) str_mode = "MCTruthClassifier";
  else if (mMode == FakeClassifierMode::Run1)         str_mode = "Run1";
  else {
    throw std::runtime_error("ERROR creating HWWFakeFlavorZjets object :: mode of running must be 0 (MCTruthClassifier, default) or 1 (Run1). Check your argument passed to constructor");
  }

  if (mIndex == FakeIndex::Leading)         str_index = "leading";
  else if (mIndex == FakeIndex::Subleading) str_index = "subleading";
  else if (mIndex == FakeIndex::Other)      str_index = "other";
  else {
    throw std::runtime_error("ERROR creating HWWFakeFlavorZjets object :: index of fake must be 1 (leading), 2 (subleading), or 3 (other, default). Check your argument passed to constructor");
  }

  INFOclass("Running with classifier mode '%s' and fake index '%s'", str_mode.Data(), str_index.Data());
}
