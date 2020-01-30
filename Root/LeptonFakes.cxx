#include "BSMtautauCAF/LeptonFakes.h"
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

ClassImp(LeptonFakes)

//______________________________________________________________________________________________

LeptonFakes::LeptonFakes(){
  this->setExpression(this->GetName() );
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

LeptonFakes::~LeptonFakes(){
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* LeptonFakes::getBranchNames() const {
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();
  return bnames;
}

//______________________________________________________________________________________________
double LeptonFakes::getValue() const {
  
  int    f_n_bjets        = this->n_bjets->EvalInstance();
  int    f_lep_0          = this->lep_0->EvalInstance();
  float  f_lep_0_pt       = this->lep_0_pt->EvalInstance();
  float  f_lephad_met_lep0_cos_dphi= this->lephad_met_lep0_cos_dphi->EvalInstance();

  ///////////////////////////////////////////////////////////////
  // determine which FF to use
  ///////////////////////////////////////////////////////////////
  // channel: ehad or muhad
  TString channel = "";
  if (1==f_lep_0) channel = "muhad";
  else if (2==f_lep_0) channel = "ehad";
  
  // region: bveto or btag
  TString region = "";
  if (0==f_n_bjets) region = "Bveto";
  else if (1==f_n_bjets) region = "Btag";

  // peiriod: Combined or Separated
  TString period = "";
  TString period_tag = "";
  if(!this->fSample->getTag("~LFFPeriod",period_tag)) std::cout<<"ERROR: Can not get LFFPeriod tag" << std::endl;
  if ("Combined" == period_tag)
    period = "All";
  else if ("Separated" == period_tag) {
    if (is2015() || is2016()) period = "1516";
    if (is2017()) period = "17";
    if (is2018()) period = "18";
  }
  else
    std::cout << "ERROR: Unknown LFFPeriod tag" << std::endl;

  // parameterization: 1D LeptonPt or 2D LeptonPt x Dphi
  TString param = "";
  TString param_tag = "";
  if(!this->fSample->getTag("~LFFParam",param_tag)) std::cout<<"ERROR: Can not get LFFParam tag" << std::endl;

  if ( "LeptonPt" == param_tag ) {
    param = "LeptonPtFF";
  }
  else if ( "LeptonPtDphi" == param_tag) {
    // dphi 1,2,3,4 in bveto category
    if (0 == f_n_bjets) {
      if (f_lephad_met_lep0_cos_dphi<0.5) param = "LeptonPtDphi1";
      else if (f_lephad_met_lep0_cos_dphi>=0.5&&f_lephad_met_lep0_cos_dphi<1) param = "LeptonPtDphi2";
      else if (f_lephad_met_lep0_cos_dphi>=1&&f_lephad_met_lep0_cos_dphi<2) param = "LeptonPtDphi3";
      else if (f_lephad_met_lep0_cos_dphi>=2) param = "LeptonPtDphi4";
    }
    // dphi 1,2,3 in btag category
    else if (1 <= f_n_bjets) {
      if (f_lephad_met_lep0_cos_dphi<0.5) param = "LeptonPtDphi1";
      else if (f_lephad_met_lep0_cos_dphi>=0.5&&f_lephad_met_lep0_cos_dphi<1) param= "LeptonPtDphi2";
      else if (f_lephad_met_lep0_cos_dphi>=1) param= "LeptonPtDphi3";
    }
  }
  
  TString histName = "LFR"+ period + channel + region + param + "FF";
  
  TH1F * h_nominal = 0;
  TH1F * h_up = 0;
  TH1F * h_down = 0;
  
  h_nominal = m_FF_hist.at(histName);
  h_up = m_FF_hist.at(histName+"_up");
  h_down = m_FF_hist.at(histName+"_down");
  
  // FF is a function of lepton pT
  int binID = std::min(h_nominal->FindBin(f_lep_0_pt), h_nominal->GetNbinsX());

  float retval = h_nominal->GetBinContent(binID);
  float retval_up = h_up->GetBinContent(binID);
  float retval_down = h_down->GetBinContent(binID);
  float retval_error = fabs(retval_up - retval_down)/2.0;

  ///////////////////////////////////////////////////////////////
  // systematic uncertainty
  ///////////////////////////////////////////////////////////////
  if ( (fSysName.Contains("FakeFactor_LepElBveto_1up") && f_lep_0==2 && f_n_bjets==0) ||
       (fSysName.Contains("FakeFactor_LepElBtag_1up") && f_lep_0==2 && f_n_bjets>0) ||
       (fSysName.Contains("FakeFactor_LepMuBveto_1up") && f_lep_0==1 && f_n_bjets==0) ||
       (fSysName.Contains("FakeFactor_LepMuBtag_1up") && f_lep_0==1 && f_n_bjets>0)  ) {
    retval += retval_error;
  }
  else if(  (fSysName.Contains("FakeFactor_LepElBveto_1down") && f_lep_0==2 && f_n_bjets==0) ||
            (fSysName.Contains("FakeFactor_LepElBtag_1down") && f_lep_0==2 && f_n_bjets>0) ||
            (fSysName.Contains("FakeFactor_LepMuBveto_1down") && f_lep_0==1 && f_n_bjets==0) ||
            (fSysName.Contains("FakeFactor_LepMuBtag_1down") && f_lep_0==1 && f_n_bjets>0) ) {
    retval -= retval_error;
  }

  return retval;
}
//______________________________________________________________________________________________

LeptonFakes::LeptonFakes(const TString& expression) : LepHadObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  fSysName = expression;
  
  TFile* aFile= TFile::Open("FakeFactors/LFR_FF.root");
  if (!aFile) {
    std::cout << "ERROR: can not find LFR_FF.root " << std::endl;
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
      m_FF_hist[key->GetName()] = hist;
    }
  }
  aFile->Close();
}

//______________________________________________________________________________________________

const TString& LeptonFakes::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool LeptonFakes::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void LeptonFakes::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool LeptonFakes::initializeSelf(){
  if (! LepHadObservable::initializeSelf()) return false;
  return true;
}

//______________________________________________________________________________________________

bool LeptonFakes::finalizeSelf(){
  if (! LepHadObservable::finalizeSelf()) return false;
  return true;
}
