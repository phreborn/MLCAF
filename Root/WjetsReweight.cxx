#include "BSMtautauCAF/WjetsReweight.h"
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

ClassImp(WjetsReweight)

//______________________________________________________________________________________________

WjetsReweight::WjetsReweight(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

WjetsReweight::~WjetsReweight(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* WjetsReweight::getBranchNames() const {
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
  bnames->Add(new TObjString("met_reco_et"));
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
double WjetsReweight::getValue() const {
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
  if (0==m_SF_hist.size()) return 0.0;

  //std::cout<<" In getValue "<<std::endl;
  double f_tau_0_phi          = this->tau_0_phi->EvalInstance();
  //double f_met_anti_iso_phi   = this->met_anti_iso_phi->EvalInstance();
  double f_lep_0              = this->lep_0->EvalInstance();
  double f_lep_0_pt       = this->lep_0_pt->EvalInstance();
  double f_lep_0_iso_Gradient   = this->lep_0_iso_Gradient->EvalInstance();
  double f_tau_0_pt       = this->tau_0_pt->EvalInstance();
  double f_tau_0_eta       = this->tau_0_eta->EvalInstance();
  double f_met_reco_et       = this->met_reco_et->EvalInstance();
  int    f_tau_0_n_charged_tracks = this->tau_0_n_charged_tracks->EvalInstance();
  int    f_n_bjets        = this->n_bjets->EvalInstance();
  double f_lephad_met_lep0_cos_dphi = this->lephad_met_lep0_cos_dphi->EvalInstance();
  double f_lephad_met_lep1_cos_dphi = this->lephad_met_lep1_cos_dphi->EvalInstance();

  ////////////////////////////
  //  Extrapolation SF
  ////////////////////////////
  if (f_tau_0_pt >= 300)  f_tau_0_pt = 299;
  if (f_lep_0_pt >= 300)  f_lep_0_pt = 299; 

  // determine which SF to use
  // period + channel + category + variable + SF
  // period (VR1516, VR17, VR18, VRAll)
  // channel (ehad, muhad, lephad)
  // category (Bveto, Btag)
  // variable (LeptonPt, LeptonPtDphi?)
  TString SF = "";   // SF name
  TH1F * h_nominal = 0;
  TH1F * h_up = 0;
  TH1F * h_down = 0;

  // peiriod
  SF = "WFRAll";

  // channel
  if ( 1 == f_lep_0) SF += "muhad";
  else if ( 2 == f_lep_0) SF += "ehad";
  else {
    std::cout << "Unknown lepton type: " << f_lep_0 << std::endl;
    return 1.0;
  }
  // category (only consider veto category)
  if ( 0 == f_n_bjets) SF += "Bveto";
  else if ( 0 < f_n_bjets) SF += "Btag"; 
  else return 1.0; 

  if ( 1 == f_tau_0_n_charged_tracks) SF += "1p";
  else if ( 3 == f_tau_0_n_charged_tracks) SF += "3p";
  else return 1.0;

  // parameterization
  TString param_tag = "";
  if(!this->fSample->getTag("~WjetsSFParam",param_tag)) std::cout<<"ERROR: Why cant I get ff name!!!\n";
  
  float variable = 0.0;
  if (param_tag == "LeptonPt") {
    SF += "LeptonPtSF";
    variable = f_lep_0_pt;
  }
  else if (param_tag == "MET") {
    SF += "METSF";
    variable = f_met_reco_et;
  }
  else if (param_tag == "TauEta") {
    SF += "TauEtaSF";
    variable = f_tau_0_eta;
  }

  SF.ReplaceAll("Btag", "Bveto");
  // tau pt 1,2,3,4,..,12 in bveto category
  //if (f_tau_0_pt>=25&&f_tau_0_pt<27) SF += "DphiTauPt1SF";
  //else if (f_tau_0_pt>=27&&f_tau_0_pt<30) SF += "DphiTauPt2SF";
  //else if (f_tau_0_pt>=30&&f_tau_0_pt<34) SF += "DphiTauPt3SF";
  //else if (f_tau_0_pt>=34&&f_tau_0_pt<39) SF += "DphiTauPt4SF";
  //else if (f_tau_0_pt>=39&&f_tau_0_pt<45) SF += "DphiTauPt5SF";
  //else if (f_tau_0_pt>=45&&f_tau_0_pt<52) SF += "DphiTauPt6SF";
  //else if (f_tau_0_pt>=52&&f_tau_0_pt<60) SF += "DphiTauPt7SF";
  //else if (f_tau_0_pt>=60&&f_tau_0_pt<70) SF += "DphiTauPt8SF";
  //else if (f_tau_0_pt>=70&&f_tau_0_pt<90) SF += "DphiTauPt9SF";
  //else if (f_tau_0_pt>=90&&f_tau_0_pt<110) SF += "DphiTauPt10SF";
  //else if (f_tau_0_pt>=110&&f_tau_0_pt<200) SF += "DphiTauPt11SF";
  //else if (f_tau_0_pt>=200) SF += "DphiTauPt12SF";

  //std::cout << "SF:" << SF << std::endl;
  h_nominal = m_SF_hist.at(SF);
  h_up = m_SF_hist.at(SF+"_up");
  h_down = m_SF_hist.at(SF+"_down");

  // SF is a function of dphi
  float retval = h_nominal->GetBinContent(h_nominal->FindBin(variable));
  float retval_up = h_up->GetBinContent(h_up->FindBin(variable));
  float retval_down = h_down->GetBinContent(h_down->FindBin(variable));
  float retval_error = fabs(retval_up - retval_down)/2.0;

  ////////////////
  // SYSTEMATICS
  ////////////////
  if    ( 
          (fSysName.Contains("FakeFactor_WjetsReweight_Bveto1p_1up") && f_tau_0_n_charged_tracks == 1 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_Bveto3p_1up") && f_tau_0_n_charged_tracks == 3 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_Btag1p_1up") && f_tau_0_n_charged_tracks == 1 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_Btag3p_1up") && f_tau_0_n_charged_tracks == 3 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_ElHadBveto1p_1up") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 1 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_MuHadBveto1p_1up") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 1 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_ElHadBveto3p_1up") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 3 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_MuHadBveto3p_1up") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 3 && f_n_bjets == 0) || 
          (fSysName.Contains("FakeFactor_WjetsReweight_ElHadBtag1p_1up") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 1 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_MuHadBtag1p_1up") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 1 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_ElHadBtag3p_1up") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 3 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_MuHadBtag3p_1up") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 3 && f_n_bjets > 0) 
        ) {
    //retval = retval+fabs(retval-1.0)/2.0;
    if (f_n_bjets == 0)
      retval = retval+fabs(retval-1.0);
    else 
      retval = 1.0+fabs(retval-1.0);
  }
  else if(
          (fSysName.Contains("FakeFactor_WjetsReweight_Bveto1p_1down") && f_tau_0_n_charged_tracks == 1 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_Bveto3p_1down") && f_tau_0_n_charged_tracks == 3 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_Btag1p_1down") && f_tau_0_n_charged_tracks == 1 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_Btag3p_1down") && f_tau_0_n_charged_tracks == 3 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_ElHadBveto1p_1down") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 1 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_MuHadBveto1p_1down") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 1 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_ElHadBveto3p_1down") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 3 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_MuHadBveto3p_1down") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 3 && f_n_bjets == 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_ElHadBtag1p_1down") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 1 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_MuHadBtag1p_1down") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 1 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_ElHadBtag3p_1down") && f_lep_0 == 2 && f_tau_0_n_charged_tracks == 3 && f_n_bjets > 0) ||
          (fSysName.Contains("FakeFactor_WjetsReweight_MuHadBtag3p_1down") && f_lep_0 == 1 && f_tau_0_n_charged_tracks == 3 && f_n_bjets > 0)
         ) {
    //retval = retval-fabs(retval-1.0)/2.0;
    if (f_n_bjets ==0 )
      retval = retval-fabs(retval-1.0);
    else 
      retval = 1.0-fabs(retval-1.0);  
  }
  // no correction to btag
  else if (f_n_bjets > 0) {
    retval = 1.0;
  }

  DEBUGclass("returning");

  return retval;
}
//______________________________________________________________________________________________

WjetsReweight::WjetsReweight(const TString& expression) : LepHadObservable(expression)
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

  std::cout << "INFO: WjetsReweight.cxx getting histograms from files. " << std::endl;

  ///////////////////////////////
  // Wjets scale factor
  ///////////////////////////////
  std::vector<TString> periods = {"WFRAll"};
  std::vector<TString> channels = {"muhad","ehad"};

  // list of available SFs
  std::vector<TString> SF_list;
  SF_list.clear();
  SF_list.reserve(16);
  for (auto period : periods) {
    for (auto channel : channels) {
      // 1D LeptonPt
      SF_list.emplace_back(period + channel + "Bveto1pLeptonPtSF");
      SF_list.emplace_back(period + channel + "Bveto3pLeptonPtSF");

      // 1D MET
      SF_list.emplace_back(period + channel + "Bveto1pMETSF");
      SF_list.emplace_back(period + channel + "Bveto3pMETSF");

      // 1D TauEta
      SF_list.emplace_back(period + channel + "Bveto1pTauEtaSF");
      SF_list.emplace_back(period + channel + "Bveto3pTauEtaSF");

      // 2D Dphi(tau, MET) x TauPt
      //SF_list.emplace_back(period + channel + "Bveto1pDphiTauPt1SF");
      //SF_list.emplace_back(period + channel + "Bveto1pDphiTauPt2SF");
      //SF_list.emplace_back(period + channel + "Bveto1pDphiTauPt3SF");
      //SF_list.emplace_back(period + channel + "Bveto1pDphiTauPt4SF");
      //SF_list.emplace_back(period + channel + "Bveto1pDphiTauPt5SF");
      //SF_list.emplace_back(period + channel + "Bveto1pDphiTauPt6SF");
      //SF_list.emplace_back(period + channel + "Bveto1pDphiTauPt7SF");
      //SF_list.emplace_back(period + channel + "Bveto1pDphiTauPt8SF");
      //SF_list.emplace_back(period + channel + "Bveto1pDphiTauPt9SF");
      //SF_list.emplace_back(period + channel + "Bveto1pDphiTauPt10SF");
      //SF_list.emplace_back(period + channel + "Bveto1pDphiTauPt11SF");
      //SF_list.emplace_back(period + channel + "Bveto1pDphiTauPt12SF");
      //
      //SF_list.emplace_back(period + channel + "Bveto3pDphiTauPt1SF");
      //SF_list.emplace_back(period + channel + "Bveto3pDphiTauPt2SF");
      //SF_list.emplace_back(period + channel + "Bveto3pDphiTauPt3SF");
      //SF_list.emplace_back(period + channel + "Bveto3pDphiTauPt4SF");
      //SF_list.emplace_back(period + channel + "Bveto3pDphiTauPt5SF");
      //SF_list.emplace_back(period + channel + "Bveto3pDphiTauPt6SF");
      //SF_list.emplace_back(period + channel + "Bveto3pDphiTauPt7SF");
      //SF_list.emplace_back(period + channel + "Bveto3pDphiTauPt8SF");
      //SF_list.emplace_back(period + channel + "Bveto3pDphiTauPt9SF");
      //SF_list.emplace_back(period + channel + "Bveto3pDphiTauPt10SF");
      //SF_list.emplace_back(period + channel + "Bveto3pDphiTauPt11SF");
      //SF_list.emplace_back(period + channel + "Bveto3pDphiTauPt12SF");
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

const TString& WjetsReweight::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool WjetsReweight::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void WjetsReweight::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}

//______________________________________________________________________________________________

bool WjetsReweight::initializeSelf(){
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
  this->met_reco_et             = new TTreeFormula( "met_reco_et",     "met_reco_p4.Et()",      this->fTree);
  this->lep_0_iso_Gradient      = new TTreeFormula( "lep_0_iso_Gradient",     "lep_0_iso_Gradient",      this->fTree);
  this->lephad_met_lep1_cos_dphi= new TTreeFormula( "lephad_met_lep1_cos_dphi", "lephad_met_lep1_cos_dphi", this->fTree);
  this->lephad_met_lep0_cos_dphi= new TTreeFormula( "lephad_met_lep0_cos_dphi", "lephad_met_lep0_cos_dphi", this->fTree);
  this->lep_0                   = new TTreeFormula( "lep_0",    "lep_0",      this->fTree);
  this->lep_0_pt                = new TTreeFormula( "lep_0_pt",     "lep_0_p4.Pt()",      this->fTree);
  this->n_bjets                 = new TTreeFormula( "n_bjets",  "n_bjets",      this->fTree);
  //this->met_anti_iso_phi = new TTreeFormula( "met_anti_iso_phi", "met_anti_iso_phi", this->fTree);
  return true;
}

//______________________________________________________________________________________________

bool WjetsReweight::finalizeSelf(){
  delete this->lep_0;
  delete this->tau_0_phi;
  delete this->tau_0_pt;
  delete this->tau_0_eta;
  delete this->met_reco_et;
  //delete this->met_anti_iso_phi;
  delete this->tau_0_n_charged_tracks;
  delete this->lephad_met_lep1_cos_dphi;
  delete this->lephad_met_lep0_cos_dphi;
  delete this->lep_0_iso_Gradient;
  delete this->n_bjets;

  return true;
}
