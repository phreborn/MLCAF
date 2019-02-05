#include "Htautau2015/TruthMatchingLep_ll_v05.h"
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

ClassImp(TruthMatchingLep_ll_v05)

//______________________________________________________________________________________________

TruthMatchingLep_ll_v05::TruthMatchingLep_ll_v05(){
  // default constructor
 
  this->setExpression(this->GetName() );
  
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

TruthMatchingLep_ll_v05::~TruthMatchingLep_ll_v05(){
  // default destructor
  DEBUGclass("destructor called");
} 


//______________________________________________________________________________________________

TObjArray* TruthMatchingLep_ll_v05::getBranchNames() const {
  // retrieve the list of branch names 
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));
  

  bnames->Add(new TObjString("leptons_matched_lep"));
  bnames->Add(new TObjString("leptons_matched_lep_pdgId"));
  bnames->Add(new TObjString("leptons_matched_lep_mother_pdgId"));
  bnames->Add(new TObjString("leptons_matched_lep_origin"));
  bnames->Add(new TObjString("leptons_matched_lep_type"));
  
  return bnames;
}

//______________________________________________________________________________________________

double TruthMatchingLep_ll_v05::getValue() const {
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

  leptons_matched_lep->GetNdata();
  leptons_matched_lep_pdgId->GetNdata();
  leptons_matched_lep_mother_pdgId->GetNdata();
  leptons_matched_lep_origin->GetNdata();
  leptons_matched_lep_type->GetNdata();

  int idx=-1;
  if(useFakeSelec){
    idx=EVS_fake->getLeptonIdx(lepIndex);
  }
  else {
    idx=EVS->getLeptonIdx(lepIndex);
  }

 
  int lep_matched_lep = this->leptons_matched_lep->EvalInstance(idx);
  int lep_matched_lep_pdgId = this->leptons_matched_lep_pdgId->EvalInstance(idx);
  int lep_matched_lep_mother_pdgId = this->leptons_matched_lep_mother_pdgId->EvalInstance(idx);
  int lep_matched_lep_origin = this->leptons_matched_lep_origin->EvalInstance(idx);
  int lep_matched_lep_type = this->leptons_matched_lep_type->EvalInstance(idx); 

  bool IsTrueLep = 0;

  if(lep_matched_lep > 0){ //matching Info is stored
    if(fabs(lep_matched_lep_pdgId) == 11 || fabs(lep_matched_lep_pdgId) == 13){ // matched lepton is true electron or muon
      if(fabs(lep_matched_lep_mother_pdgId) <= 24 ){ // matched lepton comes from Z,W,top or tau decay, for ZllS mother will be quark or gluon (mesons would be non-prompt leptons)
	IsTrueLep = 1;
      }
    }
    else if (fabs(lep_matched_lep_origin) == 13 && (fabs(lep_matched_lep_type) == 2 || fabs(lep_matched_lep_type) == 6 )){ // for Ztt
      IsTrueLep = 1;
    }
  }


  DEBUGclass("returning");

  return IsTrueLep;
}
//______________________________________________________________________________________________

TruthMatchingLep_ll_v05::TruthMatchingLep_ll_v05(const TString& expression, const int& lepton):
TQTreeObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  lepIndex=lepton;

  if(expression.Contains("fake")){
    useFakeSelec = true;
  }

}

//______________________________________________________________________________________________

const TString& TruthMatchingLep_ll_v05::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool TruthMatchingLep_ll_v05::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void TruthMatchingLep_ll_v05::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool TruthMatchingLep_ll_v05::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void TruthMatchingLep_ll_v05::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString TruthMatchingLep_ll_v05::getActiveExpression() const {
  // retrieve the expression associated with this incarnation
  
  return this->getExpression();
}

//______________________________________________________________________________________________

bool TruthMatchingLep_ll_v05::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  // this->bla = new TTreeFormula( "name", "formula", this->fTree);
  
  this->leptons_matched_lep = new TTreeFormula("leptons_matched_lep", "leptons_matched_lep", this->fTree); 
  this->leptons_matched_lep_pdgId = new TTreeFormula("leptons_matched_lep_pdgId", "leptons_matched_lep_pdgId", this->fTree);
  this->leptons_matched_lep_mother_pdgId = new TTreeFormula("leptons_matched_lep_mother_pdgId", "leptons_matched_lep_mother_pdgId", this->fTree);
  this->leptons_matched_lep_origin = new TTreeFormula("leptons_matched_lep_origin", "leptons_matched_lep_origin", this->fTree);
  this->leptons_matched_lep_type = new TTreeFormula("leptons_matched_lep_type", "leptons_matched_lep_type", this->fTree);

  EVS = new EventSelection_leplep_default(); 
  EVS_fake = new EventSelection_leplep_fake(); 
 
  return true;
}
 
//______________________________________________________________________________________________

bool TruthMatchingLep_ll_v05::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();
  
  delete this->leptons_matched_lep;
  delete this->leptons_matched_lep_pdgId;
  delete this->leptons_matched_lep_mother_pdgId;
  delete this->leptons_matched_lep_origin;
  delete this->leptons_matched_lep_type;
  delete EVS;
  delete EVS_fake;

  return true;
}
