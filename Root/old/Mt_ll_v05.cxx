#include "Htautau2015/Mt_ll_v05.h"
#include <limits>

// uncomment the following line to enable debug printouts
//#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
#include "Htautau2015/EventSelection_leplep_default.h"
#include "Htautau2015/EventSelection_leplep_fake.h"
#include "TLorentzVector.h"

ClassImp(Mt_ll_v05)

//______________________________________________________________________________________________

Mt_ll_v05::Mt_ll_v05(){
  // default constructor
 
  this->setExpression(this->GetName() );
  
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

Mt_ll_v05::~Mt_ll_v05(){
  // default destructor
  DEBUGclass("destructor called");
} 


//______________________________________________________________________________________________

TObjArray* Mt_ll_v05::getBranchNames() const {
  // retrieve the list of branch names 
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));
  
  bnames->Add(new TObjString("leptons"));
  bnames->Add(new TObjString("dilep_mt_lep0_met"));
  
  return bnames;
}

//______________________________________________________________________________________________

double Mt_ll_v05::getValue() const {
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

  int retval = -99;

  leptons->GetNdata();
  dilep_mt_lep0_met->GetNdata();


  int idx0 = -1;
  int idx1 = -1;

  if(useFakeSelec){
    idx0 = EVS_fake->getLeptonIdx(0);
    idx1 = EVS_fake->getLeptonIdx(1);
  }
  else {
    idx0 = EVS->getLeptonIdx(0);
    idx1 = EVS->getLeptonIdx(1);
  }

  int nLep = leptons->GetNdata();

  int dilepI = 0;

  if(idx0 >=0 && idx1>=0){
    for(uint ii=0; ii < nLep; ++ii) {
      bool leave = false;
      for(uint jj=ii+1; jj < nLep; ++jj) {
	if(idx0==ii && idx1==jj) {
          leave = true;
          break;
	}
        ++dilepI;
      }
      if(leave) break;
    }
    retval = dilep_mt_lep0_met->EvalInstance(dilepI);
  }

  DEBUGclass("returning");

  return retval;
}
//______________________________________________________________________________________________

Mt_ll_v05::Mt_ll_v05(const TString& expression):
TQTreeObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  if(expression.Contains("fake")){
    useFakeSelec = true;
  }

}

//______________________________________________________________________________________________

const TString& Mt_ll_v05::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool Mt_ll_v05::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void Mt_ll_v05::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool Mt_ll_v05::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void Mt_ll_v05::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString Mt_ll_v05::getActiveExpression() const {
  // retrieve the expression associated with this incarnation
  
  return this->getExpression();
}

//______________________________________________________________________________________________

bool Mt_ll_v05::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  // this->bla = new TTreeFormula( "name", "formula", this->fTree);
  
  this->leptons = new TTreeFormula( "leptons", "leptons", this->fTree);
  this->dilep_mt_lep0_met = new TTreeFormula("dilep_mt_lep0_met", "dilep_mt_lep0_met", this->fTree);

  EVS = new EventSelection_leplep_default();
  EVS_fake = new EventSelection_leplep_fake();

  return true;
}
 
//______________________________________________________________________________________________

bool Mt_ll_v05::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();
  
  delete this->leptons;  
  delete this->dilep_mt_lep0_met;
  delete EVS;
  delete EVS_fake;


  return true;
}
