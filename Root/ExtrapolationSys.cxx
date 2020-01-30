#include "BSMtautauCAF/ExtrapolationSys.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
#include "TFile.h"
#include "TMath.h"
#include <map>

ClassImp(ExtrapolationSys)

//______________________________________________________________________________________________

ExtrapolationSys::ExtrapolationSys(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

ExtrapolationSys::~ExtrapolationSys(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* ExtrapolationSys::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();

  return bnames;
}

//______________________________________________________________________________________________
double ExtrapolationSys::getValue() const {
  
  double f_lep_0              = this->lep_0->EvalInstance();
  double f_tau_0_pt       = this->tau_0_pt->EvalInstance();
  int    f_tau_0_n_charged_tracks = this->tau_0_n_charged_tracks->EvalInstance();
  int    f_n_bjets        = this->n_bjets->EvalInstance();
  double f_lephad_met_lep1_cos_dphi = this->lephad_met_lep1_cos_dphi->EvalInstance();

  ////////////////////////////
  //  Extrapolation SF
  ////////////////////////////
  if (f_tau_0_pt >= 300)  f_tau_0_pt = 299;

  // determine which SF to use
  // period + channel + category + variable + SF
  // period (VR1516, VR17, VR18, VRAll)
  // channel (ehad, muhad, lephad)
  // category (Bveto, Btag)x(1p,3p)
  // variable (LeptonPt, LeptonPtDphi?)
  TString SF = "";   // SF name
  TH1F * h_nominal = 0;

  // peiriod
  SF = "VRAll";

  // channel
  if ( 1 == f_lep_0) SF += "muhad";
  else if (2 == f_lep_0) SF += "ehad";
  else std::cout << "ERROR: unknown lepton flavor" << std::endl;

  // category (only consider bveto category)
  if ( 0 == f_n_bjets) SF += "Bveto";
  else if (1 <= f_n_bjets) SF += "Btag";
  else std::cout << "ERROR: strange #bjets" << std::endl;

  if ( 1 == f_tau_0_n_charged_tracks) SF += "1p";
  else if ( 3 == f_tau_0_n_charged_tracks) SF += "3p";
  else return 1.0;

  // parameterization
  // dphi 1,2,3 in bveto/btag category
  if (0 == f_n_bjets) {
    if (f_lephad_met_lep1_cos_dphi>=0.0&&f_lephad_met_lep1_cos_dphi<1) SF += "TauPtDphi1SF";
    else if (f_lephad_met_lep1_cos_dphi>=1&&f_lephad_met_lep1_cos_dphi<2) SF += "TauPtDphi2SF";
    else if (f_lephad_met_lep1_cos_dphi>=2) SF += "TauPtDphi3SF";
  }
  else {
    SF += "TauPtSF";
  }

  h_nominal = m_SF_hist.at(SF);
  
  // SF is a function of tau pT
  float retval = h_nominal->GetBinContent(h_nominal->FindBin(f_tau_0_pt));
  ////////////////
  // SYSTEMATICS
  ////////////////
  if    ( 
          (fSysName.Contains("FakeFactor_ExtraSysBtag_1up")    && f_n_bjets>0) ||
          (fSysName.Contains("FakeFactor_ExtraSysBtag1p_1up")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_ExtraSysBtag3p_1up")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_ExtraSysElHadBtag1p_1up")  && f_lep_0 == 2 && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_ExtraSysElHadBtag3p_1up")  && f_lep_0 == 2 && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_ExtraSysMuHadBtag1p_1up")  && f_lep_0 == 1 && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_ExtraSysMuHadBtag3p_1up")  && f_lep_0 == 1 && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_ExtraSysBveto_1up")   && f_n_bjets==0 ) ||
          (fSysName.Contains("FakeFactor_ExtraSysBveto1p_1up") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_ExtraSysBveto3p_1up") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3) || 
          (fSysName.Contains("FakeFactor_ExtraSysElHadBveto1p_1up") && f_lep_0 == 2 && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_ExtraSysElHadBveto3p_1up") && f_lep_0 == 2 && f_n_bjets==0 && f_tau_0_n_charged_tracks==3) || 
          (fSysName.Contains("FakeFactor_ExtraSysMuHadBveto1p_1up") && f_lep_0 == 1 && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_ExtraSysMuHadBveto3p_1up") && f_lep_0 == 1 && f_n_bjets==0 && f_tau_0_n_charged_tracks==3)    
        ) {
    retval = 1.0+fabs(retval-1.0);
  }
  else if(
          (fSysName.Contains("FakeFactor_ExtraSysBtag_1down")    && f_n_bjets>0) ||
          (fSysName.Contains("FakeFactor_ExtraSysBtag1p_1down")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_ExtraSysBtag3p_1down")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_ExtraSysElHadBtag1p_1down")  && f_lep_0 == 2 && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_ExtraSysElHadBtag3p_1down")  && f_lep_0 == 2 && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_ExtraSysMuHadBtag1p_1down")  && f_lep_0 == 1 && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_ExtraSysMuHadBtag3p_1down")  && f_lep_0 == 1 && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_ExtraSysBveto_1down")   && f_n_bjets==0 ) ||
          (fSysName.Contains("FakeFactor_ExtraSysBveto1p_1down") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_ExtraSysBveto3p_1down") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3) ||   
          (fSysName.Contains("FakeFactor_ExtraSysElHadBveto1p_1down") && f_lep_0 == 2 && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_ExtraSysElHadBveto3p_1down") && f_lep_0 == 2 && f_n_bjets==0 && f_tau_0_n_charged_tracks==3) || 
          (fSysName.Contains("FakeFactor_ExtraSysMuHadBveto1p_1down") && f_lep_0 == 1 && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_ExtraSysMuHadBveto3p_1down") && f_lep_0 == 1 && f_n_bjets==0 && f_tau_0_n_charged_tracks==3)    
          ) {
    retval = 1.0-fabs(retval-1.0);
  }
  else retval = 1.0;
  DEBUGclass("returning");

  return retval;
}
//______________________________________________________________________________________________

ExtrapolationSys::ExtrapolationSys(const TString& expression) : LepHadObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  fSysName = expression;

  // when files are closed histograms also dissapear, so detatch them and keep in this directory:
  //m_histoDir = new TDirectory("ffhistoDir","ffhistoDir");
  m_histoDir = 0;
  // temporary pointer to ff files:
  TFile* tempFile=0;

  std::cout << "INFO: ExtrapolationSys.cxx getting histograms from files. " << std::endl;

  ///////////////////////////////
  // extra sys
  ///////////////////////////////
  std::vector<TString> periods = {"VRAll"};
  std::vector<TString> channels = {"ehad", "muhad"};

  // list of available SFs
  std::vector<TString> SF_list;
  SF_list.clear();
  SF_list.reserve(256);
  for (auto period : periods) {
    for (auto channel : channels) {
      // 2D TauPt Dphi(lep, MET)
      SF_list.emplace_back(period + channel + "Bveto1pTauPtDphi1SF");
      SF_list.emplace_back(period + channel + "Bveto1pTauPtDphi2SF");
      SF_list.emplace_back(period + channel + "Bveto1pTauPtDphi3SF");
      SF_list.emplace_back(period + channel + "Bveto3pTauPtDphi1SF");
      SF_list.emplace_back(period + channel + "Bveto3pTauPtDphi2SF");
      SF_list.emplace_back(period + channel + "Bveto3pTauPtDphi3SF");
      SF_list.emplace_back(period + channel + "Btag1pTauPtSF");
      SF_list.emplace_back(period + channel + "Btag3pTauPtSF");
    }
  }
 
  TH1F* tempHist = 0;
  // obtain SF histograms
  for (auto fn : SF_list) {
    tempFile = TFile::Open("ScaleFactors/"+fn+".root");
    if (!tempFile) {
      std::cout << "WARNING: can not find SF " << fn << std::endl;
      continue;
    }
    else {
      tempHist = (TH1F*)tempFile->Get(fn); tempHist->SetDirectory(m_histoDir);
      m_SF_hist[fn] = tempHist;
      tempHist = (TH1F*)tempFile->Get(fn+"_up"); tempHist->SetDirectory(m_histoDir);
      m_SF_hist[fn+"_up"] = tempHist;
      tempHist = (TH1F*)tempFile->Get(fn+"_down"); tempHist->SetDirectory(m_histoDir);
      m_SF_hist[fn+"_down"] = tempHist;
      std::cout << "INFO: find SF " << fn << std::endl;
    }
    tempFile->Close(); delete tempFile; tempFile = 0;
  }
}
//______________________________________________________________________________________________

const TString& ExtrapolationSys::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool ExtrapolationSys::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void ExtrapolationSys::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool ExtrapolationSys::initializeSelf(){
  if (! LepHadObservable::initializeSelf()) return false;
  return true;
}

//______________________________________________________________________________________________

bool ExtrapolationSys::finalizeSelf(){
  if (! LepHadObservable::finalizeSelf())  return false;
  return true;
}
