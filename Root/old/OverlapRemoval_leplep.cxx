#include "Htautau2015/OverlapRemoval_leplep.h"
#include <limits>
#include <algorithm>
#include <vector>
#include <string>
#include <chrono>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(OverlapRemoval_leplep)

//______________________________________________________________________________________________
OverlapRemoval_leplep::OverlapRemoval_leplep(const TString& expression):TQTreeObservable(expression) {
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  SetName(TQObservable::makeObservableName(expression));
  setExpression(expression);
  
  if(expression.Contains("JetIdx_")){
    jetIndexMode=true;
    jetIndex=TString(expression(expression.First("_")+1,2)).Atoi();
  } else if(expression.Contains("ElIdx_")){
    elIndexMode=true;
    elIndex=TString(expression(expression.First("_")+1,2)).Atoi();
  } else if(expression.Contains("MuIdx_")){
    muIndexMode=true;
    muIndex=TString(expression(expression.First("_")+1,2)).Atoi();
  } else if(expression.Contains("TauIdx_")){
    tauIndexMode=true;
    tauIndex=TString(expression(expression.First("_")+1,2)).Atoi();
  } else if(expression.Contains("LeptonIdx_")){
    leptonIndexMode=true;
    leptonIndex=TString(expression(expression.First("_")+1,2)).Atoi();
  }
  
  if(expression.Contains("JetN")){
    jetNMode=true;
  } else if(expression.Contains("ElN")){
    elNMode=true;
  } else if(expression.Contains("MuN")){
    muNMode=true;
  } else if(expression.Contains("TauN")){
    tauNMode=true;
  } else if(expression.Contains("LeptonN")){
    leptonNMode=true;
  }
  
  if (debug) {
  std::cout << "constructor " << expression.Data();
//  std::cout << " " << TString(expression(expression.First("_")+1,2).String()).Atoi();
//  std::cout << " " << TString(expression(expression.First("_")+1,2));
//  std::cout << " " << expression.First("_")+1;
  std::cout << " " << jetIndexMode << " " << jetIndex;
  std::cout << " " << elIndexMode << " " << elIndex;
  std::cout << " " << muIndexMode << " " << muIndex;
  std::cout << " " << tauIndexMode << " " << tauIndex;
  std::cout << " " << leptonIndexMode << " " << leptonIndex;
  std::cout << " " << jetNMode << " " << elNMode << " " << muNMode << " " << tauNMode << " " << leptonNMode << std::endl;
}
  ovl = new OverlapRemovalAlg_leplep();  
}

//______________________________________________________________________________________________

OverlapRemoval_leplep::OverlapRemoval_leplep(){
  // default constructor
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

OverlapRemoval_leplep::~OverlapRemoval_leplep(){
  // default destructor
  DEBUGclass("destructor called");
} 


//______________________________________________________________________________________________

TObjArray* OverlapRemoval_leplep::getBranchNames() const {
  // retrieve the list of branch names 
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();
  bnames->SetOwner(false);

  
  bnames->Add(new TObjString("run_number"));  
  bnames->Add(new TObjString("event_number"));  

  return bnames;
}

//______________________________________________________________________________________________

double OverlapRemoval_leplep::getValue() const {
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

  //std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  double retval=-999;
  
  long current_event_number=m_event_number->EvalInstance();
  long current_run_number=m_run_number->EvalInstance();

  if (debug) std::cout << "event " << current_run_number << " "  << current_event_number << std::endl;
  
  if (jetIndexMode) {
      ovl->getJetIdx(jetIndex);
  } else if (elIndexMode) {
      ovl->getElIdx(elIndex);
  } else if (muIndexMode) {
      ovl->getJetIdx(muIndex);
  } else if (tauIndexMode) {
      ovl->getTauIdx(tauIndex);
  } else if (leptonIndexMode) {
      ovl->getLeptonIdx(leptonIndex);
  }
  
  if (jetNMode) retval         = ovl->getNJet();
  else if (elNMode) retval     = ovl->getNEl();
  else if (muNMode) retval     = ovl->getNMu();
  else if (tauNMode) retval    = ovl->getNTau();
  else if (leptonNMode) retval = ovl->getNLepton();

  DEBUGclass("returning");
  if (debug) std::cout << "retval " << retval << std::endl;
  //std::cout << "retval " << retval << std::endl;
  
  //std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
  //auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  //std::cout << duration << std::endl;
  return retval;
}

//______________________________________________________________________________________________

const TString& OverlapRemoval_leplep::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool OverlapRemoval_leplep::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void OverlapRemoval_leplep::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool OverlapRemoval_leplep::parseExpression(const TString& expr){
  // parse the expression
  (void) expr;
  return true;
}

//______________________________________________________________________________________________

void OverlapRemoval_leplep::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString OverlapRemoval_leplep::getActiveExpression() const {
  // retrieve the expression associated with this incarnation
  return this->getExpression(); /* you have to build the expression here */;
}

//______________________________________________________________________________________________

bool OverlapRemoval_leplep::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }
  
  debug=true;

  m_event_number = new TTreeFormula ("event_number", "event_number", this->fTree);
  m_run_number = new TTreeFormula ("run_number", "run_number", this->fTree);

  return true;
}
 
//___________________________________________________________________________________________

bool OverlapRemoval_leplep::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();
  delete m_event_number;
  delete m_run_number;
   
  delete ovl;

  return true;
}

