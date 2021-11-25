#include "BSMtautauCAF/OtherJetsTFF.h"
#include <limits>

#include "QFramework/TQLibrary.h"
#include "TFile.h"
#include "TMath.h"
#include <map>

ClassImp(OtherJetsTFF)



OtherJetsTFF::OtherJetsTFF() {
  this->setExpression(this->GetName() );
  DEBUGclass("default constructor called");
}



OtherJetsTFF::OtherJetsTFF(const TString& expression) : LepHadObservable(expression) {
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);
  
  INFOclass("Loading file...");
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("ApplyOtherJetsTFF", false) ) return;

  TString signalProcess = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("SignalProcess", signalProcess) ){
    ERRORclass("AnaChannel not set !!!");
  }
  TFile* file=0;
  if ("AHZ" == signalProcess) {
    file= TFile::Open("AHZ-lephad/auxData/FakeFactors/OtherJetsTFR_FF.root");
    if (!file) {
      ERRORclass("Can not find OtherJetsTFR_FF.root");
    }
  }
  else if ("LQtaub" == signalProcess) {
    file= TFile::Open(signalProcess+"-lephad/auxData/FakeFactors/OtherJetsSSR_FF.root");
    if (!file) {
      ERRORclass("Can not find OtherJetsSSR_FF.root");
    }
  }
  /// Read all the histgrams in the root files, and save it to a map so that we can find the
  /// right histgram given the name
  TList* list = file->GetListOfKeys();
  TIter next(list);
  TKey* key;

  while ( (key = (TKey*)next()) ) {
    TString className = key->GetClassName();
    if (className == "TH1F") {
      TH1F* hist = (TH1F*)file->Get(key->GetName());
      hist->SetDirectory(0);
      m_FF_hist[key->GetName()] = hist;
    }
  }
  file->Close();
}



TObjArray* OtherJetsTFF::getBranchNames() const {
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();
  return bnames;
}



bool OtherJetsTFF::initializeSelf() {
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("ApplyOtherJetsTFF", false) ) return true;
  if (! LepHadObservable::initializeSelf()) return false;
  fSysName = this->fSample->replaceInTextRecursive("$(variation)","~");

  return true;
}



bool OtherJetsTFF::finalizeSelf() {
  if (! LepHadObservable::finalizeSelf()) return false;
  return true;
}



auto OtherJetsTFF::getFakeFactorHist() const {
  TString signalProcess = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("SignalProcess", signalProcess) ){
    ERRORclass("AnaChannel not set !!!");
  }
  // determine which FF hist we want: All
  TString histName = "OtherJetsTFR";
  if ("LQtaub" == signalProcess) { histName = "OtherJetsSSR";}


  // -- period: Combined or Separated
  TString period = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("OtherJetsTFFPeriod", period) ) {
    ERRORclass("Can not get OtherJetsTFFPeriod tag");
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
    ERRORclass("Unknown OtherJetsTFFPeriod tag");
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
   }

  // -- charge: OS/SS
  if (this->lephad_qxq->EvalInstance() == -1) {
    if ("LQtaub" == signalProcess) { 
      histName += "SS";
    }
    else {
      histName += "OS";
    } 
  }
  else {
    histName += "SS";
  }

  // -- category: Bveto/Btag
  if (bjetCount()>=1) {
    histName += "Btag";
  }
  else {
    if ("LQtaub" == signalProcess) { 
      histName += "Btag";
    }
    else {
      histName += "Bveto";
    }
  }

  if ("LQtaub" == signalProcess) {
    histName += "";
  }
  else {
    histName += "MediumMT";
  }  

  // -- 1p/3p
  if (this->tau_0_n_charged_tracks->EvalInstance() == 1) {
    histName += "1p";
  }
  else {
    histName += "3p";
  }
  
  // -- parameterization
  if ("LQtaub" == signalProcess) {
    histName += "TauPtFF";
  }
  else {
    if (bjetCount()>=1) {
      histName += "BTBinTauPtFF";
    }
    else {
      histName += "TauPtFF";
    }
  }
  // -- Get up down and nominal histos
  const TH1F * h_nominal = 0;
  const TH1F * h_up = 0;
  const TH1F * h_down = 0;

  auto it = m_FF_hist.find(histName); 
  if ( it != m_FF_hist.end() ) h_nominal = it->second;
  else {
    std::cout << "ERROR! Unavailable FF: " << histName << std::endl;
    for (auto item : m_FF_hist) {
      std::cout << "Available FF: " << item.first << std::endl;
    }
  }

  it = m_FF_hist.find(histName+"_up");
  if ( it != m_FF_hist.end() ) h_up = it->second;
  else std::cout << "ERROR! Unavailable FF: " << histName+"_up" << std::endl;
 
  it = m_FF_hist.find(histName+"_down"); 
  if ( it != m_FF_hist.end() ) h_down = it->second;
  else std::cout << "ERROR! Unavailable FF: " << histName+"_down" << std::endl;


  return std::make_tuple(h_nominal, h_up, h_down);
}



double OtherJetsTFF::getValue() const {
  TString signalProcess = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("SignalProcess", signalProcess) ){
    ERRORclass("AnaChannel not set !!!");
  }


  // Check whether we want to apply the fake factor
  bool apply = false;
  if (! TQTaggable::getGlobalTaggable("aliases")->getTagBool("ApplyOtherJetsTFF", apply)) {
    ERRORclass("Can not get ApplyOtherJetsTFF tag");
  }
  if (!apply) return 1.0;

  const TH1F* h_nominal;
  const TH1F* h_up;
  const TH1F* h_down;

  std::tie(h_nominal,h_up,h_down)  = getFakeFactorHist();


  int f_n_bjets        = this->n_bjets->EvalInstance();
  int f_tau_0_n_charged_tracks = this->tau_0_n_charged_tracks->EvalInstance();
  float f_lep_0_pt = this->lep_0_pt->EvalInstance();
  float f_tau_0_pt = this->tau_0_pt->EvalInstance();
  float f_jet_0_pt = this->jet_0_pt->EvalInstance();
  float f_bjet_0_pt = this->bjet_0_pt->EvalInstance();
  float st = f_lep_0_pt + f_tau_0_pt + f_jet_0_pt;
  float SumOfPt = f_lep_0_pt + f_tau_0_pt + f_bjet_0_pt;

  float variable = 0.0;
  if ("LQtaub" == signalProcess) {
    variable = f_tau_0_pt;
  }
  else {
    variable = f_tau_0_pt;
  }


  int binID = std::min(h_nominal->FindFixBin(variable), h_nominal->GetNbinsX());
  if (binID == 0) binID = 1;

  float retval = h_nominal->GetBinContent(binID);
  float retval_up = h_up->GetBinContent(binID);
  float retval_down = h_down->GetBinContent(binID);
  float retval_error = fabs(retval_up - retval_down)/2.0;

  ///////////////////////////////////////////////////////////////
  // systematic uncertainty
  ///////////////////////////////////////////////////////////////
  float ratio_scale_1p = 1.0; // Needs re-evaluation
  float ratio_scale_3p = 1.0;
  if ("LQtaub" == signalProcess) {
    ratio_scale_1p = 1.0; // Needs re-evaluation
    ratio_scale_3p = 1.0;
  }
  else {
    ratio_scale_1p = 0.862; // Needs re-evaluation
    ratio_scale_3p = 0.881;
  }

  if    ( (fSysName.Contains("FakeFactor_OtherJetsBtag1p_1up")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_OtherJetsBtag3p_1up")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_OtherJetsBveto1p_1up") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_OtherJetsBveto3p_1up") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3)    ) {
    if (f_n_bjets>0 && f_tau_0_n_charged_tracks==1)
      retval *= (ratio_scale_1p+0.262);
    else if (f_n_bjets>0 && f_tau_0_n_charged_tracks==3)
      retval *= (ratio_scale_3p+0.262);
    else
      retval += retval_error;
  }
  else if((fSysName.Contains("FakeFactor_OtherJetsBtag1p_1down")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_OtherJetsBtag3p_1down")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_OtherJetsBveto1p_1down") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_OtherJetsBveto3p_1down") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3)    ) {
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
