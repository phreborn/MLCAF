#include "Htautau/Trigger.h"
#include <limits>

// uncomment the following line to enable debug printouts
//#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(Trigger)

//______________________________________________________________________________________________

Trigger::Trigger(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

Trigger::~Trigger(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* Trigger::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo"));
  bnames->Add(new TObjString("eleTrigMatch_0_HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo"));
  bnames->Add(new TObjString("tau_0_trig_HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo"));

  bnames->Add(new TObjString("HLT_mu14_tau25_medium1_tracktwo"));
  bnames->Add(new TObjString("muTrigMatch_0_HLT_mu14_tau25_medium1_tracktwo"));
  bnames->Add(new TObjString("tau_0_trig_HLT_mu14_tau25_medium1_tracktwo"));

  bnames->Add(new TObjString("HLT_mu20_iloose_L1MU15"));
  bnames->Add(new TObjString("muTrigMatch_0_HLT_mu20_iloose_L1MU15"));

  bnames->Add(new TObjString("HLT_mu40"));
  bnames->Add(new TObjString("muTrigMatch_0_HLT_mu40"));

  bnames->Add(new TObjString("HLT_e24_lhmedium_L1EM20VH"));
  bnames->Add(new TObjString("eleTrigMatch_0_HLT_e24_lhmedium_L1EM20VH"));

  bnames->Add(new TObjString("HLT_e60_lhmedium"));
  bnames->Add(new TObjString("eleTrigMatch_0_HLT_e60_lhmedium"));

  bnames->Add(new TObjString("HLT_e120_lhloose"));
  bnames->Add(new TObjString("eleTrigMatch_0_HLT_e120_lhloose"));

  bnames->Add(new TObjString("HLT_e24_lhtight_nod0_ivarloose"));
  bnames->Add(new TObjString("eleTrigMatch_0_HLT_e24_lhtight_nod0_ivarloose"));

  bnames->Add(new TObjString("HLT_e60_lhmedium_nod0"));
  bnames->Add(new TObjString("eleTrigMatch_0_HLT_e60_lhmedium_nod0"));

  bnames->Add(new TObjString("HLT_e140_lhloose_nod0"));
  bnames->Add(new TObjString("eleTrigMatch_0_HLT_e140_lhloose_nod0"));

  bnames->Add(new TObjString("HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo"));
  bnames->Add(new TObjString("eleTrigMatch_0_HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo"));
  bnames->Add(new TObjString("tau_0_trig_HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo"));

  bnames->Add(new TObjString("HLT_mu24_imedium"));
  bnames->Add(new TObjString("muTrigMatch_0_HLT_mu24_imedium"));

  bnames->Add(new TObjString("HLT_mu50"));
  bnames->Add(new TObjString("muTrigMatch_0_HLT_mu50"));

  bnames->Add(new TObjString("HLT_mu14_iloose_tau25_medium1_tracktwo"));
  bnames->Add(new TObjString("muTrigMatch_0_HLT_mu14_iloose_tau25_medium1_tracktwo"));
  bnames->Add(new TObjString("tau_0_trig_HLT_mu14_iloose_tau25_medium1_tracktwo"));

  return bnames;
}

//______________________________________________________________________________________________

double Trigger::getValue() const {
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

  int HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo = this->HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo->EvalInstance();
  int eleTrigMatch_0_HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo = this->eleTrigMatch_0_HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo->EvalInstance();
  int tau_0_trig_HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo = this->tau_0_trig_HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo->EvalInstance();

  int HLT_mu14_tau25_medium1_tracktwo = this->HLT_mu14_tau25_medium1_tracktwo->EvalInstance();
  int muTrigMatch_0_HLT_mu14_tau25_medium1_tracktwo = this->muTrigMatch_0_HLT_mu14_tau25_medium1_tracktwo->EvalInstance();
  int tau_0_trig_HLT_mu14_tau25_medium1_tracktwo = this->tau_0_trig_HLT_mu14_tau25_medium1_tracktwo->EvalInstance();

  int HLT_mu20_iloose_L1MU15 = this->HLT_mu20_iloose_L1MU15->EvalInstance();
  int muTrigMatch_0_HLT_mu20_iloose_L1MU15 = this->muTrigMatch_0_HLT_mu20_iloose_L1MU15->EvalInstance();

  int HLT_mu40 = this->HLT_mu40->EvalInstance();
  int muTrigMatch_0_HLT_mu40 = this->muTrigMatch_0_HLT_mu40->EvalInstance();

  int HLT_e24_lhmedium_L1EM20VH = this->HLT_e24_lhmedium_L1EM20VH->EvalInstance();
  int eleTrigMatch_0_HLT_e24_lhmedium_L1EM20VH = this->eleTrigMatch_0_HLT_e24_lhmedium_L1EM20VH->EvalInstance();

  int HLT_e60_lhmedium = this->HLT_e60_lhmedium->EvalInstance();
  int eleTrigMatch_0_HLT_e60_lhmedium = this->eleTrigMatch_0_HLT_e60_lhmedium->EvalInstance();

  int HLT_e120_lhloose = this->HLT_e120_lhloose->EvalInstance();
  int eleTrigMatch_0_HLT_e120_lhloose = this->eleTrigMatch_0_HLT_e120_lhloose->EvalInstance();

  int HLT_e24_lhtight_nod0_ivarloose = this->HLT_e24_lhtight_nod0_ivarloose->EvalInstance();
  int eleTrigMatch_0_HLT_e24_lhtight_nod0_ivarloose = this->eleTrigMatch_0_HLT_e24_lhtight_nod0_ivarloose->EvalInstance();

  int HLT_e60_lhmedium_nod0 = this->HLT_e60_lhmedium_nod0->EvalInstance();
  int eleTrigMatch_0_HLT_e60_lhmedium_nod0 = this->eleTrigMatch_0_HLT_e60_lhmedium_nod0->EvalInstance();

  int HLT_e140_lhloose_nod0 = this->HLT_e140_lhloose_nod0->EvalInstance();
  int eleTrigMatch_0_HLT_e140_lhloose_nod0 = this->eleTrigMatch_0_HLT_e140_lhloose_nod0->EvalInstance();

  int HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo = this->HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo->EvalInstance();
  int eleTrigMatch_0_HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo = this->eleTrigMatch_0_HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo->EvalInstance();
  int tau_0_trig_HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo = this->tau_0_trig_HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo->EvalInstance();

  int HLT_mu24_imedium = this->HLT_mu24_imedium->EvalInstance();
  int muTrigMatch_0_HLT_mu24_imedium = this->muTrigMatch_0_HLT_mu24_imedium->EvalInstance();

  int HLT_mu50 = this->HLT_mu50->EvalInstance();
  int muTrigMatch_0_HLT_mu50 = this->muTrigMatch_0_HLT_mu50->EvalInstance();

  int HLT_mu14_iloose_tau25_medium1_tracktwo = this->HLT_mu14_iloose_tau25_medium1_tracktwo->EvalInstance();
  int muTrigMatch_0_HLT_mu14_iloose_tau25_medium1_tracktwo = this->muTrigMatch_0_HLT_mu14_iloose_tau25_medium1_tracktwo->EvalInstance();
  int tau_0_trig_HLT_mu14_iloose_tau25_medium1_tracktwo = this->tau_0_trig_HLT_mu14_iloose_tau25_medium1_tracktwo->EvalInstance();

  bool isTrigger = false;

  if (isMuon()) {
      if (isSLT()) {
          if (is2015()) {
    	      isTrigger = (HLT_mu20_iloose_L1MU15 == 1 && muTrigMatch_0_HLT_mu20_iloose_L1MU15 == 1) || (HLT_mu40 == 1 && muTrigMatch_0_HLT_mu40 == 1);
          } else if (is2016()) {
        	  isTrigger = (HLT_mu24_imedium == 1 && muTrigMatch_0_HLT_mu24_imedium == 1) || (HLT_mu50 == 1 && muTrigMatch_0_HLT_mu50 == 1);
          }
	    } else if (isTLT()) {
          if (is2015()) {
        	  isTrigger = (HLT_mu14_tau25_medium1_tracktwo == 1 && muTrigMatch_0_HLT_mu14_tau25_medium1_tracktwo && tau_0_trig_HLT_mu14_tau25_medium1_tracktwo == 1);
          } else if (is2016()) {
       	    isTrigger = (HLT_mu14_iloose_tau25_medium1_tracktwo == 1 && muTrigMatch_0_HLT_mu14_iloose_tau25_medium1_tracktwo && tau_0_trig_HLT_mu14_iloose_tau25_medium1_tracktwo == 1);
          }
      }
  } else if (isElectron()) {
      if (isSLT()) {
          if (is2015()) {
  	        isTrigger = (HLT_e24_lhmedium_L1EM20VH == 1 && eleTrigMatch_0_HLT_e24_lhmedium_L1EM20VH == 1) || (HLT_e60_lhmedium == 1 && eleTrigMatch_0_HLT_e60_lhmedium == 1) || (HLT_e120_lhloose == 1 && eleTrigMatch_0_HLT_e120_lhloose == 1);
          } else if (is2016()) {
      	    isTrigger = (HLT_e24_lhtight_nod0_ivarloose == 1 && eleTrigMatch_0_HLT_e24_lhtight_nod0_ivarloose == 1) || (HLT_e60_lhmedium_nod0 == 1 && eleTrigMatch_0_HLT_e60_lhmedium_nod0 == 1) || (HLT_e140_lhloose_nod0 == 1 && eleTrigMatch_0_HLT_e140_lhloose_nod0 == 1);
          }
     	} else if (isTLT()) {
          if (is2015()) {
        	  isTrigger = (HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo == 1 && eleTrigMatch_0_HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo == 1 && tau_0_trig_HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo == 1);
          } else if (is2016()) {
         	  isTrigger = (HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo == 1 && eleTrigMatch_0_HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo == 1 && tau_0_trig_HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo == 1);
        	}
      }
  }

  DEBUGclass("returning");

  return isTrigger;
}
//______________________________________________________________________________________________

Trigger::Trigger(const TString& expression): LepHadObservable(expression)
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
bool Trigger::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________
bool Trigger::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if (!LepHadObservable::initializeSelf()) {
      return false;
  }

  // this->bla = new TTreeFormula( "name", "formula", this->fTree);
  this->HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo = new TTreeFormula( "HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo", "HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo", this->fTree);
  this->eleTrigMatch_0_HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo = new TTreeFormula( "eleTrigMatch_0_HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo", "eleTrigMatch_0_HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo", this->fTree);
  this->tau_0_trig_HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo = new TTreeFormula( "tau_0_trig_HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo", "tau_0_trig_HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo", this->fTree);

  this->HLT_mu14_tau25_medium1_tracktwo = new TTreeFormula( "HLT_mu14_tau25_medium1_tracktwo", "HLT_mu14_tau25_medium1_tracktwo", this->fTree);
  this->muTrigMatch_0_HLT_mu14_tau25_medium1_tracktwo = new TTreeFormula( "muTrigMatch_0_HLT_mu14_tau25_medium1_tracktwo", "muTrigMatch_0_HLT_mu14_tau25_medium1_tracktwo", this->fTree);
  this->tau_0_trig_HLT_mu14_tau25_medium1_tracktwo = new TTreeFormula( "tau_0_trig_HLT_mu14_tau25_medium1_tracktwo", "tau_0_trig_HLT_mu14_tau25_medium1_tracktwo", this->fTree);

  this->HLT_mu20_iloose_L1MU15 = new TTreeFormula( "HLT_mu20_iloose_L1MU15", "HLT_mu20_iloose_L1MU15", this->fTree);
  this->muTrigMatch_0_HLT_mu20_iloose_L1MU15 = new TTreeFormula( "muTrigMatch_0_HLT_mu20_iloose_L1MU15", "muTrigMatch_0_HLT_mu20_iloose_L1MU15", this->fTree);

  this->HLT_mu40 = new TTreeFormula( "HLT_mu40", "HLT_mu40", this->fTree);
  this->muTrigMatch_0_HLT_mu40 = new TTreeFormula( "muTrigMatch_0_HLT_mu40", "muTrigMatch_0_HLT_mu40", this->fTree);

  this->HLT_e24_lhmedium_L1EM20VH = new TTreeFormula( "HLT_e24_lhmedium_L1EM20VH", "HLT_e24_lhmedium_L1EM20VH", this->fTree);
  this->eleTrigMatch_0_HLT_e24_lhmedium_L1EM20VH = new TTreeFormula( "eleTrigMatch_0_HLT_e24_lhmedium_L1EM20VH", "eleTrigMatch_0_HLT_e24_lhmedium_L1EM20VH", this->fTree);

  this->HLT_e60_lhmedium = new TTreeFormula( "HLT_e60_lhmedium", "HLT_e60_lhmedium", this->fTree);
  this->eleTrigMatch_0_HLT_e60_lhmedium = new TTreeFormula( "eleTrigMatch_0_HLT_e60_lhmedium", "eleTrigMatch_0_HLT_e60_lhmedium", this->fTree);

  this->HLT_e120_lhloose = new TTreeFormula( "HLT_e120_lhloose", "HLT_e120_lhloose", this->fTree);
  this->eleTrigMatch_0_HLT_e120_lhloose = new TTreeFormula( "eleTrigMatch_0_HLT_e120_lhloose", "eleTrigMatch_0_HLT_e120_lhloose", this->fTree);

  this->HLT_e24_lhtight_nod0_ivarloose = new TTreeFormula( "HLT_e24_lhtight_nod0_ivarloose", "HLT_e24_lhtight_nod0_ivarloose", this->fTree);
  this->eleTrigMatch_0_HLT_e24_lhtight_nod0_ivarloose = new TTreeFormula( "eleTrigMatch_0_HLT_e24_lhtight_nod0_ivarloose", "eleTrigMatch_0_HLT_e24_lhtight_nod0_ivarloose", this->fTree);

  this->HLT_e60_lhmedium_nod0 = new TTreeFormula( "HLT_e60_lhmedium_nod0", "HLT_e60_lhmedium_nod0", this->fTree);
  this->eleTrigMatch_0_HLT_e60_lhmedium_nod0 = new TTreeFormula( "eleTrigMatch_0_HLT_e60_lhmedium_nod0", "eleTrigMatch_0_HLT_e60_lhmedium_nod0", this->fTree);

  this->HLT_e140_lhloose_nod0 = new TTreeFormula( "HLT_e140_lhloose_nod0", "HLT_e140_lhloose_nod0", this->fTree);
  this->eleTrigMatch_0_HLT_e140_lhloose_nod0 = new TTreeFormula( "eleTrigMatch_0_HLT_e140_lhloose_nod0", "eleTrigMatch_0_HLT_e140_lhloose_nod0", this->fTree);

  this->HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo = new TTreeFormula( "HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo", "HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo", this->fTree);
  this->eleTrigMatch_0_HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo = new TTreeFormula( "eleTrigMatch_0_HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo", "eleTrigMatch_0_HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo", this->fTree);
  this->tau_0_trig_HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo = new TTreeFormula( "tau_0_trig_HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo", "tau_0_trig_HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo", this->fTree);

  this->HLT_mu24_imedium = new TTreeFormula( "HLT_mu24_imedium", "HLT_mu24_imedium", this->fTree);
  this->muTrigMatch_0_HLT_mu24_imedium = new TTreeFormula( "muTrigMatch_0_HLT_mu24_imedium", "muTrigMatch_0_HLT_mu24_imedium", this->fTree);

  this->HLT_mu50 = new TTreeFormula( "HLT_mu50", "HLT_mu50", this->fTree);
  this->muTrigMatch_0_HLT_mu50 = new TTreeFormula( "muTrigMatch_0_HLT_mu50", "muTrigMatch_0_HLT_mu50", this->fTree);

  this->HLT_mu14_iloose_tau25_medium1_tracktwo = new TTreeFormula( "HLT_mu14_iloose_tau25_medium1_tracktwo", "HLT_mu14_iloose_tau25_medium1_tracktwo", this->fTree);
  this->muTrigMatch_0_HLT_mu14_iloose_tau25_medium1_tracktwo = new TTreeFormula( "muTrigMatch_0_HLT_mu14_iloose_tau25_medium1_tracktwo", "muTrigMatch_0_HLT_mu14_iloose_tau25_medium1_tracktwo", this->fTree);
  this->tau_0_trig_HLT_mu14_iloose_tau25_medium1_tracktwo = new TTreeFormula( "tau_0_trig_HLT_mu14_iloose_tau25_medium1_tracktwo", "tau_0_trig_HLT_mu14_iloose_tau25_medium1_tracktwo", this->fTree);

  return true;
}

//______________________________________________________________________________________________

bool Trigger::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete this->HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo;
  delete this->eleTrigMatch_0_HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo;
  delete this->tau_0_trig_HLT_e17_lhmedium_nod0_tau25_medium1_tracktwo;

  delete this->HLT_mu14_tau25_medium1_tracktwo;
  delete this->muTrigMatch_0_HLT_mu14_tau25_medium1_tracktwo;
  delete this->tau_0_trig_HLT_mu14_tau25_medium1_tracktwo;

  delete this->HLT_mu20_iloose_L1MU15;
  delete this->muTrigMatch_0_HLT_mu20_iloose_L1MU15;

  delete this->HLT_mu40;
  delete this->muTrigMatch_0_HLT_mu40;

  delete this->HLT_e24_lhmedium_L1EM20VH;
  delete this->eleTrigMatch_0_HLT_e24_lhmedium_L1EM20VH;

  delete this->HLT_e60_lhmedium;
  delete this->eleTrigMatch_0_HLT_e60_lhmedium;

  delete this->HLT_e120_lhloose;
  delete this->eleTrigMatch_0_HLT_e120_lhloose;

  delete this->HLT_e24_lhtight_nod0_ivarloose;
  delete this->eleTrigMatch_0_HLT_e24_lhtight_nod0_ivarloose;

  delete this->HLT_e60_lhmedium_nod0;
  delete this->eleTrigMatch_0_HLT_e60_lhmedium_nod0;

  delete this->HLT_e140_lhloose_nod0;
  delete this->eleTrigMatch_0_HLT_e140_lhloose_nod0;

  delete this->HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo;
  delete this->eleTrigMatch_0_HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo;
  delete this->tau_0_trig_HLT_e17_lhmedium_nod0_iloose_tau25_medium1_tracktwo;

  delete this->HLT_mu24_imedium;
  delete this->muTrigMatch_0_HLT_mu24_imedium;

  delete this->HLT_mu50;
  delete this->muTrigMatch_0_HLT_mu50;

  delete this->HLT_mu14_iloose_tau25_medium1_tracktwo;
  delete this->muTrigMatch_0_HLT_mu14_iloose_tau25_medium1_tracktwo;
  delete this->tau_0_trig_HLT_mu14_iloose_tau25_medium1_tracktwo;

  return true;
}
