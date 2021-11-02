#include "BSMtautauCAF/MultiJetsTFF.h"
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

ClassImp(MultiJetsTFF)

//______________________________________________________________________________________________

MultiJetsTFF::MultiJetsTFF(){
  this->setExpression(this->GetName() );
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

MultiJetsTFF::~MultiJetsTFF(){
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* MultiJetsTFF::getBranchNames() const {
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();
  return bnames;
}

//______________________________________________________________________________________________
double MultiJetsTFF::getValue() const {
  int    f_n_bjets        = this->n_bjets->EvalInstance();
  int    f_lep_0          = this->lep_0->EvalInstance();
  int f_tau_0_n_charged_tracks = this->tau_0_n_charged_tracks->EvalInstance();
  float  f_tau_0_pt       = this->tau_0_pt->EvalInstance();

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
  else if (1<=f_n_bjets) region = "Btag";
  
  if ( 1 == f_tau_0_n_charged_tracks) region += "1p";
  else if ( 3 == f_tau_0_n_charged_tracks) region += "3p";
  else return 1.0;

  // peiriod: Combined or Separated
  TString period = "";
  TString period_tag = "";
  //if(!this->fSample->getTag("~QCDTFFPeriod",period_tag)) std::cout<<"ERROR: Can not get QCDTFFPeriod tag" << std::endl;
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("QCDTFFPeriod", period_tag) ) ERRORclass("Can not get QCDTFFPeriod tag");
  if ("Combined" == period_tag)
    period = "All";
  else if ("Separated" == period_tag) {
    if (is2015() || is2016()) period = "1516";
    if (is2017()) period = "17";
    if (is2018()) period = "18";
  }
  else
    ERRORclass("Unknown QCDTFFPeriod tag");

  // parameterization: 1D LeptonPt or 2D LeptonPt x Dphi
  TString param = "";
  TString param_tag = "";
  //if(!this->fSample->getTag("~QCDTFFParam",param_tag)) std::cout<<"ERROR: Can not get QCDTFFParam tag" << std::endl;
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("QCDTFFParam", param_tag) ) ERRORclass("Can not get QCDTFFParam tag");

  if ( "TauPt" == param_tag ) {
    param = "TauPt";
  }
  TString histName = "QCDTFR"+ period + channel + region + param + "FF";
  
  TH1F * h_nominal = 0;
  TH1F * h_up = 0;
  TH1F * h_down = 0;
 
  auto it = m_FF_hist.find(histName); 
  if ( it != m_FF_hist.end() ) h_nominal = it->second;
  else {
    std::cout << "ERROR! Unavailable FF: " << histName << std::endl;
    for (auto item : m_FF_hist)
      std::cout << "Available FF: " << item.first << std::endl;
  }

  it = m_FF_hist.find(histName+"_up"); 
  if ( it != m_FF_hist.end() ) h_up = it->second;
  else std::cout << "ERROR! Unavailable FF: " << histName+"_up" << std::endl;
  
  it = m_FF_hist.find(histName+"_down"); 
  if ( it != m_FF_hist.end() ) h_down = it->second;
  else std::cout << "ERROR! Unavailable FF: " << histName+"_down" << std::endl;
  
  // FF is a function of tau pT
  int binID = std::min(h_nominal->FindBin(f_tau_0_pt), h_nominal->GetNbinsX());

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

MultiJetsTFF::MultiJetsTFF(const TString& expression) : LepHadObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  //fSysName = expression;

  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("UseQCDTFF", false) ) return;
  INFOclass("Loading file...");

  TFile* aFile= TFile::Open("bsmtautau_lephad/auxData/FakeFactors/QCDTFR_FF.root");
  if (!aFile) {
    ERRORclass("Can not find QCDTFR_FF.root");
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

const TString& MultiJetsTFF::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool MultiJetsTFF::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void MultiJetsTFF::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool MultiJetsTFF::initializeSelf(){
  if (! LepHadObservable::initializeSelf()) return false;

  fSysName = this->fSample->replaceInTextRecursive("$(variation)","~");

  return true;
}

//______________________________________________________________________________________________

bool MultiJetsTFF::finalizeSelf(){
  if (! LepHadObservable::finalizeSelf()) return false;
  return true;
}
