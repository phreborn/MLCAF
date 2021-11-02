#include "BSMtautauCAF/OtherJetsTFR.h"
#include <limits>

#include "QFramework/TQLibrary.h"
#include "TFile.h"
#include "TMath.h"
#include <map>

ClassImp(OtherJetsTFR)



OtherJetsTFR::OtherJetsTFR() {
  this->setExpression(this->GetName() );
  DEBUGclass("default constructor called");
}



OtherJetsTFR::OtherJetsTFR(const TString& expression) : LepHadObservable(expression) {
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);
  
  INFOclass("Loading file...");
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("ApplyOtherJetsTFR", false) ) return;

  TFile* file= TFile::Open("AHZ-lephad/auxData/FakeFactors/MCOtherJetsTFR_FF.root");
  if (!file) {
    ERRORclass("Can not find MCOtherJetsTFR_FF.root");
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



TObjArray* OtherJetsTFR::getBranchNames() const {
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();
  return bnames;
}



bool OtherJetsTFR::initializeSelf() {
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("ApplyOtherJetsTFR", false) ) return true;
  if (! LepHadObservable::initializeSelf()) return false;
  fSysName = this->fSample->replaceInTextRecursive("$(variation)","~");

  return true;
}



bool OtherJetsTFR::finalizeSelf() {
  if (! LepHadObservable::finalizeSelf()) return false;
  return true;
}



const TH1F* OtherJetsTFR::getFakeFactorHist() const {
  // determine which FF hist we want: All
  TString histName = "MCOtherJetsTFR";

  // -- period: Combined or Separated
  TString period = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("OtherJetsTFRPeriod", period) ) {
    ERRORclass("Can not get OtherJetsTFRPeriod tag");
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
    ERRORclass("Unknown OtherJetsTFRPeriod tag");
    return nullptr;
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
    return nullptr;
  }

  // -- charge: OS/SS, use SS for now
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

  histName += "MediumMT";
  
  // -- 1p/3p
  if (this->tau_0_n_charged_tracks->EvalInstance() == 1) {
    histName += "1p";
  }
  else {
    histName += "3p";
  }
  
  // -- parameterization
  histName += "TauPtFF";

  auto it = m_FF_hist.find(histName); 
  if ( it != m_FF_hist.end() ) {
    return it->second;
  }
  else {
    std::cout << "ERROR! Unavailable FF: " << histName << std::endl;
    for (auto item : m_FF_hist) {
      std::cout << "Available FF: " << item.first << std::endl;
    }
  } 
 
  return nullptr;
}



double OtherJetsTFR::getValue() const {
  // Check whether we want to apply the fake factor
  bool apply = false;
  if (! TQTaggable::getGlobalTaggable("aliases")->getTagBool("ApplyOtherJetsTFR", apply)) {
    ERRORclass("Can not get ApplyOtherJetsTFR tag");
  }
  if (!apply) return 1.0;
  

  const TH1F* hist = getFakeFactorHist();

  float f_tau_0_pt = this->tau_0_pt->EvalInstance();
  int binID = std::min(hist->FindFixBin(f_tau_0_pt), hist->GetNbinsX());
  if (binID == 0) binID = 1;
  
  return hist->GetBinContent(binID);
}
