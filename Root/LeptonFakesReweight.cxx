#include "BSMtautauCAF/LeptonFakesReweight.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
#include "TFile.h"
#include "TMath.h"
#include <map>

ClassImp(LeptonFakesReweight)

//______________________________________________________________________________________________

LeptonFakesReweight::LeptonFakesReweight(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

LeptonFakesReweight::~LeptonFakesReweight(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* LeptonFakesReweight::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();

  //bnames->SetOwner(true);
  return bnames;
}

//______________________________________________________________________________________________
double LeptonFakesReweight::getValue() const {
  
  int    f_n_bjets        = this->n_bjets->EvalInstance();
  double f_lep_0              = this->lep_0->EvalInstance();
  double f_tau_0_pt       = this->tau_0_pt->EvalInstance();
  double f_lephad_met_lep0_cos_dphi = this->lephad_met_lep0_cos_dphi->EvalInstance();

  ///////////////////////////////////////////////////////////////
  // determine which SF to use
  ///////////////////////////////////////////////////////////////
  // channel: only apply correction to muhad channel
  TString channel = "";
  if (1==f_lep_0) channel = "muhad";
  else if (2==f_lep_0) return 1.0;
  
  // region: bveto or btag
  TString region = "";
  if (0==f_n_bjets) region = "Bveto";
  else if (1<=f_n_bjets) region = "Btag";
  
  // peiriod: Combined or Separated
  TString period = "All";

  // parameterization: 2D TauPt x Dphi
  TString param = "";
  if (0 == f_n_bjets) {
  // dphi 1,2,3,4 in bveto category
    if (f_lephad_met_lep0_cos_dphi<0.5) param = "TauPtDphi1";
    else if (f_lephad_met_lep0_cos_dphi>=0.5&&f_lephad_met_lep0_cos_dphi<1) param = "TauPtDphi2";
    else if (f_lephad_met_lep0_cos_dphi>=1&&f_lephad_met_lep0_cos_dphi<2) param = "TauPtDphi3";
    else if (f_lephad_met_lep0_cos_dphi>=2) param = "TauPtDphi4";
  }
  // dphi 1,2,3 in btag category
  else {
    if (f_lephad_met_lep0_cos_dphi<0.5) param = "TauPtDphi1";
    else if (f_lephad_met_lep0_cos_dphi>=0.5&&f_lephad_met_lep0_cos_dphi<1) param = "TauPtDphi2";
    else if (f_lephad_met_lep0_cos_dphi>=1) param = "TauPtDphi3";
  }
  
  TString histName = "LFR"+ period + channel + region + param + "SF";
  
  TH1F * h_nominal = 0;
  TH1F * h_up = 0;
  TH1F * h_down = 0;
 
  auto it = m_SF_hist.find(histName); 
  if ( it != m_SF_hist.end() ) h_nominal = it->second;
  else {
    std::cout << "ERROR! Unavailable SF: " << histName << std::endl;
    for (auto item : m_SF_hist)
      std::cout << "Available SF: " << item.first << std::endl;
  }

  it = m_SF_hist.find(histName+"_up"); 
  if ( it != m_SF_hist.end() ) h_up = it->second;
  else std::cout << "ERROR! Unavailable SF: " << histName+"_up" << std::endl;
  
  it = m_SF_hist.find(histName+"_down"); 
  if ( it != m_SF_hist.end() ) h_down = it->second;
  else std::cout << "ERROR! Unavailable SF: " << histName+"_down" << std::endl;
  
  // SF is a function of tau pT
  int binID = std::min(h_nominal->FindBin(f_tau_0_pt), h_nominal->GetNbinsX());

  float retval = h_nominal->GetBinContent(binID);
  float retval_up = h_up->GetBinContent(binID);
  float retval_down = h_down->GetBinContent(binID);
  float retval_error = fabs(retval_up - retval_down)/2.0;
  
  ///////////////////////////////////////////////////////////////
  // systematic uncertainty
  ///////////////////////////////////////////////////////////////
  if    ( (fSysName.Contains("FakeFactor_QCDReweight_MuHadBtag_1up")    && f_n_bjets>0) ||
          (fSysName.Contains("FakeFactor_QCDReweight_MuHadBveto_1up")   && f_n_bjets==0 )) {
    //retval = retval+fabs(retval-1.0)/2.0;
    retval = retval+fabs(retval-1.0);
  }
  else if((fSysName.Contains("FakeFactor_QCDReweight_MuHadBtag_1down")    && f_n_bjets>0) ||
          (fSysName.Contains("FakeFactor_QCDReweight_MuHadBveto_1down")   && f_n_bjets==0 )) {
    retval = retval-fabs(retval-1.0);
  }

  DEBUGclass("returning");

  return retval;
}
//______________________________________________________________________________________________

LeptonFakesReweight::LeptonFakesReweight(const TString& expression) : LepHadObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  //fSysName = expression;

  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("UseQCDSF", false) ) return;
  INFOclass("Loading file...");

  TFile* aFile= TFile::Open("bsmtautau_lephad/auxData/ScaleFactors/LFR_SF.root");
  if (!aFile) {
    ERRORclass("Can not find LFR_SF.root");
  }

  /// Read all the histgrams in the root files, and save it to a map so that we can find the
  /// right histgram given the name
  TList* list = aFile->GetListOfKeys();
  TIter next(list);
  TKey* key;

  while ( (key = (TKey*)next()) ) {
    TString className = key->GetClassName();
    if (className == "TH1F") {
      TH1F* hist = (TH1F*)aFile->Get(key->GetName());
      hist->SetDirectory(0);
      m_SF_hist[key->GetName()] = hist;
    }
  }
  aFile->Close();
}
//______________________________________________________________________________________________

const TString& LeptonFakesReweight::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool LeptonFakesReweight::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void LeptonFakesReweight::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool LeptonFakesReweight::initializeSelf(){
  if (!LepHadObservable::initializeSelf()) return false;

  fSysName = this->fSample->replaceInTextRecursive("$(sfVariation.lsf)","~");

  return true;
}

//______________________________________________________________________________________________

bool LeptonFakesReweight::finalizeSelf(){
  if (!LepHadObservable::finalizeSelf()) return false;
  return true;
}
