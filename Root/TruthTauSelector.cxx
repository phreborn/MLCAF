#include "BSMtautauCAF/TruthTauSelector.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(TruthTauSelector)



TruthTauSelector::TruthTauSelector(){
  this->setExpression(this->GetName());
}



TObjArray* TruthTauSelector::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  TObjArray* bnames = LepHadObservable::getBranchNames();

  bnames->Add(new TObjString("tau_0_matched_isHadTau"));
  bnames->Add(new TObjString("tau_0_matched_isEle"));
  bnames->Add(new TObjString("tau_0_matched_isMuon"));
  bnames->Add(new TObjString("tau_0_matched_classifierParticleType"));

  return bnames;
}



double TruthTauSelector::getValue() const {

  if (isData()) return 1.0;

  double retval = -9999;

  int temp_tau_0_matched_isHadTau = this->tau_0_matched_isHadTau->EvalInstance();
  int temp_tau_0_matched_isEle    = this->tau_0_matched_isEle->EvalInstance();
  int temp_tau_0_matched_isMuon   = this->tau_0_matched_isMuon->EvalInstance();
  int temp_tau_0_matched_type     = this->tau_0_matched_classifierParticleType->EvalInstance();

  bool isTrueEleFake = temp_tau_0_matched_isEle == 1 && temp_tau_0_matched_type == 2;
  bool isTrueMuFake  = temp_tau_0_matched_isMuon == 1 && temp_tau_0_matched_type == 6;
  bool isTrueTau     = temp_tau_0_matched_isHadTau == 1;

  if(isTrueTau) {
    retval = 30;  //Truth tau
  }
  else if(isTrueMuFake) {
    retval = 20;  //Mu fake
  }
  else if(isTrueEleFake) {
    retval = 5;   //Ele fake
  }
  else {
    retval = -30; //Jet fake
  }

  return retval;
}



TruthTauSelector::TruthTauSelector(const TString& expression):
LepHadObservable(expression) {
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);
}



const TString& TruthTauSelector::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}



bool TruthTauSelector::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}



void TruthTauSelector::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}



bool TruthTauSelector::initializeSelf(){
  if (!LepHadObservable::initializeSelf()) return false;

  if (!isData()) {
    this->tau_0_matched_isHadTau = new TTreeFormula("tau_0_matched_isHadTau", "tau_0_matched_isHadTau", this->fTree);
    this->tau_0_matched_isEle = new TTreeFormula("tau_0_matched_isEle", "tau_0_matched_isEle", this->fTree);
    this->tau_0_matched_isMuon = new TTreeFormula("tau_0_matched_isMuon", "tau_0_matched_isMuon", this->fTree);
    this->tau_0_matched_classifierParticleType = new TTreeFormula("tau_0_matched_classifierParticleType", "tau_0_matched_classifierParticleType", this->fTree);
  }
  return true;
}



bool TruthTauSelector::finalizeSelf(){
  if (! LepHadObservable::finalizeSelf()) return false;

  if (!isData()) {
    delete this->tau_0_matched_isHadTau;
    delete this->tau_0_matched_isEle;
    delete this->tau_0_matched_isMuon;
    delete this->tau_0_matched_classifierParticleType;
  }

  return true;
}
