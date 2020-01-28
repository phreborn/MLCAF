#include "BSMtautauCAF/LPXKfactor.h"
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

ClassImp(LPXKfactor)

//______________________________________________________________________________________________

LPXKfactor::LPXKfactor(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

LPXKfactor::~LPXKfactor(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* LPXKfactor::getBranchNames() const {
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
    bnames->Add(new TObjString("mc_channel_number"));
  }

  return bnames;
}

//______________________________________________________________________________________________
double LPXKfactor::getValue() const {
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
  //std::cout << "In LPXKfactoor::getValue" << std::endl;
  if (0==m_SF_graph.size()) return 1.0;
  if (isData()) return 1.0;
  
  int f_mc_channel_number = this->mc_channel_number->EvalInstance();
  // determine which SF to use
  TString SF = "";   // SF name
  TString Sample = "";
  if ( (f_mc_channel_number>=301000 && f_mc_channel_number<=301018) || f_mc_channel_number == 361106 )
     Sample = "DYee";
  else if ( (f_mc_channel_number>=301020 && f_mc_channel_number<=301038) || f_mc_channel_number == 361107 )
     Sample = "DYmumu";
  else if ( (f_mc_channel_number>=301040 && f_mc_channel_number<=301058) || f_mc_channel_number == 361108 )
     Sample = "DYtautau"; 
  else 
     return 1.0;

  SF = Sample;
  // obtain the graph
  TGraphAsymmErrors* graph_nominal = 0;
  graph_nominal = m_SF_graph.at(SF+"_LPX_kFactors");

  // determine the bin
  int bin = -1;
  std::map<int, int>::const_iterator it;
  it = m_DSID_bin.find(f_mc_channel_number);
  
  if (it == m_DSID_bin.end()) 
  {
    std::cout << "Error! Unknown DSID!" << std::endl;
    return 1.0;
  }
  else bin = it->second;
  
  double retval = 1.0;
  double _x = 0.0;
  graph_nominal ->GetPoint(bin, _x, retval);

  ////////////////
  // SYSTEMATICS
  ////////////////
  TGraphAsymmErrors* graph_sys = 0;
  double relsys = 1.0;
  if ( fSysName.Contains("LPX_KFACTOR_CHOICE_HERAPDF20_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_CHOICE_HERAPDF20__1cont");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_CHOICE_HERAPDF20_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_CHOICE_HERAPDF20__1cont");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= (2-relsys);
  }
  else if ( fSysName.Contains("LPX_KFACTOR_CHOICE_NNPDF30_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_CHOICE_NNPDF30__1cont");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_CHOICE_NNPDF30_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_CHOICE_NNPDF30__1cont");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= (2-relsys);
  }
  else if ( fSysName.Contains("LPX_KFACTOR_CHOICE_epWZ16_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_CHOICE_epWZ16__1cont");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_CHOICE_epWZ16_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_CHOICE_epWZ16__1cont");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= (2-relsys);
  }
  else if ( fSysName.Contains("LPX_KFACTOR_REDCHOICE_NNPDF30_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_REDCHOICE_NNPDF30__1cont");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_REDCHOICE_NNPDF30_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_REDCHOICE_NNPDF30__1cont");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= (2-relsys);
  }
  else if ( fSysName.Contains("LPX_KFACTOR_ALPHAS_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_ALPHAS__1up");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_ALPHAS_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_ALPHAS__1down");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_BEAM_ENERGY_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_BEAM_ENERGY__1up");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_BEAM_ENERGY_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_BEAM_ENERGY__1down");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_PDF_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_PDF__1up");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_PDF_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_PDF__1down");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_PDF_EW_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_PDF_EW__1up");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_PDF_EW_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_PDF_EW__1down");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_PDF_epWZ16_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_PDF_epWZ16__1up");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_PDF_epWZ16_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_PDF_epWZ16__1down");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_PI_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_PI__1up");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_PI_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_PI__1down");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_SCALE_W_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_SCALE_W__1up");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_SCALE_W_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_SCALE_W__1down");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_SCALE_Z_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_SCALE_Z__1up");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_SCALE_Z_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_SCALE_Z__1down");
    graph_sys -> GetPoint(bin, _x, relsys);
    retval *= relsys;
  }

  DEBUGclass("returning");

  //std::cout << SF << "\t" << f_mc_channel_number << "\t" << _x << "\t" << retval << std::endl;
  return retval;
}
//______________________________________________________________________________________________

LPXKfactor::LPXKfactor(const TString& expression) : LepHadObservable(expression)
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

  //std::cout << "INFO: LPXKfactor.cxx getting histograms from files. " << std::endl;
  std::cout << "INFO: LPXKfactor getting functions " << std::endl;

  ///////////////////////////////
  // LPX kfactor
  ///////////////////////////////
  // first bin is for inclusive sample
  for (int i = 0; i < 19; ++i) {
    m_DSID_bin[301000+i] = i+1;  // DYee
    m_DSID_bin[301020+i] = i+1;  // DYmumu
    m_DSID_bin[301040+i] = i+1;  // DYtautau
  }
  m_DSID_bin[361106] = 0;
  m_DSID_bin[361107] = 0;
  m_DSID_bin[361108] = 0;

  std::vector<TString> SF_list;
  SF_list.clear();
  SF_list.reserve(64);
  SF_list.emplace_back("LPX_kFactors");
  SF_list.emplace_back("LPX_sys_weight_LPX_KFACTOR_CHOICE_HERAPDF20__1cont");
  SF_list.emplace_back("LPX_sys_weight_LPX_KFACTOR_CHOICE_NNPDF30__1cont");
  SF_list.emplace_back("LPX_sys_weight_LPX_KFACTOR_REDCHOICE_NNPDF30__1cont");
  SF_list.emplace_back("LPX_sys_weight_LPX_KFACTOR_CHOICE_epWZ16__1cont");
  SF_list.emplace_back("LPX_sys_weight_LPX_KFACTOR_PDF_EW__1up");
  SF_list.emplace_back("LPX_sys_weight_LPX_KFACTOR_PDF_EW__1down");
  SF_list.emplace_back("LPX_sys_weight_LPX_KFACTOR_ALPHAS__1up");
  SF_list.emplace_back("LPX_sys_weight_LPX_KFACTOR_ALPHAS__1down");
  SF_list.emplace_back("LPX_sys_weight_LPX_KFACTOR_SCALE_W__1up");
  SF_list.emplace_back("LPX_sys_weight_LPX_KFACTOR_SCALE_W__1down");
  SF_list.emplace_back("LPX_sys_weight_LPX_KFACTOR_PI__1up");
  SF_list.emplace_back("LPX_sys_weight_LPX_KFACTOR_PI__1down");
  SF_list.emplace_back("LPX_sys_weight_LPX_KFACTOR_PDF__1up");
  SF_list.emplace_back("LPX_sys_weight_LPX_KFACTOR_PDF__1down");
  SF_list.emplace_back("LPX_sys_weight_LPX_KFACTOR_PDF_epWZ16__1up");
  SF_list.emplace_back("LPX_sys_weight_LPX_KFACTOR_PDF_epWZ16__1down");
  SF_list.emplace_back("LPX_sys_weight_LPX_KFACTOR_SCALE_Z__1up");
  SF_list.emplace_back("LPX_sys_weight_LPX_KFACTOR_SCALE_Z__1down");
  SF_list.emplace_back("LPX_sys_weight_LPX_KFACTOR_BEAM_ENERGY__1up");
  SF_list.emplace_back("LPX_sys_weight_LPX_KFACTOR_BEAM_ENERGY__1down");

  std::vector<TString> Sample_list;
  Sample_list.clear();
  Sample_list.reserve(3);
  Sample_list.emplace_back("DYee");
  Sample_list.emplace_back("DYmumu");
  Sample_list.emplace_back("DYtautau");

  TGraphAsymmErrors* tempGraph = 0;
  for (auto sample : Sample_list) {
    tempFile = TFile::Open("Systematics/LPK_k-Factors_"+sample+".root");
    if (!tempFile) {
      std::cout << "WARNING: can not find SF " << sample << std::endl;
      continue;
    }
    else {
      for (auto SF : SF_list) {
        tempGraph = (TGraphAsymmErrors*)tempFile->Get(SF);
        tempGraph->SetName(sample+"_"+SF);
        m_SF_graph[tempGraph->GetName()] = tempGraph;
        std::cout << "INFO: find SF " << tempGraph->GetName() << std::endl;
      }
      tempFile->Close(); delete tempFile; tempFile = 0;
    }
  }
}
//______________________________________________________________________________________________

const TString& LPXKfactor::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool LPXKfactor::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void LPXKfactor::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool LPXKfactor::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void LPXKfactor::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString LPXKfactor::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool LPXKfactor::initializeSelf(){
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

  if (this->fTree->FindLeaf("mc_channel_number")) this->mc_channel_number = new TTreeFormula( "mc_channel_number", "mc_channel_number", this->fTree);

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

bool LPXKfactor::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

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