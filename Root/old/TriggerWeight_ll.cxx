#include "Htautau2015/TriggerWeight_ll.h"
#include <limits>

// uncomment the following line to enable debug printouts
//#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(TriggerWeight_ll)

//______________________________________________________________________________________________

TriggerWeight_ll::TriggerWeight_ll(){
  // default constructor
 
  this->setExpression(this->GetName() );

  std::cout << "default constructor called" << std::endl;
  
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

TriggerWeight_ll::~TriggerWeight_ll(){
  // default destructor
  DEBUGclass("destructor called");
} 


//______________________________________________________________________________________________

TObjArray* TriggerWeight_ll::getBranchNames() const {
  // retrieve the list of branch names 
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));
  
  bnames->Add(new TObjString("lep_0"));
  bnames->Add(new TObjString("lep_1"));
  bnames->Add(new TObjString("lep_0_pt"));
  bnames->Add(new TObjString("lep_1_pt"));
  bnames->Add(new TObjString("lep_0_HLT_e24_lhmedium_L1EM18VH"));
  bnames->Add(new TObjString("lep_0_HLT_e60_lhmedium"));
  bnames->Add(new TObjString("lep_0_HLT_e120_lhloose"));
  bnames->Add(new TObjString("lep_0_HLT_e24_lhmedium_L1EM20VH"));
  bnames->Add(new TObjString("lep_0_HLT_mu20_iloose_L1MU15"));
  bnames->Add(new TObjString("lep_0_HLT_mu50"));
  bnames->Add(new TObjString("lep_1_HLT_e24_lhmedium_L1EM18VH"));
  bnames->Add(new TObjString("lep_1_HLT_e60_lhmedium"));
  bnames->Add(new TObjString("lep_1_HLT_e120_lhloose"));
  bnames->Add(new TObjString("lep_1_HLT_e24_lhmedium_L1EM20VH"));
  bnames->Add(new TObjString("lep_1_HLT_mu20_iloose_L1MU15"));
  bnames->Add(new TObjString("lep_1_HLT_mu50"));
  bnames->Add(new TObjString("HLT_e17_loose_mu14"));
  bnames->Add(new TObjString("HLT_mu18_mu8noL1"));
  bnames->Add(new TObjString("HLT_2e12_lhloose_L12EM10VH"));
  bnames->Add(new TObjString("lep_0_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_LOOSE"));
  bnames->Add(new TObjString("lep_1_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_LOOSE"));
  bnames->Add(new TObjString("lep_0_NOMINAL_EL_TRIG_MEDIUM"));
  bnames->Add(new TObjString("lep_1_NOMINAL_EL_TRIG_MEDIUM"));
  
  
  return bnames;
}

//______________________________________________________________________________________________

double TriggerWeight_ll::getValue() const {
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
  int lep_0_pt = this->lep_0_pt->EvalInstance();
  int lep_1_pt = this->lep_1_pt->EvalInstance();
  int lep_0_HLT_e24_lhmedium_L1EM18VH = this->lep_0_HLT_e24_lhmedium_L1EM18VH ->EvalInstance();
  int lep_0_HLT_e60_lhmedium = this->lep_0_HLT_e60_lhmedium ->EvalInstance();
  int lep_0_HLT_e120_lhloose = this->lep_0_HLT_e120_lhloose ->EvalInstance();
  int lep_0_HLT_e24_lhmedium_L1EM20VH = this->lep_0_HLT_e24_lhmedium_L1EM20VH ->EvalInstance();
  int lep_0_HLT_mu20_iloose_L1MU15 = this->lep_0_HLT_mu20_iloose_L1MU15 ->EvalInstance();
  int lep_0_HLT_mu50 = this->lep_0_HLT_mu50 ->EvalInstance();
  int lep_1_HLT_e24_lhmedium_L1EM18VH = this->lep_1_HLT_e24_lhmedium_L1EM18VH ->EvalInstance();
  int lep_1_HLT_e60_lhmedium = this->lep_1_HLT_e60_lhmedium ->EvalInstance();
  int lep_1_HLT_e120_lhloose = this->lep_1_HLT_e120_lhloose ->EvalInstance();
  int lep_1_HLT_e24_lhmedium_L1EM20VH = this->lep_1_HLT_e24_lhmedium_L1EM20VH ->EvalInstance();
  int lep_1_HLT_mu20_iloose_L1MU15 = this->lep_1_HLT_mu20_iloose_L1MU15 ->EvalInstance();
  int lep_1_HLT_mu50 = this->lep_1_HLT_mu50 ->EvalInstance();
  int HLT_e17_loose_mu14 = this->HLT_e17_loose_mu14 ->EvalInstance();
  int HLT_mu18_mu8noL1 = this->HLT_mu18_mu8noL1 ->EvalInstance();
  int HLT_2e12_lhloose_L12EM10VH = this->HLT_2e12_lhloose_L12EM10VH ->EvalInstance();

  // Trigger SF only for MC
  float lep_0_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_LOOSE= this->lep_0_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_LOOSE ->EvalInstance();
  float lep_1_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_LOOSE= this->lep_1_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_LOOSE ->EvalInstance();
  float lep_0_NOMINAL_EL_TRIG_MEDIUM = this->lep_0_NOMINAL_EL_TRIG_MEDIUM ->EvalInstance();
  float lep_1_NOMINAL_EL_TRIG_MEDIUM= this->lep_1_NOMINAL_EL_TRIG_MEDIUM ->EvalInstance();


  float TriggerWeight = 1.;

  if (lep_0 == 1 && lep_1 == 1){ //mm
    if (lep_0_pt >= 22*1000 && (lep_0_HLT_mu20_iloose_L1MU15==1 || lep_0_HLT_mu50==1)){
      TriggerWeight *= lep_0_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_LOOSE;
    }
    else if (lep_0_pt/1000 < 22  && lep_0_pt/1000 >=20 && lep_1_pt/1000 >=10 && HLT_mu18_mu8noL1==1){
      TriggerWeight *= 1.;
    }
  }
  else if (lep_0 == 2 && lep_1 == 2){ // ee
    if (lep_0_pt >= 26*1000 && (lep_0_HLT_e24_lhmedium_L1EM18VH==1 || lep_0_HLT_e60_lhmedium==1 || lep_0_HLT_e120_lhloose==1)){
      TriggerWeight *= lep_0_NOMINAL_EL_TRIG_MEDIUM;
    }
    else if (lep_0_pt< 26000 && lep_0_pt >= 15000 && lep_1_pt >= 15000 && HLT_2e12_lhloose_L12EM10VH==1){
      TriggerWeight *= 1.;
    }

  }
  else if (lep_0 == 1 && lep_1 == 2){ //me
    if (lep_1_pt < 26 * 1000 && lep_0_pt >= 22 * 1000 && (lep_0_HLT_mu20_iloose_L1MU15==1 || lep_0_HLT_mu50==1)){
      TriggerWeight *= lep_0_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_LOOSE;
    }
    else if (lep_1_pt >= 26 * 1000 && (lep_1_HLT_e24_lhmedium_L1EM18VH==1 || lep_1_HLT_e60_lhmedium==1 || lep_1_HLT_e120_lhloose==1)) {
      TriggerWeight *= lep_1_NOMINAL_EL_TRIG_MEDIUM;
    }
    else if (lep_1_pt < 26 * 1000 && lep_1_pt >= 19 * 1000 && lep_0_pt < 22 * 1000 && lep_0_pt >= 16 * 1000 && HLT_e17_loose_mu14==1 ){
      TriggerWeight *= 1.;
    }
  }
  else if (lep_0 == 2 && lep_1 == 1) { // em
    if (lep_0_pt >= 26 * 1000 && (lep_0_HLT_e24_lhmedium_L1EM18VH==1 || lep_0_HLT_e60_lhmedium==1 || lep_0_HLT_e120_lhloose==1)){
      TriggerWeight *= lep_0_NOMINAL_EL_TRIG_MEDIUM;
    }
    else if (lep_0_pt < 26 * 1000 && lep_1_pt >=22 * 1000 && (lep_1_HLT_mu20_iloose_L1MU15==1 || lep_1_HLT_mu50==1)){
      TriggerWeight *= lep_1_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_LOOSE;
    }
    else if (lep_0_pt < 26 * 1000 && lep_0_pt >= 19 * 1000 && lep_1_pt < 22 * 1000 && lep_1_pt >= 16 * 1000 && HLT_e17_loose_mu14==1){
      TriggerWeight *= 1.;
    }
  }



  DEBUGclass("returning");

  return TriggerWeight;
}
//______________________________________________________________________________________________

TriggerWeight_ll::TriggerWeight_ll(const TString& expression):
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

const TString& TriggerWeight_ll::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool TriggerWeight_ll::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void TriggerWeight_ll::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool TriggerWeight_ll::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void TriggerWeight_ll::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString TriggerWeight_ll::getActiveExpression() const {
  // retrieve the expression associated with this incarnation
  
  return this->getExpression();
}

//______________________________________________________________________________________________

bool TriggerWeight_ll::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  // this->bla = new TTreeFormula( "name", "formula", this->fTree);
  
  this->lep_0 = new TTreeFormula( "lep_0", "lep_0", this->fTree);
  this->lep_1 = new TTreeFormula( "lep_1", "lep_1", this->fTree);
  this->lep_0_pt = new TTreeFormula( "lep_0_pt", "lep_0_pt", this->fTree);
  this->lep_1_pt = new TTreeFormula( "lep_1_pt", "lep_1_pt", this->fTree);
  this->lep_0_HLT_e24_lhmedium_L1EM18VH = new TTreeFormula( "lep_0_HLT_e24_lhmedium_L1EM18VH", "lep_0_HLT_e24_lhmedium_L1EM18VH", this->fTree);
  this->lep_0_HLT_e60_lhmedium = new TTreeFormula( "lep_0_HLT_e60_lhmedium", "lep_0_HLT_e60_lhmedium", this->fTree);
  this->lep_0_HLT_e120_lhloose = new TTreeFormula( "lep_0_HLT_e120_lhloose", "lep_0_HLT_e120_lhloose", this->fTree);
  this->lep_0_HLT_e24_lhmedium_L1EM20VH = new TTreeFormula( "lep_0_HLT_e24_lhmedium_L1EM20VH", "lep_0_HLT_e24_lhmedium_L1EM20VH", this->fTree);
  this->lep_0_HLT_mu20_iloose_L1MU15 = new TTreeFormula( "lep_0_HLT_mu20_iloose_L1MU15", "lep_0_HLT_mu20_iloose_L1MU15", this->fTree);
  this->lep_0_HLT_mu50 = new TTreeFormula( "lep_0_HLT_mu50", "lep_0_HLT_mu50", this->fTree);
  this->lep_1_HLT_e24_lhmedium_L1EM18VH = new TTreeFormula( "lep_1_HLT_e24_lhmedium_L1EM18VH", "lep_1_HLT_e24_lhmedium_L1EM18VH", this->fTree);
  this->lep_1_HLT_e60_lhmedium = new TTreeFormula( "lep_1_HLT_e60_lhmedium", "lep_1_HLT_e60_lhmedium", this->fTree);
  this->lep_1_HLT_e120_lhloose = new TTreeFormula( "lep_1_HLT_e120_lhloose", "lep_1_HLT_e120_lhloose", this->fTree);
  this->lep_1_HLT_e24_lhmedium_L1EM20VH = new TTreeFormula( "lep_1_HLT_e24_lhmedium_L1EM20VH", "lep_1_HLT_e24_lhmedium_L1EM20VH", this->fTree);
  this->lep_1_HLT_mu20_iloose_L1MU15 = new TTreeFormula( "lep_1_HLT_mu20_iloose_L1MU15", "lep_1_HLT_mu20_iloose_L1MU15", this->fTree);
  this->lep_1_HLT_mu50 = new TTreeFormula( "lep_1_HLT_mu50", "lep_1_HLT_mu50", this->fTree);
  this->HLT_e17_loose_mu14 = new TTreeFormula( "HLT_e17_loose_mu14", "HLT_e17_loose_mu14", this->fTree);
  this->HLT_mu18_mu8noL1 = new TTreeFormula( "HLT_mu18_mu8noL1", "HLT_mu18_mu8noL1", this->fTree);
  this->HLT_2e12_lhloose_L12EM10VH = new TTreeFormula( "HLT_2e12_lhloose_L12EM10VH", "HLT_2e12_lhloose_L12EM10VH", this->fTree);  
  this->lep_0_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_LOOSE = new TTreeFormula( "lep_0_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_LOOSE", "lep_0_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_LOOSE", this->fTree);
  this->lep_1_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_LOOSE = new TTreeFormula( "lep_1_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_LOOSE", "lep_1_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_LOOSE", this->fTree);
  this->lep_0_NOMINAL_EL_TRIG_MEDIUM = new TTreeFormula( "lep_0_NOMINAL_EL_TRIG_MEDIUM", "lep_0_NOMINAL_EL_TRIG_MEDIUM", this->fTree);
  this->lep_1_NOMINAL_EL_TRIG_MEDIUM = new TTreeFormula( "lep_1_NOMINAL_EL_TRIG_MEDIUM", "lep_1_NOMINAL_EL_TRIG_MEDIUM", this->fTree);
  
  return true;
}
 
//______________________________________________________________________________________________

bool TriggerWeight_ll::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();
  
  delete this->lep_0;
  delete this->lep_1;

  delete this->lep_0_pt;
  delete this->lep_1_pt;
  delete this->lep_0_HLT_e24_lhmedium_L1EM18VH;
  delete this->lep_0_HLT_e60_lhmedium;
  delete this->lep_0_HLT_e120_lhloose;
  delete this->lep_0_HLT_e24_lhmedium_L1EM20VH;
  delete this->lep_0_HLT_mu20_iloose_L1MU15;
  delete this->lep_0_HLT_mu50;
  delete this->lep_1_HLT_e24_lhmedium_L1EM18VH;
  delete this->lep_1_HLT_e60_lhmedium;
  delete this->lep_1_HLT_e120_lhloose;
  delete this->lep_1_HLT_e24_lhmedium_L1EM20VH;
  delete this->lep_1_HLT_mu20_iloose_L1MU15;
  delete this->lep_1_HLT_mu50;
  delete this->HLT_e17_loose_mu14;
  delete this->HLT_mu18_mu8noL1;
  delete this->HLT_2e12_lhloose_L12EM10VH;
  delete this->lep_0_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_LOOSE;
  delete this->lep_1_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_LOOSE;
  delete this->lep_0_NOMINAL_EL_TRIG_MEDIUM;
  delete this->lep_1_NOMINAL_EL_TRIG_MEDIUM;
  

  return true;
}
