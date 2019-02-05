#include "Htautau/TriggerSF.h"
#include <limits>

// uncomment the following line to enable debug printouts
//#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(TriggerSF)

//______________________________________________________________________________________________

TriggerSF::TriggerSF(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

TriggerSF::~TriggerSF(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* TriggerSF::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("jet_0_pt"));
  bnames->Add(new TObjString("jet_0_eta"));
  bnames->Add(new TObjString("tau_0_pt"));
  bnames->Add(new TObjString("lep_0_pt"));

  bnames->Add(new TObjString("n_muons"));
  bnames->Add(new TObjString("n_electrons"));

  bnames->Add(new TObjString("tau_0_NOMINAL_effSF_HLT_tau25_medium1_tracktwo_JETIDBDTMEDIUM"));
  bnames->Add(new TObjString("lep_0_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("lep_0_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04"));

  bnames->Add(new TObjString("lep_0_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE"));
  bnames->Add(new TObjString("lep_0_NOMINAL_HLT_mu14_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE"));

  return bnames;
}

//______________________________________________________________________________________________

double TriggerSF::getValue() const {
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

  double jet_0_pt = this->jet_0_pt->EvalInstance();
  double jet_0_eta = this->jet_0_eta->EvalInstance();
  double tau_0_pt = this->tau_0_pt->EvalInstance();
  double lep_0_pt = this->lep_0_pt->EvalInstance();

  int n_muons = this->n_muons->EvalInstance();
  int n_electrons = this->n_electrons->EvalInstance();

  double tau_0_NOMINAL_effSF_HLT_tau25_medium1_tracktwo_JETIDBDTMEDIUM = this->tau_0_NOMINAL_effSF_HLT_tau25_medium1_tracktwo_JETIDBDTMEDIUM->EvalInstance();
  double lep_0_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04 = this->lep_0_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04->EvalInstance();
  double lep_0_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04 = this->lep_0_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04->EvalInstance();

  double lep_0_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE = this->lep_0_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE->EvalInstance();
  double lep_0_NOMINAL_HLT_mu14_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE = this->lep_0_NOMINAL_HLT_mu14_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE->EvalInstance();

  double triggerSF = 0.;

  if (n_muons > 0 && n_electrons == 0)
    {
      if (lep_0_pt > 22.)
      	{
	  triggerSF = lep_0_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE;
	  //triggerSF = 0.;
      	}
      else if (lep_0_pt > 16. && lep_0_pt < 22. && tau_0_pt > 30. && jet_0_pt > 70. && fabs(jet_0_eta) < 3.)
      	{
	  triggerSF = tau_0_NOMINAL_effSF_HLT_tau25_medium1_tracktwo_JETIDBDTMEDIUM;
	  //triggerSF = 0.;
      	}
      else
      	{
      	  triggerSF = 0.;
      	}
    }
  else if (n_electrons > 0 && n_muons == 0)
    {
      if (lep_0_pt > 26.)
      	{
	  triggerSF = lep_0_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04;
	  //triggerSF = 0.;
      	}
      else if (lep_0_pt > 19. && lep_0_pt < 26. && tau_0_pt > 30. && jet_0_pt > 70. && fabs(jet_0_eta) < 3.)
      	{
	  triggerSF = tau_0_NOMINAL_effSF_HLT_tau25_medium1_tracktwo_JETIDBDTMEDIUM;
	  //triggerSF = 0.;
      	}
      else
      	{
      	  triggerSF = 0.;
      	}
    }
  else
    {
      triggerSF = 0.;
    }

  DEBUGclass("returning");

  return triggerSF;
}
//______________________________________________________________________________________________

TriggerSF::TriggerSF(const TString& expression):
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

const TString& TriggerSF::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool TriggerSF::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void TriggerSF::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool TriggerSF::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void TriggerSF::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString TriggerSF::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool TriggerSF::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  // this->bla = new TTreeFormula( "name", "formula", this->fTree);

  this->jet_0_pt = new TTreeFormula( "jet_0_pt", "jet_0_pt", this->fTree);
  this->jet_0_eta = new TTreeFormula( "jet_0_eta", "jet_0_eta", this->fTree);
  this->tau_0_pt = new TTreeFormula( "tau_0_pt", "tau_0_pt", this->fTree);
  this->lep_0_pt = new TTreeFormula( "lep_0_pt", "lep_0_pt", this->fTree);

  this->n_muons = new TTreeFormula( "n_muons", "n_muons", this->fTree);
  this->n_electrons = new TTreeFormula( "n_electrons", "n_electrons", this->fTree);

  this->tau_0_NOMINAL_effSF_HLT_tau25_medium1_tracktwo_JETIDBDTMEDIUM = new TTreeFormula( "tau_0_NOMINAL_effSF_HLT_tau25_medium1_tracktwo_JETIDBDTMEDIUM", "tau_0_NOMINAL_effSF_HLT_tau25_medium1_tracktwo_JETIDBDTMEDIUM", this->fTree);
  this->lep_0_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04 = new TTreeFormula( "lep_0_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04", "lep_0_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->lep_0_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04 = new TTreeFormula( "lep_0_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04", "lep_0_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04", this->fTree);

  this->lep_0_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE = new TTreeFormula( "lep_0_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE", "lep_0_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE", this->fTree);
  this->lep_0_NOMINAL_HLT_mu14_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE = new TTreeFormula( "lep_0_NOMINAL_HLT_mu14_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE", "lep_0_NOMINAL_HLT_mu14_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE", this->fTree);

  return true;
}

//______________________________________________________________________________________________

bool TriggerSF::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete this->jet_0_pt;
  delete this->jet_0_eta;
  delete this->tau_0_pt;
  delete this->lep_0_pt;

  delete this->n_muons;
  delete this->n_electrons;

  delete this->tau_0_NOMINAL_effSF_HLT_tau25_medium1_tracktwo_JETIDBDTMEDIUM;
  delete this->lep_0_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04;
  delete this->lep_0_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04;

  delete this->lep_0_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE;
  delete this->lep_0_NOMINAL_HLT_mu14_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE;

  return true;
}
