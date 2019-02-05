#include "Htautau/BSMRandomBlind.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(BSMRandomBlind)

//______________________________________________________________________________________________

BSMRandomBlind::BSMRandomBlind(){
  // default constructor
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

BSMRandomBlind::~BSMRandomBlind(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* BSMRandomBlind::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();
  bnames->SetOwner(false);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("event_number"));

  if (!fOptionName.Contains("data") ) {
    bnames->Add(new TObjString("NOMINAL_pileup_random_event_number"));
  }

  return bnames;
}

//______________________________________________________________________________________________

double BSMRandomBlind::getValue() const {
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

  UInt_t    event_number = this->event_number->EvalInstance();

  rRandomGenerator->SetSeed(event_number);
  double retval = rRandomGenerator->Rndm();

  DEBUGclass("returning");
  return retval;
}
//______________________________________________________________________________________________

BSMRandomBlind::BSMRandomBlind(const TString& expression):
TQTreeObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  fOptionName = expression;
}

//______________________________________________________________________________________________

const TString& BSMRandomBlind::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool BSMRandomBlind::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void BSMRandomBlind::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool BSMRandomBlind::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void BSMRandomBlind::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString BSMRandomBlind::getActiveExpression() const {
  // retrieve the expression associated with this incarnation
  return "" ;/* you have to build the expression here */;
}

//______________________________________________________________________________________________

bool BSMRandomBlind::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  this->event_number = new TTreeFormula( "event_number", "event_number", this->fTree);

  rRandomGenerator = new TRandom3();

  return true;
}

//______________________________________________________________________________________________

bool BSMRandomBlind::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete  this->event_number;
  delete  rRandomGenerator;

  return true;
}
