#include "Htautau2015/ScaleFactor_ll.h"
#include <limits>

// uncomment the following line to enable debug printouts
//#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(ScaleFactor_ll)

//______________________________________________________________________________________________

ScaleFactor_ll::ScaleFactor_ll(){
  // default constructor
 
  this->setExpression(this->GetName() );
  
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

ScaleFactor_ll::~ScaleFactor_ll(){
  // default destructor
  DEBUGclass("destructor called");
} 


//______________________________________________________________________________________________

TObjArray* ScaleFactor_ll::getBranchNames() const {
  // retrieve the list of branch names 
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));
  
  bnames->Add(new TObjString("lep_0"));
  bnames->Add(new TObjString("lep_1"));
  bnames->Add(new TObjString("lep_0_NOMINAL_MU_RECO_MEDIUM"));
  bnames->Add(new TObjString("lep_0_NOMINAL_MU_RECO_TIGHT"));
  bnames->Add(new TObjString("lep_0_NOMINAL_MU_RECO_LOOSE"));
  bnames->Add(new TObjString("lep_0_NOMINAL_MU_ISO_LOOSE"));   
  bnames->Add(new TObjString("lep_0_NOMINAL_EL_RECO"));	       
  bnames->Add(new TObjString("lep_0_NOMINAL_EL_ID_MEDIUM"));   
  bnames->Add(new TObjString("lep_0_NOMINAL_EL_ID_TIGHT"));   
  bnames->Add(new TObjString("lep_0_NOMINAL_EL_ID_LOOSE"));   
  bnames->Add(new TObjString("lep_0_NOMINAL_EL_ISO_LOOSE"));   
  bnames->Add(new TObjString("lep_1_NOMINAL_MU_RECO_MEDIUM")); 
  bnames->Add(new TObjString("lep_1_NOMINAL_MU_RECO_TIGHT")); 
  bnames->Add(new TObjString("lep_1_NOMINAL_MU_RECO_LOOSE")); 
  bnames->Add(new TObjString("lep_1_NOMINAL_MU_ISO_LOOSE"));   
  bnames->Add(new TObjString("lep_1_NOMINAL_EL_RECO"));	       
  bnames->Add(new TObjString("lep_1_NOMINAL_EL_ID_MEDIUM"));   
  bnames->Add(new TObjString("lep_1_NOMINAL_EL_ID_TIGHT"));   
  bnames->Add(new TObjString("lep_1_NOMINAL_EL_ID_LOOSE"));   
  bnames->Add(new TObjString("lep_1_NOMINAL_EL_ISO_LOOSE"));   

  
  return bnames;
}

//______________________________________________________________________________________________

double ScaleFactor_ll::getValue() const {
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

  int lep_0 = this->lep_0->EvalInstance();
  int lep_1 = this->lep_1->EvalInstance();
  double lep_0_NOMINAL_MU_RECO_MEDIUM = this->lep_0_NOMINAL_MU_RECO_MEDIUM->EvalInstance();
  double lep_0_NOMINAL_MU_RECO_TIGHT  = this->lep_0_NOMINAL_MU_RECO_TIGHT->EvalInstance();
  double lep_0_NOMINAL_MU_RECO_LOOSE  = this->lep_0_NOMINAL_MU_RECO_LOOSE->EvalInstance();
  double lep_0_NOMINAL_MU_ISO_LOOSE   = this->lep_0_NOMINAL_MU_ISO_LOOSE->EvalInstance();
  double lep_0_NOMINAL_EL_RECO        = this->lep_0_NOMINAL_EL_RECO->EvalInstance();
  double lep_0_NOMINAL_EL_ID_MEDIUM   = this->lep_0_NOMINAL_EL_ID_MEDIUM->EvalInstance();
  double lep_0_NOMINAL_EL_ID_TIGHT    = this->lep_0_NOMINAL_EL_ID_TIGHT->EvalInstance();
  double lep_0_NOMINAL_EL_ID_LOOSE    = this->lep_0_NOMINAL_EL_ID_LOOSE->EvalInstance();
  double lep_0_NOMINAL_EL_ISO_LOOSE   = this->lep_0_NOMINAL_EL_ISO_LOOSE->EvalInstance();   
  double lep_1_NOMINAL_MU_RECO_MEDIUM = this->lep_1_NOMINAL_MU_RECO_MEDIUM->EvalInstance();
  double lep_1_NOMINAL_MU_RECO_TIGHT  = this->lep_1_NOMINAL_MU_RECO_TIGHT->EvalInstance();
  double lep_1_NOMINAL_MU_RECO_LOOSE  = this->lep_1_NOMINAL_MU_RECO_LOOSE->EvalInstance();
  double lep_1_NOMINAL_MU_ISO_LOOSE   = this->lep_1_NOMINAL_MU_ISO_LOOSE->EvalInstance();
  double lep_1_NOMINAL_EL_RECO        = this->lep_1_NOMINAL_EL_RECO->EvalInstance();
  double lep_1_NOMINAL_EL_ID_MEDIUM   = this->lep_1_NOMINAL_EL_ID_MEDIUM->EvalInstance();  
  double lep_1_NOMINAL_EL_ID_TIGHT    = this->lep_1_NOMINAL_EL_ID_TIGHT->EvalInstance();  
  double lep_1_NOMINAL_EL_ID_LOOSE    = this->lep_1_NOMINAL_EL_ID_LOOSE->EvalInstance();  
  double lep_1_NOMINAL_EL_ISO_LOOSE   = this->lep_1_NOMINAL_EL_ISO_LOOSE->EvalInstance();

 
  double ScaleFactor = 1.;
  double SF_lep0 = 1.;
  double SF_lep1 = 1.;

  if (lep_0 == 2 && lep_1 == 2)
    {
      if (isMedMed){
	SF_lep0 = lep_0_NOMINAL_EL_RECO * lep_0_NOMINAL_EL_ID_MEDIUM * lep_0_NOMINAL_EL_ISO_LOOSE;
	SF_lep1 = lep_1_NOMINAL_EL_RECO * lep_1_NOMINAL_EL_ID_MEDIUM * lep_1_NOMINAL_EL_ISO_LOOSE;
      }
      else if (isTightTight){
	SF_lep0 = lep_0_NOMINAL_EL_RECO * lep_0_NOMINAL_EL_ID_TIGHT * lep_0_NOMINAL_EL_ISO_LOOSE;
        SF_lep1 = lep_1_NOMINAL_EL_RECO * lep_1_NOMINAL_EL_ID_TIGHT * lep_1_NOMINAL_EL_ISO_LOOSE;
      }
      else if (isTightLoose){
	SF_lep0 = lep_0_NOMINAL_EL_RECO * lep_0_NOMINAL_EL_ID_TIGHT * lep_0_NOMINAL_EL_ISO_LOOSE;
        SF_lep1 = lep_1_NOMINAL_EL_RECO * lep_1_NOMINAL_EL_ID_LOOSE * lep_1_NOMINAL_EL_ISO_LOOSE;
      }
    }
  else if (lep_0 == 1 && lep_1 == 1)
    {
      if (isMedMed){
	SF_lep0 = lep_0_NOMINAL_MU_RECO_MEDIUM * lep_0_NOMINAL_MU_ISO_LOOSE;
	SF_lep1 = lep_1_NOMINAL_MU_RECO_MEDIUM * lep_1_NOMINAL_MU_ISO_LOOSE;
      }
      else if (isTightTight){
	SF_lep0 = lep_0_NOMINAL_MU_RECO_TIGHT * lep_0_NOMINAL_MU_ISO_LOOSE;
        SF_lep1 = lep_1_NOMINAL_MU_RECO_TIGHT * lep_1_NOMINAL_MU_ISO_LOOSE;
      }
      else if (isTightLoose){
	SF_lep0 = lep_0_NOMINAL_MU_RECO_TIGHT * lep_0_NOMINAL_MU_ISO_LOOSE;
        SF_lep1 = lep_1_NOMINAL_MU_RECO_LOOSE * lep_1_NOMINAL_MU_ISO_LOOSE;
      }
    }
  else if (lep_0 == 2 && lep_1 == 1)
    {
      if (isMedMed){
	SF_lep0 = lep_0_NOMINAL_EL_RECO * lep_0_NOMINAL_EL_ID_MEDIUM * lep_0_NOMINAL_EL_ISO_LOOSE;
	SF_lep1 = lep_1_NOMINAL_MU_RECO_MEDIUM * lep_1_NOMINAL_MU_ISO_LOOSE;
      }
      else if (isTightTight){
	SF_lep0 = lep_0_NOMINAL_EL_RECO * lep_0_NOMINAL_EL_ID_TIGHT * lep_0_NOMINAL_EL_ISO_LOOSE;
        SF_lep1 = lep_1_NOMINAL_MU_RECO_TIGHT * lep_1_NOMINAL_MU_ISO_LOOSE;
      }
      else if (isTightLoose){
	SF_lep0 = lep_0_NOMINAL_EL_RECO * lep_0_NOMINAL_EL_ID_TIGHT * lep_0_NOMINAL_EL_ISO_LOOSE;
        SF_lep1 = lep_1_NOMINAL_MU_RECO_LOOSE * lep_1_NOMINAL_MU_ISO_LOOSE;
      }
    }
  else if (lep_0 == 1 && lep_1== 2)
    {
      if(isMedMed){
	SF_lep0 = lep_0_NOMINAL_MU_RECO_MEDIUM * lep_0_NOMINAL_MU_ISO_LOOSE;
	SF_lep1 = lep_1_NOMINAL_EL_RECO * lep_1_NOMINAL_EL_ID_MEDIUM * lep_1_NOMINAL_EL_ISO_LOOSE;
      }
      else if (isTightTight){
	SF_lep0 = lep_0_NOMINAL_MU_RECO_TIGHT * lep_0_NOMINAL_MU_ISO_LOOSE;
        SF_lep1 = lep_1_NOMINAL_EL_RECO * lep_1_NOMINAL_EL_ID_TIGHT * lep_1_NOMINAL_EL_ISO_LOOSE;
      }
      else if (isTightLoose){
	SF_lep0 = lep_0_NOMINAL_MU_RECO_TIGHT * lep_0_NOMINAL_MU_ISO_LOOSE;
        SF_lep1 = lep_1_NOMINAL_EL_RECO * lep_1_NOMINAL_EL_ID_LOOSE * lep_1_NOMINAL_EL_ISO_LOOSE;
      }
    }
  

  ScaleFactor = SF_lep0 * SF_lep1;  

  DEBUGclass("returning");

  return ScaleFactor;
}
//______________________________________________________________________________________________

ScaleFactor_ll::ScaleFactor_ll(const TString& expression):
TQTreeObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  if (expression.Contains("medmed")){
    isMedMed = true;
  }
  else if (expression.Contains("tighttight")){
    isTightTight = true;
  }
  else if (expression.Contains("tightloose")){
    isTightLoose = true;
  }
  else {
    DEBUGclass("ERROR in ScaleFactor: No lepton selection criteria found for '%s'", expression);
  }
}

//______________________________________________________________________________________________

const TString& ScaleFactor_ll::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool ScaleFactor_ll::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void ScaleFactor_ll::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool ScaleFactor_ll::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void ScaleFactor_ll::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString ScaleFactor_ll::getActiveExpression() const {
  // retrieve the expression associated with this incarnation
  
  return this->getExpression();
}

//______________________________________________________________________________________________

bool ScaleFactor_ll::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  // this->bla = new TTreeFormula( "name", "formula", this->fTree);
  
  this->lep_0 = new TTreeFormula( "lep_0", "lep_0", this->fTree);
  this->lep_1 = new TTreeFormula( "lep_1", "lep_1", this->fTree);
  this->lep_0_NOMINAL_MU_RECO_MEDIUM = new TTreeFormula( "lep_0_NOMINAL_MU_RECO_MEDIUM", "lep_0_NOMINAL_MU_RECO_MEDIUM", this->fTree);
  this->lep_0_NOMINAL_MU_RECO_TIGHT = new TTreeFormula( "lep_0_NOMINAL_MU_RECO_TIGHT", "lep_0_NOMINAL_MU_RECO_TIGHT", this->fTree);
  this->lep_0_NOMINAL_MU_RECO_LOOSE = new TTreeFormula( "lep_0_NOMINAL_MU_RECO_LOOSE", "lep_0_NOMINAL_MU_RECO_LOOSE", this->fTree);
  this->lep_0_NOMINAL_MU_ISO_LOOSE   = new TTreeFormula( "lep_0_NOMINAL_MU_ISO_LOOSE", "lep_0_NOMINAL_MU_ISO_LOOSE", this->fTree);
  this->lep_0_NOMINAL_EL_RECO        = new TTreeFormula( "lep_0_NOMINAL_EL_RECO", "lep_0_NOMINAL_EL_RECO", this->fTree);
  this->lep_0_NOMINAL_EL_ID_MEDIUM   = new TTreeFormula( "lep_0_NOMINAL_EL_ID_MEDIUM", "lep_0_NOMINAL_EL_ID_MEDIUM", this->fTree);
  this->lep_0_NOMINAL_EL_ID_TIGHT   = new TTreeFormula( "lep_0_NOMINAL_EL_ID_TIGHT", "lep_0_NOMINAL_EL_ID_TIGHT", this->fTree);
  this->lep_0_NOMINAL_EL_ID_LOOSE   = new TTreeFormula( "lep_0_NOMINAL_EL_ID_LOOSE", "lep_0_NOMINAL_EL_ID_LOOSE", this->fTree);
  this->lep_0_NOMINAL_EL_ISO_LOOSE   = new TTreeFormula( "lep_0_NOMINAL_EL_ISO_LOOSE", "lep_0_NOMINAL_EL_ISO_LOOSE", this->fTree);
  this->lep_1_NOMINAL_MU_RECO_MEDIUM = new TTreeFormula( "lep_1_NOMINAL_MU_RECO_MEDIUM", "lep_1_NOMINAL_MU_RECO_MEDIUM", this->fTree);
  this->lep_1_NOMINAL_MU_RECO_TIGHT = new TTreeFormula( "lep_1_NOMINAL_MU_RECO_TIGHT", "lep_1_NOMINAL_MU_RECO_TIGHT", this->fTree);
  this->lep_1_NOMINAL_MU_RECO_LOOSE = new TTreeFormula( "lep_1_NOMINAL_MU_RECO_LOOSE", "lep_1_NOMINAL_MU_RECO_LOOSE", this->fTree);
  this->lep_1_NOMINAL_MU_ISO_LOOSE   = new TTreeFormula( "lep_1_NOMINAL_MU_ISO_LOOSE", "lep_1_NOMINAL_MU_ISO_LOOSE", this->fTree);
  this->lep_1_NOMINAL_EL_RECO        = new TTreeFormula( "lep_1_NOMINAL_EL_RECO", "lep_1_NOMINAL_EL_RECO", this->fTree);
  this->lep_1_NOMINAL_EL_ID_MEDIUM   = new TTreeFormula( "lep_1_NOMINAL_EL_ID_MEDIUM", "lep_1_NOMINAL_EL_ID_MEDIUM", this->fTree);
  this->lep_1_NOMINAL_EL_ID_TIGHT   = new TTreeFormula( "lep_1_NOMINAL_EL_ID_TIGHT", "lep_1_NOMINAL_EL_ID_TIGHT", this->fTree);
  this->lep_1_NOMINAL_EL_ID_LOOSE   = new TTreeFormula( "lep_1_NOMINAL_EL_ID_LOOSE", "lep_1_NOMINAL_EL_ID_LOOSE", this->fTree);
  this->lep_1_NOMINAL_EL_ISO_LOOSE   = new TTreeFormula( "lep_1_NOMINAL_EL_ISO_LOOSE", "lep_1_NOMINAL_EL_ISO_LOOSE", this->fTree);

  return true;
}
 
//______________________________________________________________________________________________

bool ScaleFactor_ll::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();
  
  delete this->lep_0;
  delete this->lep_1;
  delete this->lep_0_NOMINAL_MU_RECO_MEDIUM;
  delete this->lep_0_NOMINAL_MU_RECO_TIGHT;
  delete this->lep_0_NOMINAL_MU_RECO_LOOSE;
  delete this->lep_0_NOMINAL_MU_ISO_LOOSE;
  delete this->lep_0_NOMINAL_EL_RECO;
  delete this->lep_0_NOMINAL_EL_ID_MEDIUM;
  delete this->lep_0_NOMINAL_EL_ID_TIGHT;
  delete this->lep_0_NOMINAL_EL_ID_LOOSE;
  delete this->lep_0_NOMINAL_EL_ISO_LOOSE;
  delete this->lep_1_NOMINAL_MU_RECO_MEDIUM;
  delete this->lep_1_NOMINAL_MU_RECO_TIGHT;
  delete this->lep_1_NOMINAL_MU_RECO_LOOSE;
  delete this->lep_1_NOMINAL_MU_ISO_LOOSE;
  delete this->lep_1_NOMINAL_EL_RECO;
  delete this->lep_1_NOMINAL_EL_ID_MEDIUM;
  delete this->lep_1_NOMINAL_EL_ID_TIGHT;
  delete this->lep_1_NOMINAL_EL_ID_LOOSE;
  delete this->lep_1_NOMINAL_EL_ISO_LOOSE;


  return true;
}
