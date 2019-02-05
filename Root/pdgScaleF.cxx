#include "Htautau/pdgScaleF.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
#include "TFile.h"
#include <map>

ClassImp(pdgScaleF)

//______________________________________________________________________________________________

pdgScaleF::pdgScaleF(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

pdgScaleF::~pdgScaleF(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* pdgScaleF::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("tau_0_n_tracks"));
  bnames->Add(new TObjString("tau_0_truth_pdgId"));

  return bnames;
}

//______________________________________________________________________________________________

double pdgScaleF::getValue() const {
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

  //std::cout<<" In getValue "<<std::endl;
  int    f_tau_0_n_tracks    = this->tau_0_n_tracks   ->EvalInstance();
  int    f_tau_0_truth_pdgId = this->tau_0_truth_pdgId->EvalInstance();

  double tmp_leptonFF(0);
  if( f_tau_0_n_tracks==1 ) {
    tmp_leptonFF = h_ratio_1p->GetBinContent( h_ratio_1p->FindBin(f_tau_0_truth_pdgId) );
  }
  else if( f_tau_0_n_tracks==3 ) {
    tmp_leptonFF = h_ratio_3p->GetBinContent( h_ratio_3p->FindBin(f_tau_0_truth_pdgId) );
  }

  //std::cout<<" retval / r_qcd / ff_mj / ff_ew : "<< retval <<"/ "<< r_qcd <<"/ "<< ff_mj <<"/ "<< ff_ew << std::endl;

  DEBUGclass("returning");
  //return 0;
  return tmp_leptonFF;
}
//______________________________________________________________________________________________

pdgScaleF::pdgScaleF(const TString& expression):
TQTreeObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  fSysName = expression;

  TString ff_file_path = "/storage/groups/atljak/HiggsTauTauLepHad/WorkArea/HistAna_trunk/pdgRatio.root";
  TFile *infile_leptonff = new TFile( ff_file_path );

  h_ratio_1p = (TH1F*)infile_leptonff->Get("pdgRatio1p");
  h_ratio_3p = (TH1F*)infile_leptonff->Get("pdgRatio3p");

}

//______________________________________________________________________________________________

const TString& pdgScaleF::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool pdgScaleF::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void pdgScaleF::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool pdgScaleF::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void pdgScaleF::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString pdgScaleF::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool pdgScaleF::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  this->tau_0_n_tracks    = new TTreeFormula( "tau_0_n_tracks",    "tau_0_n_tracks",    this->fTree);
  this->tau_0_truth_pdgId = new TTreeFormula( "tau_0_truth_pdgId", "tau_0_truth_pdgId", this->fTree);

  return true;
}

//______________________________________________________________________________________________

bool pdgScaleF::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete this->tau_0_n_tracks;
  delete this->tau_0_truth_pdgId;

  return true;
}
