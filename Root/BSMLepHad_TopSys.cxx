#include "BSMtautauCAF/BSMLepHad_TopSys.h"
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

ClassImp(BSMLepHad_TopSys)

//______________________________________________________________________________________________

BSMLepHad_TopSys::BSMLepHad_TopSys(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

BSMLepHad_TopSys::~BSMLepHad_TopSys(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* BSMLepHad_TopSys::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  // old systematics
  bnames->Add(new TObjString("lep_0_pt"));
  bnames->Add(new TObjString("tau_0_pt"));
  bnames->Add(new TObjString("lephad_mt_lep0_met"));
  bnames->Add(new TObjString("lephad_mt_lep1_met"));
  bnames->Add(new TObjString("lephad_dphi"));

  // new systematics
  bnames->Add(new TObjString("pmg_truth_weight_ISRHi"));
  bnames->Add(new TObjString("pmg_truth_weight_ISRLo"));
  bnames->Add(new TObjString("pmg_truth_weight_FSRHi"));
  bnames->Add(new TObjString("pmg_truth_weight_FSRLo"));

  return bnames;
}

//______________________________________________________________________________________________

double BSMLepHad_TopSys::getValue() const {
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

  // old systematics
  double f_lep_0_pt       = this->lep_0_pt->EvalInstance();
  double f_tau_0_pt       = this->tau_0_pt->EvalInstance();
  double f_lepmet_mt1     = this->lephad_mt_lep0_met->EvalInstance();
  double f_lepmet_mt2     = this->lephad_mt_lep1_met->EvalInstance();
  double f_lephad_dphi    = this->lephad_dphi->EvalInstance();

  double mttot = std::sqrt(f_lepmet_mt1*f_lepmet_mt1 + f_lepmet_mt2*f_lepmet_mt2 + 2.*f_lep_0_pt*f_tau_0_pt*(1-cos(f_lephad_dphi)) );

  double cor_Rad  = 1.11 - 0.0007 * mttot;
  double cor_ShUe = 1.18 - 0.0015 * mttot + 1.5 * 0.000001 * mttot * mttot;
  if(mttot>500) {
   cor_ShUe = 1.18 - 0.0015 * 500 + 1.5 * 0.000001 * 500 * 500;
  }


  double retval(1);

  // old systematics
  if( fSysName.Contains("TTBAR_Radiation_1up") ) {
    retval = cor_Rad;
  }
  if( fSysName.Contains("TTBAR_Radiation_1down") ) {
    retval = -1*(cor_Rad - 1) + 1;
  }

  if( fSysName.Contains("TTBAR_ShowerUE_1up") ) {
    retval = cor_ShUe;
  }
  if( fSysName.Contains("TTBAR_ShowerUE_1down") ) {
    retval = -1*(cor_ShUe - 1) + 1;
  }

#if 0
  // new systematics
  if( fSysName.Contains("TTBar_ISR_1up") ) {
    double f_pmg_truth_weight_ISRHi = this->pmg_truth_weight_ISRHi->EvalInstance();
    retval = f_pmg_truth_weight_ISRHi;
  }
  if( fSysName.Contains("TTBar_ISR_1down") ) {
    double f_pmg_truth_weight_ISRLo = this->pmg_truth_weight_ISRLo->EvalInstance();
    retval = f_pmg_truth_weight_ISRLo;
  }

  if( fSysName.Contains("TTBar_FSR_1up") ) {
    double f_pmg_truth_weight_FSRHi = this->pmg_truth_weight_FSRHi->EvalInstance();
    retval = f_pmg_truth_weight_FSRHi;
  }
  if( fSysName.Contains("TTBar_FSR_1down") ) {
    double f_pmg_truth_weight_FSRLo = this->pmg_truth_weight_FSRLo->EvalInstance();
    retval = f_pmg_truth_weight_FSRLo;
  }
#else
  // new systematics from truth level analysis
  if ( fSysName.Contains("TTBar_ISR_1up") || fSysName.Contains("TTBar_ISR_1down")||
       fSysName.Contains("TTBar_FSR_1up") || fSysName.Contains("TTBar_FSR_1down")||
       fSysName.Contains("TTBar_PS") || fSysName.Contains("TTBar_ME") ) {
    if (mttot > 600 ) mttot = 599;
    retval = m_hSys->GetBinContent(m_hSys->FindBin(mttot));
    // the last bin of ISR up variation is the same as that of down variation, which is strange. 
    // mirror this bin
    if ( fSysName.Contains("TTBar_ISR_1up") && retval < 1.0) retval = 2.0-retval;
  }
#endif

  DEBUGclass("returning");
  //return 0;
  return retval;
}
//______________________________________________________________________________________________

BSMLepHad_TopSys::BSMLepHad_TopSys(const TString& expression):
LepHadObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  fSysName = expression;
}

//______________________________________________________________________________________________

const TString& BSMLepHad_TopSys::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool BSMLepHad_TopSys::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void BSMLepHad_TopSys::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool BSMLepHad_TopSys::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void BSMLepHad_TopSys::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString BSMLepHad_TopSys::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool BSMLepHad_TopSys::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  // old systematics
  this->lephad_dphi        = new TTreeFormula( "lephad_dphi",        "lephad_dphi",        this->fTree);
  this->tau_0_pt           = new TTreeFormula( "tau_0_pt",           "tau_0_p4.Pt()",      this->fTree);
  this->lep_0_pt           = new TTreeFormula( "lep_0_pt",           "lep_0_p4.Pt()",      this->fTree);
  this->lephad_mt_lep0_met = new TTreeFormula( "lephad_mt_lep0_met", "lephad_mt_lep0_met", this->fTree);
  this->lephad_mt_lep1_met = new TTreeFormula( "lephad_mt_lep1_met", "lephad_mt_lep1_met", this->fTree);

  // new systematics
  if( fSysName.Contains("TTBar_ISR_1up") ) {
    this->pmg_truth_weight_ISRHi = new TTreeFormula( "pmg_truth_weight_ISRHi", "pmg_truth_weight_ISRHi", this->fTree);
  }
  if( fSysName.Contains("TTBar_ISR_1down") ) {
    this->pmg_truth_weight_ISRLo = new TTreeFormula( "pmg_truth_weight_ISRLo", "pmg_truth_weight_ISRLo", this->fTree);
  }
  if( fSysName.Contains("TTBar_FSR_1up") ) {
    this->pmg_truth_weight_FSRHi = new TTreeFormula( "pmg_truth_weight_FSRHi", "pmg_truth_weight_FSRHi", this->fTree);
  }
  if( fSysName.Contains("TTBar_FSR_1down") ) {
    this->pmg_truth_weight_FSRLo = new TTreeFormula( "pmg_truth_weight_FSRLo", "pmg_truth_weight_FSRLo", this->fTree);
  }

  // new systematics based on truth level analysis
  TFile* tempFile=0;
  m_histoDir = 0;

  tempFile = TFile::Open("Systematics/LepHadCombined_TopSys.root");
  if (!tempFile) {
    std::cout << "WARNING: can not find top systematics " << std::endl;
    return false;  
  }

  if ( fSysName.Contains("TTBar_ISR_1up") ) {
    m_hSys = (TH1F*)tempFile->Get("hISR_up"); m_hSys->SetDirectory(m_histoDir);
  }
  else if ( fSysName.Contains("TTBar_ISR_1down") ) {
    m_hSys = (TH1F*)tempFile->Get("hISR_down"); m_hSys->SetDirectory(m_histoDir);
  }
  else if ( fSysName.Contains("TTBar_FSR_1up") ) {
    m_hSys = (TH1F*)tempFile->Get("hFSR_up"); m_hSys->SetDirectory(m_histoDir);
  }
  else if ( fSysName.Contains("TTBar_FSR_1down") ) {
    m_hSys = (TH1F*)tempFile->Get("hFSR_down"); m_hSys->SetDirectory(m_histoDir);
  }
  else if ( fSysName.Contains("TTBar_PS")) {
    m_hSys = (TH1F*)tempFile->Get("hPowhegHerwig7"); m_hSys->SetDirectory(m_histoDir);
  }
  else if ( fSysName.Contains("TTBar_ME")) {
    m_hSys = (TH1F*)tempFile->Get("haMcAtNloPythia8"); m_hSys->SetDirectory(m_histoDir);
  }
  tempFile->Close(); delete tempFile; tempFile=0;

  return true;
}

//______________________________________________________________________________________________

bool BSMLepHad_TopSys::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  // old systematics
  delete this->lephad_dphi;
  delete this->tau_0_pt;
  delete this->lep_0_pt;
  delete this->lephad_mt_lep0_met;
  delete this->lephad_mt_lep1_met;

  // new systematics
  delete this->pmg_truth_weight_ISRHi;
  delete this->pmg_truth_weight_ISRLo;
  delete this->pmg_truth_weight_FSRHi;
  delete this->pmg_truth_weight_FSRLo;

  return true;
}
