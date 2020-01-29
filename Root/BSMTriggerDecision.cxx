#include "BSMtautauCAF/BSMTriggerDecision.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(BSMTriggerDecision)

//______________________________________________________________________________________________

BSMTriggerDecision::BSMTriggerDecision(){
  // default constructor
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

BSMTriggerDecision::~BSMTriggerDecision(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* BSMTriggerDecision::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();
  // 2015 trigger
  bnames->Add(new TObjString("HLT_e24_lhmedium_L1EM20VH"));
  bnames->Add(new TObjString("eleTrigMatch_0_HLT_e24_lhmedium_L1EM20VH"));

  bnames->Add(new TObjString("HLT_e60_lhmedium"));
  bnames->Add(new TObjString("eleTrigMatch_0_HLT_e60_lhmedium"));

  // 2016 trigger
  bnames->Add(new TObjString("HLT_e26_lhtight_nod0_ivarloose"));
  bnames->Add(new TObjString("eleTrigMatch_0_HLT_e26_lhtight_nod0_ivarloose"));

  bnames->Add(new TObjString("HLT_e60_lhmedium_nod0"));
  bnames->Add(new TObjString("eleTrigMatch_0_HLT_e60_lhmedium_nod0"));

  // 2015 trigger
  bnames->Add(new TObjString("HLT_e120_lhloose"));
  bnames->Add(new TObjString("eleTrigMatch_0_HLT_e120_lhloose"));

  // 2016 trigger
  bnames->Add(new TObjString("HLT_e140_lhloose_nod0"));
  bnames->Add(new TObjString("eleTrigMatch_0_HLT_e140_lhloose_nod0"));

  // 2015 trigger
  bnames->Add(new TObjString("HLT_mu20_iloose_L1MU15"));
  bnames->Add(new TObjString("muTrigMatch_0_HLT_mu20_iloose_L1MU15"));

  // 2016 trigger
  bnames->Add(new TObjString("HLT_mu26_ivarmedium"));
  bnames->Add(new TObjString("muTrigMatch_0_HLT_mu26_ivarmedium"));

  bnames->Add(new TObjString("HLT_mu50"));
  bnames->Add(new TObjString("muTrigMatch_0_HLT_mu50"));

  return bnames;
}

//______________________________________________________________________________________________

double BSMTriggerDecision::getValue() const {

  UInt_t    run_number = this->x_run_number->EvalInstance();

  bool Is2016 = 0;
  if( run_number>290000 )  Is2016 = 1;

  int    value_of_lep_0    = this->lep_0->EvalInstance();

  double value_of_lep_0_pt = this->lep_0_pt->EvalInstance();

  // 2015 trigger
  int value_of_HLT_e24_lhmedium_L1EM              = this->HLT_e24_lhmedium_L1EM20VH                ->EvalInstance();
  int value_of_eleTrigMatch_0_HLT_e24_lhmedium_L1EM20VH = this->eleTrigMatch_0_HLT_e24_lhmedium_L1EM20VH ->EvalInstance();

  int value_of_HLT_e60_lhmedium                   = this->HLT_e60_lhmedium                                ->EvalInstance();
  int value_of_eleTrigMatch_0_HLT_e60_lhmedium    = this->eleTrigMatch_0_HLT_e60_lhmedium                 ->EvalInstance();

  // 2016 trigger
  int value_of_HLT_e26_lhtight_nod0_ivarloose       = this->HLT_e26_lhtight_nod0_ivarloose                ->EvalInstance();
  int value_of_eleTrigMatch_0_HLT_e26_lhtight_nod0_ivarloose = this->eleTrigMatch_0_HLT_e26_lhtight_nod0_ivarloose ->EvalInstance();

  int value_of_HLT_e60_lhmedium_nod0                = this->HLT_e60_lhmedium_nod0                          ->EvalInstance();
  int value_of_eleTrigMatch_0_HLT_e60_lhmedium_nod0 = this->eleTrigMatch_0_HLT_e60_lhmedium_nod0           ->EvalInstance();

  // 2015 trigger
  int value_of_HLT_e120_lhloose                   = this->HLT_e120_lhloose                                ->EvalInstance();
  int value_of_eleTrigMatch_0_HLT_e120_lhloose    = this->eleTrigMatch_0_HLT_e120_lhloose                 ->EvalInstance();

  // 2016 trigger
  int value_of_HLT_e140_lhloose_nod0                  = this->HLT_e140_lhloose_nod0                       ->EvalInstance();
  int value_of_eleTrigMatch_0_HLT_e140_lhloose_nod0   = this->eleTrigMatch_0_HLT_e140_lhloose_nod0        ->EvalInstance();

  // 2015 trigger
  int value_of_HLT_mu20_iloose_L1MU15                 = this->HLT_mu20_iloose_L1MU15               ->EvalInstance();
  int value_of_muTrigMatch_0_HLT_mu20_iloose_L1MU15   = this->muTrigMatch_0_HLT_mu20_iloose_L1MU15 ->EvalInstance();

  // 2016 trigger
  int value_of_HLT_mu26_ivarmedium                 = this->HLT_mu26_ivarmedium               ->EvalInstance();
  int value_of_muTrigMatch_0_HLT_mu26_ivarmedium   = this->muTrigMatch_0_HLT_mu26_ivarmedium ->EvalInstance();

  int value_of_HLT_mu50                   = this->HLT_mu50               ->EvalInstance();
  int value_of_muTrigMatch_0_HLT_mu50     = this->muTrigMatch_0_HLT_mu50 ->EvalInstance();


  bool passEleTrig = 0;

  bool passEleTrigLow    = 0;
  bool passEleTrigHigh   = 0;
  bool passEleTrigHigher = 0;

  if(value_of_lep_0==2) {
    if(!Is2016) {
      //2015
      passEleTrigLow    = value_of_HLT_e24_lhmedium_L1EM==1 && value_of_eleTrigMatch_0_HLT_e24_lhmedium_L1EM20VH==1;
      passEleTrigHigher = value_of_HLT_e120_lhloose==1 && value_of_eleTrigMatch_0_HLT_e120_lhloose==1;
      passEleTrigHigh  = value_of_HLT_e60_lhmedium==1 && value_of_eleTrigMatch_0_HLT_e60_lhmedium==1;
    }
    else{
      //2016
      passEleTrigLow    = value_of_HLT_e26_lhtight_nod0_ivarloose==1 && value_of_eleTrigMatch_0_HLT_e26_lhtight_nod0_ivarloose==1;
      passEleTrigHigher = value_of_HLT_e140_lhloose_nod0==1 && value_of_eleTrigMatch_0_HLT_e140_lhloose_nod0==1;
      passEleTrigHigh   = value_of_HLT_e60_lhmedium_nod0==1 && value_of_eleTrigMatch_0_HLT_e60_lhmedium_nod0==1;
    }

  }

  if( passEleTrigLow || passEleTrigHigh || passEleTrigHigher ) {
    passEleTrig = 1;
  }

  bool passMuTrig = 0;

  if(value_of_lep_0==1) {
    if (value_of_lep_0_pt > 55 ) {
      passMuTrig = value_of_HLT_mu50==1 && value_of_muTrigMatch_0_HLT_mu50==1;
    }
    else {
      if(!Is2016) {
        //2015
        passMuTrig = value_of_HLT_mu20_iloose_L1MU15==1 && value_of_muTrigMatch_0_HLT_mu20_iloose_L1MU15==1;
      }
      else{
        //2016
        passMuTrig = value_of_HLT_mu26_ivarmedium==1 && value_of_muTrigMatch_0_HLT_mu26_ivarmedium==1;
      }
    }
  }

  double retval = -1;
  if(passEleTrig || passMuTrig) retval = 1;

  DEBUGclass("returning");
  return retval;
}
//______________________________________________________________________________________________

BSMTriggerDecision::BSMTriggerDecision(const TString& expression):
LepHadObservable(expression)
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

const TString& BSMTriggerDecision::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool BSMTriggerDecision::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void BSMTriggerDecision::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool BSMTriggerDecision::initializeSelf(){
  if (! LepHadObservable::initializeSelf()) return false;

  this->lep_0_pt      = new TTreeFormula("lep_0_pt", "lep_0_p4.Pt()", this->fTree);
  this->lep_0         = new TTreeFormula("lep_0",    "lep_0",    this->fTree);

  this->HLT_e24_lhmedium_L1EM20VH                 = new TTreeFormula( "HLT_e24_lhmedium_L1EM20VH", "HLT_e24_lhmedium_L1EM20VH", this->fTree);
  this->eleTrigMatch_0_HLT_e24_lhmedium_L1EM20VH  = new TTreeFormula( "eleTrigMatch_0_HLT_e24_lhmedium_L1EM20VH"  , "eleTrigMatch_0_HLT_e24_lhmedium_L1EM20VH"  , this->fTree);

  this->HLT_e26_lhtight_nod0_ivarloose                 = new TTreeFormula( "HLT_e26_lhtight_nod0_ivarloose", "HLT_e26_lhtight_nod0_ivarloose", this->fTree);
  this->eleTrigMatch_0_HLT_e26_lhtight_nod0_ivarloose  = new TTreeFormula( "eleTrigMatch_0_HLT_e26_lhtight_nod0_ivarloose"  , "eleTrigMatch_0_HLT_e26_lhtight_nod0_ivarloose"  , this->fTree);
  this->HLT_e60_lhmedium                               = new TTreeFormula( "HLT_e60_lhmedium"               , "HLT_e60_lhmedium"               , this->fTree);
  this->eleTrigMatch_0_HLT_e60_lhmedium                = new TTreeFormula( "eleTrigMatch_0_HLT_e60_lhmedium", "eleTrigMatch_0_HLT_e60_lhmedium", this->fTree);
  this->HLT_e60_lhmedium_nod0                               = new TTreeFormula( "HLT_e60_lhmedium_nod0"               , "HLT_e60_lhmedium_nod0"               , this->fTree);
  this->eleTrigMatch_0_HLT_e60_lhmedium_nod0                = new TTreeFormula( "eleTrigMatch_0_HLT_e60_lhmedium_nod0", "eleTrigMatch_0_HLT_e60_lhmedium_nod0", this->fTree);

  this->HLT_e120_lhloose                               = new TTreeFormula( "HLT_e120_lhloose"               , "HLT_e120_lhloose"               , this->fTree);
  this->eleTrigMatch_0_HLT_e120_lhloose                = new TTreeFormula( "eleTrigMatch_0_HLT_e120_lhloose", "eleTrigMatch_0_HLT_e120_lhloose", this->fTree);

  this->HLT_e140_lhloose_nod0                          = new TTreeFormula( "HLT_e140_lhloose_nod0"               , "HLT_e140_lhloose_nod0"               , this->fTree);
  this->eleTrigMatch_0_HLT_e140_lhloose_nod0           = new TTreeFormula( "eleTrigMatch_0_HLT_e140_lhloose_nod0", "eleTrigMatch_0_HLT_e140_lhloose_nod0", this->fTree);

  this->HLT_mu20_iloose_L1MU15                 = new TTreeFormula( "HLT_mu20_iloose_L1MU15"               , "HLT_mu20_iloose_L1MU15"               , this->fTree);
  this->muTrigMatch_0_HLT_mu20_iloose_L1MU15   = new TTreeFormula( "muTrigMatch_0_HLT_mu20_iloose_L1MU15" , "muTrigMatch_0_HLT_mu20_iloose_L1MU15" , this->fTree);

  this->HLT_mu26_ivarmedium                 = new TTreeFormula( "HLT_mu26_ivarmedium"               , "HLT_mu26_ivarmedium"               , this->fTree);
  this->muTrigMatch_0_HLT_mu26_ivarmedium   = new TTreeFormula( "muTrigMatch_0_HLT_mu26_ivarmedium" , "muTrigMatch_0_HLT_mu26_ivarmedium" , this->fTree);
  this->HLT_mu50                         = new TTreeFormula( "HLT_mu50"                       , "HLT_mu50"                       , this->fTree);
  this->muTrigMatch_0_HLT_mu50           = new TTreeFormula( "muTrigMatch_0_HLT_mu50"         , "muTrigMatch_0_HLT_mu50"         , this->fTree);

  return true;
}

//______________________________________________________________________________________________

bool BSMTriggerDecision::finalizeSelf(){
  if (! LepHadObservable::finalizeSelf()) return false;

  delete  this->HLT_e24_lhmedium_L1EM20VH                ;
  delete  this->eleTrigMatch_0_HLT_e24_lhmedium_L1EM20VH ;

  delete  this->HLT_e26_lhtight_nod0_ivarloose                ;
  delete  this->eleTrigMatch_0_HLT_e26_lhtight_nod0_ivarloose ;

  delete  this->HLT_e60_lhmedium_nod0               ;
  delete  this->eleTrigMatch_0_HLT_e60_lhmedium_nod0;

  delete  this->HLT_e60_lhmedium               ;
  delete  this->eleTrigMatch_0_HLT_e60_lhmedium;

  delete  this->HLT_e120_lhloose               ;
  delete  this->eleTrigMatch_0_HLT_e120_lhloose;

  delete  this->HLT_e140_lhloose_nod0               ;
  delete  this->eleTrigMatch_0_HLT_e140_lhloose_nod0;

  delete  this->HLT_mu20_iloose_L1MU15              ;
  delete  this->muTrigMatch_0_HLT_mu20_iloose_L1MU15;

  delete  this->HLT_mu26_ivarmedium              ;
  delete  this->muTrigMatch_0_HLT_mu26_ivarmedium;
  delete  this->HLT_mu50              ;
  delete  this->muTrigMatch_0_HLT_mu50;

  return true;
}
