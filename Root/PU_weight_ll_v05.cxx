#include "Htautau/PU_weight_ll_v05.h"
#include <limits>

#include "TFile.h"

// uncomment the following line to enable debug printouts
//#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(PU_weight_ll_v05)

//______________________________________________________________________________________________

PU_weight_ll_v05::PU_weight_ll_v05(){
  // default constructor

  this->setExpression(this->GetName() );

  std::cout << "default constructor called" << std::endl;

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

PU_weight_ll_v05::~PU_weight_ll_v05(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* PU_weight_ll_v05::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

   bnames->Add(new TObjString("weight_mc"));
   bnames->Add(new TObjString(PU_weight_name));
   bnames->Add(new TObjString("sherpa_weight"));
   bnames->Add(new TObjString("n_truth_jets"));
   bnames->Add(new TObjString("true_parent_pdgId"));
   bnames->Add(new TObjString("true_parent_pt"));
   bnames->Add(new TObjString(RRN_name));

  return bnames;
}

//______________________________________________________________________________________________

double PU_weight_ll_v05::getValue() const {
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

  PU_weight->GetNdata();
  RRN->GetNdata();
  //jets_JvtEfficiencyDown_effPU_weight->GetNdata();
  //jets_JvtEfficiencyUp_effPU_weight->GetNdata();

  double PU_weight_nom  = this->PU_weight->EvalInstance(0);
  int RandRunNumb= this->RRN->EvalInstance();
  //double PU_weight_down = this->jets_JvtEfficiencyDown_effPU_weight->EvalInstance(0);
  //double PU_weight_up   = this->jets_JvtEfficiencyUp_effPU_weight->EvalInstance(0);

  double PU_weight = 1.;

  // check here for nom, sys up, sys down
  PU_weight *= PU_weight_nom;

  if (m_isSherpa) {
    PU_weight *= sherpa_weight->EvalInstance();
  }

  if ( m_isMG && (abs(m_systematic) == 10 || abs(m_systematic) ==20 || abs(m_systematic) == 30 || abs(m_systematic) ==40) ) {
      int pdgid = true_parent_pdgId->EvalInstance();
      if (pdgid == 23) {
          double pt = true_parent_pt->EvalInstance()/1000.0;
          int njet = n_truth_jets->EvalInstance();
          double scale = m_MG_histo->GetBinContent(m_MG_histo->FindBin(pt,njet));
          if (m_systematic < 0  && scale != 0) scale=2.0-scale;
          if (scale == 0) scale = 1.0;
          PU_weight *= scale;
          //std::cout << "scale MG " << pt << " " << njet << " " << scale << std::endl;
      }
  }

  DEBUGclass("returning");
  //if(PU_weight<0){
  //  std::cout << "PU WEIGHT:" << PU_weight_nom << std::endl;
  //}

  if(doRRN){
    return RandRunNumb;
  }
  else{
    return PU_weight;
  }
}
//______________________________________________________________________________________________

PU_weight_ll_v05::PU_weight_ll_v05(const TString& expression, int systematic):
TQTreeObservable(expression),m_systematic(systematic)
{

  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  if(expression.Contains("random_run_number")){
    doRRN=true;
  }

}

//______________________________________________________________________________________________

const TString& PU_weight_ll_v05::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool PU_weight_ll_v05::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void PU_weight_ll_v05::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool PU_weight_ll_v05::parseExpression(const TString& expr){
  // parse the expression
  (void) expr;
  return true;
}

//______________________________________________________________________________________________

void PU_weight_ll_v05::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString PU_weight_ll_v05::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool PU_weight_ll_v05::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  // this->bla = new TTreeFormula( "name", "formula", this->fTree);
  PU_weight_name="pu_NOMINAL_pileup_combined_weight";
  RRN_name = "NOMINAL_pileup_random_run_number";
  if (m_systematic ==-1) {
      PU_weight_name="pu_PRW_DATASF_1down_pileup_combined_weight";
      RRN_name = "PRW_DATASF_1down_pileup_random_run_number";
      DEBUGclass("PU down");
  }
  else if (m_systematic == +1) {
      PU_weight_name="pu_PRW_DATASF_1up_pileup_combined_weight";
      RRN_name = "PRW_DATASF_1up_pileup_random_run_number";
      DEBUGclass("PU up");
  }

  this->PU_weight = new TTreeFormula( "pu_weight",PU_weight_name+" * weight_mc", this->fTree);
  this->RRN = new TTreeFormula("RRN", RRN_name, this->fTree);
  //this->jets_JvtEfficiencyDown_effPU_weight = new TTreeFormula( "jets_JvtEfficiencyDown_effPU_weight", "jets_JvtEfficiencyDown_effPU_weight", this->fTree);
  //this->jets_JvtEfficiencyUp_effPU_weight = new TTreeFormula( "jets_JvtEfficiencyUp_effPU_weight", "jets_JvtEfficiencyUp_effPU_weight", this->fTree);

  m_isSherpa=false;
  this->fSample->getTag("~isSherpa", m_isSherpa);
  if (m_isSherpa) {
     this->sherpa_weight = new TTreeFormula("sherpa_weight", "sherpa_weight", this->fTree);
  }

  m_isMG=false;
  this->fSample->getTag("~isMG", m_isMG);
  if (m_isMG && (abs(m_systematic) == 10 || abs(m_systematic) ==20 || abs(m_systematic) == 30 || abs(m_systematic) ==40) ) {
     this->n_truth_jets = new TTreeFormula("n_truth_jets", "n_truth_jets", this->fTree);
     this->true_parent_pdgId = new TTreeFormula("true_parent_pdgId", "true_parent_pdgId", this->fTree);
     this->true_parent_pt = new TTreeFormula("true_parent_pt", "true_parent_pt", this->fTree);

     TFile *  file=0;

     if (abs(m_systematic) == 10 ) {
         file = new TFile("zUncert/fac_histosout.root");
         m_MG_histo = (TH2F*)file->Get("fac");
     }
     if (abs(m_systematic) == 20 ) {
         file = new TFile("zUncert/ren_histosout.root");
         m_MG_histo = (TH2F*)file->Get("ren");
     }
     if (abs(m_systematic) == 30 ) {
         file = new TFile("zUncert/ckkw_histosout.root");
         m_MG_histo = (TH2F*)file->Get("ckk");
     }
     if (abs(m_systematic) == 40 ) {
         file = new TFile("zUncert/qsf_histosout.root");
         m_MG_histo = (TH2F*)file->Get("qsf");
     }

     m_MG_histo->SetDirectory(0);
     if (file) file->Close();
  }


  return true;
}

//______________________________________________________________________________________________

bool PU_weight_ll_v05::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete this->PU_weight;

  return true;
}
