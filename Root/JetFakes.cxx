#include "BSMtautauCAF/JetFakes.h"
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

ClassImp(JetFakes)

//______________________________________________________________________________________________

JetFakes::JetFakes(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

JetFakes::~JetFakes(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* JetFakes::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();
  return bnames;
}

//______________________________________________________________________________________________
double JetFakes::getValue() const {
  
  int f_n_bjets        = this->n_bjets->EvalInstance();
  int f_tau_0_n_charged_tracks = this->tau_0_n_charged_tracks->EvalInstance();
  
  int f_lep_0              = this->lep_0->EvalInstance();
  double f_tau_0_pt       = this->tau_0_pt->EvalInstance();
  double f_lephad_met_lep1_cos_dphi = this->lephad_met_lep1_cos_dphi->EvalInstance();
  double f_lep_0_pt   = this->lep_0_pt->EvalInstance();

  ///////////////////////////////////////////////////////////////
  // determine which FF to use
  ///////////////////////////////////////////////////////////////
  // channel: ehad or muhad
  TString channel = "";
  if (1==f_lep_0) channel = "muhad";
  else if (2==f_lep_0) channel = "ehad";
  
  // region: bveto (btag use bveto FF), 1p or 3p
  TString region = "Bveto";

  if ( 1 == f_tau_0_n_charged_tracks) region += "1p";
  else if ( 3 == f_tau_0_n_charged_tracks) region += "3p";
  else return 1.0;

  // peiriod: Combined or Separated
  TString period = "";
  TString period_tag = "";
  //if(!this->fSample->getTag("~WFFPeriod",period_tag)) std::cout<<"ERROR: Can not get WFFPeriod tag" << std::endl;
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("WFFPeriod", period_tag) ) ERRORclass("Can not get WFFPeriod tag");
  if ("Combined" == period_tag)
    period = "All";
  else if ("Separated" == period_tag) {
    if (is2015() || is2016()) period = "1516";
    if (is2017()) period = "17";
    if (is2018()) period = "18";
  }
  else
    std::cout << "ERROR: Unknown WFFPeriod tag" << std::endl;

  // parameterization
  TString param = "";
  TString param_tag = "";
  //if(!this->fSample->getTag("~WFFParam",param_tag)) std::cout<<"ERROR: Can not get WFFParam tag" << std::endl;
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("WFFParam", param_tag) ) ERRORclass("Can not get WFFParam tag");
  if ( "TauPt" == param_tag ) {
    param = "TauPt";
  }
  else if ( "TauPtDphi" == param_tag) {
    // dphi 1,2,3,4 in bveto/btag category
    if (0 == f_n_bjets) {
      if (f_lephad_met_lep1_cos_dphi>=0.0&&f_lephad_met_lep1_cos_dphi<1) param = "TauPtDphi1";
      else if (f_lephad_met_lep1_cos_dphi>=1&&f_lephad_met_lep1_cos_dphi<2) param = "TauPtDphi2";
      else if (f_lephad_met_lep1_cos_dphi>=2&&f_lephad_met_lep1_cos_dphi<2.5) param = "TauPtDphi3";
      else if (f_lephad_met_lep1_cos_dphi>=2.5) param = "TauPtDphi4";
    }
    else if (1 <= f_n_bjets) {
      if (f_lephad_met_lep1_cos_dphi>=0.0&&f_lephad_met_lep1_cos_dphi<1) param = "TauPtDphi1";
      else if (f_lephad_met_lep1_cos_dphi>=1&&f_lephad_met_lep1_cos_dphi<2) param = "TauPtDphi2";
      else if (f_lephad_met_lep1_cos_dphi>=2&&f_lephad_met_lep1_cos_dphi<2.5) param = "TauPtDphi3";
      else if (f_lephad_met_lep1_cos_dphi>=2.5) param = "TauPtDphi4";
    }
  }
  else if ( "TauPtLeptonPt" == param_tag) {
    if (f_lep_0_pt>=30&&f_lep_0_pt<50) param = "TauPtLeptonPt1";
    else if (f_lep_0_pt>=50&&f_lep_0_pt<70) param = "TauPtLeptonPt2";
    else if (f_lep_0_pt>=70&&f_lep_0_pt<100) param = "TauPtLeptonPt3";
    else if (f_lep_0_pt>=100) param = "TauPtLeptonPt4";
  }

  TString histName = "WFR"+ period + channel + region + param + "FF";

  TH1F * h_nominal = 0;
  TH1F * h_up = 0;
  TH1F * h_down = 0;
 
  auto it = m_FF_hist.find(histName); 
  if ( it != m_FF_hist.end() ) h_nominal = it->second;
  else {
    std::cout << "error! unavailable FF: " << histName << std::endl;
    for (auto item : m_FF_hist)
      std::cout << "available FF: " << item.first << std::endl;
  }

  it = m_FF_hist.find(histName+"_up"); 
  if ( it != m_FF_hist.end() ) h_up = it->second;
  else std::cout << "error! unavailable FF: " << histName+"_up" << std::endl;
  
  it = m_FF_hist.find(histName+"_down"); 
  if ( it != m_FF_hist.end() ) h_down = it->second;
  else std::cout << "error! unavailable FF: " << histName+"_down" << std::endl;

  // FF is a function of tau pT
  int binID = std::min(h_nominal->FindBin(f_tau_0_pt), h_nominal->GetNbinsX());

  float retval = h_nominal->GetBinContent(binID);
  float retval_up = h_up->GetBinContent(binID);
  float retval_down = h_down->GetBinContent(binID);
  float retval_error = fabs(retval_up - retval_down)/2.0;

  ///////////////////////////////////////////////////////////////
  // systematic uncertainty
  ///////////////////////////////////////////////////////////////
  float ratio_scale_1p = 0.862;
  float ratio_scale_3p = 0.881;

  if    ( (fSysName.Contains("FakeFactor_WjetsBtag1p_1up")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_WjetsBtag3p_1up")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_WjetsBveto1p_1up") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_WjetsBveto3p_1up") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3)    ) {
    if (f_n_bjets>0 && f_tau_0_n_charged_tracks==1)
      retval *= (ratio_scale_1p+0.262);
    else if (f_n_bjets>0 && f_tau_0_n_charged_tracks==3)
      retval *= (ratio_scale_3p+0.262);
    else
      retval += retval_error;
  }
  else if((fSysName.Contains("FakeFactor_WjetsBtag1p_1down")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_WjetsBtag3p_1down")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_WjetsBveto1p_1down") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_WjetsBveto3p_1down") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3)    ) {
    if (f_n_bjets>0 && f_tau_0_n_charged_tracks==1)
      retval *= (ratio_scale_1p-0.262);
    else if (f_n_bjets>0 && f_tau_0_n_charged_tracks==3)
      retval *= (ratio_scale_3p-0.262);
    else
      retval -= retval_error;
  }
  else {
    if (f_n_bjets>0 && 1==f_tau_0_n_charged_tracks){
      retval *= ratio_scale_1p;
    }
    else if (f_n_bjets>0 && 3==f_tau_0_n_charged_tracks){
      retval *= ratio_scale_3p;
    }
  }

  return retval;
}
//______________________________________________________________________________________________

JetFakes::JetFakes(const TString& expression) : LepHadObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  //fSysName = expression;

  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("UseWjetsFF", false) ) return;
  INFOclass("Loading file...");

  TString signalProcess = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("SignalProcess", signalProcess) ){
    ERRORclass("AnaChannel not set !!!");
  }
  TFile* aFile= TFile::Open(signalProcess+"_lephad/auxData/FakeFactors/WFR_FF.root");
  if (!aFile) {
    ERRORclass("Can not find WFR_FF.root");
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
      m_FF_hist[key->GetName()] = hist;
    }
  }
  aFile->Close();
}

//______________________________________________________________________________________________

const TString& JetFakes::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool JetFakes::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void JetFakes::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool JetFakes::initializeSelf(){
  if (!LepHadObservable::initializeSelf()) return false;

  fSysName = this->fSample->replaceInTextRecursive("$(sfVariation.wff)","~");

  return true;
}

//______________________________________________________________________________________________

bool JetFakes::finalizeSelf(){
  if (!LepHadObservable::finalizeSelf())  return false; 
  return true;
}
