#include "BSMtautauCAF/TopExtrapolationSys.h"
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

ClassImp(TopExtrapolationSys)

//______________________________________________________________________________________________

TopExtrapolationSys::TopExtrapolationSys(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

TopExtrapolationSys::~TopExtrapolationSys(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* TopExtrapolationSys::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();

  return bnames;
}

//______________________________________________________________________________________________
double TopExtrapolationSys::getValue() const {
  
  double f_tau_0_pt       = this->tau_0_pt->EvalInstance();
  int    f_tau_0_n_charged_tracks = this->tau_0_n_charged_tracks->EvalInstance();
  int    f_n_bjets        = this->n_bjets->EvalInstance();
  double f_lephad_met_lep1_cos_dphi = this->lephad_met_lep1_cos_dphi->EvalInstance();
  double f_lep_0_pt = this->lep_0_pt->EvalInstance();
  double f_bjet_0_pt = this->bjet_0_pt->EvalInstance();

  double f_SumOfPt = f_lep_0_pt + f_tau_0_pt + f_bjet_0_pt;

  ///////////////////////////////////////////////////////////////
  // determine which SF to use
  ///////////////////////////////////////////////////////////////
  // channel: ehad or muhad
  TString channel = "lephad";

  // region: bveto or btag, 1p or 3p
  TString region = "";
  if ( 0 == f_n_bjets) return 1.0;
  else if (1 <= f_n_bjets) region = "Btag";
  else std::cout << "ERROR: strange #bjets" << std::endl;


  TString prong = "";
  if ( 1 == f_tau_0_n_charged_tracks || 3 == f_tau_0_n_charged_tracks) prong = "";
  else return 1.0;

  // peiriod: Combined or Separated
  TString period = "All";
  
  // parameterization
  // dphi 1,2,3 in bveto/btag category
  TString param = "St";

  TString histName = "TopExtrap"+ period + channel + region + param + prong + "SF";
  
  TH1F * h_nominal = 0;
  
  auto it = m_SF_hist.find(histName); 
  if ( it != m_SF_hist.end() ) h_nominal = it->second;
  else {
    std::cout << "error! unavailable FF: " << histName << std::endl;
    for (auto item : m_SF_hist)
      std::cout << "available FF: " << item.first << std::endl;
  }
 
  // SF is a function of variable
  int binID = std::min(h_nominal->FindBin(f_SumOfPt), h_nominal->GetNbinsX());

  float retval = h_nominal->GetBinContent(binID);

  ///////////////////////////////////////////////////////////////
  // systematic uncertainty
  ///////////////////////////////////////////////////////////////
  if    ( 
         (fSysName.Contains("FakeFactor_TopExtrap_Btag_1up")  && f_n_bjets > 0) ||
         (fSysName.Contains("FakeFactor_TopExtrap_Eltag_1up")  && f_n_bjets > 0 && isElectron()) ||
         (fSysName.Contains("FakeFactor_TopExtrap_MuBtag_1up")  && f_n_bjets > 0 && isMuon())
        ) {
    retval = 1.0+fabs(retval-1.0);
  }
  else if(
         (fSysName.Contains("FakeFactor_TopExtrap_Btag_1down")  && f_n_bjets > 0) ||
         (fSysName.Contains("FakeFactor_TopExtrap_Eltag_1down")  && f_n_bjets > 0  && isElectron()) ||
         (fSysName.Contains("FakeFactor_TopExtrap_MuBtag_1down")  && f_n_bjets > 0 && isMuon())
          ) {
    retval = 1.0-fabs(retval-1.0);
  }
  else retval = 1.0;

  return retval;
}
//______________________________________________________________________________________________

TopExtrapolationSys::TopExtrapolationSys(const TString& expression) : LepHadObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  //fSysName = expression;

  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("ApplyTopExtrapolationSF", false) ) return;
  INFOclass("Loading file...");

  TString signalProcess = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("SignalProcess", signalProcess) ){
    ERRORclass("AnaChannel not set !!!");
  }
  TFile* aFile= TFile::Open(signalProcess+"-lephad/auxData/ScaleFactors/TopExtrap_SF.root");
  if (!aFile) {
    ERRORclass("Can not find TopExtrap_SF.root");
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

const TString& TopExtrapolationSys::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool TopExtrapolationSys::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void TopExtrapolationSys::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool TopExtrapolationSys::initializeSelf(){
  if (! LepHadObservable::initializeSelf()) return false;

  fSysName = this->fSample->replaceInTextRecursive("$(variation)","~");

  return true;
}

//______________________________________________________________________________________________

bool TopExtrapolationSys::finalizeSelf(){
  if (! LepHadObservable::finalizeSelf())  return false;
  return true;
}
