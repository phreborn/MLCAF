#include "BSMtautauCAF/TruthTauSelector.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(TruthTauSelector)

//______________________________________________________________________________________________

TruthTauSelector::TruthTauSelector(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

TruthTauSelector::~TruthTauSelector(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* TruthTauSelector::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("tau_0_truth_isHadTau"));
  bnames->Add(new TObjString("tau_0_truth_isEle"));
  bnames->Add(new TObjString("tau_0_truth_isMuon"));
  bnames->Add(new TObjString("tau_0_truth_pdgId"));
  bnames->Add(new TObjString("tau_0_truth_classifierParticleType"));

  return bnames;
}

//______________________________________________________________________________________________

double TruthTauSelector::getValue() const {

  int retval = -666;
  if (isData()) return retval;

  int temp_tau_0_truth_isHadTau = this->tau_0_truth_isHadTau->EvalInstance();
  int temp_tau_0_truth_isEle    = this->tau_0_truth_isEle->EvalInstance();
  int temp_tau_0_truth_isMuon   = this->tau_0_truth_isMuon->EvalInstance();
  int temp_tau_0_truth_pdgId    = this->tau_0_truth_pdgId->EvalInstance();
  int temp_tau_0_truth_type     = this->tau_0_truth_classifierParticleType->EvalInstance();

  bool isTrueEleFake = temp_tau_0_truth_isEle == 1 && temp_tau_0_truth_type == 2;
  bool isTrueMuFake  = temp_tau_0_truth_isMuon == 1 && temp_tau_0_truth_type == 6;
  bool isTrueTau     = temp_tau_0_truth_isHadTau == 1;

  if(isTrueTau) {
    retval = 30;  //Truth tau
  }
  else if(isTrueMuFake) {
    retval = 20;  //Mu fake
  }
  else if(isTrueEleFake) {
    retval = 5;   //Ele fake
  }
  else {
    retval = -30; //Jet fake
  }

  DEBUGclass("returning");
  //return 0;
  return retval;
}
//______________________________________________________________________________________________

TruthTauSelector::TruthTauSelector(const TString& expression):
LepHadObservable(expression)
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

const TString& TruthTauSelector::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool TruthTauSelector::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void TruthTauSelector::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}

//______________________________________________________________________________________________

bool TruthTauSelector::initializeSelf(){
  if (!this->fSample->getTag("~isData", _isData)) {
    ERROR("tag isData missing");
    return false;
  }

  if ( !isData()) {
    this->tau_0_truth_isHadTau  = new TTreeFormula("tau_0_truth_isHadTau",  "tau_0_truth_isHadTau", this->fTree);
    this->tau_0_truth_isEle     = new TTreeFormula("tau_0_truth_isEle",     "tau_0_truth_isEle",    this->fTree);
    this->tau_0_truth_isMuon    = new TTreeFormula("tau_0_truth_isMuon",    "tau_0_truth_isMuon",   this->fTree);
    this->tau_0_truth_pdgId     = new TTreeFormula("tau_0_truth_pdgId",     "tau_0_truth_pdgId",    this->fTree);
    this->tau_0_truth_classifierParticleType      = new TTreeFormula("tau_0_truth_classifierParticleType",      "tau_0_truth_classifierParticleType",     this->fTree);
  }
  return true;
}

//______________________________________________________________________________________________

bool TruthTauSelector::finalizeSelf(){
  if ( !isData()) {
    delete this->tau_0_truth_isHadTau;
    delete this->tau_0_truth_isEle;
    delete this->tau_0_truth_isMuon;
    delete this->tau_0_truth_pdgId;
    delete this->tau_0_truth_classifierParticleType;
  }

  return true;
}
