#include "BSMtautauCAF/TruthLepSelector.h"
#include <limits>
#include "TObjString.h"

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(TruthLepSelector)



TruthLepSelector::TruthLepSelector(){
  this->setExpression(this->GetName());
}



TObjArray* TruthLepSelector::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  TObjArray* bnames = LepHadObservable::getBranchNames();

  bnames->Add(new TObjString("lep_0_matched_isHad"));
  bnames->Add(new TObjString("lep_0_matched_pdgId"));
  bnames->Add(new TObjString("lep_0_matched_classifierParticleType"));

  return bnames;
}



double TruthLepSelector::getValue() const {

  if (isData()) return 1.0;

  double retval = -9999;

  int temp_lep_0_matched_isHad = this->lep_0_matched_isHad->EvalInstance();
  int temp_lep_0_matched_pdgId    = this->lep_0_matched_pdgId->EvalInstance();
  int temp_lep_0_matched_type     = this->lep_0_matched_classifierParticleType->EvalInstance();

  bool isTrueEl  = fabs(temp_lep_0_matched_pdgId) == 11 && temp_lep_0_matched_type == 2;
  bool isTrueMu  = fabs(temp_lep_0_matched_pdgId) == 13 && temp_lep_0_matched_type == 6;

  if(isTrueEl) {
    retval = 10;  //Truth ele
  }
  else if(isTrueMu) {
    retval = 20;  //Truth mu
  }
  else {
    retval = 30;
  }

  return retval;
}



TruthLepSelector::TruthLepSelector(const TString& expression):
LepHadObservable(expression) {
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);
}



const TString& TruthLepSelector::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}



bool TruthLepSelector::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}



void TruthLepSelector::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}



bool TruthLepSelector::initializeSelf(){
  if (!LepHadObservable::initializeSelf()) return false;

  if (!isData()) {
    this->lep_0_matched_isHad = new TTreeFormula("lep_0_matched_isHad", "lep_0_matched_isHad", this->fTree);
    this->lep_0_matched_pdgId = new TTreeFormula("lep_0_matched_pdgId", "lep_0_matched_pdgId", this->fTree);
    this->lep_0_matched_classifierParticleType = new TTreeFormula("lep_0_matched_classifierParticleType", "lep_0_matched_classifierParticleType", this->fTree);
  }
  return true;
}



bool TruthLepSelector::finalizeSelf(){
  if (! LepHadObservable::finalizeSelf()) return false;

  if (!isData()) {
    delete this->lep_0_matched_isHad;
    delete this->lep_0_matched_pdgId;
    delete this->lep_0_matched_classifierParticleType;
  }

  return true;
}

