#include "BSMtautauCAF/MTLepJet.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(MTLepJet)

//______________________________________________________________________________________________

MTLepJet::MTLepJet(){
  // default constructor
  this->setExpression(this->GetName() );
  DEBUGclass("default constructor called");
}
//______________________________________________________________________________________________

MTLepJet::MTLepJet(const TString& expression) : LepHadObservable(expression)
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

MTLepJet::~MTLepJet(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* MTLepJet::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();

  return bnames;
}

//______________________________________________________________________________________________

double MTLepJet::getValue() const {
  
  float f_lep_0_pt                = this->lep_0_pt->EvalInstance();
  float f_jet_0_pt                = this->jet_0_pt->EvalInstance();
  float f_lep_0_phi                = this->lep_0_phi->EvalInstance();
  float f_jet_0_phi                = this->jet_0_phi->EvalInstance();

  float f_lepjet_dphi = 0.0;
  f_lepjet_dphi = 3.14-std::fabs(std::fabs(f_lep_0_phi-f_jet_0_phi)-3.14);

  float retval = std::sqrt( 2.*f_lep_0_pt*(f_jet_0_pt/1000.)*(1-cos(f_lepjet_dphi)) );

  return retval;
}
//______________________________________________________________________________________________

bool MTLepJet::initializeSelf(){
  if (!LepHadObservable::initializeSelf())  return false;
  return true;
}

//______________________________________________________________________________________________

bool MTLepJet::finalizeSelf(){
  if (!LepHadObservable::finalizeSelf()) return false;
  return true;
}

//______________________________________________________________________________________________

const TString& MTLepJet::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool MTLepJet::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void MTLepJet::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
