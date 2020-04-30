#include "BSMtautauCAF/InvMTauJet.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(InvMTauJet)

//______________________________________________________________________________________________

InvMTauJet::InvMTauJet(){
  // default constructor
  this->setExpression(this->GetName() );
  DEBUGclass("default constructor called");
}
//______________________________________________________________________________________________

InvMTauJet::InvMTauJet(const TString& expression) : LepHadObservable(expression)
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

InvMTauJet::~InvMTauJet(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* InvMTauJet::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();

  return bnames;
}

//______________________________________________________________________________________________

double InvMTauJet::getValue() const {
  
  float f_tau_0_px                = this->tau_0_px->EvalInstance();
  float f_tau_0_py                = this->tau_0_py->EvalInstance();
  float f_tau_0_pz                = this->tau_0_pz->EvalInstance();
  float f_tau_0_E                 = this->tau_0_E->EvalInstance();
  float f_jet_0_pt                = this->jet_0_pt->EvalInstance();
  float f_jet_0_phi                = this->jet_0_phi->EvalInstance();
  float f_jet_0_eta                = this->jet_0_eta->EvalInstance();
  float f_jet_0_m                = this->jet_0_m->EvalInstance();

  float f_jet_0_E = std::sqrt( (f_jet_0_m/1000.)*(f_jet_0_m/1000.)+(f_jet_0_pt/1000.)*(f_jet_0_pt/1000.)+(f_jet_0_pt/1000.)*(f_jet_0_pt/1000.)*(cosh(f_jet_0_eta))*(cosh(f_jet_0_eta)) );
  float f_jet_0_px = (f_jet_0_pt/1000.)*cos(f_jet_0_phi);
  float f_jet_0_py = (f_jet_0_pt/1000.)*sin(f_jet_0_phi);
  float f_jet_0_pz = (f_jet_0_pt/1000.)*cosh(f_jet_0_eta);
  
  float retval = std::sqrt( (f_jet_0_E+f_tau_0_E)*(f_jet_0_E+f_tau_0_E)-(f_jet_0_px+f_tau_0_px)*(f_jet_0_px+f_tau_0_px)-(f_jet_0_py+f_tau_0_py)*(f_jet_0_py+f_tau_0_py)-(f_jet_0_pz+f_tau_0_pz)*(f_jet_0_pz+f_tau_0_pz) );

  return retval;
}
//______________________________________________________________________________________________

bool InvMTauJet::initializeSelf(){
  if (!LepHadObservable::initializeSelf())  return false;
  return true;
}

//______________________________________________________________________________________________

bool InvMTauJet::finalizeSelf(){
  if (!LepHadObservable::finalizeSelf()) return false;
  return true;
}

//______________________________________________________________________________________________

const TString& InvMTauJet::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool InvMTauJet::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void InvMTauJet::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
