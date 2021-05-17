#include "BSMtautauCAF/TopSF.h"
#include <limits>

#include "QFramework/TQLibrary.h"
#include "TFile.h"
#include "TMath.h"
#include <map>

ClassImp(TopSF)



TopSF::TopSF() {
  this->setExpression(this->GetName() );
  DEBUGclass("default constructor called");
}



TopSF::TopSF(const TString& expression) : LepHadObservable(expression) {
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);
  
  INFOclass("Loading file...");

  TFile* file= TFile::Open("AHZ-lephad/auxData/ScaleFactors/TopCR_SF.root");
  if (!file) {
    ERRORclass("Can not find TopCR_SF.root");
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



TObjArray* TopSF::getBranchNames() const {
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();
  return bnames;
}



bool TopSF::initializeSelf() {
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("ApplyTopSF", false) ) return true;
  if (! LepHadObservable::initializeSelf()) return false;
  fSysName = this->fSample->replaceInTextRecursive("$(sfVariation.lff)","~");

  return true;
}



bool TopSF::finalizeSelf() {
  if (! LepHadObservable::finalizeSelf()) return false;
  return true;
}



const TH1F* TopSF::getFakeFactorHist() const {
  // determine which SF hist we want: All
  TString histName = "TCR";

  // -- period: Combined or Separated
  TString period = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("TopSFPeriod", period) ) {
    ERRORclass("Can not get TopSFPeriod tag");
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
    ERRORclass("Unknown TopSFPeriod tag");
    return nullptr;
  }

  float f_lephad_dphi = this->lephad_dphi->EvalInstance();
  if (f_lephad_dphi>2.4) {
    histName += "lephadTCRTauIDMediumMTStSF2";
  }
  else if (f_lephad_dphi>1.8) {
    histName += "lephad2bTVRNoTauIDMediumMTStSF2";
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



double TopSF::getValue() const {
  // Check whether we want to apply the fake factor
  bool apply = false;
  if (! TQTaggable::getGlobalTaggable("aliases")->getTagBool("ApplyTopSF", apply)) {
    ERRORclass("Can not get ApplyTopSF tag");
  }
  if (!apply) return 1.0;
  

  const TH1F* hist = getFakeFactorHist();

  float f_lep_0_pt = this->lep_0_pt->EvalInstance();
  float f_tau_0_pt = this->tau_0_pt->EvalInstance();
  float f_jet_0_pt = this->jet_0_pt->EvalInstance();
  float st = f_lep_0_pt + f_tau_0_pt + f_jet_0_pt;

  int binID = std::min(hist->FindFixBin(st), hist->GetNbinsX());
  if (binID == 0) binID = 1;

  return hist->GetBinContent(binID);
}
