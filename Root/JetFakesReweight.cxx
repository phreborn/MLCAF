#include "BSMtautauCAF/JetFakesReweight.h"
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

ClassImp(JetFakesReweight)

//______________________________________________________________________________________________

JetFakesReweight::JetFakesReweight(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

JetFakesReweight::~JetFakesReweight(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* JetFakesReweight::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();

  return bnames;
}

//______________________________________________________________________________________________
double JetFakesReweight::getValue() const {
  
  int    f_n_bjets        = this->n_bjets->EvalInstance();
  int    f_tau_0_n_charged_tracks = this->tau_0_n_charged_tracks->EvalInstance();
  double f_lep_0              = this->lep_0->EvalInstance();
  double f_lep_0_pt       = this->lep_0_pt->EvalInstance();
  double f_tau_0_pt       = this->tau_0_pt->EvalInstance();
  double f_tau_0_eta       = this->tau_0_eta->EvalInstance();
  double f_met_reco_et       = this->met_reco_et->EvalInstance();

  ///////////////////////////////////////////////////////////////
  // determine which SF to use
  ///////////////////////////////////////////////////////////////
  // channel: ehad or muhad
  TString channel = "";
  if (1==f_lep_0) channel = "muhad";
  else if (2==f_lep_0) channel = "ehad";
  
  // region: bveto (btag use bveto SF), 1p or 3p
  TString region = "Bveto";

  if ( 1 == f_tau_0_n_charged_tracks) region += "1p";
  else if ( 3 == f_tau_0_n_charged_tracks) region += "3p";
  else return 1.0;

  // peiriod: Combined or Separated
  TString period = "All";

  // parameterization
  TString param = "";
  TString param_tag = "";
  float variable = 0.0;
  //if(!this->fSample->getTag("~WjetsSFParam",param_tag)) std::cout<<"ERROR: Can not find WjetsSFParam tag" << std::endl;
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("WjetsSFParam", param_tag) ) ERRORclass("Can not get WjetsSFParam tag");
  if (param_tag == "LeptonPt") {
    param = "LeptonPt";
    variable = f_lep_0_pt;
  }
  else if (param_tag == "MET") {
    param = "MET";
    variable = f_met_reco_et;
  }
  else if (param_tag == "TauEta") {
    param = "TauEta";
    variable = f_tau_0_eta;
  }

  TString histName = "WFR"+ period + channel + region + param + "SF";

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

  // FF is a function of variable
  int binID = std::min(h_nominal->FindBin(variable), h_nominal->GetNbinsX());

  float retval = h_nominal->GetBinContent(binID);
  float retval_up = h_up->GetBinContent(binID);
  float retval_down = h_down->GetBinContent(binID);
  float retval_error = fabs(retval_up - retval_down)/2.0;

  ///////////////////////////////////////////////////////////////
  // systematic uncertainty
  ///////////////////////////////////////////////////////////////
  if    ( 
          (fSysName.Contains("FakeFactor_WjetsReweight_Bveto1p_1up") && f_tau_0_n_charged_tracks == 1 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_Bveto3p_1up") && f_tau_0_n_charged_tracks == 3 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_Btag1p_1up") && f_tau_0_n_charged_tracks == 1 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_Btag3p_1up") && f_tau_0_n_charged_tracks == 3 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_ElHadBveto1p_1up") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 1 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_MuHadBveto1p_1up") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 1 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_ElHadBveto3p_1up") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 3 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_MuHadBveto3p_1up") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 3 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_ElHadBtag1p_1up") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 1 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_MuHadBtag1p_1up") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 1 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_ElHadBtag3p_1up") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 3 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_MuHadBtag3p_1up") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 3 && f_n_bjets > 0) 
        ) {
    if (f_n_bjets == 0)
      retval = retval+fabs(retval-1.0);
    else 
      retval = 1.0+fabs(retval-1.0);
  }
  else if(
          (fSysName.Contains("FakeFactor_WjetsReweight_Bveto1p_1down") && f_tau_0_n_charged_tracks == 1 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_Bveto3p_1down") && f_tau_0_n_charged_tracks == 3 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_Btag1p_1down") && f_tau_0_n_charged_tracks == 1 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_Btag3p_1down") && f_tau_0_n_charged_tracks == 3 && f_n_bjets > 0) || 
          (fSysName.Contains("FakeFactor_WjetsReweight_ElHadBveto1p_1down") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 1 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_MuHadBveto1p_1down") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 1 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_ElHadBveto3p_1down") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 3 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_MuHadBveto3p_1down") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 3 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_ElHadBtag1p_1down") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 1 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_MuHadBtag1p_1down") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 1 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_ElHadBtag3p_1down") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 3 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_MuHadBtag3p_1down") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 3 && f_n_bjets > 0) 
         ) {
    if (f_n_bjets ==0 )
      retval = retval-fabs(retval-1.0);
    else 
      retval = 1.0-fabs(retval-1.0);  
  }
  // no correction to btag
  else if (f_n_bjets > 0) {
    retval = 1.0;
  }

  return retval;
}
//______________________________________________________________________________________________

JetFakesReweight::JetFakesReweight(const TString& expression) : LepHadObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  fSysName = expression;

  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("UseWjetsSF", false) ) return;
  INFOclass("Loading file...");

  TFile* aFile= TFile::Open("ScaleFactors/WFR_SF.root");
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

const TString& JetFakesReweight::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool JetFakesReweight::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void JetFakesReweight::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}

//______________________________________________________________________________________________

bool JetFakesReweight::initializeSelf(){
  if (! LepHadObservable::initializeSelf()) return false;
  return true;
}

//______________________________________________________________________________________________

bool JetFakesReweight::finalizeSelf(){
  if (! LepHadObservable::finalizeSelf()) return false;
  return true;
}
