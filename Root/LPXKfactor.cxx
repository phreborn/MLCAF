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
  TObjArray* bnames = LepHadObservable::getBranchNames();

  return bnames;
}

//______________________________________________________________________________________________
double LPXKfactor::getValue() const {
  
  if (isData()) return 1.0;
  
  int f_mc_channel_number = this->mc_channel_number->EvalInstance();

  //////////////////////////////////////////////////////////////////////// 
  // determine which LPX Kfactor to use
  //////////////////////////////////////////////////////////////////////// 
  
  TString Sample = "";
  if ( (f_mc_channel_number>=301000 && f_mc_channel_number<=301018) || f_mc_channel_number == 361106 )
     Sample = "DYee";
  else if ( (f_mc_channel_number>=301020 && f_mc_channel_number<=301038) || f_mc_channel_number == 361107 )
     Sample = "DYmumu";
  else if ( (f_mc_channel_number>=301040 && f_mc_channel_number<=301058) || f_mc_channel_number == 361108 )
     Sample = "DYtautau"; 
  else 
     return 1.0;

  // obtain the graph
  TGraphAsymmErrors* graph_nominal = 0;
  graph_nominal = m_SF_graph.at(Sample+"_LPX_kFactors");

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
  double x = 0.0;
  graph_nominal ->GetPoint(bin, x, retval);

  //////////////////////////////////////////////////////////////////////// 
  // SYSTEMATICS
  //////////////////////////////////////////////////////////////////////// 
  
  TGraphAsymmErrors* graph_sys = 0;
  double relsys = 1.0;
  if ( fSysName.Contains("LPX_KFACTOR_CHOICE_HERAPDF20_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_CHOICE_HERAPDF20__1cont");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_CHOICE_HERAPDF20_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_CHOICE_HERAPDF20__1cont");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= (2-relsys);
  }
  else if ( fSysName.Contains("LPX_KFACTOR_CHOICE_NNPDF30_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_CHOICE_NNPDF30__1cont");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_CHOICE_NNPDF30_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_CHOICE_NNPDF30__1cont");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= (2-relsys);
  }
  else if ( fSysName.Contains("LPX_KFACTOR_CHOICE_epWZ16_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_CHOICE_epWZ16__1cont");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_CHOICE_epWZ16_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_CHOICE_epWZ16__1cont");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= (2-relsys);
  }
  else if ( fSysName.Contains("LPX_KFACTOR_REDCHOICE_NNPDF30_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_REDCHOICE_NNPDF30__1cont");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_REDCHOICE_NNPDF30_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_REDCHOICE_NNPDF30__1cont");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= (2-relsys);
  }
  else if ( fSysName.Contains("LPX_KFACTOR_ALPHAS_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_ALPHAS__1up");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_ALPHAS_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_ALPHAS__1down");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_BEAM_ENERGY_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_BEAM_ENERGY__1up");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_BEAM_ENERGY_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_BEAM_ENERGY__1down");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_PDF_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_PDF__1up");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_PDF_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_PDF__1down");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_PDF_EW_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_PDF_EW__1up");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_PDF_EW_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_PDF_EW__1down");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_PDF_epWZ16_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_PDF_epWZ16__1up");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_PDF_epWZ16_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_PDF_epWZ16__1down");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_PI_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_PI__1up");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_PI_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_PI__1down");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_SCALE_W_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_SCALE_W__1up");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_SCALE_W_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_SCALE_W__1down");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_SCALE_Z_Corr_1up")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_SCALE_Z__1up");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= relsys;
  }
  else if ( fSysName.Contains("LPX_KFACTOR_SCALE_Z_Corr_1down")) {
    graph_sys = m_SF_graph.at(Sample+"_LPX_sys_weight_LPX_KFACTOR_SCALE_Z__1down");
    graph_sys -> GetPoint(bin, x, relsys);
    retval *= relsys;
  }

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
  INFOclass("LPXKfactor getting functions...");

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
      std::cout << "ERROR: can not find LPX Kfactor for " << sample << std::endl;
      continue;
    }
    else {
      for (auto SF : SF_list) {
        tempGraph = (TGraphAsymmErrors*)tempFile->Get(SF);
        tempGraph->SetName(sample+"_"+SF);
        m_SF_graph[tempGraph->GetName()] = tempGraph;
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

bool LPXKfactor::initializeSelf(){
  if (!LepHadObservable::initializeSelf()) return false;
  return true;
}

//______________________________________________________________________________________________

bool LPXKfactor::finalizeSelf(){
  if (!LepHadObservable::finalizeSelf()) return false;
  return true;
}
