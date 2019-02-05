#include "Htautau/LeptonFF.h"
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

ClassImp(LeptonFF)

//______________________________________________________________________________________________

LeptonFF::LeptonFF(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

LeptonFF::~LeptonFF(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* LeptonFF::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("lep_0"));
  bnames->Add(new TObjString("lep_0_pt"));
  bnames->Add(new TObjString("lep_0_eta"));
  bnames->Add(new TObjString("n_bjets"));

  bnames->Add(new TObjString("run_number"));
  bnames->Add(new TObjString("NOMINAL_pileup_random_run_number"));

  return bnames;
}

//______________________________________________________________________________________________

double LeptonFF::getValue() const {
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
  double f_lep_0_pt  = this->lep_0_pt->EvalInstance();
  double f_lep_0_eta = fabs( this->lep_0_eta->EvalInstance() );
  int    f_lep_0     = this->lep_0->EvalInstance();
  int    f_n_bjets   = this->n_bjets->EvalInstance();

  double tmp_leptonFF(0);

  if( f_lep_0==1 ) {

    if(f_lep_0_pt<55) {
      if( f_n_bjets==0 ) {
        tmp_leptonFF = h_ff_flCR_muhad_lowPt_bveto_fl->GetBinContent( h_ff_flCR_muhad_lowPt_bveto_fl->FindBin(f_lep_0_eta) );
      }
      else {
        tmp_leptonFF = h_ff_flCR_muhad_lowPt_btag_fl ->GetBinContent( h_ff_flCR_muhad_lowPt_btag_fl ->FindBin(f_lep_0_eta) );
      }
    }
    else if(f_lep_0_pt>55) {
      if( f_n_bjets==0 ) {
        tmp_leptonFF = h_ff_flCR_muhad_highPt_bveto_fl->GetBinContent( h_ff_flCR_muhad_highPt_bveto_fl->FindBin(f_lep_0_eta) );
      }
      else {
        tmp_leptonFF = h_ff_flCR_muhad_highPt_btag_fl ->GetBinContent( h_ff_flCR_muhad_highPt_btag_fl ->FindBin(f_lep_0_eta) );
      }
    }

  }
  else if( f_lep_0==2 ) {

    if( f_n_bjets==0 ) {
      tmp_leptonFF = h_ff_flCR_ehad_bveto_fl->GetBinContent( h_ff_flCR_ehad_bveto_fl->FindBin(f_lep_0_eta) );
    }
    else {
      tmp_leptonFF = h_ff_flCR_ehad_btag_fl ->GetBinContent( h_ff_flCR_ehad_btag_fl ->FindBin(f_lep_0_eta) );
    }

  }

  //std::cout<<" retval / r_qcd / ff_mj / ff_ew : "<< retval <<"/ "<< r_qcd <<"/ "<< ff_mj <<"/ "<< ff_ew << std::endl;

  DEBUGclass("returning");
  //return 0;
  return tmp_leptonFF;
}
//______________________________________________________________________________________________

LeptonFF::LeptonFF(const TString& expression):
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

  TString ff_file_path = "/afs/cern.ch/user/v/vmuckhof/public/tag_00_02_26_05/hist_lepton_fake_factor_nom_and_unc.root";
  TFile *infile_leptonff = new TFile( ff_file_path );

  h_ff_flCR_ehad_bveto_fl         = (TH1D*)infile_leptonff->Get("h_ff_flCR_ehad_bveto_fl_nom"        );
  h_ff_flCR_ehad_btag_fl          = (TH1D*)infile_leptonff->Get("h_ff_flCR_ehad_btag_fl_nom"         );
  h_ff_flCR_muhad_lowPt_bveto_fl  = (TH1D*)infile_leptonff->Get("h_ff_flCR_muhad_lowPt_bveto_fl_nom" );
  h_ff_flCR_muhad_highPt_bveto_fl = (TH1D*)infile_leptonff->Get("h_ff_flCR_muhad_highPt_bveto_fl_nom");
  h_ff_flCR_muhad_lowPt_btag_fl   = (TH1D*)infile_leptonff->Get("h_ff_flCR_muhad_lowPt_btag_fl_nom"  );
  h_ff_flCR_muhad_highPt_btag_fl  = (TH1D*)infile_leptonff->Get("h_ff_flCR_muhad_highPt_btag_fl_nom" );

}

//______________________________________________________________________________________________

const TString& LeptonFF::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool LeptonFF::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void LeptonFF::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool LeptonFF::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void LeptonFF::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString LeptonFF::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool LeptonFF::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  this->run_number     = new TTreeFormula( "run_number",    "run_number",    this->fTree);
  this->NOMINAL_pileup_random_run_number     = new TTreeFormula( "NOMINAL_pileup_random_run_number",    "NOMINAL_pileup_random_run_number",    this->fTree);

  this->lep_0     = new TTreeFormula( "lep_0",     "lep_0",    this->fTree);
  this->lep_0_pt  = new TTreeFormula( "lep_0_pt",  "lep_0_pt", this->fTree);
  this->lep_0_eta = new TTreeFormula( "lep_0_eta", "lep_0_eta",this->fTree);
  this->n_bjets   = new TTreeFormula( "n_bjets",   "n_bjets",  this->fTree);

  return true;
}

//______________________________________________________________________________________________

bool LeptonFF::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete this->run_number;
  delete this->NOMINAL_pileup_random_run_number;
  delete this->lep_0;
  delete this->lep_0_pt;
  delete this->lep_0_eta;
  delete this->n_bjets;

  return true;
}
