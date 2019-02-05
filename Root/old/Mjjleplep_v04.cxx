#include "Htautau2015/Mjjleplep_v04.h"
#include "QFramework/TQIterator.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(Mjjleplep_v04)

//______________________________________________________________________________________________

Mjjleplep_v04::Mjjleplep_v04(){
  // default constructor
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

Mjjleplep_v04::~Mjjleplep_v04(){
  // default destructor
  DEBUGclass("destructor called");
} 


//______________________________________________________________________________________________

TObjArray* Mjjleplep_v04::getBranchNames() const {
  // retrieve the list of branch names 
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();
  bnames->SetOwner(false);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));
  
  bnames->Add(new TObjString("jets_pt"));  
  bnames->Add(new TObjString("jets_eta"));  
  bnames->Add(new TObjString("jets_phi"));  
  bnames->Add(new TObjString("jets_m"));  
  return bnames;
}

//______________________________________________________________________________________________

double Mjjleplep_v04::getValue() const {
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

  int idx0=-1;
  int idx1=-1;
  idx0=getObservable("JetIdx_0",fSample)->getValue();
  idx1=getObservable("JetIdx_1",fSample)->getValue();
  std::cout << "idx " << idx0 << " " << idx1 << std::endl;
  idx0=OVR->getJetIdx(0);
  idx1=OVR->getJetIdx(1);
  std::cout << "idxb " << idx0 << " " << idx1 << std::endl;
  if (idx0==-1 || idx1==-1) return -999;
  double jet_0_pt = this->jets_pt->EvalInstance(idx0);
  double jet_0_eta = this->jets_eta->EvalInstance(idx0);
  double jet_0_phi = this->jets_phi->EvalInstance(idx0);
  double jet_0_m = this->jets_m->EvalInstance(idx0);
  double jet_1_pt = this->jets_pt->EvalInstance(idx1);
  double jet_1_eta = this->jets_eta->EvalInstance(idx1);
  double jet_1_phi = this->jets_phi->EvalInstance(idx1);
  double jet_1_m = this->jets_m->EvalInstance(idx1);

  // TLorentzVector* jet0 = new TLorentzVector();
  // TLorentzVector* jet1 = new TLorentzVector();
  


  this->jet0->SetPtEtaPhiM( jet_0_pt, jet_0_eta, jet_0_phi, jet_0_m );
  this->jet1->SetPtEtaPhiM( jet_1_pt, jet_1_eta, jet_1_phi, jet_1_m );

  if (!jet0 || !jet1) return 0;
  const double retval = ((*jet0) + (*jet1)).M();
  //    std::cout << retval << std::endl;


  DEBUGclass("returning");
  return retval;
}
//______________________________________________________________________________________________

Mjjleplep_v04::Mjjleplep_v04(const TString& expression):
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

const TString& Mjjleplep_v04::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool Mjjleplep_v04::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void Mjjleplep_v04::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool Mjjleplep_v04::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void Mjjleplep_v04::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString Mjjleplep_v04::getActiveExpression() const {
  // retrieve the expression associated with this incarnation
  return this->getExpression(); /* you have to build the expression here */;
}

//______________________________________________________________________________________________

bool Mjjleplep_v04::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  this->jet0 = new TLorentzVector();
  this->jet1 = new TLorentzVector();
  
  getObservable("JetIdx_0",fSample)->initialize(fSample);
  getObservable("JetIdx_1",fSample)->initialize(fSample);

  this->jets_pt = new TTreeFormula( "jets_pt", "jets_pt", this->fTree);
  this->jets_eta = new TTreeFormula( "jets_eta", "jets_eta", this->fTree);
  this->jets_phi = new TTreeFormula( "jets_phi", "jets_phi", this->fTree);
  this->jets_m = new TTreeFormula( "jets_m", "jets_m", this->fTree);
  
  OVR = new OverlapRemovalAlg_leplep();

  return true;
}
 
//______________________________________________________________________________________________

bool Mjjleplep_v04::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();
  delete this->jet0;
  delete this->jet1;

  delete this->jets_pt;
  delete this->jets_eta;
  delete this->jets_phi;
  delete this->jets_m;

  delete OVR;

  return true;
}
