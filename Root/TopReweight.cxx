#include "BSMtautauCAF/TopReweight.h"
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

ClassImp(TopReweight)

//______________________________________________________________________________________________

TopReweight::TopReweight(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

TopReweight::~TopReweight(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* TopReweight::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();

  //bnames->SetOwner(true);
  return bnames;
}

//______________________________________________________________________________________________
double TopReweight::getValue() const {
  
  double f_tau_0_pt       = this->tau_0_pt->EvalInstance();
  int    f_n_bjets        = this->n_bjets->EvalInstance();
  int    f_tau_0_n_charged_tracks = this->tau_0_n_charged_tracks->EvalInstance();


  ///////////////////////////////////////////////////////////////
  // determine which SF to use
  ///////////////////////////////////////////////////////////////
  // channel: lephad 
  TString channel = "lephad";
  
  // region: btag, 1p or 3p
  TString region = "";
  if ( 0 == f_n_bjets ) return 1.0;
  else if (1<= f_n_bjets) region = "Btag";

  if ( 1 == f_tau_0_n_charged_tracks) region += "1p";
  else if ( 3 == f_tau_0_n_charged_tracks) region += "3p";
  else return 1.0;

  // peiriod: Combined or Separated
  TString period = "All";

  // parameterization
  TString param = "TauPt";

  TString histName = "TCR"+ period + channel + region + param + "SF";

  TH1F * h_nominal = 0;
  TH1F * h_up = 0;
  TH1F * h_down = 0;
 
  auto it = m_SF_hist.find(histName); 
  if ( it != m_SF_hist.end() ) h_nominal = it->second;
  else {
    std::cout << "error! unavailable FF: " << histName << std::endl;
    for (auto item : m_SF_hist)
      std::cout << "available FF: " << item.first << std::endl;
  }

  it = m_SF_hist.find(histName+"_up"); 
  if ( it != m_SF_hist.end() ) h_up = it->second;
  else std::cout << "error! unavailable FF: " << histName+"_up" << std::endl;
  
  it = m_SF_hist.find(histName+"_down"); 
  if ( it != m_SF_hist.end() ) h_down = it->second;
  else std::cout << "error! unavailable FF: " << histName+"_down" << std::endl;

  // FF is a function of tauPt 
  int binID = std::min(h_nominal->FindBin(f_tau_0_pt), h_nominal->GetNbinsX());

  float retval = h_nominal->GetBinContent(binID);
  float retval_up = h_up->GetBinContent(binID);
  float retval_down = h_down->GetBinContent(binID);
  float retval_error = fabs(retval_up - retval_down)/2.0;

  ///////////////////////////////////////////////////////////////
  // systematic uncertainty
  ///////////////////////////////////////////////////////////////
  if    ( (fSysName.Contains("TopReweight_LepHadBtag1p_1up")    && f_n_bjets>0) ||
          (fSysName.Contains("TopReweight_LepHadBtag3p_1up")   && f_n_bjets==0 )) {
    retval = retval+retval_error;
  }
  else if((fSysName.Contains("TopReweight_LepHadBtag1p_1down")    && f_n_bjets>0) ||
          (fSysName.Contains("TopReweight_LepHadBtag3p_1down")   && f_n_bjets==0 )) {
    retval = retval-retval_error;
  }

  return retval;
}
//______________________________________________________________________________________________

TopReweight::TopReweight(const TString& expression) : LepHadObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  //fSysName = expression;

  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("UseTopSF", false) ) return;
  INFOclass("Loading file...");

  TFile* aFile= TFile::Open("bsmtautau_lephad/auxData/ScaleFactors/TCR_SF.root");
  if (!aFile) {
    ERRORclass("Can not find WFR_SF.root");
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

const TString& TopReweight::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool TopReweight::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void TopReweight::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool TopReweight::initializeSelf(){
  if (! LepHadObservable::initializeSelf()) return false;

  fSysName = this->fSample->replaceInTextRecursive("$(sfVariation.top)","~");

  return true;
}

//______________________________________________________________________________________________

bool TopReweight::finalizeSelf(){
  if (! LepHadObservable::finalizeSelf()) return false;
  return true;
}
