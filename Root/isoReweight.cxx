#include "BSMtautauCAF/isoReweight.h"
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

ClassImp(isoReweight)

//______________________________________________________________________________________________

isoReweight::isoReweight(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

isoReweight::~isoReweight(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* isoReweight::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();
  //bnames->SetOwner(true);
  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("lep_0"));
  bnames->Add(new TObjString("lep_0_eta"));
  bnames->Add(new TObjString("lep_0_phi"));
  bnames->Add(new TObjString("lep_0_pt"));
  bnames->Add(new TObjString("n_bjets"));
  bnames->Add(new TObjString("lephad_met_lep0_cos_dphi"));

  if (isData()) {
    bnames->Add(new TObjString("run_number"));
  } else {
    bnames->Add(new TObjString("NOMINAL_pileup_random_run_number"));
  }


  return bnames;
}

//______________________________________________________________________________________________
double isoReweight::getValue() const {
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
  double f_lep_0_phi      = this->lep_0_phi->EvalInstance();
  int    f_lep_0          = this->lep_0->EvalInstance();
  float  f_lep_0_eta      = this->lep_0_eta->EvalInstance();
  float  f_lep_0_pt       = this->lep_0_pt->EvalInstance();
  int    f_n_bjets        = this->n_bjets->EvalInstance();
  float  f_lephad_met_lep0_cos_dphi= this->lephad_met_lep0_cos_dphi->EvalInstance();

  // fake factor valid range up to 300
  if (f_lep_0_pt>=300) f_lep_0_pt=299;
  // determine which FF to use
  // period + channel + category + variable + FF
  // period (LFR1516, LFR17, LFR18, LFRAll)
  // channel (ehad, muhad, lephad)
  // category (Bveto, Btag)
  // variable (LeptonPt, LeptonPtDphi?)
  TString FF = "";   // FF name
  TH1F * h_nominal = 0;
  TH1F * h_up = 0;
  TH1F * h_down = 0;

  // peiriod
  TString period_tag = "";
  if(!this->fSample->getTag("~LFFPeriod",period_tag)) std::cout<<"ERROR: Why cant I get ff name!!!\n";

  if (period_tag == "Separated") {
    if(this->x_run_number->EvalInstance() <= LIMIT_2016) FF = "LFR1516";
    else if(this->x_run_number->EvalInstance() > LIMIT_2016 && this->x_run_number->EvalInstance() <= LIMIT_2017) FF = "LFR17";
    else if(this->x_run_number->EvalInstance() > LIMIT_2017 && this->x_run_number->EvalInstance() <= LIMIT_2018) FF = "LFR18";
    else std::cout << "ERROR: srange run number " << this->x_run_number->EvalInstance() << std::endl; 
  }
  else if (period_tag == "Combined")
    FF = "LFRAll";

  // channel
  if ( 1 == f_lep_0) FF += "muhad";
  else if (2 == f_lep_0) FF += "ehad";
  else std::cout << "ERROR: unknown lepton flavor" << std::endl;

  // category 
  if ( 0 == f_n_bjets) FF += "Bveto";
  else if (1 <= f_n_bjets) FF += "Btag";
  else std::cout << "ERROR: strange #bjets";

  // parameterization
  TString param_tag = "";
  if(!this->fSample->getTag("~LFFParam",param_tag)) std::cout<<"ERROR: Why cant I get ff name!!!\n";
  if ( "LeptonPt" == param_tag ) {
    FF += "LeptonPtFF";
  }
  else if ( "LeptonPtDphi" == param_tag) {
    // dphi 1,2,3,4 in bveto category
    if (0 == f_n_bjets) {
      if (f_lephad_met_lep0_cos_dphi<0.5) FF += "LeptonPtDphi1FF";
      else if (f_lephad_met_lep0_cos_dphi>=0.5&&f_lephad_met_lep0_cos_dphi<1) FF += "LeptonPtDphi2FF";
      else if (f_lephad_met_lep0_cos_dphi>=1&&f_lephad_met_lep0_cos_dphi<2) FF += "LeptonPtDphi3FF";
      else if (f_lephad_met_lep0_cos_dphi>=2) FF += "LeptonPtDphi4FF";
    }
    // dphi 1,2,3 in btag category
    else if (1 <= f_n_bjets) {
      if (f_lephad_met_lep0_cos_dphi<0.5) FF += "LeptonPtDphi1FF";
      else if (f_lephad_met_lep0_cos_dphi>=0.5&&f_lephad_met_lep0_cos_dphi<1) FF += "LeptonPtDphi2FF";
      else if (f_lephad_met_lep0_cos_dphi>=1) FF += "LeptonPtDphi3FF";
    }
  }

  h_nominal = m_FF_hist.at(FF);
  h_up = m_FF_hist.at(FF+"_up");
  h_down = m_FF_hist.at(FF+"_down");
  
  // FF is a function of lepton pT
  float retval = h_nominal->GetBinContent(h_nominal->FindBin(f_lep_0_pt));
  float retval_up = h_up->GetBinContent(h_up->FindBin(f_lep_0_pt));
  float retval_down = h_down->GetBinContent(h_down->FindBin(f_lep_0_pt));
  float retval_error = fabs(retval_up - retval_down)/2.0;

  // systematic uncertainty
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

  DEBUGclass("returning");

  return retval;
}
//______________________________________________________________________________________________

isoReweight::isoReweight(const TString& expression) : LepHadObservable(expression)
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
  std::cout << "INFO: isoReweight.cxx getting histograms from files. " << std::endl;

  ///////////////////////////////
  //  Lepton FF
  ///////////////////////////////
  std::vector<TString> periods = {"LFR1516", "LFR17", "LFR18", "LFRAll"};
  std::vector<TString> channels = {"ehad", "muhad"};
  
  // list of available FFs
  std::vector<TString> FF_list;
  FF_list.clear();
  FF_list.reserve(256);
  for (auto period : periods) {
    for (auto channel : channels) {
      // 1D LeptonPt
      FF_list.emplace_back(period + channel + "BvetoLeptonPtFF");
      FF_list.emplace_back(period + channel + "BtagLeptonPtFF");
      // 2D LeptonPt Dphi(lep, MET)
      FF_list.emplace_back(period + channel + "BvetoLeptonPtDphi1FF");
      FF_list.emplace_back(period + channel + "BvetoLeptonPtDphi2FF");
      FF_list.emplace_back(period + channel + "BvetoLeptonPtDphi3FF");
      FF_list.emplace_back(period + channel + "BvetoLeptonPtDphi4FF");
      FF_list.emplace_back(period + channel + "BtagLeptonPtDphi1FF");
      FF_list.emplace_back(period + channel + "BtagLeptonPtDphi2FF");
      FF_list.emplace_back(period + channel + "BtagLeptonPtDphi3FF");
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

const TString& isoReweight::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool isoReweight::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void isoReweight::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool isoReweight::initializeSelf(){
  if (!this->fSample->getTag("~isData", _isData)) {
    ERROR("tag isData missing");
    return false;
  }

  if (this->fTree->FindLeaf("NOMINAL_pileup_random_run_number")) this->x_run_number = new TTreeFormula("NOMINAL_pileup_random_run_number", "NOMINAL_pileup_random_run_number", this->fTree);
  else                                                           this->x_run_number = new TTreeFormula("run_number", "run_number", this->fTree);


  this->lep_0_phi      = new TTreeFormula( "lep_0_phi",     "lep_0_p4.Phi()",      this->fTree);
  this->lep_0      = new TTreeFormula( "lep_0",     "lep_0",      this->fTree);
  this->lep_0_eta      = new TTreeFormula( "lep_0_eta",     "lep_0_p4.Eta()",      this->fTree);
  this->lep_0_pt      = new TTreeFormula( "lep_0_pt",     "lep_0_p4.Pt()",      this->fTree);
  this->lephad_met_lep0_cos_dphi      = new TTreeFormula( "lephad_met_lep0_cos_dphi",     "lephad_met_lep0_cos_dphi",      this->fTree);
  this->n_bjets      = new TTreeFormula( "n_bjets",      "n_bjets",      this->fTree);

  return true;
}

//______________________________________________________________________________________________

bool isoReweight::finalizeSelf(){
  delete this->lep_0_phi;
  delete this->lep_0;
  delete this->lep_0_eta;
  delete this->lep_0_pt;
  delete this->lephad_met_lep0_cos_dphi;

  delete this->n_bjets;

  return true;
}
