#include "BSMtautauCAF/ptReweight.h"
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

ClassImp(ptReweight)

//______________________________________________________________________________________________

ptReweight::ptReweight(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

ptReweight::~ptReweight(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* ptReweight::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("tau_0_phi"));
  bnames->Add(new TObjString("tau_0_n_charged_tracks"));
  bnames->Add(new TObjString("tau_0_pt"));
  bnames->Add(new TObjString("lep_0_pt"));
  bnames->Add(new TObjString("lep_0"));
  bnames->Add(new TObjString("n_bjets"));
  bnames->Add(new TObjString("lephad_met_lep1_cos_dphi"));

  if (isData()) {
    bnames->Add(new TObjString("run_number"));
  } else {
    bnames->Add(new TObjString("NOMINAL_pileup_random_run_number"));
  }

  return bnames;
}

//______________________________________________________________________________________________
double ptReweight::getValue() const {
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
  int    f_tau_0_n_charged_tracks = this->tau_0_n_charged_tracks->EvalInstance();
  int    f_n_bjets        = this->n_bjets->EvalInstance();
  double f_lep_0              = this->lep_0->EvalInstance();
  double f_tau_0_phi          = this->tau_0_phi->EvalInstance();
  double f_tau_0_pt       = this->tau_0_pt->EvalInstance();
  double f_lep_0_pt   = this->lep_0_pt->EvalInstance();
  double f_lephad_met_lep1_cos_dphi = this->lephad_met_lep1_cos_dphi->EvalInstance();

  // fake factor valid range up to 300GeV
  if(f_tau_0_pt>300) f_tau_0_pt = 299;
 
  // determine which FF to use
  // period + channel + category + variable + FF
  // period (WFR1516, WFR17, WFR18, WFRAll)
  // channel (ehad, muhad, lephad)
  // category (Bveto, Btag)x(1p,3p)
  // variable (LeptonPt, LeptonPtDphi?)
  TString FF = "";   // FF name
  TH1F * h_nominal = 0;
  TH1F * h_up = 0;
  TH1F * h_down = 0;

  // peiriod
  TString period_tag = "";
  if(!this->fSample->getTag("~WFFPeriod",period_tag)) std::cout<<"ERROR: Why cant I get ff name!!!\n";

  if (period_tag == "Separated") {
    if(this->x_run_number->EvalInstance() <= LIMIT_2016) FF = "WFR1516";
    else if(this->x_run_number->EvalInstance() > LIMIT_2016 && this->x_run_number->EvalInstance() <= LIMIT_2017) FF = "WFR17";
    else if(this->x_run_number->EvalInstance() > LIMIT_2017 && this->x_run_number->EvalInstance() <= LIMIT_2018) FF = "WFR18";
    else std::cout << "ERROR: srange run number " << this->x_run_number->EvalInstance() << std::endl; 
  }
  else if (period_tag == "Combined")
    FF = "WFRAll";

  // channel
  if ( 1 == f_lep_0) FF += "muhad";
  else if (2 == f_lep_0) FF += "ehad";
  else std::cout << "ERROR: unknown lepton flavor" << std::endl;

  // category 
  if ( 0 == f_n_bjets) FF += "Bveto";
  else if (1 <= f_n_bjets) FF += "Btag";
  else std::cout << "ERROR: strange #bjets" << std::endl;

  if ( 1 == f_tau_0_n_charged_tracks) FF += "1p";
  else if ( 3 == f_tau_0_n_charged_tracks) FF += "3p";
  else return 1.0;

  // parameterization
  TString param_tag = "";
  if(!this->fSample->getTag("~WFFParam",param_tag)) std::cout<<"ERROR: Why cant I get ff name!!!\n";
  if ( "TauPt" == param_tag ) {
    FF += "TauPtFF";
  }
  else if ( "TauPtDphi" == param_tag) {
    // dphi 1,2,3,4 in bveto/btag category
    if (0 == f_n_bjets) {
      if (f_lephad_met_lep1_cos_dphi>=0.0&&f_lephad_met_lep1_cos_dphi<1) FF += "TauPtDphi1FF";
      else if (f_lephad_met_lep1_cos_dphi>=1&&f_lephad_met_lep1_cos_dphi<2) FF += "TauPtDphi2FF";
      else if (f_lephad_met_lep1_cos_dphi>=2&&f_lephad_met_lep1_cos_dphi<2.5) FF += "TauPtDphi3FF";
      else if (f_lephad_met_lep1_cos_dphi>=2.5) FF += "TauPtDphi4FF";
    }
    else if (1 <= f_n_bjets) {
      // use FF from bveto category
      FF.ReplaceAll("Btag", "Bveto");
      if (f_lephad_met_lep1_cos_dphi>=0.0&&f_lephad_met_lep1_cos_dphi<1) FF += "TauPtDphi1FF";
      else if (f_lephad_met_lep1_cos_dphi>=1&&f_lephad_met_lep1_cos_dphi<2) FF += "TauPtDphi2FF";
      else if (f_lephad_met_lep1_cos_dphi>=2&&f_lephad_met_lep1_cos_dphi<2.5) FF += "TauPtDphi3FF";
      else if (f_lephad_met_lep1_cos_dphi>=2.5) FF += "TauPtDphi4FF";
    }
  }

  h_nominal = m_FF_hist.at(FF);
  h_up = m_FF_hist.at(FF+"_up");
  h_down = m_FF_hist.at(FF+"_down");
  
  // FF is a function of tau pT
  float retval = h_nominal->GetBinContent(h_nominal->FindBin(f_tau_0_pt));
  float retval_up = h_up->GetBinContent(h_up->FindBin(f_tau_0_pt));
  float retval_down = h_down->GetBinContent(h_down->FindBin(f_tau_0_pt));
  float retval_error = fabs(retval_up - retval_down)/2.0;

  // systematic uncertainty
  if    ( (fSysName.Contains("FakeFactor_WjetsBtag_1up")    && f_n_bjets>0) ||
          (fSysName.Contains("FakeFactor_WjetsBtag1p_1up")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_WjetsBtag3p_1up")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_WjetsBveto_1up")   && f_n_bjets==0 ) ||
          (fSysName.Contains("FakeFactor_WjetsBveto1p_1up") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_WjetsBveto3p_1up") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3)    ) {
    if (fSysName.Contains("Btag"))
      retval *= 1.2;
    else
      retval += retval_error;
  }
  else if((fSysName.Contains("FakeFactor_WjetsBtag_1down")    && f_n_bjets>0) ||
          (fSysName.Contains("FakeFactor_WjetsBtag1p_1down")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_WjetsBtag3p_1down")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_WjetsBveto_1down")   && f_n_bjets==0 ) ||
          (fSysName.Contains("FakeFactor_WjetsBveto1p_1down") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_WjetsBveto3p_1down") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3)    ) {
    if (fSysName.Contains("Btag"))
      retval *= 0.8;
    else
      retval -= retval_error;
  }

  return retval;
}
//______________________________________________________________________________________________

ptReweight::ptReweight(const TString& expression) : LepHadObservable(expression)
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
  std::cout << "INFO: ptReweight.cxx getting histograms from files. " << std::endl;
  ///////////////////////////////
  //  Wjets FF
  ///////////////////////////////
  std::vector<TString> periods = {"WFR1516", "WFR17", "WFR18", "WFRAll"};
  std::vector<TString> channels = {"ehad", "muhad"};

  // list of available FFs
  std::vector<TString> FF_list;
  FF_list.clear();
  FF_list.reserve(256);
  for (auto period : periods) {
    for (auto channel : channels) {
      // 1D LeptonPt
      FF_list.emplace_back(period + channel + "Bveto1pTauPtFF");
      FF_list.emplace_back(period + channel + "Bveto1pTauPtFF");
      FF_list.emplace_back(period + channel + "Btag3pTauPtFF");
      FF_list.emplace_back(period + channel + "Btag3pTauPtFF");
      // 2D TauPt Dphi(lep, MET)
      FF_list.emplace_back(period + channel + "Bveto1pTauPtDphi1FF");
      FF_list.emplace_back(period + channel + "Bveto1pTauPtDphi2FF");
      FF_list.emplace_back(period + channel + "Bveto1pTauPtDphi3FF");
      FF_list.emplace_back(period + channel + "Bveto1pTauPtDphi4FF");
      FF_list.emplace_back(period + channel + "Bveto3pTauPtDphi1FF");
      FF_list.emplace_back(period + channel + "Bveto3pTauPtDphi2FF");
      FF_list.emplace_back(period + channel + "Bveto3pTauPtDphi3FF");
      FF_list.emplace_back(period + channel + "Bveto3pTauPtDphi4FF");
      //FF_list.emplace_back(period + channel + "Btag1pTauPtDphi1FF");
      //FF_list.emplace_back(period + channel + "Btag1pTauPtDphi2FF");
      //FF_list.emplace_back(period + channel + "Btag1pTauPtDphi3FF");
      //FF_list.emplace_back(period + channel + "Btag1pTauPtDphi4FF");
      //FF_list.emplace_back(period + channel + "Btag3pTauPtDphi1FF");
      //FF_list.emplace_back(period + channel + "Btag3pTauPtDphi2FF");
      //FF_list.emplace_back(period + channel + "Btag3pTauPtDphi3FF");
      //FF_list.emplace_back(period + channel + "Btag3pTauPtDphi4FF");
    }
  }
 
  TH1F* tempHist = 0;
  // obtain FF histograms
  for (auto fn : FF_list) {
    tempFile = TFile::Open("FakeFactors/"+fn+".root");
    if (!tempFile) {
      std::cout << "WARNING: can not find LFF " << fn << std::endl;
      continue;
    }
    else {
      tempHist = (TH1F*)tempFile->Get(fn); tempHist->SetDirectory(m_histoDir);
      m_FF_hist[fn] = tempHist;
      tempHist = (TH1F*)tempFile->Get(fn+"_up"); tempHist->SetDirectory(m_histoDir);
      m_FF_hist[fn+"_up"] = tempHist;
      tempHist = (TH1F*)tempFile->Get(fn+"_down"); tempHist->SetDirectory(m_histoDir);
      m_FF_hist[fn+"_down"] = tempHist;
      std::cout << "INFO: find LFF " << fn << std::endl;
    }
    tempFile->Close(); delete tempFile; tempFile = 0;
  }
}

//______________________________________________________________________________________________

const TString& ptReweight::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool ptReweight::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void ptReweight::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool ptReweight::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void ptReweight::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString ptReweight::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool ptReweight::initializeSelf(){
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
  this->lep_0_pt                = new TTreeFormula( "lep_0_pt",     "lep_0_p4.Pt()",      this->fTree);
  this->lephad_met_lep1_cos_dphi= new TTreeFormula( "lephad_met_lep1_cos_dphi", "lephad_met_lep1_cos_dphi", this->fTree);
  this->lep_0                   = new TTreeFormula( "lep_0",    "lep_0",      this->fTree);
  this->n_bjets                 = new TTreeFormula( "n_bjets",  "n_bjets",      this->fTree);
  return true;
}

//______________________________________________________________________________________________

bool ptReweight::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete this->lep_0;
  delete this->tau_0_phi;
  delete this->tau_0_pt;
  delete this->lep_0_pt;
  delete this->tau_0_n_charged_tracks;
  delete this->lephad_met_lep1_cos_dphi;
  delete this->n_bjets;

  return true;
}
