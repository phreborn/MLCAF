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
  fSysName = this->fSample->replaceInTextRecursive("$(sfVariation.lff)","~");

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
  TH1F* hist = nullptr;

  auto it = m_SF_hist.find(histName); 
  if ( it != m_SF_hist.end() ) {
    hist = it->second;
  }

  if (hist) {
    int binID = std::min(hist->FindFixBin(variable), hist->GetNbinsX());
    if (binID == 0) binID = 1;

    return hist->GetBinContent(binID);
  }
  else {
    std::cout << "ERROR! Unavailable FF: " << histName << std::endl;
    for (auto item : m_SF_hist) {
      std::cout << "Available FF: " << item.first << std::endl;
    }
  }

  return 1.0;
}
