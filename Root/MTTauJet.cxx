#include "BSMtautauCAF/MTTauJet.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(MTTauJet)

//______________________________________________________________________________________________

MTTauJet::MTTauJet(){
  // default constructor
  this->setExpression(this->GetName() );
  DEBUGclass("default constructor called");
}
//______________________________________________________________________________________________

MTTauJet::MTTauJet(const TString& expression) : LepHadObservable(expression)
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

MTTauJet::~MTTauJet(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* MTTauJet::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();

  return bnames;
}

//______________________________________________________________________________________________

double MTTauJet::getValue() const {
  
  float f_tau_0_pt                = this->tau_0_pt->EvalInstance();
  float f_jet_0_pt                = this->jet_0_pt->EvalInstance();
  float f_tau_0_phi                = this->tau_0_phi->EvalInstance();
  float f_jet_0_phi                = this->jet_0_phi->EvalInstance();

  float f_taujet_dphi = 0.0;
  f_taujet_dphi = 3.14-std::fabs(std::fabs(f_tau_0_phi-f_jet_0_phi)-3.14);

  float retval = std::sqrt( 2.*f_tau_0_pt*(f_jet_0_pt/1000.)*(1-cos(f_taujet_dphi)) );

  return retval;
}
//______________________________________________________________________________________________

bool MTTauJet::initializeSelf(){
  if (!LepHadObservable::initializeSelf())  return false;
  return true;
}

//______________________________________________________________________________________________

bool MTTauJet::finalizeSelf(){
  if (!LepHadObservable::finalizeSelf()) return false;
  return true;
}

//______________________________________________________________________________________________

const TString& MTTauJet::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool MTTauJet::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void MTTauJet::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
