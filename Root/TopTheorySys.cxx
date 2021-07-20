#include "BSMtautauCAF/TopTheorySys.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
#include "TFile.h"
#include "TObjString.h"
#include <map>

ClassImp(TopTheorySys)

//______________________________________________________________________________________________

TopTheorySys::TopTheorySys(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

TopTheorySys::~TopTheorySys(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* TopTheorySys::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();

  // new systematics
  bnames->Add(new TObjString("pmg_truth_weight_ISRHi"));
  bnames->Add(new TObjString("pmg_truth_weight_ISRLo"));
  bnames->Add(new TObjString("pmg_truth_weight_FSRHi"));
  bnames->Add(new TObjString("pmg_truth_weight_FSRLo"));

  return bnames;
}

//______________________________________________________________________________________________

double TopTheorySys::getValue() const {
  double retval = 1.0;

  double f_lep_0_pt       = this->lep_0_pt->EvalInstance();
  double f_tau_0_pt       = this->tau_0_pt->EvalInstance();
  double f_lepmet_mt1     = this->lephad_mt_lep0_met->EvalInstance();
  double f_lepmet_mt2     = this->lephad_mt_lep1_met->EvalInstance();
  double f_lephad_dphi    = this->lephad_dphi->EvalInstance();

  double mttot = std::sqrt(f_lepmet_mt1*f_lepmet_mt1 + f_lepmet_mt2*f_lepmet_mt2 + 2.*f_lep_0_pt*f_tau_0_pt*(1-cos(f_lephad_dphi)) );


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
    int binID =  std::min(m_hSys->FindBin(mttot),m_hSys->GetNbinsX());
    retval = m_hSys->GetBinContent(binID);
    // the last bin of ISR up variation is the same as that of down variation, which is strange. 
    // mirror this bin
    if ( fSysName.Contains("TTBar_ISR_1up") && retval < 1.0) retval = 2.0-retval;
  }
#endif

  return retval;
}
//______________________________________________________________________________________________

TopTheorySys::TopTheorySys(const TString& expression):
LepHadObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  //fSysName = expression;
}

//______________________________________________________________________________________________

const TString& TopTheorySys::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool TopTheorySys::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void TopTheorySys::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool TopTheorySys::initializeSelf(){
  if (!LepHadObservable::initializeSelf()) return false;

  fSysName = this->fSample->replaceInTextRecursive("$(sfVariation.top)","~");

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

  TString signalProcess = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("SignalProcess", signalProcess) ){
    ERRORclass("AnaChannel not set !!!");
  }
  tempFile = TFile::Open(signalProcess+"_lephad/auxData/Systematics/LepHadCombined_TopSys.root");
  if (!tempFile) {
    std::cout << "WARNING: can not find top systematics " << std::endl;
    return false;  
  }

  if ( fSysName.Contains("TTBar_ISR_1up") ) {
    m_hSys = (TH1F*)tempFile->Get("hISR_up"); m_hSys->SetDirectory(0);
  }
  else if ( fSysName.Contains("TTBar_ISR_1down") ) {
    m_hSys = (TH1F*)tempFile->Get("hISR_down"); m_hSys->SetDirectory(0);
  }
  else if ( fSysName.Contains("TTBar_FSR_1up") ) {
    m_hSys = (TH1F*)tempFile->Get("hFSR_up"); m_hSys->SetDirectory(0);
  }
  else if ( fSysName.Contains("TTBar_FSR_1down") ) {
    m_hSys = (TH1F*)tempFile->Get("hFSR_down"); m_hSys->SetDirectory(0);
  }
  else if ( fSysName.Contains("TTBar_PS")) {
    m_hSys = (TH1F*)tempFile->Get("hPowhegHerwig7"); m_hSys->SetDirectory(0);
  }
  else if ( fSysName.Contains("TTBar_ME")) {
    m_hSys = (TH1F*)tempFile->Get("haMcAtNloPythia8"); m_hSys->SetDirectory(0);
  }
  tempFile->Close(); delete tempFile; tempFile=0;

  return true;
}

//______________________________________________________________________________________________

bool TopTheorySys::finalizeSelf(){
  if (! LepHadObservable::finalizeSelf()) return false;
  
  delete this->pmg_truth_weight_ISRHi;
  delete this->pmg_truth_weight_ISRLo;
  delete this->pmg_truth_weight_FSRHi;
  delete this->pmg_truth_weight_FSRLo;

  return true;
}
