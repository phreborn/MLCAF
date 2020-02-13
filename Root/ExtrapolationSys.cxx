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

  ///////////////////////////////////////////////////////////////
  // determine which SF to use
  ///////////////////////////////////////////////////////////////
  // channel: ehad or muhad
  TString channel = "";
  if (1==f_lep_0) channel = "muhad";
  else if (2==f_lep_0) channel = "ehad";

  // region: bveto or btag, 1p or 3p
  TString region = "";
  if ( 0 == f_n_bjets) region = "Bveto";
  else if (1 <= f_n_bjets) region = "Btag";
  else std::cout << "ERROR: strange #bjets" << std::endl;

  if ( 1 == f_tau_0_n_charged_tracks) region += "1p";
  else if ( 3 == f_tau_0_n_charged_tracks) region += "3p";
  else return 1.0;

  // peiriod: Combined or Separated
  TString period = "All";
  
  // parameterization
  // dphi 1,2,3 in bveto/btag category
  TString param = "";
  if (0 == f_n_bjets) {
    if (f_lephad_met_lep1_cos_dphi>=0.0&&f_lephad_met_lep1_cos_dphi<1) param = "TauPtDphi1";
    else if (f_lephad_met_lep1_cos_dphi>=1&&f_lephad_met_lep1_cos_dphi<2) param = "TauPtDphi2";
    else if (f_lephad_met_lep1_cos_dphi>=2) param = "TauPtDphi3";
  }
  else {
    param = "TauPt";
  }

  TString histName = "VR"+ period + channel + region + param + "SF";
  
  TH1F * h_nominal = 0;
  
  auto it = m_SF_hist.find(histName); 
  if ( it != m_SF_hist.end() ) h_nominal = it->second;
  else {
    std::cout << "error! unavailable FF: " << histName << std::endl;
    for (auto item : m_SF_hist)
      std::cout << "available FF: " << item.first << std::endl;
  }
 
  // SF is a function of variable
  int binID = std::min(h_nominal->FindBin(f_tau_0_pt), h_nominal->GetNbinsX());

  float retval = h_nominal->GetBinContent(binID);

  ///////////////////////////////////////////////////////////////
  // systematic uncertainty
  ///////////////////////////////////////////////////////////////
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

  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("UseExtrapoSF", false) ) return;
  INFOclass("Loading file...");

  TFile* aFile= TFile::Open("ScaleFactors/VR_SF.root");
  if (!aFile) {
    ERRORclass("Can not find VR_SF.root");
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
