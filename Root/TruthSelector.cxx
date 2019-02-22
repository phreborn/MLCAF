#include "BSMtautauCAF/TruthSelector.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(TruthSelector)

//______________________________________________________________________________________________

TruthSelector::TruthSelector(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

TruthSelector::~TruthSelector(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* TruthSelector::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("tau_0_truth_isHadTau"));
  bnames->Add(new TObjString("tau_0_truth_isEle"));
  bnames->Add(new TObjString("tau_0_truth_isMuon"));
  bnames->Add(new TObjString("tau_0_truth_pdgId"));
  bnames->Add(new TObjString("tau_0_truth_classifierParticleType"));

  return bnames;
}

//______________________________________________________________________________________________

double TruthSelector::getValue() const {
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

  //std::cout<<" In getValue "<<std::endl;

  int retval = -666;

  int temp_tau_0_truth_isHadTau = this->tau_0_truth_isHadTau->EvalInstance();
  int temp_tau_0_truth_isEle    = this->tau_0_truth_isEle->EvalInstance();
  int temp_tau_0_truth_isMuon   = this->tau_0_truth_isMuon->EvalInstance();
  int temp_tau_0_truth_pdgId    = this->tau_0_truth_pdgId->EvalInstance();
  int temp_tau_0_truth_type     = this->tau_0_truth_classifierParticleType->EvalInstance();

  bool isTrueEleFake = temp_tau_0_truth_isEle == 1 && temp_tau_0_truth_type == 2;
  bool isTrueMuFake  = temp_tau_0_truth_isMuon == 1 && temp_tau_0_truth_type == 6;
  bool isTrueTau     = temp_tau_0_truth_isHadTau == 1;

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

  DEBUGclass("returning");
  //return 0;
  return retval;
}
//______________________________________________________________________________________________

TruthSelector::TruthSelector(const TString& expression):
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

const TString& TruthSelector::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool TruthSelector::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void TruthSelector::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool TruthSelector::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void TruthSelector::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString TruthSelector::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool TruthSelector::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))) {
    return false;
  }

  this->tau_0_truth_isHadTau  = new TTreeFormula("tau_0_truth_isHadTau",  "tau_0_truth_isHadTau", this->fTree);
  this->tau_0_truth_isEle     = new TTreeFormula("tau_0_truth_isEle",     "tau_0_truth_isEle",    this->fTree);
  this->tau_0_truth_isMuon    = new TTreeFormula("tau_0_truth_isMuon",    "tau_0_truth_isMuon",   this->fTree);
  this->tau_0_truth_pdgId     = new TTreeFormula("tau_0_truth_pdgId",     "tau_0_truth_pdgId",    this->fTree);
  this->tau_0_truth_classifierParticleType      = new TTreeFormula("tau_0_truth_classifierParticleType",      "tau_0_truth_classifierParticleType",     this->fTree);

  return true;
}

//______________________________________________________________________________________________

bool TruthSelector::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete  this->tau_0_truth_isHadTau;
  delete  this->tau_0_truth_pdgId;
  delete  this->tau_0_truth_classifierParticleType;

  return true;
}
