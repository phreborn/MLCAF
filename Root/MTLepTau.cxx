#include "BSMtautauCAF/MTLepTau.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(MTLepTau)

//______________________________________________________________________________________________

MTLepTau::MTLepTau(){
  // default constructor
  this->setExpression(this->GetName() );
  DEBUGclass("default constructor called");
}
//______________________________________________________________________________________________

MTLepTau::MTLepTau(const TString& expression) : LepHadObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

}

//______________________________________________________________________________________________

MTLepTau::~MTLepTau(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* MTLepTau::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();

  return bnames;
}

//______________________________________________________________________________________________

double MTLepTau::getValue() const {
  
  float f_lep_0_pt                = this->lep_0_pt->EvalInstance();
  float f_tau_0_pt                = this->tau_0_pt->EvalInstance();
  float f_lephad_dphi             = this->lephad_dphi->EvalInstance();

  //float retval = std::sqrt( 2.*f_lep_0_pt*f_tau_0_pt*(1-cos(f_lephad_dphi)) );
  float retval = LepHadObservable::TransverseMass(f_lep_0_pt, f_tau_0_pt, f_lephad_dphi);

  return retval;
}
//______________________________________________________________________________________________

bool MTLepTau::initializeSelf(){
  if (!LepHadObservable::initializeSelf())  return false;
  return true;
}

//______________________________________________________________________________________________

bool MTLepTau::finalizeSelf(){
  if (!LepHadObservable::finalizeSelf()) return false;
  return true;
}

//______________________________________________________________________________________________

const TString& MTLepTau::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool MTLepTau::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void MTLepTau::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
