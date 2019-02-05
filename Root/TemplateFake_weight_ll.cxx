#include "Htautau/TemplateFake_weight_ll.h"
#include <limits>

// uncomment the following line to enable debug printouts
//#define _DEBUG_

// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(TemplateFake_weight_ll)

//______________________________________________________________________________________________

TemplateFake_weight_ll::TemplateFake_weight_ll(){
  // default constructor

  this->setExpression(this->GetName() );

  std::cout << "default constructor called" << std::endl;

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

TemplateFake_weight_ll::~TemplateFake_weight_ll(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* TemplateFake_weight_ll::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

   bnames->Add(new TObjString("weight_fake"));
   bnames->Add(new TObjString("weight_fake_err"));
   bnames->Add(new TObjString("weight_lumi"));

  return bnames;
}

//______________________________________________________________________________________________

double TemplateFake_weight_ll::getValue() const {
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

  fake_weight->GetNdata();

  double fake_weight_nom  = this->fake_weight->EvalInstance(0);

  double fake_weight = 1.;

  // check here for nom, sys up, sys down
  fake_weight *= fake_weight_nom;

  DEBUGclass("returning");

  return fake_weight;
}
//______________________________________________________________________________________________

TemplateFake_weight_ll::TemplateFake_weight_ll(const TString& expression, int systematic):
TQTreeObservable(expression),m_systematic(systematic)
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

const TString& TemplateFake_weight_ll::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool TemplateFake_weight_ll::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void TemplateFake_weight_ll::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool TemplateFake_weight_ll::parseExpression(const TString& expr){
  // parse the expression
  (void) expr;
  return true;
}

//______________________________________________________________________________________________

void TemplateFake_weight_ll::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString TemplateFake_weight_ll::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool TemplateFake_weight_ll::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  // this->bla = new TTreeFormula( "name", "formula", this->fTree);
  if (m_systematic ==0 ) {
      fake_weight_name="weight_fake";
  }
  else if (m_systematic <0) {
      fake_weight_name="(weight_fake-weight_fake_err)"
      DEBUGclass("Fake down");
  }
  else if (m_systematic >0) {
      fake_weight_name="(weight_fake+weight_fake_err)"
      DEBUGclass("Fake up");
  }
  this->fake_weight = new TTreeFormula( "fake_weight",fake_weight_name+" * weight_lumi", this->fTree);

  return true;
}

//______________________________________________________________________________________________

bool TemplateFake_weight_ll::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete this->fake_weight;

  return true;
}
