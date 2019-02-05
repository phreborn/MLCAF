#include "Htautau2015/LepSelec_ll.h"
#include <limits>

// uncomment the following line to enable debug printouts
//#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(LepSelec_ll)

//______________________________________________________________________________________________

LepSelec_ll::LepSelec_ll(){
  // default constructor
 
  this->setExpression(this->GetName() );
  
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

LepSelec_ll::~LepSelec_ll(){
  // default destructor
  DEBUGclass("destructor called");
} 


//______________________________________________________________________________________________

TObjArray* LepSelec_ll::getBranchNames() const {
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
  bnames->Add(new TObjString("lep_0_eta"));
  bnames->Add(new TObjString("lep_1_eta"));
  bnames->Add(new TObjString("lep_0_cluster_eta"));
  bnames->Add(new TObjString("lep_1_cluster_eta"));
  bnames->Add(new TObjString("lep_0_id_medium"));
  bnames->Add(new TObjString("lep_1_id_medium"));
  bnames->Add(new TObjString("lep_0_id_loose"));
  bnames->Add(new TObjString("lep_1_id_loose"));
  bnames->Add(new TObjString("lep_0_id_tight"));
  bnames->Add(new TObjString("lep_1_id_tight"));
  bnames->Add(new TObjString("lep_0_iso_wp"));
  bnames->Add(new TObjString("lep_1_iso_wp"));

  
  return bnames;
}

//______________________________________________________________________________________________

double LepSelec_ll::getValue() const {
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
  double lep_0_pt  = this->lep_0_pt->EvalInstance();
  double lep_1_pt  = this->lep_1_pt->EvalInstance();
  double lep_0_eta = fabs(this->lep_0_eta->EvalInstance());
  double lep_1_eta = fabs(this->lep_1_eta->EvalInstance());
  double lep_0_cluster_eta = fabs(this->lep_0_cluster_eta->EvalInstance());
  double lep_1_cluster_eta = fabs(this->lep_1_cluster_eta->EvalInstance());
  int lep_0_id_medium = this->lep_0_id_medium->EvalInstance();
  int lep_1_id_medium = this->lep_1_id_medium->EvalInstance();
  int lep_0_id_loose = this->lep_0_id_loose->EvalInstance();
  int lep_1_id_loose = this->lep_1_id_loose->EvalInstance();
  int lep_0_id_tight = this->lep_0_id_tight->EvalInstance();
  int lep_1_id_tight = this->lep_1_id_tight->EvalInstance();
  int lep_0_iso_wp = this->lep_0_iso_wp->EvalInstance();
  int lep_1_iso_wp = this->lep_1_iso_wp->EvalInstance();


  double pt_elec = 15*1000.;
  double pt_muon = 10*1000.;
  double eta_elec = 2.47;
  double eta_muon = 2.47;

  bool IsSelectLep = 0;

  if(isMedMed){ // two med leptons
    if (lep_0_id_medium == 1 && lep_1_id_medium == 1)
      {
	if ((lep_0_iso_wp % 100) >= 10 && (lep_1_iso_wp % 100) >= 10)
	  {  
	    if (lep_0 == 2 && lep_1 == 2)
	      {
		if(lep_0_pt >= pt_elec && lep_1_pt >= pt_elec && fabs(lep_0_cluster_eta) <= eta_elec && fabs(lep_1_cluster_eta) <= eta_elec)
		  {
		    IsSelectLep=1;
		  }  
	      }
	    else if (lep_0 == 1 && lep_1 == 1)
	      {
		if(lep_0_pt >= pt_muon && lep_1_pt >= pt_muon && fabs(lep_0_eta) <= eta_muon && fabs(lep_1_eta) <= eta_muon)
		  {
		    IsSelectLep=1;
		  }
	      }
	    else if (lep_0 == 2 && lep_1 == 1)
	      {
		if(lep_0_pt >= pt_elec && lep_1_pt >= pt_muon && fabs(lep_0_cluster_eta) <= eta_elec && fabs(lep_1_eta) <= eta_muon)
		  {
		    IsSelectLep=1;
		  }
	      }
	    else if (lep_0 == 1 && lep_1== 2)
	      {
		if(lep_0_pt >= pt_muon && lep_1_pt >= pt_elec && fabs(lep_0_eta) <= eta_muon && fabs(lep_1_cluster_eta) <= eta_elec)
		  {
		    IsSelectLep=1;
		  }
	      }
	  }
      }
  }
  else if (isTightTight){ // two tight leptons
    if (lep_0_id_tight == 1 && lep_1_id_tight == 1)
      {
        if ((lep_0_iso_wp % 100) >= 10 && (lep_1_iso_wp % 100) >= 10)
          {
            if (lep_0 == 2 && lep_1 == 2)
              {
                if(lep_0_pt >= pt_elec && lep_1_pt >= pt_elec && lep_0_cluster_eta <= eta_elec && lep_1_cluster_eta <= eta_elec)
                  {
                    IsSelectLep=1;
                  }
              }
            else if (lep_0 == 1 && lep_1 == 1)
              {
                if(lep_0_pt >= pt_muon && lep_1_pt >= pt_muon && lep_0_eta <= eta_muon && lep_1_eta <= eta_muon)
                  {
                    IsSelectLep=1;
                  }
              }
            else if (lep_0 == 2 && lep_1 == 1)
              {
                if(lep_0_pt >= pt_elec && lep_1_pt >= pt_muon && lep_0_cluster_eta <= eta_elec && lep_1_eta <= eta_muon)
                  {
                    IsSelectLep=1;
                  }
              }
            else if (lep_0 == 1 && lep_1== 2)
	      {
		if(lep_0_pt >= pt_muon && lep_1_pt >= pt_elec && lep_0_eta <= eta_muon && lep_1_cluster_eta <= eta_elec)
		  {
		    IsSelectLep=1;
		  }
	      }
	  }
      }
  }
  else if (isTightLoose){ // tight, loose leptons                                                                                                                                                             
    if (lep_0_id_tight == 1 && lep_1_id_loose == 1)
      {
	if ((lep_0_iso_wp % 100) >= 10 && (lep_1_iso_wp % 100) >= 10)
          {
            if (lep_0 == 2 && lep_1 == 2)
              {
                if(lep_0_pt >= pt_elec && lep_1_pt >= pt_elec && lep_0_cluster_eta <= eta_elec && lep_1_cluster_eta <= eta_elec)
                  {
                    IsSelectLep=1;
                  }
              }
            else if (lep_0 == 1 && lep_1 == 1)
              {
                if(lep_0_pt >= pt_muon && lep_1_pt >= pt_muon && lep_0_eta <= eta_muon && lep_1_eta <= eta_muon)
                  {
                    IsSelectLep=1;
                  }
              }
            else if (lep_0 == 2 && lep_1 == 1)
              {
                if(lep_0_pt >= pt_elec && lep_1_pt >= pt_muon && lep_0_cluster_eta <= eta_elec && lep_1_eta <= eta_muon)
                  {
                    IsSelectLep=1;
                  }
              }
            else if (lep_0 == 1 && lep_1== 2)
              {
                if(lep_0_pt >= pt_muon && lep_1_pt >= pt_elec && lep_0_eta <= eta_muon && lep_1_cluster_eta <= eta_elec)
                  {
                    IsSelectLep=1;
                  }
              }
          }
      }
  }

  DEBUGclass("returning");

  return IsSelectLep;
}
//______________________________________________________________________________________________

LepSelec_ll::LepSelec_ll(const TString& expression):
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
  else{
    DEBUGclass("ERROR: No lepton selection criteria found for '%s'", expression);
  }

}

//______________________________________________________________________________________________

const TString& LepSelec_ll::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool LepSelec_ll::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void LepSelec_ll::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool LepSelec_ll::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void LepSelec_ll::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString LepSelec_ll::getActiveExpression() const {
  // retrieve the expression associated with this incarnation
  
  return this->getExpression();
}

//______________________________________________________________________________________________

bool LepSelec_ll::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  // this->bla = new TTreeFormula( "name", "formula", this->fTree);
  
  this->lep_0 = new TTreeFormula( "lep_0", "lep_0", this->fTree);
  this->lep_1 = new TTreeFormula( "lep_1", "lep_1", this->fTree);
  this->lep_0_pt  = new TTreeFormula( "lep_0_pt", "lep_0_pt", this->fTree);
  this->lep_1_pt  = new TTreeFormula( "lep_1_pt", "lep_1_pt", this->fTree);
  this->lep_0_eta = new TTreeFormula( "lep_0_eta", "lep_0_eta", this->fTree);
  this->lep_1_eta = new TTreeFormula( "lep_1_eta", "lep_1_eta", this->fTree);
  this->lep_0_cluster_eta = new TTreeFormula( "lep_0_cluster_eta", "lep_0_cluster_eta", this->fTree);
  this->lep_1_cluster_eta = new TTreeFormula( "lep_1_cluster_eta", "lep_1_cluster_eta", this->fTree);
  this->lep_0_id_medium = new TTreeFormula( "lep_0_id_medium", "lep_0_id_medium", this->fTree);
  this->lep_1_id_medium = new TTreeFormula( "lep_1_id_medium", "lep_1_id_medium", this->fTree);
  this->lep_0_id_loose = new TTreeFormula( "lep_0_id_loose", "lep_0_id_loose", this->fTree);
  this->lep_1_id_loose = new TTreeFormula( "lep_1_id_loose", "lep_1_id_loose", this->fTree);
  this->lep_0_id_tight = new TTreeFormula( "lep_0_id_tight", "lep_0_id_tight", this->fTree);
  this->lep_1_id_tight = new TTreeFormula( "lep_1_id_tight", "lep_1_id_tight", this->fTree);
  this->lep_0_iso_wp = new TTreeFormula( "lep_0_iso_wp", "lep_0_iso_wp", this->fTree);
  this->lep_1_iso_wp = new TTreeFormula( "lep_1_iso_wp", "lep_1_iso_wp", this->fTree);

  return true;
}
 
//______________________________________________________________________________________________

bool LepSelec_ll::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();
  
  delete this->lep_0;
  delete this->lep_1;
  delete this->lep_0_pt;
  delete this->lep_1_pt;
  delete this->lep_0_eta;
  delete this->lep_1_eta;
  delete this->lep_0_cluster_eta;
  delete this->lep_1_cluster_eta;
  delete this->lep_0_id_medium;
  delete this->lep_1_id_medium;
  delete this->lep_0_id_loose;
  delete this->lep_1_id_loose;
  delete this->lep_0_id_tight;
  delete this->lep_1_id_tight;
  delete this->lep_0_iso_wp;
  delete this->lep_1_iso_wp;
  



  return true;
}
