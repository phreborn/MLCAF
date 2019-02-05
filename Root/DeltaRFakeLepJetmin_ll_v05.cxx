#include "Htautau/DeltaRFakeLepJetmin_ll_v05.h"
#include <limits>

// uncomment the following line to enable debug printouts
//#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
#include "Htautau/EventSelection_leplep_default.h"
#include "Htautau/EventSelection_leplep_fake.h"

ClassImp(DeltaRFakeLepJetmin_ll_v05)

//______________________________________________________________________________________________

DeltaRFakeLepJetmin_ll_v05::DeltaRFakeLepJetmin_ll_v05(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

DeltaRFakeLepJetmin_ll_v05::~DeltaRFakeLepJetmin_ll_v05(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* DeltaRFakeLepJetmin_ll_v05::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));


  bnames->Add(new TObjString("leptons_pt"));
  bnames->Add(new TObjString("leptons_eta"));
  bnames->Add(new TObjString("leptons_phi"));
  bnames->Add(new TObjString("leptons_m"));
  bnames->Add(new TObjString("jets_pt"));
  bnames->Add(new TObjString("jets_eta"));
  bnames->Add(new TObjString("jets_phi"));
  bnames->Add(new TObjString("jets_m"));

  return bnames;
}

//______________________________________________________________________________________________

double DeltaRFakeLepJetmin_ll_v05::getValue() const {
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


  leptons_pt->GetNdata();
  leptons_eta->GetNdata();
  leptons_phi->GetNdata();
  leptons_m->GetNdata();

  jets_pt->GetNdata();
  jets_eta->GetNdata();
  jets_phi->GetNdata();
  jets_m->GetNdata();

  int idx1 = -1;

  double dRlj = 9999999.;

  if(useFakeSelec){
    idx1 = EVS_fake->getLeptonIdx(1);
  }
  else {
    idx1 = EVS->getLeptonIdx(1);
  }
  //build lepton TLV
  TLorentzVector lep1; lep1.Clear();
  if(idx1 >= 0){
    //std::cout << "I have a subleading lepton at " << idx1 << std::endl;
    lep1.SetPtEtaPhiM(leptons_pt->EvalInstance(idx1), leptons_eta->EvalInstance(idx1), leptons_phi->EvalInstance(idx1), leptons_m->EvalInstance(idx1));
    int nJet = -1;
    if(useFakeSelec){
      nJet = EVS_fake->getNJet();
    }
    else {
      nJet = EVS->getNJet();
    }
    for(int i=0; i<nJet; i++){
      int idxj = -1;
      if(useFakeSelec){
	idxj = EVS_fake->getNJet();
      }
      else {
	idxj = EVS->getNJet();
      }
      //std::cout << "Found jet at " <<  idxj << std::endl;
      TLorentzVector jet; jet.Clear();
      if(idxj>=0){
        jet.SetPtEtaPhiM(jets_pt->EvalInstance(idxj), jets_eta->EvalInstance(idxj), jets_phi->EvalInstance(idxj), jets_m->EvalInstance(idxj));
        double dRlj_tmp = lep1.DeltaR(jet);
        if(dRlj_tmp < dRlj){
	  //std::cout << "found new min with jet " << idxj << ": " << dRlj_tmp << std::endl;
          dRlj = dRlj_tmp;
        }
      }
    }
  }

  //std::cout << "-> min dRlj: " << dRlj << std::endl;

  DEBUGclass("returning");

  return dRlj;
}
//______________________________________________________________________________________________

DeltaRFakeLepJetmin_ll_v05::DeltaRFakeLepJetmin_ll_v05(const TString& expression):
TQTreeObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  if(expression.Contains("fake")){
    useFakeSelec = true;
  }


}

//______________________________________________________________________________________________

const TString& DeltaRFakeLepJetmin_ll_v05::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool DeltaRFakeLepJetmin_ll_v05::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void DeltaRFakeLepJetmin_ll_v05::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool DeltaRFakeLepJetmin_ll_v05::parseExpression(const TString& expr){
  // parse the expression
  (void) expr;
  return true;
}

//______________________________________________________________________________________________

void DeltaRFakeLepJetmin_ll_v05::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString DeltaRFakeLepJetmin_ll_v05::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool DeltaRFakeLepJetmin_ll_v05::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  // this->bla = new TTreeFormula( "name", "formula", this->fTree);

  this->leptons_pt = new TTreeFormula( "leptons_pt", "leptons_pt", this->fTree);
  this->leptons_eta = new TTreeFormula( "leptons_eta", "leptons_eta", this->fTree);
  this->leptons_phi = new TTreeFormula( "leptons_phi", "leptons_phi", this->fTree);
  this->leptons_m = new TTreeFormula( "leptons_m", "leptons_m", this->fTree);

  this->jets_pt = new TTreeFormula( "jets_pt", "jets_pt", this->fTree);
  this->jets_eta = new TTreeFormula( "jets_eta", "jets_eta", this->fTree);
  this->jets_phi = new TTreeFormula( "jets_phi", "jets_phi", this->fTree);
  this->jets_m = new TTreeFormula( "jets_m", "jets_m", this->fTree);

  EVS = new EventSelection_leplep_default();
  EVS_fake = new EventSelection_leplep_fake();

  return true;
}

//______________________________________________________________________________________________

bool DeltaRFakeLepJetmin_ll_v05::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete this->leptons_pt;
  delete this->leptons_eta;
  delete this->leptons_phi;
  delete this->leptons_m;
  delete this->jets_pt;
  delete this->jets_eta;
  delete this->jets_phi;
  delete this->jets_m;
  delete EVS;
  delete EVS_fake;


  return true;
}
