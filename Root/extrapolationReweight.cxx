#include "BSMtautauCAF/extrapolationReweight.h"
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

ClassImp(extrapolationReweight)

//______________________________________________________________________________________________

extrapolationReweight::extrapolationReweight(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

extrapolationReweight::~extrapolationReweight(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* extrapolationReweight::getBranchNames() const {
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
double extrapolationReweight::getValue() const {
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
  //std::cout<<" In getValue "<<std::endl;
  double f_tau_0_phi          = this->tau_0_phi->EvalInstance();
  //double f_met_anti_iso_phi   = this->met_anti_iso_phi->EvalInstance();
  double f_lep_0              = this->lep_0->EvalInstance();
  double f_lep_0_iso_Gradient   = this->lep_0_iso_Gradient->EvalInstance();
  double f_tau_0_pt       = this->tau_0_pt->EvalInstance();
  int    f_tau_0_n_charged_tracks = this->tau_0_n_charged_tracks->EvalInstance();
  int    f_n_bjets        = this->n_bjets->EvalInstance();
  double f_lephad_met_lep0_cos_dphi = this->lephad_met_lep0_cos_dphi->EvalInstance();
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
  TH1F * h_up = 0;
  TH1F * h_down = 0;

  // peiriod
  SF = "VRAll";

  // channel
  if ( 1 == f_lep_0) SF += "muhad";
  else if (2 == f_lep_0) SF += "ehad";
  else std::cout << "ERROR: unknown lepton flavor" << std::endl;

  // category (only consider bveto category)
  if ( 0 == f_n_bjets) SF += "Bveto";
  else if (1 <= f_n_bjets) return 1.0;
  else std::cout << "ERROR: strange #bjets" << std::endl;

  if ( 1 == f_tau_0_n_charged_tracks) SF += "1p";
  else if ( 3 == f_tau_0_n_charged_tracks) SF += "3p";
  else return 1.0;

  // parameterization
  // dphi 1,2,3 in bveto/btag category
  if (f_lephad_met_lep1_cos_dphi>=0.0&&f_lephad_met_lep1_cos_dphi<1) SF += "TauPtDphi1SF";
  else if (f_lephad_met_lep1_cos_dphi>=1&&f_lephad_met_lep1_cos_dphi<2) SF += "TauPtDphi2SF";
  else if (f_lephad_met_lep1_cos_dphi>=2) SF += "TauPtDphi3SF";

  h_nominal = m_SF_hist.at(SF);
  h_up = m_SF_hist.at(SF+"_up");
  h_down = m_SF_hist.at(SF+"_down");
  
  // SF is a function of tau pT
  float retval = h_nominal->GetBinContent(h_nominal->FindBin(f_tau_0_pt));
  float retval_up = h_up->GetBinContent(h_up->FindBin(f_tau_0_pt));
  float retval_down = h_down->GetBinContent(h_down->FindBin(f_tau_0_pt));
  float retval_error = fabs(retval_up - retval_down)/2.0;
  ////////////////
  // SYSTEMATICS
  ////////////////
  if    ( (fSysName.Contains("FakeFactor_ExtraSysBtag_1up")    && f_n_bjets>0) ||
          (fSysName.Contains("FakeFactor_ExtraSysBtag1p_1up")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_ExtraSysBtag3p_1up")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_ExtraSysBveto_1up")   && f_n_bjets==0 ) ||
          (fSysName.Contains("FakeFactor_ExtraSysBveto1p_1up") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_ExtraSysBveto3p_1up") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3)    ) {
    retval = 1.0+fabs(retval-1.0);
  }
  else if((fSysName.Contains("FakeFactor_ExtraSysBtag_1down")    && f_n_bjets>0) ||
          (fSysName.Contains("FakeFactor_ExtraSysBtag1p_1down")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_ExtraSysBtag3p_1down")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_ExtraSysBveto_1down")   && f_n_bjets==0 ) ||
          (fSysName.Contains("FakeFactor_ExtraSysBveto1p_1down") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_ExtraSysBveto3p_1down") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3)    ) {
    retval = 1.0-fabs(retval-1.0);
  }

  DEBUGclass("returning");

  return retval;
}
//______________________________________________________________________________________________

extrapolationReweight::extrapolationReweight(const TString& expression) : LepHadObservable(expression)
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

  std::cout << "INFO: extrapolationReweight.cxx getting histograms from files. " << std::endl;

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

const TString& extrapolationReweight::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool extrapolationReweight::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void extrapolationReweight::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool extrapolationReweight::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void extrapolationReweight::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString extrapolationReweight::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool extrapolationReweight::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  if (!this->fSample->getTag("~isData", _isData)) {
    ERROR("tag isData missing");
    return false;
  }

  if (this->fTree->FindLeaf("NOMINAL_pileup_random_run_number")) this->x_run_number = new TTreeFormula("NOMINAL_pileup_random_run_number", "NOMINAL_pileup_random_run_number", this->fTree);
  else                                                           this->x_run_number = new TTreeFormula("run_number", "run_number", this->fTree);


  this->tau_0_phi               = new TTreeFormula( "tau_0_phi",     "tau_0_p4.Phi()",      this->fTree);
  this->tau_0_n_charged_tracks  = new TTreeFormula( "tau_0_n_charged_tracks","tau_0_n_charged_tracks", this->fTree);
  this->tau_0_pt                = new TTreeFormula( "tau_0_pt",     "tau_0_p4.Pt()",      this->fTree);
  this->lep_0_iso_Gradient      = new TTreeFormula( "lep_0_iso_Gradient",     "lep_0_iso_Gradient",      this->fTree);
  this->lephad_met_lep1_cos_dphi= new TTreeFormula( "lephad_met_lep1_cos_dphi", "lephad_met_lep1_cos_dphi", this->fTree);
  this->lephad_met_lep0_cos_dphi= new TTreeFormula( "lephad_met_lep0_cos_dphi", "lephad_met_lep0_cos_dphi", this->fTree);
  this->lep_0                   = new TTreeFormula( "lep_0",    "lep_0",      this->fTree);
  this->n_bjets                 = new TTreeFormula( "n_bjets",  "n_bjets",      this->fTree);
  //this->met_anti_iso_phi = new TTreeFormula( "met_anti_iso_phi", "met_anti_iso_phi", this->fTree);
  return true;
}

//______________________________________________________________________________________________

bool extrapolationReweight::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete this->lep_0;
  delete this->tau_0_phi;
  delete this->tau_0_pt;
  //delete this->met_anti_iso_phi;
  delete this->tau_0_n_charged_tracks;
  delete this->lephad_met_lep1_cos_dphi;
  delete this->lephad_met_lep0_cos_dphi;
  delete this->lep_0_iso_Gradient;
  delete this->n_bjets;

  return true;
}
