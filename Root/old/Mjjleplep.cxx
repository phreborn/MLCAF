#include "Htautau2015/Mjjleplep.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(Mjjleplep)

//______________________________________________________________________________________________

Mjjleplep::Mjjleplep(){
  // default constructor
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

Mjjleplep::~Mjjleplep(){
  // default destructor
  DEBUGclass("destructor called");
} 


//______________________________________________________________________________________________

TObjArray* Mjjleplep::getBranchNames() const {
  // retrieve the list of branch names 
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();
  bnames->SetOwner(false);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));
  bnames->Add(new TObjString("jet_0_pt"));  
  bnames->Add(new TObjString("jet_0_eta"));  
  bnames->Add(new TObjString("jet_0_phi"));  
  bnames->Add(new TObjString("jet_0_m"));  
  bnames->Add(new TObjString("jet_1_pt"));  
  bnames->Add(new TObjString("jet_1_eta"));  
  bnames->Add(new TObjString("jet_1_phi"));  
  bnames->Add(new TObjString("jet_1_m"));  


  return bnames;
}

//______________________________________________________________________________________________

double Mjjleplep::getValue() const {
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
  double jet_0_phi = this->jet_0_phi->EvalInstance();
  double jet_0_m = this->jet_0_m->EvalInstance();
  double jet_1_pt = this->jet_1_pt->EvalInstance();
  double jet_1_eta = this->jet_1_eta->EvalInstance();
  double jet_1_phi = this->jet_1_phi->EvalInstance();
  double jet_1_m = this->jet_1_m->EvalInstance();

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

Mjjleplep::Mjjleplep(const TString& expression):
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

const TString& Mjjleplep::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool Mjjleplep::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void Mjjleplep::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool Mjjleplep::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void Mjjleplep::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString Mjjleplep::getActiveExpression() const {
  // retrieve the expression associated with this incarnation
  return this->getExpression(); /* you have to build the expression here */;
}

//______________________________________________________________________________________________

bool Mjjleplep::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  this->jet0 = new TLorentzVector();
  this->jet1 = new TLorentzVector();

  this->jet_0_pt = new TTreeFormula( "jet_0_pt", "jet_0_pt", this->fTree);
  this->jet_0_eta = new TTreeFormula( "jet_0_eta", "jet_0_eta", this->fTree);
  this->jet_0_phi = new TTreeFormula( "jet_0_phi", "jet_0_phi", this->fTree);
  this->jet_0_m = new TTreeFormula( "jet_0_m", "jet_0_m", this->fTree);

  this->jet_1_pt = new TTreeFormula( "jet_1_pt", "jet_1_pt", this->fTree);
  this->jet_1_eta = new TTreeFormula( "jet_1_eta", "jet_1_eta", this->fTree);
  this->jet_1_phi = new TTreeFormula( "jet_1_phi", "jet_1_phi", this->fTree);
  this->jet_1_m = new TTreeFormula( "jet_1_m", "jet_1_m", this->fTree);



  return true;
}
 
//______________________________________________________________________________________________

bool Mjjleplep::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();
  delete this->jet0;
  delete this->jet1;

  delete this->jet_0_pt;
  delete this->jet_0_eta;
  delete this->jet_0_phi;
  delete this->jet_0_m;

  delete this->jet_1_pt;
  delete this->jet_1_eta;
  delete this->jet_1_phi;
  delete this->jet_1_m;

  return true;
}
