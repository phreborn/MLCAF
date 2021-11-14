#include "BSMtautauCAF/MCFakesSYS.h"
#include <limits>

#include "QFramework/TQLibrary.h"
#include "TFile.h"
#include "TMath.h"
#include <map>

ClassImp(MCFakesSYS)



MCFakesSYS::MCFakesSYS() {
  this->setExpression(this->GetName() );
  DEBUGclass("default constructor called");
}



MCFakesSYS::MCFakesSYS(const TString& expression) : LepHadObservable(expression) {
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);
  
  INFOclass("Loading file...");
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("ApplyMCFakesSYS", false) ) return;
  
  TString signalProcess = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("SignalProcess", signalProcess) ){
    ERRORclass("AnaChannel not set !!!");
  }
  TFile* file= TFile::Open(signalProcess+"-lephad/auxData/ScaleFactors/MCFakesSYS_SF.root");
  if (!file) {
    ERRORclass("Can not find MCFakesSYS_SF.root");
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



TObjArray* MCFakesSYS::getBranchNames() const {
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();
  return bnames;
}



bool MCFakesSYS::initializeSelf() {
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("ApplyMCFakesSYS", false) ) return true;
  if (! LepHadObservable::initializeSelf()) return false;
  fSysName = this->fSample->replaceInTextRecursive("$(variation)","~");

  return true;
}



bool MCFakesSYS::finalizeSelf() {
  if (! LepHadObservable::finalizeSelf()) return false;
  return true;
}



const TH1F* MCFakesSYS::getFakeFactorHist() const {
  // determine which FF hist we want: All
  TString histName = "SSR";

  // -- period: Combined or Separated
  //TString period = "";
  //if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("MCFakesSYSPeriod", period) ) {
  //  ERRORclass("Can not get MCFakesSYSPeriod tag");
  //}

  //if ("Combined" == period) {
  //  histName += "All";
  //}
  //else if ("Separated" == period) {
  //  if (is2015() || is2016()) histName += "1516";
  //  if (is2017()) histName += "17";
  //  if (is2018()) histName += "18";
  //}
  //else {
  //  ERRORclass("Unknown MCFakesSYSPeriod tag");
  //  return nullptr;
  //}

  histName += "All";

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

  // -- 1p/3p
  if (this->tau_0_n_charged_tracks->EvalInstance() == 1) {
    histName += "1p";
  }
  else {
    histName += "3p";
  }
  
  // -- parameterization
  histName += "StSF";

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



double MCFakesSYS::getValue() const {
  // Check whether we want to apply the fake factor
  bool apply = false;
  if (! TQTaggable::getGlobalTaggable("aliases")->getTagBool("ApplyMCFakesSYS", apply)) {
    ERRORclass("Can not get ApplyMCFakesSYS tag");
  }
  if (!apply) return 1.0;
  

  const TH1F* hist = getFakeFactorHist();

  int f_lep_0 = this->lep_0->EvalInstance();
  int f_tau_0_n_charged_tracks = this->tau_0_n_charged_tracks->EvalInstance();
  int f_n_bjets        = this->n_bjets->EvalInstance();
  float f_tau_0_pt = this->tau_0_pt->EvalInstance();
  float f_lep_0_pt = this->lep_0_pt->EvalInstance();
  float f_bjet_0_pt = this->bjet_0_pt->EvalInstance();
  
  float f_SumOfPt = f_tau_0_pt + f_lep_0_pt + f_bjet_0_pt;

  if (0 == f_n_bjets) { return 1.0;}

  int binID = std::min(hist->FindFixBin(f_SumOfPt), hist->GetNbinsX());
  if (binID == 0) binID = 1;

  float retval = 1.0;
  float error = hist->GetBinContent(binID);

  if    (
         (fSysName.Contains("MCFakes_ElHadBtag1p_1up")  && f_lep_0==2 && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
         (fSysName.Contains("MCFakes_ElHadBtag3p_1up")  && f_lep_0==2 && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
         (fSysName.Contains("MCFakes_MuHadBtag1p_1up")  && f_lep_0==1 && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
         (fSysName.Contains("MCFakes_MuHadBtag3p_1up")  && f_lep_0==1 && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
         (fSysName.Contains("MCFakes_Btag1p_1up")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
         (fSysName.Contains("MCFakes_Btag3p_1up")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==3)
        ) {
    retval = 1.0+fabs(error-1.0);
  }
  else if(
           (fSysName.Contains("MCFakes_ElHadBtag1p_1down")  && f_lep_0==2 && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
           (fSysName.Contains("MCFakes_ElHadBtag3p_1down")  && f_lep_0==2 && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
           (fSysName.Contains("MCFakes_MuHadBtag1p_1down")  && f_lep_0==1 && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
           (fSysName.Contains("MCFakes_MuHadBtag3p_1down")  && f_lep_0==1 && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
           (fSysName.Contains("MCFakes_Btag1p_1down")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
           (fSysName.Contains("MCFakes_Btag3p_1down")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==3)
          ) {
    retval = 1.0-fabs(error-1.0);
  }
  else retval = 1.0;

  return retval;
}
