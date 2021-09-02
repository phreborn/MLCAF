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
  fSysName = this->fSample->replaceInTextRecursive("$(variation)","~");

  return true;
}



bool MultiJetsLFF::finalizeSelf() {
  if (! LepHadObservable::finalizeSelf()) return false;
  return true;
}



auto MultiJetsLFF::getFakeFactorHist() const {
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



double MultiJetsLFF::getValue() const {
  // Check whether we want to apply the fake factor
  bool apply = false;
  if (! TQTaggable::getGlobalTaggable("aliases")->getTagBool("ApplyMultiJetsLFF", apply)) {
    ERRORclass("Can not get ApplyMultiJetsLFF tag");
  }
  if (!apply) return 1.0;
  
  const TH1F* h_nominal;
  const TH1F* h_up;
  const TH1F* h_down;

  std::tie(h_nominal,h_up,h_down)  = getFakeFactorHist();


  float f_lep_0_pt = this->lep_0_pt->EvalInstance();
  int f_lep_0 = this->lep_0_pt->EvalInstance();
  int f_n_bjets = this->n_bjets->EvalInstance();

  int binID = std::min(h_nominal->FindFixBin(f_lep_0_pt), h_nominal->GetNbinsX());
  if (binID == 0) binID = 1;

  float retval = h_nominal->GetBinContent(binID);
  float retval_up = h_up->GetBinContent(binID);
  float retval_down = h_down->GetBinContent(binID);
  float retval_error = fabs(retval_up - retval_down)/2.0;

  ///////////////////////////////////////////////////////////////
  // systematic uncertainty
  ///////////////////////////////////////////////////////////////
  if ( (fSysName.Contains("FakeFactor_MFR_ElBveto_1up") && f_lep_0==2 && f_n_bjets==0) ||
       (fSysName.Contains("FakeFactor_MFR_ElBtag_1up") && f_lep_0==2 && f_n_bjets>0) ||
       (fSysName.Contains("FakeFactor_MFR_MuBveto_1up") && f_lep_0==1 && f_n_bjets==0) ||
       (fSysName.Contains("FakeFactor_MFR_MuBtag_1up") && f_lep_0==1 && f_n_bjets>0)  ) {
    retval += retval_error;
  }
  else if(  (fSysName.Contains("FakeFactor_MFR_ElBveto_1down") && f_lep_0==2 && f_n_bjets==0) ||
            (fSysName.Contains("FakeFactor_MFR_ElBtag_1down") && f_lep_0==2 && f_n_bjets>0) ||
            (fSysName.Contains("FakeFactor_MFR_MuBveto_1down") && f_lep_0==1 && f_n_bjets==0) ||
            (fSysName.Contains("FakeFactor_MFR_MuBtag_1down") && f_lep_0==1 && f_n_bjets>0) ) {
    retval -= retval_error;

  }



  return retval;
}
