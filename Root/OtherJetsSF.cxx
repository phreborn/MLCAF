#include "BSMtautauCAF/OtherJetsSF.h"
#include <limits>

#include "QFramework/TQLibrary.h"
#include "TFile.h"
#include "TMath.h"
#include <map>

ClassImp(OtherJetsSF)



OtherJetsSF::OtherJetsSF() {
  this->setExpression(this->GetName() );
  DEBUGclass("default constructor called");
}



OtherJetsSF::OtherJetsSF(const TString& expression) : LepHadObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  //fSysName = expression;

  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("ApplyOtherJetsSF", false) ) return;
  INFOclass("Loading file...");

  TFile* aFile= TFile::Open("AHZ-lephad/auxData/ScaleFactors/OtherJetsTFR_SF.root");
  if (!aFile) {
    ERRORclass("Can not find OtherJetsTFR_SF.root");
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



TObjArray* OtherJetsSF::getBranchNames() const {
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();
  return bnames;
}



bool OtherJetsSF::initializeSelf() {
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("ApplyOtherJetsSF", false) ) return true;
  if (! LepHadObservable::initializeSelf()) return false;
  fSysName = this->fSample->replaceInTextRecursive("$(variation)","~");

  return true;
}



bool OtherJetsSF::finalizeSelf(){
  if (! LepHadObservable::finalizeSelf()) return false;
  return true;
}



double OtherJetsSF::getValue() const {
  // determine which SF to use
  TString histName = "OtherJetsTFR";
  
  // -- period: Combined or Separated
  TString period = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("OtherJetsSFPeriod", period) ) {
    ERRORclass("Can not get OtherJetsSFPeriod tag");
  }
  
  if ("Combined" == period) {
    histName += "All";
  }
  else if ("Separated" == period) {
    if (is2015() || is2016()) histName += "1516";
    if (is2017()) histName += "17";
    if (is2018()) histName += "18";
  }
  else {
    ERRORclass("Unknown OtherJetsSFPeriod tag");
    return 1.0;
  }
  
  // -- channel: ehad/muhad
  if (isMuon()) {
    histName += "muhad";
  } 
  else if (isElectron()) {
    histName += "ehad";
  }
  else {
    ERRORclass("Unknown channel");
    return 1.0;
  }
  
  // -- charge: OS/SS
  if (this->lephad_qxq->EvalInstance() == -1) {
    histName += "OS";
  }
  else {
    histName += "SS";
  }
  
  // -- category: Bveto/Btag
  if (bjetCount()>=1) {
    histName += "Btag";
  }
  else {
    histName += "Bveto";
  }
  
  // -- MT region
  TString param = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("OtherJetsSFParam", param) ) ERRORclass("Can not get OtherJetsSFParam tag");
  if (param != "MTLepMET") {
    histName += "MediumMT";
  }
  else {
    histName += "NoMT";
  }

  // -- 1p/3p
  if (this->tau_0_n_charged_tracks->EvalInstance() == 1) {
    histName += "1p";
  }
  else {
    histName += "3p";
  }

  // -- parameterization
  double variable = 0.0;
  if (param == "LeptonPt") {
    variable = this->lep_0_pt->EvalInstance();
  }
  else if (param == "MET") {
    variable = this->met_reco_et->EvalInstance();
  }
  else if (param == "TauEta") {
    variable = this->tau_0_eta->EvalInstance();
  }
  else if (param == "MTLepMET") {
    variable = this->lephad_mt_lep0_met->EvalInstance();
  }
  else {
    std::cout << "Unknown parameterization: " << param << std::endl;
  }
  histName += param;
  histName += "SF";

  // -- obtain the histogram
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
  

  float f_tau_0_pt = this->tau_0_pt->EvalInstance();
  int f_n_bjets        = this->n_bjets->EvalInstance();
  int f_tau_0_n_charged_tracks = this->tau_0_n_charged_tracks->EvalInstance();
  int f_lep_0 = this->lep_0_pt->EvalInstance();

  // SF is a function of tau pT
  int binID = std::min(h_nominal->FindBin(f_tau_0_pt), h_nominal->GetNbinsX());
  if (binID == 0) binID = 1;

  float retval = h_nominal->GetBinContent(binID);
  float retval_up = h_up->GetBinContent(binID);
  float retval_down = h_down->GetBinContent(binID);
  float retval_error = fabs(retval_up - retval_down)/2.0;


  ///////////////////////////////////////////////////////////////
  // systematic uncertainty
  ///////////////////////////////////////////////////////////////
  if    ( 
          (fSysName.Contains("FakeFactor_OtherJetsReweight_Bveto1p_1up") && f_tau_0_n_charged_tracks == 1 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_Bveto3p_1up") && f_tau_0_n_charged_tracks == 3 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_Btag1p_1up") && f_tau_0_n_charged_tracks == 1 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_Btag3p_1up") && f_tau_0_n_charged_tracks == 3 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_ElHadBveto1p_1up") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 1 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_MuHadBveto1p_1up") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 1 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_ElHadBveto3p_1up") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 3 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_MuHadBveto3p_1up") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 3 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_ElHadBtag1p_1up") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 1 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_MuHadBtag1p_1up") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 1 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_ElHadBtag3p_1up") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 3 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_MuHadBtag3p_1up") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 3 && f_n_bjets > 0) 
        ) {
    if (f_n_bjets == 0)
      retval = retval+fabs(retval-1.0);
    else 
      retval = 1.0+fabs(retval-1.0);
  }
  else if(
          (fSysName.Contains("FakeFactor_OtherJetsReweight_Bveto1p_1down") && f_tau_0_n_charged_tracks == 1 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_Bveto3p_1down") && f_tau_0_n_charged_tracks == 3 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_Btag1p_1down") && f_tau_0_n_charged_tracks == 1 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_Btag3p_1down") && f_tau_0_n_charged_tracks == 3 && f_n_bjets > 0) || 
          (fSysName.Contains("FakeFactor_OtherJetsReweight_ElHadBveto1p_1down") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 1 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_MuHadBveto1p_1down") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 1 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_ElHadBveto3p_1down") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 3 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_MuHadBveto3p_1down") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 3 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_ElHadBtag1p_1down") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 1 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_MuHadBtag1p_1down") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 1 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_ElHadBtag3p_1down") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 3 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_OtherJetsReweight_MuHadBtag3p_1down") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 3 && f_n_bjets > 0) 
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


  DEBUGclass("returning");

  return retval;

}
