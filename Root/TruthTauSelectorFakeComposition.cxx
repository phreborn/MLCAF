#include "BSMtautauCAF/TruthTauSelectorFakeComposition.h"
#include <limits>
#include "TObjString.h"

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(TruthTauSelectorFakeComposition)



TruthTauSelectorFakeComposition::TruthTauSelectorFakeComposition(){
  this->setExpression(this->GetName());
}



TObjArray* TruthTauSelectorFakeComposition::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  TObjArray* bnames = LepHadObservable::getBranchNames();

  bnames->Add(new TObjString("tau_0_matched_isHadTau"));
  bnames->Add(new TObjString("tau_0_matched_isEle"));
  bnames->Add(new TObjString("tau_0_matched_isMuon"));
  bnames->Add(new TObjString("tau_0_matched_classifierParticleType"));
  bnames->Add(new TObjString("tau_0_matched_isJet"));
  bnames->Add(new TObjString("tau_0_matched_pdgId"));

  return bnames;
}



double TruthTauSelectorFakeComposition::getValue() const {

  if (isData()) return 1.0;

  double retval = -9999;

  int temp_tau_0_matched_isHadTau = this->tau_0_matched_isHadTau->EvalInstance();
  int temp_tau_0_matched_isEle    = this->tau_0_matched_isEle->EvalInstance();
  int temp_tau_0_matched_isMuon   = this->tau_0_matched_isMuon->EvalInstance();
  int temp_tau_0_matched_type     = this->tau_0_matched_classifierParticleType->EvalInstance();
  int temp_tau_0_matched_isJet    = this->tau_0_matched_isJet->EvalInstance();
  int temp_tau_0_matched_pdgId    = this->tau_0_matched_pdgId->EvalInstance();


  bool isTrueEleFake = temp_tau_0_matched_isEle == 1 && temp_tau_0_matched_type == 2;
  bool isTrueMuFake  = temp_tau_0_matched_isMuon == 1 && temp_tau_0_matched_type == 6;
  bool isTrueTau     = temp_tau_0_matched_isHadTau == 1;
  bool isGluonFake   = temp_tau_0_matched_pdgId == 21 && temp_tau_0_matched_isJet == 1;
  bool isBotttomFake = temp_tau_0_matched_pdgId == 5 && temp_tau_0_matched_isJet == 1;
  bool isCharmFake   = temp_tau_0_matched_pdgId == 4 && temp_tau_0_matched_isJet == 1;
  bool isUDSFake     = temp_tau_0_matched_pdgId > 0 && temp_tau_0_matched_pdgId < 4 && temp_tau_0_matched_isJet == 1;
  bool isOther       = temp_tau_0_matched_isJet == 1 && !isGluonFake && !isBotttomFake && !isCharmFake && !isUDSFake;

  if(isTrueTau) {
    retval = 30;  //Truth tau
  }
  else if(isTrueMuFake) {
    retval = 20;  //Mu fake
  }
  else if(isTrueEleFake) {
    retval = 5;   //Ele fake
  }
  else if(isGluonFake) {
    retval = 100; //Jet fake
  }
  else if(isBotttomFake) {
    retval = 200;
  }
  else if(isCharmFake) {
    retval = 300;
  }
  else if(isUDSFake) {
    retval = 400;
  }
  else if(isOther) {
    retval = 500;
  }
  else retval = -1;
  return retval;
}



TruthTauSelectorFakeComposition::TruthTauSelectorFakeComposition(const TString& expression):
LepHadObservable(expression) {
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);
}



const TString& TruthTauSelectorFakeComposition::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}



bool TruthTauSelectorFakeComposition::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}



void TruthTauSelectorFakeComposition::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}



bool TruthTauSelectorFakeComposition::initializeSelf(){
  if (!LepHadObservable::initializeSelf()) return false;

  if (!isData()) {
    this->tau_0_matched_isHadTau = new TTreeFormula("tau_0_matched_isHadTau", "tau_0_matched_isHadTau", this->fTree);
    this->tau_0_matched_isEle = new TTreeFormula("tau_0_matched_isEle", "tau_0_matched_isEle", this->fTree);
    this->tau_0_matched_isMuon = new TTreeFormula("tau_0_matched_isMuon", "tau_0_matched_isMuon", this->fTree);
    this->tau_0_matched_classifierParticleType = new TTreeFormula("tau_0_matched_classifierParticleType", "tau_0_matched_classifierParticleType", this->fTree);
    this->tau_0_matched_isJet = new TTreeFormula("tau_0_matched_isJet", "tau_0_matched_isJet", this->fTree);
    this->tau_0_matched_pdgId = new TTreeFormula("tau_0_matched_pdgId", "tau_0_matched_pdgId", this->fTree);

  }
  return true;
}



bool TruthTauSelectorFakeComposition::finalizeSelf(){
  if (! LepHadObservable::finalizeSelf()) return false;

  if (!isData()) {
    delete this->tau_0_matched_isHadTau;
    delete this->tau_0_matched_isEle;
    delete this->tau_0_matched_isMuon;
    delete this->tau_0_matched_classifierParticleType;
    delete this->tau_0_matched_isJet;
    delete this->tau_0_matched_pdgId;

  }

  return true;
}

