#include "BSMtautauCAF/MultiJetsLFF.h"
#include <limits>

#include "QFramework/TQLibrary.h"
#include "TFile.h"
#include "TMath.h"
#include <map>

ClassImp(MultiJetsLFF)



MultiJetsLFF::MultiJetsLFF() {
  this->setExpression(this->GetName() );
  DEBUGclass("default constructor called");
}



MultiJetsLFF::MultiJetsLFF(const TString& expression) : LepHadObservable(expression) {
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);
  
  INFOclass("Loading file...");
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("ApplyMultiJetsLFF", false) ) return;

  TFile* file= TFile::Open("AHZ-lephad/auxData/FakeFactors/MultiJetsLFR_FF.root");
  if (!file) {
    ERRORclass("Can not find MultiJetsLFR_FF.root");
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



TObjArray* MultiJetsLFF::getBranchNames() const {
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();
  return bnames;
}



bool MultiJetsLFF::initializeSelf() {
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("ApplyMultiJetsLFF", false) ) return true;
  if (! LepHadObservable::initializeSelf()) return false;
  fSysName = this->fSample->replaceInTextRecursive("$(sfVariation.lff)","~");

  return true;
}



bool MultiJetsLFF::finalizeSelf() {
  if (! LepHadObservable::finalizeSelf()) return false;
  return true;
}



const TH1F* MultiJetsLFF::getFakeFactorHist() const {
  // determine which FF hist we want: All
  TString histName = "MultiJetsLFRTopCorrected";

  // -- period: Combined or Separated
  TString period = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("MultiJetsLFFPeriod", period) ) {
    ERRORclass("Can not get MultiJetsLFFPeriod tag");
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
    ERRORclass("Unknown LFFPeriod tag");
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
  histName += "SS";

  // -- category: Bveto/Btag
  if (bjetCount()>=1) {
    histName += "Btag";
  }
  else {
    histName += "Bveto";
  }

  // -- parameterization
  float f_lep_0_eta = this->lep_0_eta->EvalInstance();
  if (std::abs(f_lep_0_eta)<=1.52) {
    histName += "LeptonPtCentralFF";
  }
  else {
    histName += "LeptonPtForwardFF";
  }

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



double MultiJetsLFF::getValue() const {
  // Check whether we want to apply the fake factor
  bool apply = false;
  if (! TQTaggable::getGlobalTaggable("aliases")->getTagBool("ApplyMultiJetsLFF", apply)) {
    ERRORclass("Can not get ApplyMultiJetsLFF tag");
  }
  if (!apply) return 1.0;
  

  const TH1F* hist = getFakeFactorHist();

  float f_lep_0_pt = this->lep_0_pt->EvalInstance();
  int binID = std::min(hist->FindFixBin(f_lep_0_pt), hist->GetNbinsX());
  if (binID == 0) binID = 1;

  return hist->GetBinContent(binID);
}
