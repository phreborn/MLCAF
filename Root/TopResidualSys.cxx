#include "BSMtautauCAF/TopResidualSys.h"
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

ClassImp(TopResidualSys)

//______________________________________________________________________________________________

TopResidualSys::TopResidualSys(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

TopResidualSys::~TopResidualSys(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* TopResidualSys::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();

  return bnames;
}

//______________________________________________________________________________________________
double TopResidualSys::getValue() const {
  
  int f_n_bjets        = this->n_bjets->EvalInstance();
  float f_lep_0_pt = this->lep_0_pt->EvalInstance();
  float f_tau_0_pt = this->tau_0_pt->EvalInstance();
  float f_jets_scalar_sum_pt = this->jets_scalar_sum_pt->EvalInstance();
  float f_bjet_0_pt = this->bjet_0_pt->EvalInstance();
  float f_met = this->met_reco_et->EvalInstance();

  float st = f_lep_0_pt + f_tau_0_pt + f_bjet_0_pt;

  ///////////////////////////////////////////////////////////////
  // determine which SF to use
  ///////////////////////////////////////////////////////////////

  TString histName = "unc_ttbarCor_vs_topCor_"; 

  // category: low bjet pt or high bjet pt
  if ( f_bjet_0_pt < 200) {
    histName += "lowbjetpt_";
  } 
  else if (f_bjet_0_pt >= 200) {
    histName += "highbjetpt_";
  }

  histName += "lephad";
  
  TH1F * h_nominal = 0;
  
  auto it = m_SF_hist.find(histName); 
  if ( it != m_SF_hist.end() ) h_nominal = it->second;
  else {
    std::cout << "error! unavailable unc.: " << histName << std::endl;
    for (auto item : m_SF_hist)
      std::cout << "available unc.: " << item.first << std::endl;
  }
 
  // SF is a function of variable
  int binID = std::min(h_nominal->FindBin(st), h_nominal->GetNbinsX());

  float retval = h_nominal->GetBinContent(binID);

  ///////////////////////////////////////////////////////////////
  // systematic uncertainty
  ///////////////////////////////////////////////////////////////
  if    ( 
         (fSysName.Contains("TopResi_Btag_1up")  && f_n_bjets > 0) ||
         (fSysName.Contains("TopResi_ElBtag_1up")  && f_n_bjets > 0 && isElectron()) ||
         (fSysName.Contains("TopResi_MuBtag_1up")  && f_n_bjets > 0 && isMuon())
        ) {
    retval = 1.0+fabs(retval-1.0);
  }
  else if(
         (fSysName.Contains("TopResi_Btag_1down")  && f_n_bjets > 0) ||
         (fSysName.Contains("TopResi_ElBtag_1down")  && f_n_bjets > 0  && isElectron()) ||
         (fSysName.Contains("TopResi_MuBtag_1down")  && f_n_bjets > 0 && isMuon())
          ) {
    retval = 1.0-fabs(retval-1.0);
  }
  else retval = 1.0;

  return retval;
}
//______________________________________________________________________________________________

TopResidualSys::TopResidualSys(const TString& expression) : LepHadObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  //fSysName = expression;

  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("ApplyTopResidualSF", false) ) return;
  INFOclass("Loading file...");

  TString signalProcess = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("SignalProcess", signalProcess) ){
    ERRORclass("AnaChannel not set !!!");
  }
  TFile* aFile= TFile::Open(signalProcess+"-lephad/auxData/ScaleFactors/Unc_TopCorrection_VS_TTBarCorrection_LepHad.root");
  if (!aFile) {
    ERRORclass("Can not find Unc_TopCorrection_VS_TTBarCorrection_LepHad.root");
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

const TString& TopResidualSys::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool TopResidualSys::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void TopResidualSys::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool TopResidualSys::initializeSelf(){
  if (! LepHadObservable::initializeSelf()) return false;

  fSysName = this->fSample->replaceInTextRecursive("$(variation)","~");

  return true;
}

//______________________________________________________________________________________________

bool TopResidualSys::finalizeSelf(){
  if (! LepHadObservable::finalizeSelf())  return false;
  return true;
}
