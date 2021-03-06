#include "BSMtautauCAF/MCFakesSF.h"
#include <limits>

#include "QFramework/TQLibrary.h"
#include "TFile.h"
#include "TMath.h"
#include <map>

ClassImp(MCFakesSF)



MCFakesSF::MCFakesSF() {
  this->setExpression(this->GetName() );
  DEBUGclass("default constructor called");
}



MCFakesSF::MCFakesSF(const TString& expression) : LepHadObservable(expression) {
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);
  
  INFOclass("Loading file...");
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("ApplyMCFakesSF", false) ) return;
  
  TString signalProcess = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("SignalProcess", signalProcess) ){
    ERRORclass("AnaChannel not set !!!");
  }
  TFile* file= TFile::Open(signalProcess+"-lephad/auxData/ScaleFactors/OtherJetsSSR_SF.root");
  if (!file) {
    ERRORclass("Can not find OtherJetsSSR_SF.root");
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



TObjArray* MCFakesSF::getBranchNames() const {
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();
  return bnames;
}



bool MCFakesSF::initializeSelf() {
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("ApplyMCFakesSF", false) ) return true;
  if (! LepHadObservable::initializeSelf()) return false;
  fSysName = this->fSample->replaceInTextRecursive("$(variation)","~");

  return true;
}



bool MCFakesSF::finalizeSelf() {
  if (! LepHadObservable::finalizeSelf()) return false;
  return true;
}



auto MCFakesSF::getFakeFactorHist() const {
  // determine which FF hist we want: All
  float f_bjet_0_pt = this->bjet_0_pt->EvalInstance();

  TString histName = "OtherJetsSSR";

  histName += "All";

  // -- channel: muhad
  histName += "muhad";

  // -- category: Bveto/Btag
  histName += "Btag";

  // -- 1p/3p
  if (this->tau_0_n_charged_tracks->EvalInstance() == 1) {
    histName += "1p";
  }
  else {
    histName += "3p";
  }
  
  // -- parameterization
  TString param_tag = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("MCFakesSFParam", param_tag) ) {
    ERRORclass("Can not get MCFakesSFParam tag");
  }

  if ( "TauPt" == param_tag ) {
    histName += "TauPtSF";
  }
  else if ( "TauPtBjetPt" == param_tag) {
    if ( f_bjet_0_pt < 75.0 ) {
      histName += "TauPtBjetPt1SF";
    }
    else if ( f_bjet_0_pt >= 75.0 && f_bjet_0_pt < 125.0 ) {
      histName += "TauPtBjetPt2SF";
    }
    else if ( f_bjet_0_pt >= 125.0 ) {
      histName += "TauPtBjetPt3SF";
    }
  }

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



double MCFakesSF::getValue() const {
  // Check whether we want to apply the fake factor
  bool apply = false;
  if (! TQTaggable::getGlobalTaggable("aliases")->getTagBool("ApplyMCFakesSF", apply)) {
    ERRORclass("Can not get ApplyMCFakesSF tag");
  }
  if (!apply) return 1.0;

  const TH1F* h_nominal;
  const TH1F* h_up;
  const TH1F* h_down;

  int f_lep_0 = this->lep_0->EvalInstance();
  int f_tau_0_n_charged_tracks = this->tau_0_n_charged_tracks->EvalInstance();
  int f_n_bjets        = this->n_bjets->EvalInstance();
  float f_tau_0_pt = this->tau_0_pt->EvalInstance();
  float f_lep_0_pt = this->lep_0_pt->EvalInstance();
  float f_bjet_0_pt = this->bjet_0_pt->EvalInstance();
  
  float variable = 0.0;
  TString param_tag = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("MCFakesSFParam", param_tag) ) {
    ERRORclass("Can not get MCFakesSFParam tag");
  }

  if ( "TauPt" == param_tag ) {
    variable = f_tau_0_pt;
  }
  else if ( "TauPtBjetPt" == param_tag) {
    variable = f_tau_0_pt;
  }
  else {
    variable = f_tau_0_pt;
  } 

  if (0 == f_n_bjets) { return 1.0;}
  std::tie(h_nominal,h_up,h_down)  = getFakeFactorHist();  

  int binID = std::min(h_nominal->FindFixBin(variable), h_nominal->GetNbinsX());
  if (binID == 0) binID = 1;

  float retval = h_nominal->GetBinContent(binID);
  float retval_up = h_up->GetBinContent(binID);
  float retval_down = h_down->GetBinContent(binID);
  float retval_error = fabs(retval_up - retval_down)/2.0;

  // relative difference between OS and SS SFs
  // SFs of OS and SS SFs (SF_OS/SF_SS)
  // 1p: 0.96 +- 0.23
  // 3p: 1.11 +- 0.51
  //float retval_scale_1p = 0.04; // 1 - 0.96
  //float retval_scale_3p = 0.11; // 1 - 1.11

  //if (f_tau_0_n_charged_tracks==1) {
  //  retval_error = sqrt(retval_error*retval_error + retval_scale_1p*retval_scale_1p);
  //}
  //else if (f_tau_0_n_charged_tracks==3) {
  //  retval_error = sqrt(retval_error*retval_error + retval_scale_3p*retval_scale_3p);
  //}

  if    (
         (fSysName.Contains("MCFakes_Btag1p_1up")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
         (fSysName.Contains("MCFakes_Btag3p_1up")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==3)
        ) {
    retval += retval_error;
  }
  else if(
           (fSysName.Contains("MCFakes_Btag1p_1down")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
           (fSysName.Contains("MCFakes_Btag3p_1down")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==3)
          ) {
    retval -= retval_error;
  }

  return retval;
}
