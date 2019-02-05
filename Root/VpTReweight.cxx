#include "Htautau/VpTReweight.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(VpTReweight)

//______________________________________________________________________________________________

VpTReweight::VpTReweight(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

VpTReweight::~VpTReweight(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* VpTReweight::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(false);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("lep_0_pt"));
  bnames->Add(new TObjString("lep_0_phi"));
  bnames->Add(new TObjString("met_reco_etx"));
  bnames->Add(new TObjString("met_reco_ety"));


  return bnames;
}

//______________________________________________________________________________________________

double VpTReweight::getValue() const {
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

  double value_of_lep_0_pt     = this->lep_0_pt->EvalInstance();
  double value_of_lep_0_phi    = this->lep_0_phi->EvalInstance();
  double value_of_met_reco_etx = this->met_reco_etx->EvalInstance();
  double value_of_met_reco_ety = this->met_reco_ety->EvalInstance();

  double value_of_lepmet_pt_1 = value_of_lep_0_pt*cos(value_of_lep_0_phi) + value_of_met_reco_etx;
  double value_of_lepmet_pt_2 = value_of_lep_0_pt*sin(value_of_lep_0_phi) + value_of_met_reco_ety;

  double value_of_lepmet_pt = sqrt( value_of_lepmet_pt_1*value_of_lepmet_pt_1 + value_of_lepmet_pt_2*value_of_lepmet_pt_2 );

  double retval = 1;
  //double retval = 0.912 + 0.00254 * value_of_lep_0_pt;
  //

  DEBUGclass("returning");
  return retval;
}
//______________________________________________________________________________________________

VpTReweight::VpTReweight(const TString& expression):
TQTreeObservable(expression)
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

const TString& VpTReweight::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool VpTReweight::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void VpTReweight::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool VpTReweight::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void VpTReweight::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString VpTReweight::getActiveExpression() const {
  // retrieve the expression associated with this incarnation
  return this->getExpression();
}

//______________________________________________________________________________________________

bool VpTReweight::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  this->lep_0_pt     = new TTreeFormula( "lep_0_pt",     "lep_0_pt",     this->fTree);
  this->lep_0_phi    = new TTreeFormula( "lep_0_phi",    "lep_0_phi",    this->fTree);
  this->met_reco_etx = new TTreeFormula( "met_reco_etx", "met_reco_etx", this->fTree);
  this->met_reco_ety = new TTreeFormula( "met_reco_ety", "met_reco_ety", this->fTree);

  return true;
}

//______________________________________________________________________________________________

bool VpTReweight::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete this->lep_0_pt;
  delete this->lep_0_phi;
  delete this->met_reco_etx;
  delete this->met_reco_ety;

  return true;
}
