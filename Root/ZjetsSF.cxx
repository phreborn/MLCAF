#include "BSMtautauCAF/ZjetsSF.h"
#include <limits>

#include "QFramework/TQLibrary.h"
#include "TFile.h"
#include "TMath.h"
#include <map>

ClassImp(ZjetsSF)



ZjetsSF::ZjetsSF() {
  this->setExpression(this->GetName() );
  DEBUGclass("default constructor called");
}



ZjetsSF::ZjetsSF(const TString& expression) : LepHadObservable(expression) {
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);
  
  INFOclass("Loading file...");
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("ApplyZjetsSF", false) ) return;

  TString signalProcess = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("SignalProcess", signalProcess) ){
    ERRORclass("AnaChannel not set !!!");
  }
  TFile* file=0;
  if ("AHZ" == signalProcess) {
    file= TFile::Open(signalProcess+"-lephad/auxData/ScaleFactors/Zjets_SF.root");
    if (!file) {
      ERRORclass("Can not find TopCR_SF.root");
    }
  }
  else if ("LQtaub" == signalProcess) {
    file= TFile::Open(signalProcess+"-lephad/auxData/ScaleFactors/Zjets_SF.root");    
    if (!file) {
      ERRORclass("Can not find Zjets_SF.root");
    }
  }
  if (!file) {
    ERRORclass("Can not find any ROOT file of Zjets SFs");
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



TObjArray* ZjetsSF::getBranchNames() const {
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();
  return bnames;
}



bool ZjetsSF::initializeSelf() {
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("ApplyZjetsSF", false) ) return true;
  if (! LepHadObservable::initializeSelf()) return false;
  fSysName = this->fSample->replaceInTextRecursive("$(variation)","~");

  return true;
}



bool ZjetsSF::finalizeSelf() {
  if (! LepHadObservable::finalizeSelf()) return false;
  return true;
}



auto ZjetsSF::getFakeFactorHist() const {
  // determine which SF hist we want: All
  TString histName = "ZCR";

  histName += "All";
  histName += "lephad";
  histName += "Btag";
  histName += "VisibleMassOneBin";

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



double ZjetsSF::getValue() const {
  // Check whether we want to apply the fake factor
  bool apply = false;
  if (! TQTaggable::getGlobalTaggable("aliases")->getTagBool("ApplyZjetsSF", apply)) {
    ERRORclass("Can not get ApplyZjetsSF tag");
  }
  if (!apply) return 1.0;

  if (isData()) return 1.0;
  if ( !isZHF() ) return 1.0;
  
  TString signalProcess = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("SignalProcess", signalProcess) ){
    ERRORclass("AnaChannel not set !!!");
  }

  int f_n_bjets        = this->n_bjets->EvalInstance();
  if (f_n_bjets==0) return 1.0;


  const TH1F* h_nominal;
  const TH1F* h_up;
  const TH1F* h_down;

  std::tie(h_nominal,h_up,h_down)  = getFakeFactorHist();

  int binID = 1;

  float retval = h_nominal->GetBinContent(binID);
  float retval_up = h_up->GetBinContent(binID);;
  float retval_down = h_down->GetBinContent(binID);
  float retval_error = fabs(retval_up - retval_down)/2.0;

  ///////////////////////////////////////////////////////////////
  // systematic uncertainty
  ///////////////////////////////////////////////////////////////
  if ( (fSysName.Contains("ZjetsReweight_Btag_1up") && f_n_bjets>0)  ) {
    retval += retval_error;
  }
  else if( (fSysName.Contains("ZjetsReweight_Btag_1down") && f_n_bjets>0) ) {
    retval -= retval_error;
  }
  return retval;
}
