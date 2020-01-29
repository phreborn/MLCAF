#include "BSMtautauCAF/TauReweight.h"
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
ClassImp(TauReweight)

//______________________________________________________________________________________________

TauReweight::TauReweight(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

TauReweight::~TauReweight(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* TauReweight::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));
  bnames->Add(new TObjString("tau_0_phi"));
  bnames->Add(new TObjString("met_anti_iso_phi"));
  bnames->Add(new TObjString("lep_0_iso_Gradient"));
  bnames->Add(new TObjString("tau_0_n_charged_tracks"));
  bnames->Add(new TObjString("tau_0_pt"));
  bnames->Add(new TObjString("tau_0_eta"));
  bnames->Add(new TObjString("lep_0"));
  bnames->Add(new TObjString("n_bjets"));
  bnames->Add(new TObjString("lephad_met_lep0_cos_dphi"));
  bnames->Add(new TObjString("lephad_met_lep1_cos_dphi"));

  if (isData()) {
    bnames->Add(new TObjString("run_number"));
  } else {
    bnames->Add(new TObjString("NOMINAL_pileup_random_run_number"));
  }

  return bnames;
}

//______________________________________________________________________________________________
double TauReweight::getValue() const {
  // in the rest of this function, you should retrieve the data and calculate your return value
  // here is the place where most of your custom code should go
  // a couple of comments should guide you through the process
  // when writing your code, please keep in mind that this code can be executed several times on every event
  // make your code efficient. catch all possible problems. when in doubt, contact experts!

  // here, you should calculate your return value
  // of course, you can use other data members of your observable at any time
  /* example block for TTreeFormula method:
     const double retval = this->fFormula->Eval(0.);
     */
  /* exmple block for TTree::SetBranchAddress method:
     const double retval = this->fBranch1 + this->fBranch2;
     */
  //std::cout << "in getValue" << std::endl;
  if (0==m_SF_fun.size()) return 1.0;

  double f_tau_0_phi          = this->tau_0_phi->EvalInstance();
  //double f_met_anti_iso_phi   = this->met_anti_iso_phi->EvalInstance();
  double f_lep_0              = this->lep_0->EvalInstance();
  double f_lep_0_iso_Gradient   = this->lep_0_iso_Gradient->EvalInstance();
  double f_tau_0_pt       = this->tau_0_pt->EvalInstance();
  double f_tau_0_eta      = this->tau_0_eta->EvalInstance();
  int    f_tau_0_n_charged_tracks = this->tau_0_n_charged_tracks->EvalInstance();
  int    f_n_bjets        = this->n_bjets->EvalInstance();
  double f_lephad_met_lep0_cos_dphi = this->lephad_met_lep0_cos_dphi->EvalInstance();
  double f_lephad_met_lep1_cos_dphi = this->lephad_met_lep1_cos_dphi->EvalInstance();

  if (100>=f_tau_0_pt) return 1.0;
  if (6000<=f_tau_0_pt) f_tau_0_pt = 5999;

  // determine which SF to use
  TString SF = "taupt_";   // SF name
  TF1 * fun_nominal = 0;
  //std::cout << fabs(f_tau_0_eta) << std::endl;
  // barrel/endcap
  if (1.37>fabs(f_tau_0_eta)) SF += "barrel";
  else if (1.52<fabs(f_tau_0_eta)) SF += "endcap";
  else return 1.0;

  // 1prong/3prong
  if (1 == f_tau_0_n_charged_tracks ) SF += "1p";
  else if (3 == f_tau_0_n_charged_tracks) SF += "3p";
  else return 1.0;
  
  fun_nominal = m_SF_fun.at(SF);
  // parameterization
  // SF is a function of tau pT
  float retval = fun_nominal->Eval(f_tau_0_pt);
  //std::cout << SF << "\t" << f_tau_0_pt << "\t" << retval << std::endl;
  ////////////////
  // SYSTEMATICS
  ////////////////
  // strange: neglible
/*
  TGraphAsymmErrors* graph_sys = 0;
  graph_sys = m_SF_graph.at(SF);

  double * x = graph_sys->GetX();
  double * x_error_low = graph_sys->GetEXlow();
  double * x_error_high = graph_sys->GetEXhigh();

  double * y = graph_sys->GetY();
  double * y_error_low = graph_sys->GetEYlow();
  double * y_error_high = graph_sys->GetEYhigh();

  int N = graph_sys->GetN();
  cout << N << endl;
  for (int i=0; i<N; ++i) {
    cout.precision(5);
    cout << "[" << x[i]-x_error_low[i] << "," << x[i]+x_error_high[i] << "]\t" 
              << y[i] << "\t+" << y_error_high[i] << "\t-" << y_error_low[i] << "\t"
              << fun_nominal->Eval(x[i]) 
              << endl;;
  }

  if((fSysName.Contains("MatTransCorr_barrel_1p") && 1.37>fabs(f_tau_0_eta) && 1 == f_tau_0_n_charged_tracks) ||
     (fSysName.Contains("MatTransCorr_barrel_3p") && 1.37>fabs(f_tau_0_eta) && 3 == f_tau_0_n_charged_tracks) ||
     (fSysName.Contains("MatTransCorr_endcap_1p") && 1.52<fabs(f_tau_0_eta) && 1 == f_tau_0_n_charged_tracks) ||
     (fSysName.Contains("MatTransCorr_endcap_3p") && 1.52<fabs(f_tau_0_eta) && 3 == f_tau_0_n_charged_tracks) ) {
    double x = .0;
    double nominal = .0;
    double error = .0;
    retval += error;
  }  
*/
  DEBUGclass("returning");

  return retval;
}
//______________________________________________________________________________________________

TauReweight::TauReweight(const TString& expression) : LepHadObservable(expression)
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

  //std::cout << "INFO: TauReweight.cxx getting histograms from files. " << std::endl;
  std::cout << "INFO: TauReweight getting functions " << std::endl;

  ///////////////////////////////
  // Tau scale factor
  ///////////////////////////////
  tempFile = TFile::Open("Systematics/material_transport.root");
  TGraphAsymmErrors* tempGraph = 0;
  if (!tempFile) {
    std::cout << "WARNING: can not find material_transport.root " << std::endl;
    return;
  }

  /// barrel 1p
  TF1* fun_barrel1p = new TF1("fun_barrel1p","[0]+[1]*TMath::Log10(x)+[2]*TMath::Power(TMath::Log10(x),2)+[3]*TMath::Power(TMath::Log10(x),3)+[4]*TMath::Power(TMath::Log10(x),4)",0,6000);
  //fun_barrel1p->SetParameters(2.91204e-01,1.09026e+00,-5.60785e-01,9.43443e-02,0);
  fun_barrel1p->SetParameters(4.97952e-01,9.35584e-01,-6.32106e-01, 1.72705e-01,-1.37163e-02);
  m_SF_fun["taupt_barrel1p"] = fun_barrel1p;

  //tempGraph = (TGraphAsymmErrors*)tempFile->Get("tid/efficiencies/hists/g_ratio_SFBarrelLvl0_EffWRTTruthWprime_MatTransOnReco1PTauJets_ptTruthTotalGeV_logDYtautau_maton");
  tempGraph = (TGraphAsymmErrors*)tempFile->Get("tid/efficiencies/hists/g_ratio_SFBarrelLvl0_EffWRTTruthWprime_MatTransOnReco1PTauJets_ptTruthGeV_logDYtautau_maton");
  m_SF_graph["taupt_barrel1p"] = tempGraph;

  /// barrel 3p
  TF1* fun_barrel3p = new TF1("fun_barrel3p","[0]+[1]*TMath::Log10(x)+[2]*TMath::Power(TMath::Log10(x),2)+[3]*TMath::Power(TMath::Log10(x),3)+[4]*TMath::Power(TMath::Log10(x),4)",0,6000);
  //fun_barrel3p->SetParameters(9.31260e-01,-2.02958e-03,6.43390e-02,-2.80092e-02,0);
  fun_barrel3p->SetParameters(6.52722e-01,4.13763e-01,-1.33905e-01,0,0);
  m_SF_fun["taupt_barrel3p"] = fun_barrel3p;

  //tempGraph = (TGraphAsymmErrors*)tempFile->Get("tid/efficiencies/hists/g_ratio_SFBarrelLvl0_EffWRTTruthWprime_MatTransOnReco3PTauJets_ptTruthTotalGeV_logDYtautau_maton");
  tempGraph = (TGraphAsymmErrors*)tempFile->Get("tid/efficiencies/hists/g_ratio_SFBarrelLvl0_EffWRTTruthWprime_MatTransOnReco3PTauJets_ptTruthGeV_logDYtautau_maton");
  m_SF_graph["taupt_barrel3p"] = tempGraph;
 
  /// endcap 1p
  TF1* fun_endcap1p = new TF1("fun_endcap1p","[0]+[1]*TMath::Log10(x)+[2]*TMath::Power(TMath::Log10(x),2)+[3]*TMath::Power(TMath::Log10(x),3)+[4]*TMath::Power(TMath::Log10(x),4)",0,6000);
  //fun_endcap1p->SetParameters(-3.77269e+00,8.75961e+00,-5.82921e+00,1.65136e+00,-1.66298e-01);
  fun_endcap1p->SetParameters(1.27573,-2.69045e-01,-1.51140e-02,5.57960e-02,-7.76429e-03);
  m_SF_fun["taupt_endcap1p"] = fun_endcap1p;

  //tempGraph = (TGraphAsymmErrors*)tempFile->Get("tid/efficiencies/hists/g_ratio_SFEndcapLvl0_EffWRTTruthWprime_MatTransOnReco1PTauJets_ptTruthTotalGeV_logDYtautau_maton");
  tempGraph = (TGraphAsymmErrors*)tempFile->Get("tid/efficiencies/hists/g_ratio_SFEndcapLvl0_EffWRTTruthWprime_MatTransOnReco1PTauJets_ptTruthGeV_logDYtautau_maton");
  m_SF_graph["taupt_endcap1p"] = tempGraph;

  /// endcap 3p
  TF1* fun_endcap3p = new TF1("fun_endcap3p","[0]+[1]*TMath::Log10(x)+[2]*TMath::Power(TMath::Log10(x),2)+[3]*TMath::Power(TMath::Log10(x),3)+[4]*TMath::Power(TMath::Log10(x),4)",0,6000);
  //fun_endcap3p->SetParameters(7.69077e-01,2.76432e-01,-9.40499e-02,0,0);
  fun_endcap3p->SetParameters(8.26519e-01,2.13503e-01,-8.20376e-02,0,0);
  m_SF_fun["taupt_endcap3p"] = fun_endcap3p;

  //tempGraph = (TGraphAsymmErrors*)tempFile->Get("tid/efficiencies/hists/g_ratio_SFEndcapLvl0_EffWRTTruthWprime_MatTransOnReco3PTauJets_ptTruthTotalGeV_logDYtautau_maton");
  tempGraph = (TGraphAsymmErrors*)tempFile->Get("tid/efficiencies/hists/g_ratio_SFEndcapLvl0_EffWRTTruthWprime_MatTransOnReco3PTauJets_ptTruthGeV_logDYtautau_maton");
  m_SF_graph["taupt_endcap3p"] = tempGraph;

  tempFile->Close(); delete tempFile; tempFile = 0;

}
//______________________________________________________________________________________________

const TString& TauReweight::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool TauReweight::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void TauReweight::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}

//______________________________________________________________________________________________

bool TauReweight::initializeSelf(){
  if (!this->fSample->getTag("~isData", _isData)) {
    ERROR("tag isData missing");
    return false;
  }

  if (this->fTree->FindLeaf("NOMINAL_pileup_random_run_number")) this->x_run_number = new TTreeFormula("NOMINAL_pileup_random_run_number", "NOMINAL_pileup_random_run_number", this->fTree);
  else                                                           this->x_run_number = new TTreeFormula("run_number", "run_number", this->fTree);


  this->tau_0_phi               = new TTreeFormula( "tau_0_phi",     "tau_0_p4.Phi()",      this->fTree);
  this->tau_0_n_charged_tracks  = new TTreeFormula( "tau_0_n_charged_tracks","tau_0_n_charged_tracks", this->fTree);
  this->tau_0_pt                = new TTreeFormula( "tau_0_pt",     "tau_0_p4.Pt()",      this->fTree);
  this->tau_0_eta               = new TTreeFormula( "tau_0_eta",     "tau_0_p4.Eta()",      this->fTree);
  this->lep_0_iso_Gradient      = new TTreeFormula( "lep_0_iso_Gradient",     "lep_0_iso_Gradient",      this->fTree);
  this->lephad_met_lep1_cos_dphi= new TTreeFormula( "lephad_met_lep1_cos_dphi", "lephad_met_lep1_cos_dphi", this->fTree);
  this->lephad_met_lep0_cos_dphi= new TTreeFormula( "lephad_met_lep0_cos_dphi", "lephad_met_lep0_cos_dphi", this->fTree);
  this->lep_0                   = new TTreeFormula( "lep_0",    "lep_0",      this->fTree);
  this->n_bjets                 = new TTreeFormula( "n_bjets",  "n_bjets",      this->fTree);
  //this->met_anti_iso_phi = new TTreeFormula( "met_anti_iso_phi", "met_anti_iso_phi", this->fTree);
  return true;
}

//______________________________________________________________________________________________

bool TauReweight::finalizeSelf(){
  delete this->lep_0;
  delete this->tau_0_phi;
  delete this->tau_0_pt;
  delete this->tau_0_eta;
  //delete this->met_anti_iso_phi;
  delete this->tau_0_n_charged_tracks;
  delete this->lephad_met_lep1_cos_dphi;
  delete this->lephad_met_lep0_cos_dphi;
  delete this->lep_0_iso_Gradient;
  delete this->n_bjets;

  return true;
}
