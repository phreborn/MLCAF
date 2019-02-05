#include "Htautau/BSMTriggerMETDecision.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(BSMTriggerMETDecision)

//______________________________________________________________________________________________

BSMTriggerMETDecision::BSMTriggerMETDecision(){
  // default constructor
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

BSMTriggerMETDecision::~BSMTriggerMETDecision(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* BSMTriggerMETDecision::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();
  bnames->SetOwner(false);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("run_number"));

  if (!fOptionName.Contains("data") ) {
  bnames->Add(new TObjString("NOMINAL_pileup_random_run_number"));
  }

  bnames->Add(new TObjString("lep_0"));
  bnames->Add(new TObjString("lep_0_pt"));
  bnames->Add(new TObjString("lep_0_phi"));
  bnames->Add(new TObjString("met_reco_et"));
  bnames->Add(new TObjString("met_reco_phi"));

  //* 2015 trigger
  bnames->Add(new TObjString("HLT_xe70"       ));
  bnames->Add(new TObjString("HLT_xe70_mht"   ));
  bnames->Add(new TObjString("HLT_xe70_tc_lcw"));

  //* 2016 trigger
  bnames->Add(new TObjString("HLT_xe80_tc_lcw_L1XE50"));
  bnames->Add(new TObjString("HLT_xe90_mht_L1XE50"   ));
  bnames->Add(new TObjString("HLT_xe100_mht_L1XE50"  ));
  bnames->Add(new TObjString("HLT_xe110_mht_L1XE50"  ));

  return bnames;
}

//______________________________________________________________________________________________

double BSMTriggerMETDecision::getValue() const {
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

  UInt_t    run_number = this->run_number->EvalInstance();

  if (!fOptionName.Contains("data") ) {
    run_number = this->NOMINAL_pileup_random_run_number->EvalInstance();
  }

  int    value_of_lep_0    = this->lep_0->EvalInstance();

  double value_of_lep_0_pt     = this->lep_0_pt    ->EvalInstance();
  double value_of_lep_0_phi    = this->lep_0_phi   ->EvalInstance();
  double value_of_met_reco_et  = this->met_reco_et ->EvalInstance();
  double value_of_met_reco_phi = this->met_reco_phi->EvalInstance();

  //* 2015 trigger
  int value_of_HLT_xe70        = this->HLT_xe70        ->EvalInstance();
  int value_of_HLT_xe70_mht    = this->HLT_xe70_mht    ->EvalInstance();
  int value_of_HLT_xe70_tc_lcw = this->HLT_xe70_tc_lcw ->EvalInstance();

  //* 2016 trigger
  int value_of_HLT_xe80_tc_lcw_L1XE50 = this->HLT_xe80_tc_lcw_L1XE50->EvalInstance();
  int value_of_HLT_xe90_mht_L1XE50    = this->HLT_xe90_mht_L1XE50   ->EvalInstance();
  int value_of_HLT_xe100_mht_L1XE50   = this->HLT_xe100_mht_L1XE50  ->EvalInstance();
  int value_of_HLT_xe110_mht_L1XE50   = this->HLT_xe110_mht_L1XE50  ->EvalInstance();

  double x_VectPtMuonMET = value_of_lep_0_pt*cos(value_of_lep_0_phi) + value_of_met_reco_et*cos(value_of_met_reco_phi);
  double y_VectPtMuonMET = value_of_lep_0_pt*sin(value_of_lep_0_phi) + value_of_met_reco_et*sin(value_of_met_reco_phi);
  double VectPtMuonMET = sqrt( x_VectPtMuonMET*x_VectPtMuonMET + y_VectPtMuonMET*y_VectPtMuonMET );

  bool passMetTrig = 0;
  //*2015
  if( run_number<=290000 && VectPtMuonMET>150 )    passMetTrig = value_of_HLT_xe70==1 || value_of_HLT_xe70_mht==1 || value_of_HLT_xe70_tc_lcw==1;

  //*2016
  if ( VectPtMuonMET>150 ) {
    if( run_number>=296939 && run_number<=300908 ) passMetTrig = value_of_HLT_xe80_tc_lcw_L1XE50==1 || value_of_HLT_xe90_mht_L1XE50==1;
    if( run_number>=301912 && run_number<=302393 ) passMetTrig = value_of_HLT_xe90_mht_L1XE50==1;
    if( run_number>=302737 && run_number<=302872 ) passMetTrig = value_of_HLT_xe100_mht_L1XE50==1;
  }
  if( run_number>=302919 && VectPtMuonMET>160 )    passMetTrig = value_of_HLT_xe110_mht_L1XE50==1;

  DEBUGclass("returning");

  if (passMetTrig) return  1;
  else             return -1;

}
//______________________________________________________________________________________________

BSMTriggerMETDecision::BSMTriggerMETDecision(const TString& expression):
TQTreeObservable(expression)
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

const TString& BSMTriggerMETDecision::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool BSMTriggerMETDecision::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void BSMTriggerMETDecision::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool BSMTriggerMETDecision::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void BSMTriggerMETDecision::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString BSMTriggerMETDecision::getActiveExpression() const {
  // retrieve the expression associated with this incarnation
  return "" ;/* you have to build the expression here */;
}

//______________________________________________________________________________________________

bool BSMTriggerMETDecision::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  this->run_number = new TTreeFormula( "run_number", "run_number", this->fTree);

  if (!fOptionName.Contains("data") ) {
  this->NOMINAL_pileup_random_run_number = new TTreeFormula( "NOMINAL_pileup_random_run_number", "NOMINAL_pileup_random_run_number", this->fTree);
  }

  this->lep_0         = new TTreeFormula("lep_0",    "lep_0",    this->fTree);
  this->lep_0_pt      = new TTreeFormula("lep_0_pt", "lep_0_pt", this->fTree);
  this->lep_0_phi     = new TTreeFormula("lep_0_phi", "lep_0_phi", this->fTree);
  this->met_reco_et   = new TTreeFormula("met_reco_et", "met_reco_et", this->fTree);
  this->met_reco_phi  = new TTreeFormula("met_reco_phi", "met_reco_phi", this->fTree);

  //* 2015 trigger
  this->HLT_xe70               = new TTreeFormula( "HLT_xe70"       ,        "HLT_xe70"              , this->fTree);
  this->HLT_xe70_mht           = new TTreeFormula( "HLT_xe70_mht"   ,        "HLT_xe70_mht"          , this->fTree);
  this->HLT_xe70_tc_lcw        = new TTreeFormula( "HLT_xe70_tc_lcw",        "HLT_xe70_tc_lcw"       , this->fTree);

  //* 2016 trigger
  this->HLT_xe80_tc_lcw_L1XE50 = new TTreeFormula( "HLT_xe80_tc_lcw_L1XE50", "HLT_xe80_tc_lcw_L1XE50", this->fTree);
  this->HLT_xe90_mht_L1XE50    = new TTreeFormula( "HLT_xe90_mht_L1XE50"   , "HLT_xe90_mht_L1XE50"   , this->fTree);
  this->HLT_xe100_mht_L1XE50   = new TTreeFormula( "HLT_xe100_mht_L1XE50"  , "HLT_xe100_mht_L1XE50"  , this->fTree);
  this->HLT_xe110_mht_L1XE50   = new TTreeFormula( "HLT_xe110_mht_L1XE50"  , "HLT_xe110_mht_L1XE50"  , this->fTree);


  return true;
}

//______________________________________________________________________________________________

bool BSMTriggerMETDecision::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete  this->run_number;

  if (!fOptionName.Contains("data") ) {
  delete  this->NOMINAL_pileup_random_run_number;
  }

  delete  this->lep_0_pt;
  delete  this->lep_0   ;

  delete  this->lep_0_phi   ;
  delete  this->met_reco_et ;
  delete  this->met_reco_phi;

  delete  this->HLT_xe70       ;
  delete  this->HLT_xe70_mht   ;
  delete  this->HLT_xe70_tc_lcw;

  delete  this->HLT_xe80_tc_lcw_L1XE50;
  delete  this->HLT_xe90_mht_L1XE50   ;
  delete  this->HLT_xe100_mht_L1XE50  ;
  delete  this->HLT_xe110_mht_L1XE50  ;

  return true;
}
