#include "BSMtautauCAF/MTtot.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(MTtot)

//______________________________________________________________________________________________

MTtot::MTtot(){
  // default constructor
  this->setExpression(this->GetName() );
  DEBUGclass("default constructor called");
}
//______________________________________________________________________________________________

MTtot::MTtot(const TString& expression) : LepHadObservable(expression)
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

MTtot::~MTtot(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* MTtot::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();

  return bnames;
}

//______________________________________________________________________________________________

double MTtot::getValue() const {
  // in the rest of this function, you should retrieve the data and calculate your return value
  // here is the place where most of your custom code should go
  // a couple of comments should guide you through the process
  // when writing your code, please keep in mind that this code can be executed several times on every event
  // make your code efficient. catch all possible problems. when in doubt, contact experts!

  // here, you should calculate your return value
  // of course, you can use other data members of your observable at any time
  /* example block for TTreeFormula method:
  const double retval = this->fFormula->Eval(0.);
  */
  /* exmple block for TTree::SetBranchAddress method:
  const double retval = this->fBranch1 + this->fBranch2;
  */

  float f_lephad_mt_lep0_met      = this->lephad_mt_lep0_met->EvalInstance();
  float f_lephad_mt_lep1_met      = this->lephad_mt_lep1_met->EvalInstance();
  float f_lep_0_pt                = this->lep_0_pt->EvalInstance();
  float f_tau_0_pt                = this->tau_0_pt->EvalInstance();
  float f_lephad_dphi             = this->lephad_dphi->EvalInstance();

  float retval = std::sqrt(f_lephad_mt_lep0_met*f_lephad_mt_lep0_met + f_lephad_mt_lep1_met*f_lephad_mt_lep1_met + 2.*f_lep_0_pt*f_tau_0_pt*(1-cos(f_lephad_dphi)) );

  DEBUGclass("returning");
  return retval;
}
//______________________________________________________________________________________________

bool MTtot::initializeSelf(){
  if (!LepHadObservable::initializeSelf())  return false;
  return true;
}

//______________________________________________________________________________________________

bool MTtot::finalizeSelf(){
  if (!LepHadObservable::finalizeSelf()) return false;
  return true;
}

//______________________________________________________________________________________________

const TString& MTtot::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool MTtot::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void MTtot::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
