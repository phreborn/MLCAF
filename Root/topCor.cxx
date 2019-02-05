#include "Htautau/topCor.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
#include "TFile.h"
#include <map>

ClassImp(topCor)

//______________________________________________________________________________________________

topCor::topCor(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

topCor::~topCor(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* topCor::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("lep_0"));
  bnames->Add(new TObjString("lep_0_pt"));
  bnames->Add(new TObjString("n_bjets"));

  return bnames;
}

//______________________________________________________________________________________________

double topCor::getValue() const {
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
  double f_lep_0_pt  = this->lep_0_pt->EvalInstance();
  int    f_lep_0     = this->lep_0->EvalInstance();
  int    f_n_bjets   = this->n_bjets->EvalInstance();

  double tmp_leptonFF(1);

  if( f_lep_0==2 ) {

    if( f_n_bjets>=1 ) {
    if( f_lep_0_pt>30 && f_lep_0_pt<140 ) tmp_leptonFF = 0.89;
    if( f_lep_0_pt>140 )
        //p0                        =      1.30193   +/-   0.142016
        //p1                        =  -0.00184297   +/-   0.000662017
      tmp_leptonFF = 1.302 - 0.00184297*f_lep_0_pt;
    }

  }

  //std::cout<<" retval / r_qcd / ff_mj / ff_ew : "<< retval <<"/ "<< r_qcd <<"/ "<< ff_mj <<"/ "<< ff_ew << std::endl;

  DEBUGclass("returning");
  //return 0;
  return tmp_leptonFF;
}
//______________________________________________________________________________________________

topCor::topCor(const TString& expression):
TQTreeObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  fSysName = expression;
}

//______________________________________________________________________________________________

const TString& topCor::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool topCor::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void topCor::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool topCor::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void topCor::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString topCor::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool topCor::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  this->run_number     = new TTreeFormula( "run_number",    "run_number",    this->fTree);
  this->NOMINAL_pileup_random_run_number     = new TTreeFormula( "NOMINAL_pileup_random_run_number",    "NOMINAL_pileup_random_run_number",    this->fTree);

  this->lep_0     = new TTreeFormula( "lep_0",     "lep_0",    this->fTree);
  this->lep_0_pt  = new TTreeFormula( "lep_0_pt",  "lep_0_pt", this->fTree);
  this->n_bjets   = new TTreeFormula( "n_bjets",   "n_bjets",  this->fTree);

  return true;
}

//______________________________________________________________________________________________

bool topCor::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete this->lep_0;
  delete this->lep_0_pt;
  delete this->n_bjets;

  return true;
}
