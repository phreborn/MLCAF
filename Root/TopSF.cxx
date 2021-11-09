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
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("ApplyTopSF", false) ) return;

  TString signalProcess = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("SignalProcess", signalProcess) ){
    ERRORclass("AnaChannel not set !!!");
  }
  TFile* file= TFile::Open(signalProcess+"-lephad/auxData/ScaleFactors/TopCR_SF.root");
  //TFile* file= TFile::Open("AHZ-lephad/auxData/ScaleFactors/TopCR_SF.root");
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
  fSysName = this->fSample->replaceInTextRecursive("$(variation)","~");

  return true;
}



bool TopSF::finalizeSelf() {
  if (! LepHadObservable::finalizeSelf()) return false;
  return true;
}



auto TopSF::getFakeFactorHist() const {
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
  }

  float f_lephad_dphi = this->lephad_dphi->EvalInstance();
  if (f_lephad_dphi>2.4) {
    histName += "lephadTCRTauIDMediumMTStSF2";
  }
  else if (f_lephad_dphi>1.8) {
    histName += "lephad2bTVRNoTauIDMediumMTStSF2";
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



double TopSF::getValue() const {
  // Check whether we want to apply the fake factor
  bool apply = false;
  if (! TQTaggable::getGlobalTaggable("aliases")->getTagBool("ApplyTopSF", apply)) {
    ERRORclass("Can not get ApplyTopSF tag");
  }
  if (!apply) return 1.0;
  
  const TH1F* h_nominal;
  const TH1F* h_up;
  const TH1F* h_down;

  std::tie(h_nominal,h_up,h_down)  = getFakeFactorHist();


  float f_lep_0_pt = this->lep_0_pt->EvalInstance();
  int f_n_bjets = this->n_bjets->EvalInstance();
  float f_tau_0_pt = this->tau_0_pt->EvalInstance();
  float f_jet_0_pt = this->jet_0_pt->EvalInstance();
  float st = f_lep_0_pt + f_tau_0_pt + f_jet_0_pt;

  int binID = std::min(h_nominal->FindFixBin(st), h_nominal->GetNbinsX());
  if (binID == 0) binID = 1;

  float retval = h_nominal->GetBinContent(binID);
  float retval_up = h_up->GetBinContent(binID);
  float retval_down = h_down->GetBinContent(binID);
  float retval_error = fabs(retval_up - retval_down)/2.0;


  ///////////////////////////////////////////////////////////////
  // systematic uncertainty
  ///////////////////////////////////////////////////////////////
  if ( (fSysName.Contains("FakeFactor_TCR_ElBveto_1up") && isElectron() && f_n_bjets==0) ||
       (fSysName.Contains("FakeFactor_TCR_ElBtag_1up") && isElectron() && f_n_bjets>0) ||
       (fSysName.Contains("FakeFactor_TCR_MuBveto_1up") && isMuon() && f_n_bjets==0) ||
       (fSysName.Contains("FakeFactor_TCR_MuBtag_1up") && isMuon() && f_n_bjets>0)  ) {
    retval += retval_error;
  }
  else if(  (fSysName.Contains("FakeFactor_TCR_ElBveto_1down") && isElectron() && f_n_bjets==0) ||
            (fSysName.Contains("FakeFactor_TCR_ElBtag_1down") && isElectron() && f_n_bjets>0) ||
            (fSysName.Contains("FakeFactor_TCR_MuBveto_1down") && isMuon() && f_n_bjets==0) ||
            (fSysName.Contains("FakeFactor_TCR_MuBtag_1down") && isMuon() && f_n_bjets>0) ) {
    retval -= retval_error;

  }



  return retval;
}
