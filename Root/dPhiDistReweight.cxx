#include "Htautau/dPhiDistReweight.h"
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

ClassImp(dPhiDistReweight)

//______________________________________________________________________________________________

dPhiDistReweight::dPhiDistReweight(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

dPhiDistReweight::~dPhiDistReweight(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* dPhiDistReweight::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("tau_0_phi"));
  bnames->Add(new TObjString("met_reco_phi"));

  bnames->Add(new TObjString("tau_0_pt"));
  bnames->Add(new TObjString("tau_0_n_tracks"));
  bnames->Add(new TObjString("lep_0"));
  bnames->Add(new TObjString("n_bjets"));
  bnames->Add(new TObjString("lephad_mt_lep0_met"));
  bnames->Add(new TObjString("lephad_qxq"));

  bnames->Add(new TObjString("run_number"));
  bnames->Add(new TObjString("NOMINAL_pileup_random_run_number"));

  return bnames;
}

//______________________________________________________________________________________________

double dPhiDistReweight::getValue() const {
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
  double f_tau_0_phi      = this->tau_0_phi->EvalInstance();
  double f_met_reco_phi   = this->met_reco_phi->EvalInstance();

  double f_tau_0_pt       = this->tau_0_pt->EvalInstance();
  double f_lepmet_mt      = this->lephad_mt_lep0_met->EvalInstance();
  int    f_lephad_qxq     = this->lephad_qxq->EvalInstance();
  int    f_tau_0_n_tracks = this->tau_0_n_tracks->EvalInstance();
  int    f_lep_0          = this->lep_0->EvalInstance();
  int    f_n_bjets        = this->n_bjets->EvalInstance();

  int    f_NOMINAL_pileup_random_run_number = 1;
  if( fSysName.Contains("Data") ) {
    f_NOMINAL_pileup_random_run_number = this->run_number->EvalInstance();
  }
  else {
    f_NOMINAL_pileup_random_run_number = this->NOMINAL_pileup_random_run_number->EvalInstance();
  }

  //* fake factor valiated range up to 200GeV
  if(f_tau_0_pt>200) f_tau_0_pt = 199;

  double nonclosure_MJ(1);

  double dphitmet = 3.1415926 - fabs( fabs( f_tau_0_phi - f_met_reco_phi ) - 3.1415926);

  nonclosure_MJ    = h_dphi_distcor ->GetBinContent( h_dphi_distcor ->FindBin(dphitmet) );

  DEBUGclass("returning");
  //return 0;
  return nonclosure_MJ;
}
//______________________________________________________________________________________________

dPhiDistReweight::dPhiDistReweight(const TString& expression):
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

  TString dphi_cor_input_path = "/storage/groups/atljak/HiggsTauTauLepHad/WorkArea/caf2016Nov03/Htautau/share/MSSM_FakeFactor/dPhiDistributionCorrection/DphiRatio.root";
  TFile *infile_dphi_cor = new TFile( dphi_cor_input_path );
  h_dphi_distcor= (TH1D*)infile_dphi_cor->Get("DphiRatio");

}

//______________________________________________________________________________________________

const TString& dPhiDistReweight::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool dPhiDistReweight::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void dPhiDistReweight::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool dPhiDistReweight::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void dPhiDistReweight::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString dPhiDistReweight::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool dPhiDistReweight::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  this->run_number     = new TTreeFormula( "run_number",    "run_number",    this->fTree);
  this->NOMINAL_pileup_random_run_number     = new TTreeFormula( "NOMINAL_pileup_random_run_number",    "NOMINAL_pileup_random_run_number",    this->fTree);

  this->lep_0     = new TTreeFormula( "lep_0",    "lep_0",    this->fTree);

  this->tau_0_pt       = new TTreeFormula( "tau_0_pt",      "tau_0_pt",       this->fTree);
  this->tau_0_phi      = new TTreeFormula( "tau_0_phi",     "tau_0_phi",      this->fTree);
  this->tau_0_n_tracks = new TTreeFormula( "tau_0_n_tracks","tau_0_n_tracks", this->fTree);

  this->lephad_qxq         = new TTreeFormula( "lephad_qxq",         "lephad_qxq",         this->fTree);
  this->lephad_mt_lep0_met = new TTreeFormula( "lephad_mt_lep0_met", "lephad_mt_lep0_met", this->fTree);

  this->n_bjets      = new TTreeFormula( "n_bjets",      "n_bjets",      this->fTree);
  this->met_reco_phi = new TTreeFormula( "met_reco_phi", "met_reco_phi", this->fTree);

  return true;
}

//______________________________________________________________________________________________

bool dPhiDistReweight::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete this->tau_0_phi;
  delete this->met_reco_phi;
  delete this->tau_0_pt;
  delete this->lephad_qxq;
  delete this->lephad_mt_lep0_met;
  delete this->tau_0_n_tracks;
  delete this->lep_0;
  delete this->run_number;
  delete this->NOMINAL_pileup_random_run_number;
  delete this->n_bjets;

  return true;
}
