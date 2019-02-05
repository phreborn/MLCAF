#include "Htautau2015/DphiLL_ll_v05.h"
#include <limits>

// uncomment the following line to enable debug printouts
//#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
#include "Htautau2015/EventSelection_leplep_default.h"

ClassImp(DphiLL_ll_v05)

//______________________________________________________________________________________________

DphiLL_ll_v05::DphiLL_ll_v05(){
  // default constructor
 
  this->setExpression(this->GetName() );
  
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

DphiLL_ll_v05::~DphiLL_ll_v05(){
  // default destructor
  DEBUGclass("destructor called");
} 


//______________________________________________________________________________________________

TObjArray* DphiLL_ll_v05::getBranchNames() const {
  // retrieve the list of branch names 
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));
  
  bnames->Add(new TObjString("leptons"));
  bnames->Add(new TObjString("dilep_dphi"));

  
  return bnames;
}

//______________________________________________________________________________________________

double DphiLL_ll_v05::getValue() const {
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

  double retval = 99;

  dilep_dphi->GetNdata();

  int idx0 = -1;
  int idx1 = -1;

  idx0 = EVS->getLeptonIdx(0);
  idx1 = EVS->getLeptonIdx(1);

  int nLep = leptons->GetNdata();

  int dilepI = 0;

  //std::cout << "idx0: " << idx0 << " idx1: " << idx1 <<std::endl;
  //std::cout << "nLep: " << nLep << std::endl;

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
    //std::cout << "-> dilepI: " << dilepI << std::endl;
    retval = dilep_dphi->EvalInstance(dilepI);
  }
  //else {
  //  std::cout<< "WARNING in DphiLL:: Have negative lep indices!!" << std::endl;
  //}
  //std::cout << "x0: " << dilep_x0 << " x1: " << dilep_x1 << std::endl;
  //std::cout << "retval :" << retval << std::endl;
  //else std::cout << "Event does not pass selection!!" << std::endl;

  DEBUGclass("returning");

  return retval;
}
//______________________________________________________________________________________________

DphiLL_ll_v05::DphiLL_ll_v05(const TString& expression):
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

const TString& DphiLL_ll_v05::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool DphiLL_ll_v05::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void DphiLL_ll_v05::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool DphiLL_ll_v05::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void DphiLL_ll_v05::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString DphiLL_ll_v05::getActiveExpression() const {
  // retrieve the expression associated with this incarnation
  
  return this->getExpression();
}

//______________________________________________________________________________________________

bool DphiLL_ll_v05::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  // this->bla = new TTreeFormula( "name", "formula", this->fTree);

  this->leptons = new TTreeFormula( "leptons", "leptons", this->fTree);   
  this->dilep_dphi = new TTreeFormula("dilep_dphi", "dilep_dphi", this->fTree);

  EVS = new EventSelection_leplep_default();

  return true;
}
 
//______________________________________________________________________________________________

bool DphiLL_ll_v05::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();
  
  delete this->leptons;
  delete this->dilep_dphi;
  delete EVS;


  return true;
}
