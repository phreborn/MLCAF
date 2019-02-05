#include "Htautau2015/Trigger_ll_v05.h"
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

ClassImp(Trigger_ll_v05)

//______________________________________________________________________________________________

Trigger_ll_v05::Trigger_ll_v05(){
  // default constructor
 
  this->setExpression(this->GetName() );

  std::cout << "default constructor called" << std::endl;
  
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

Trigger_ll_v05::~Trigger_ll_v05(){
  // default destructor
  DEBUGclass("destructor called");
} 


//______________________________________________________________________________________________

TObjArray* Trigger_ll_v05::getBranchNames() const {
  // retrieve the list of branch names 
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));
  
  bnames->Add(new TObjString("leptons"));
  bnames->Add(new TObjString("leptons_pt"));
  bnames->Add(new TObjString("leptons_HLT_e24_lhmedium_L1EM18VH"));
  bnames->Add(new TObjString("leptons_HLT_e60_lhmedium"));
  bnames->Add(new TObjString("leptons_HLT_e120_lhloose"));
  bnames->Add(new TObjString("leptons_HLT_e24_lhmedium_L1EM20VH"));
  bnames->Add(new TObjString("leptons_HLT_mu20_iloose_L1MU15"));
  bnames->Add(new TObjString("leptons_HLT_mu50"));
  bnames->Add(new TObjString("HLT_e17_loose_mu14"));
  bnames->Add(new TObjString("HLT_mu18_mu8noL1"));
  bnames->Add(new TObjString("HLT_2e12_lhloose_L12EM10VH"));
  
  return bnames;
}

//______________________________________________________________________________________________

double Trigger_ll_v05::getValue() const {
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

  int idx0 = -1;
  int idx1 = -1;

  if(useFakeSelec){
    //std::cout << "In Trigger:: use fake selection" << std::endl;
    idx0 = EVS_fake->getLeptonIdx(0);
    idx1 = EVS_fake->getLeptonIdx(1);
  }
  else {
    //std::cout << "In Trigger:: use default selection" << std::endl;
    idx0 = EVS->getLeptonIdx(0);
    idx1 = EVS->getLeptonIdx(1);
  }

  bool isTriggered = 0;
  int TriggerType = 0;

  if(isData){
    if(useFakeSelec){
      //std::cout << "... In Trigger:: use fake selection for data" << std::endl;
      isTriggered = EVS_fake->getTriggered_data();
    }
    else {
      //std::cout << "... In Trigger:: use default selection for data" << std::endl;
      isTriggered = EVS->getTriggered_data();
    }
  }
  else {
    if(useFakeSelec){
      //std::cout << "... In Trigger:: use fake selection for mc" << std::endl;
      isTriggered = EVS_fake->getTriggered_MC();
    }
    else {
      //std::cout << "... In Trigger:: use default selection for mc" << std::endl;
      isTriggered = EVS->getTriggered_MC();
    }
  }
  if(useFakeSelec){
    TriggerType = EVS_fake->getTriggerType();
  }
  else {
    TriggerType = EVS->getTriggerType();
  }

  //std::cout << "in OBS: trigger type " << TriggerType << std::endl;

  //std::cout << "---------END" << std::endl;

  DEBUGclass("returning");

  //std::cout << "Triggered " << isTriggered << std::endl;
  //std::cout << "-------" << std::endl;
  if(isTrigType){
    return TriggerType;
  }
  else {
    return isTriggered;
  }

}
//______________________________________________________________________________________________

Trigger_ll_v05::Trigger_ll_v05(const TString& expression):
TQTreeObservable(expression)
{

  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  if(expression.Contains("Data")){
    DEBUGclass("use data here '%s'", expression.Data());
    isData = true;
  }
  else isData = false;

  if(expression.Contains("TriggerType")){
    isTrigType = true;
  }

  if(expression.Contains("fake")){
    useFakeSelec = true;
  }

}

//______________________________________________________________________________________________

const TString& Trigger_ll_v05::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool Trigger_ll_v05::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void Trigger_ll_v05::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool Trigger_ll_v05::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void Trigger_ll_v05::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString Trigger_ll_v05::getActiveExpression() const {
  // retrieve the expression associated with this incarnation
  
  return this->getExpression();
}

//______________________________________________________________________________________________

bool Trigger_ll_v05::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  // this->bla = new TTreeFormula( "name", "formula", this->fTree);
  
  EVS = new EventSelection_leplep_default();
  EVS_fake = new EventSelection_leplep_fake();

  this->leptons    = new TTreeFormula( "leptons", "leptons", this->fTree);
  this->leptons_pt = new TTreeFormula( "leptons_pt", "leptons_pt", this->fTree);
  this->leptons_HLT_e24_lhmedium_L1EM18VH = new TTreeFormula( "leptons_HLT_e24_lhmedium_L1EM18VH", "leptons_HLT_e24_lhmedium_L1EM18VH", this->fTree);
  this->leptons_HLT_e60_lhmedium = new TTreeFormula( "leptons_HLT_e60_lhmedium", "leptons_HLT_e60_lhmedium", this->fTree);
  this->leptons_HLT_e120_lhloose = new TTreeFormula( "leptons_HLT_e120_lhloose", "leptons_HLT_e120_lhloose", this->fTree);
  this->leptons_HLT_e24_lhmedium_L1EM20VH = new TTreeFormula( "leptons_HLT_e24_lhmedium_L1EM20VH", "leptons_HLT_e24_lhmedium_L1EM20VH", this->fTree);
  this->leptons_HLT_mu20_iloose_L1MU15 = new TTreeFormula( "leptons_HLT_mu20_iloose_L1MU15", "leptons_HLT_mu20_iloose_L1MU15", this->fTree);
  this->leptons_HLT_mu50 = new TTreeFormula( "leptons_HLT_mu50", "leptons_HLT_mu50", this->fTree);
  this->HLT_e17_loose_mu14 = new TTreeFormula( "HLT_e17_loose_mu14", "HLT_e17_loose_mu14", this->fTree);
  this->HLT_mu18_mu8noL1 = new TTreeFormula( "HLT_mu18_mu8noL1", "HLT_mu18_mu8noL1", this->fTree);
  this->HLT_2e12_lhloose_L12EM10VH = new TTreeFormula( "HLT_2e12_lhloose_L12EM10VH", "HLT_2e12_lhloose_L12EM10VH", this->fTree);  


  return true;
}
 
//______________________________________________________________________________________________

bool Trigger_ll_v05::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();
  
  delete this->leptons;
  delete this->leptons_pt;
  delete this->leptons_HLT_e24_lhmedium_L1EM18VH;
  delete this->leptons_HLT_e60_lhmedium;
  delete this->leptons_HLT_e120_lhloose;
  delete this->leptons_HLT_e24_lhmedium_L1EM20VH;
  delete this->leptons_HLT_mu20_iloose_L1MU15;
  delete this->leptons_HLT_mu50;
  delete this->HLT_e17_loose_mu14;
  delete this->HLT_mu18_mu8noL1;
  delete this->HLT_2e12_lhloose_L12EM10VH;

  delete EVS;
  delete EVS_fake;

  return true;
}
