#include "BSMtautauCAF/LepHadObservable.h"
#include "TObjString.h"

// uncomment the following line to enable debug printouts
//#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);


// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

// ClassImp(LepHadObservable)

//______________________________________________________________________________________________

LepHadObservable::LepHadObservable(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}


//______________________________________________________________________________________________

TObjArray* LepHadObservable::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();
  //bnames->SetOwner(true);
  
  bnames->Add(new TObjString("n_bjets"));
  bnames->Add(new TObjString("lep_0_iso_electron"));
  bnames->Add(new TObjString("lep_0_iso_muon"));
  bnames->Add(new TObjString("tau_0_jet_id"));

  if (isData()) {
    bnames->Add(new TObjString("run_number"));
  } else {
    bnames->Add(new TObjString("NOMINAL_pileup_random_run_number"));
    bnames->Add(new TObjString("mc_channel_number"));
  }
  
  bnames->Add(new TObjString("n_electrons"));
  bnames->Add(new TObjString("n_muons"));
  bnames->Add(new TObjString("lep_0"));
  bnames->Add(new TObjString("lep_0_pt"));
  bnames->Add(new TObjString("lep_0_eta"));
  bnames->Add(new TObjString("lep_0_phi"));
  bnames->Add(new TObjString("tau_0_n_charged_tracks"));  
  bnames->Add(new TObjString("tau_0_pt"));
  bnames->Add(new TObjString("tau_0_eta"));
  bnames->Add(new TObjString("tau_0_phi"));
  bnames->Add(new TObjString("lephad_qxq"));
  bnames->Add(new TObjString("jet_0_pt"));
  bnames->Add(new TObjString("lephad_dphi"));
  bnames->Add(new TObjString("met_reco_et"));
  bnames->Add(new TObjString("met_reco_etx"));
  bnames->Add(new TObjString("met_reco_ety"));
  bnames->Add(new TObjString("met_reco_phi"));
  bnames->Add(new TObjString("lephad_met_lep0_cos_dphi"));
  bnames->Add(new TObjString("lephad_met_lep1_cos_dphi"));
  bnames->Add(new TObjString("lephad_mt_lep0_met"));
  bnames->Add(new TObjString("lephad_mt_lep1_met"));
  bnames->Add(new TObjString("bjet_0_pt"));
  bnames->Add(new TObjString("jets_scalar_sum_pt"));

  return bnames;
}

//______________________________________________________________________________________________

LepHadObservable::LepHadObservable(const TString& expression): TQTreeObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);
}

//______________________________________________________________________________________________

const TString& LepHadObservable::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool LepHadObservable::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void LepHadObservable::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}

//______________________________________________________________________________________________
bool LepHadObservable::isData() const {
  return m_isData;
}

//______________________________________________________________________________________________
bool LepHadObservable::isMC() const {
  return !m_isData;
}
//______________________________________________________________________________________________
bool LepHadObservable::is2015() const {
  long xrn = x_run_number->EvalInstance();
  return xrn <= LIMIT_2015 && xrn > 0;
}

//______________________________________________________________________________________________
bool LepHadObservable::is2016() const {
  long xrn = x_run_number->EvalInstance();
  return xrn > LIMIT_2015 && xrn <= LIMIT_2016;
}

//______________________________________________________________________________________________
bool LepHadObservable::is2017() const {
  long xrn = x_run_number->EvalInstance();
  return xrn > LIMIT_2016 && xrn <= LIMIT_2017;
}

//______________________________________________________________________________________________
bool LepHadObservable::is2018() const {
  long xrn = x_run_number->EvalInstance();
  return xrn > LIMIT_2017 && xrn <= LIMIT_2018;
}

//______________________________________________________________________________________________
bool LepHadObservable::isMuon() const {
  return lep_0->EvalInstance()==1;
}

//______________________________________________________________________________________________
bool LepHadObservable::isElectron() const {
  return lep_0->EvalInstance()==2;
}

//______________________________________________________________________________________________
bool LepHadObservable::isTTBar() const {
  return m_isTTBar;
}
//______________________________________________________________________________________________
bool LepHadObservable::isSTop() const {
  return m_isSTop;
}


unsigned int LepHadObservable::bjetCount() const {
  return n_bjets->EvalInstance();
}


bool LepHadObservable::isTauID() const {
  return tau_0_jet_id->EvalInstance()==1;

}

bool LepHadObservable::isLepISO() const {
  return ( (lep_0->EvalInstance()==2 && lep_0_iso_electron->EvalInstance()==1)
            || (lep_0->EvalInstance()==1 && lep_0_iso_muon->EvalInstance()==1) );
}

//______________________________________________________________________________________________
bool LepHadObservable::isSLT() const {
  return true;
}

//______________________________________________________________________________________________
bool LepHadObservable::isHighPt() const {

  if(lep_0_pt->EvalInstance() > 55) return true;
  else return false;

}

//______________________________________________________________________________________________
float LepHadObservable::TransverseMass(float pt1, float pt2, float dphi) const{
  float MT = std::sqrt( 2. * pt1 * pt2 * ( 1 - cos(dphi) ) );
  return MT;
} 

//______________________________________________________________________________________________
bool LepHadObservable::initializeSelf(){
   
  std::shared_ptr<TQTaggable> masterConfig = TQTaggable::getGlobalTaggable("master");
  m_verbose = masterConfig->getTagBoolDefault("LepHadObservable.verbose", false);

  if (!this->fSample->getTag("~isData", m_isData)) {
    ERROR("tag isData missing");
    return false;
  }
  
  if (!this->fSample->getTag("~isTTBar", m_isTTBar)) {
    ERROR("tag isTTBar missing");
    return false;
  }
  
  if (!this->fSample->getTag("~isSTop", m_isSTop)) {
    ERROR("tag isSTop missing");
    return false;
  }
  
  // variables depending on the configuration
  // -- btagging
  TString btaggingWP = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("BtaggingWP", btaggingWP) ) {
    ERRORclass("BtaggingWP not set !!! ");
  }
  if (btaggingWP == "MV2c10") { // temp fix for old samples
    this->n_bjets = new TTreeFormula( "n_bjets", "n_bjets", this->fTree);
  }
  else {
    this->n_bjets = new TTreeFormula( "n_bjets", "n_bjets_" + btaggingWP, this->fTree);
  }

  // -- electron isolation
  TString eleIsoWP = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("ElectronIsoWP", eleIsoWP) ) {
    ERRORclass("ElectronIsoWP not set !!!");
  }
  this->lep_0_iso_electron = new TTreeFormula( "lep_0_iso_electron", "lep_0_iso_" + eleIsoWP, this->fTree);
 
  // -- muon isolation 
  TString muonIsoWP = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("MuonIsoWP", muonIsoWP) ) {
    ERRORclass("MuonIsoWP not set !!!");
  }
  this->lep_0_iso_muon = new TTreeFormula( "lep_0_iso_muon", "lep_0_iso_" + muonIsoWP, this->fTree);
  
  // -- tau ID
  TString tauIDWP = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("TauIDWP", tauIDWP) ) {
    ERRORclass("TauIDWP not set !!! ");
  }
  this->tau_0_jet_id = new TTreeFormula( "tau_0_jet_id", "tau_0_jet_" + tauIDWP, this->fTree);

  // variables only available in MC
  if (isData())  
    this->x_run_number = new TTreeFormula("run_number", "run_number", this->fTree);
  else {
    this->x_run_number = new TTreeFormula("NOMINAL_pileup_random_run_number", "NOMINAL_pileup_random_run_number", this->fTree);
    this->mc_channel_number = new TTreeFormula("mc_channel_number", "mc_channel_number", this->fTree);
  }

  // other variables
  this->n_muons = new TTreeFormula("n_muons", "n_muons", this->fTree);
  this->n_electrons = new TTreeFormula("n_electrons", "n_electrons", this->fTree);
  this->lep_0 = new TTreeFormula("lep_0", "lep_0", this->fTree);
  this->lep_0_pt = new TTreeFormula("lep_0_pt", "lep_0_p4.Pt()", this->fTree);
  this->lep_0_eta = new TTreeFormula("lep_0_eta", "lep_0_p4.Eta()", this->fTree);
  this->lep_0_phi = new TTreeFormula("lep_0_phi", "lep_0_p4.Phi()", this->fTree);
  this->tau_0_n_charged_tracks = new TTreeFormula("tau_0_n_charged_tracks", "tau_0_n_charged_tracks", this->fTree); 
  this->tau_0_pt = new TTreeFormula("tau_0_pt", "tau_0_p4.Pt()", this->fTree);
  this->tau_0_eta = new TTreeFormula("tau_0_eta", "tau_0_p4.Eta()", this->fTree);
  this->tau_0_phi = new TTreeFormula("tau_0_phi", "tau_0_p4.Phi()", this->fTree);
  this->lephad_qxq = new TTreeFormula("lephad_qxq", "lephad_qxq", this->fTree);
  this->jet_0_pt = new TTreeFormula("jet_0_pt", "jet_0_p4.Pt()", this->fTree);
  this->bjet_0_pt = new TTreeFormula("bjet_0_pt", "bjet_0_p4.Pt()", this->fTree);
  this->jets_scalar_sum_pt = new TTreeFormula("jets_scalar_sum_pt", "jets_scalar_sum_pt", this->fTree);
  this->lephad_dphi = new TTreeFormula("lephad_dphi", "lephad_dphi", this->fTree);
  this->met_reco_et = new TTreeFormula("met_reco_et", "met_reco_p4.Pt()", this->fTree);
  this->met_reco_etx = new TTreeFormula("met_reco_etx", "met_reco_p4.Px()", this->fTree);
  this->met_reco_ety = new TTreeFormula("met_reco_ety", "met_reco_p4.Py()", this->fTree);
  this->met_reco_phi = new TTreeFormula("met_reco_phi", "met_reco_p4.Phi()", this->fTree);
  this->lephad_mt_lep0_met = new TTreeFormula("lephad_mt_lep0_met", "lephad_mt_lep0_met", this->fTree);
  this->lephad_mt_lep1_met = new TTreeFormula("lephad_mt_lep1_met", "lephad_mt_lep1_met", this->fTree);
  this->lephad_met_lep0_cos_dphi = new TTreeFormula("lephad_met_lep0_cos_dphi", "lephad_met_lep0_cos_dphi", this->fTree);
  this->lephad_met_lep1_cos_dphi = new TTreeFormula("lephad_met_lep1_cos_dphi", "lephad_met_lep1_cos_dphi", this->fTree);

  return true;
}

//______________________________________________________________________________________________

bool LepHadObservable::finalizeSelf(){
  
  delete this->n_bjets;  
  delete this->lep_0_iso_electron;
  delete this->lep_0_iso_muon;
  delete this->tau_0_jet_id;
  
  delete this->x_run_number;
  delete this->mc_channel_number;
  
  delete this->n_muons;
  delete this->n_electrons;
  delete this->lep_0;
  delete this->lep_0_pt;
  delete this->lep_0_eta;
  delete this->lep_0_phi;
  delete this->tau_0_n_charged_tracks;
  delete this->tau_0_pt;
  delete this->tau_0_eta;
  delete this->tau_0_phi;
  delete this->lephad_qxq;
  delete this->jet_0_pt;
  delete this->jets_scalar_sum_pt;
  delete this->lephad_dphi;
  delete this->met_reco_et;
  delete this->met_reco_etx;
  delete this->met_reco_ety;
  delete this->met_reco_phi;
  delete this->lephad_mt_lep0_met;
  delete this->lephad_mt_lep1_met;
  delete this->lephad_met_lep0_cos_dphi;
  delete this->lephad_met_lep1_cos_dphi;
  
  return true;
}
