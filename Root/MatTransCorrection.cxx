#include "BSMtautauCAF/MatTransCorrection.h"
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

using namespace std;
ClassImp(MatTransCorrection)

//______________________________________________________________________________________________

MatTransCorrection::MatTransCorrection(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

MatTransCorrection::~MatTransCorrection(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* MatTransCorrection::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();

  return bnames;
}

//______________________________________________________________________________________________
double MatTransCorrection::getValue() const {

  double f_tau_0_pt       = tau_0_pt->EvalInstance();
  double f_tau_0_eta      = tau_0_eta->EvalInstance();
  int    f_tau_0_n_charged_tracks = tau_0_n_charged_tracks->EvalInstance();

  /// only apply material transport correction with tauPt > 100 GeV
  if (100>=f_tau_0_pt) return 1.0;


  ///////////////////////////////////////////////////////////////////
  // determine which SF to use
  ///////////////////////////////////////////////////////////////////
  TString SF = "taupt_";   // SF name
  // barrel/endcap
  if (1.37>fabs(f_tau_0_eta)) SF += "barrel";
  else if (1.52<fabs(f_tau_0_eta)) SF += "endcap";
  else return 1.0;

  // 1prong/3prong
  if (1 == f_tau_0_n_charged_tracks ) SF += "1p";
  else if (3 == f_tau_0_n_charged_tracks) SF += "3p";
  else return 1.0;
  
  TF1 * fun_nominal = 0;
  fun_nominal = m_SF_fun.at(SF);
 
  // hotfix for overflow 
  if (6000<=f_tau_0_pt) f_tau_0_pt = 5999;
  float retval = fun_nominal->Eval(f_tau_0_pt);
  
  ///////////////////////////////////////////////////////////////////
  // SYSTEMATICS
  ///////////////////////////////////////////////////////////////////
  /// effect is negligible, by default not used in lephad 
# if 0 
  TGraphAsymmErrors* graph_sys = 0;
  graph_sys = m_SF_graph.at(SF);

  int N = graph_sys->GetN();

  double * x = graph_sys->GetX();
  double * x_error_low = graph_sys->GetEXlow();
  double * x_error_high = graph_sys->GetEXhigh();

  double * y = graph_sys->GetY();
  double * y_error_low = graph_sys->GetEYlow();
  double * y_error_high = graph_sys->GetEYhigh();

  /// find the binID
  int binID = -999;
  for (int i=0; i<N; ++i) {
    if (tau_0_pt >= x_error_low[i] && tau_0_pt <= x_error_high[i]) {
      binID = i;
      break;
    }
  }
  
  double error = 0.5 * fabs(y_error_high[i]-y_error_low[i]);

  if((fSysName.Contains("MatTransCorr_barrel_1p") && 1.37>fabs(f_tau_0_eta) && 1 == f_tau_0_n_charged_tracks) ||
     (fSysName.Contains("MatTransCorr_barrel_3p") && 1.37>fabs(f_tau_0_eta) && 3 == f_tau_0_n_charged_tracks) ||
     (fSysName.Contains("MatTransCorr_endcap_1p") && 1.52<fabs(f_tau_0_eta) && 1 == f_tau_0_n_charged_tracks) ||
     (fSysName.Contains("MatTransCorr_endcap_3p") && 1.52<fabs(f_tau_0_eta) && 3 == f_tau_0_n_charged_tracks) ) {
    retval += error;
  }  
#endif
  return retval;
}
//______________________________________________________________________________________________

MatTransCorrection::MatTransCorrection(const TString& expression) : LepHadObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  //fSysName = expression;

  TFile* tempFile=0;

  INFOclass("MatTransCorrection getting functions...");

  INFOclass("Loading file...");
  tempFile = TFile::Open("bsmtautau_lephad/auxData/Systematics/material_transport.root");
  TGraphAsymmErrors* tempGraph = 0;
  if (!tempFile) {
    WARNclass("Can not find material_transport.root");
    return;
  }

  /// barrel 1p
  TF1* fun_barrel1p = new TF1("fun_barrel1p","[0]+[1]*TMath::Log10(x)+[2]*TMath::Power(TMath::Log10(x),2)+[3]*TMath::Power(TMath::Log10(x),3)+[4]*TMath::Power(TMath::Log10(x),4)",0,6000);
  fun_barrel1p->SetParameters(4.97952e-01,9.35584e-01,-6.32106e-01, 1.72705e-01,-1.37163e-02);
  m_SF_fun["taupt_barrel1p"] = fun_barrel1p;
  tempGraph = (TGraphAsymmErrors*)tempFile->Get("tid/efficiencies/hists/g_ratio_SFBarrelLvl0_EffWRTTruthWprime_MatTransOnReco1PTauJets_ptTruthGeV_logDYtautau_maton");
  m_SF_graph["taupt_barrel1p"] = tempGraph;

  /// barrel 3p
  TF1* fun_barrel3p = new TF1("fun_barrel3p","[0]+[1]*TMath::Log10(x)+[2]*TMath::Power(TMath::Log10(x),2)+[3]*TMath::Power(TMath::Log10(x),3)+[4]*TMath::Power(TMath::Log10(x),4)",0,6000);
  fun_barrel3p->SetParameters(6.52722e-01,4.13763e-01,-1.33905e-01,0,0);
  m_SF_fun["taupt_barrel3p"] = fun_barrel3p;
  tempGraph = (TGraphAsymmErrors*)tempFile->Get("tid/efficiencies/hists/g_ratio_SFBarrelLvl0_EffWRTTruthWprime_MatTransOnReco3PTauJets_ptTruthGeV_logDYtautau_maton");
  m_SF_graph["taupt_barrel3p"] = tempGraph;
 
  /// endcap 1p
  TF1* fun_endcap1p = new TF1("fun_endcap1p","[0]+[1]*TMath::Log10(x)+[2]*TMath::Power(TMath::Log10(x),2)+[3]*TMath::Power(TMath::Log10(x),3)+[4]*TMath::Power(TMath::Log10(x),4)",0,6000);
  fun_endcap1p->SetParameters(1.27573,-2.69045e-01,-1.51140e-02,5.57960e-02,-7.76429e-03);
  m_SF_fun["taupt_endcap1p"] = fun_endcap1p;
  tempGraph = (TGraphAsymmErrors*)tempFile->Get("tid/efficiencies/hists/g_ratio_SFEndcapLvl0_EffWRTTruthWprime_MatTransOnReco1PTauJets_ptTruthGeV_logDYtautau_maton");
  m_SF_graph["taupt_endcap1p"] = tempGraph;

  /// endcap 3p
  TF1* fun_endcap3p = new TF1("fun_endcap3p","[0]+[1]*TMath::Log10(x)+[2]*TMath::Power(TMath::Log10(x),2)+[3]*TMath::Power(TMath::Log10(x),3)+[4]*TMath::Power(TMath::Log10(x),4)",0,6000);
  fun_endcap3p->SetParameters(8.26519e-01,2.13503e-01,-8.20376e-02,0,0);
  m_SF_fun["taupt_endcap3p"] = fun_endcap3p;
  tempGraph = (TGraphAsymmErrors*)tempFile->Get("tid/efficiencies/hists/g_ratio_SFEndcapLvl0_EffWRTTruthWprime_MatTransOnReco3PTauJets_ptTruthGeV_logDYtautau_maton");
  m_SF_graph["taupt_endcap3p"] = tempGraph;

  tempFile->Close(); delete tempFile; tempFile = 0;

}
//______________________________________________________________________________________________

const TString& MatTransCorrection::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool MatTransCorrection::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void MatTransCorrection::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}

//______________________________________________________________________________________________

bool MatTransCorrection::initializeSelf(){
  if (!LepHadObservable::initializeSelf()) return false;

  fSysName = this->fSample->replaceInTextRecursive("$(sfVariation.material)","~");

  return true;
}

//______________________________________________________________________________________________

bool MatTransCorrection::finalizeSelf(){
  if (!LepHadObservable::finalizeSelf()) return false;
  return true;
}
