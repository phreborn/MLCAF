#include "BSMtautauCAF/LepHadObservable.h"

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

LepHadObservable::~LepHadObservable(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* LepHadObservable::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();
  //bnames->SetOwner(true);

  if (isData()) {
    bnames->Add(new TObjString("run_number"));
  } else {
    bnames->Add(new TObjString("NOMINAL_pileup_random_run_number"));
    bnames->Add(new TObjString("mc_channel_number"));
  }
  
  bnames->Add(new TObjString("n_bjets"));
  bnames->Add(new TObjString("n_electrons"));
  bnames->Add(new TObjString("n_muons"));
  
  bnames->Add(new TObjString("lep_0"));
  bnames->Add(new TObjString("lep_0_pt"));
  bnames->Add(new TObjString("lep_0_eta"));
  bnames->Add(new TObjString("lep_0_phi"));
  bnames->Add(new TObjString("lep_0_iso_Gradient"));
  bnames->Add(new TObjString("lep_0_iso_FCTightTrackOnly"));
  bnames->Add(new TObjString("lep_0_iso_FCTight_FixedRad"));
    
  bnames->Add(new TObjString("tau_0_n_charged_tracks"));  
  bnames->Add(new TObjString("tau_0_pt"));
  bnames->Add(new TObjString("tau_0_eta"));
  bnames->Add(new TObjString("tau_0_phi"));
  bnames->Add(new TObjString("tau_0_jet_bdt_medium"));

  bnames->Add(new TObjString("lephad_dphi"));

  bnames->Add(new TObjString("met_reco_et"));
  bnames->Add(new TObjString("met_reco_etx"));
  bnames->Add(new TObjString("met_reco_ety"));

  bnames->Add(new TObjString("lephad_met_lep0_cos_dphi"));
  bnames->Add(new TObjString("lephad_met_lep1_cos_dphi"));
  bnames->Add(new TObjString("lephad_mt_lep0_met"));
  bnames->Add(new TObjString("lephad_mt_lep1_met"));

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
  return _isData;
}

//______________________________________________________________________________________________
bool LepHadObservable::isMC() const {
  return !_isData;
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

bool LepHadObservable::isTauID() const {
  return tau_0_jet_bdt_medium->EvalInstance()==1;

}

bool LepHadObservable::isLepISO() const {
  return ( (lep_0->EvalInstance()==2 && lep_0_iso_Gradient->EvalInstance()==1)
            || (lep_0->EvalInstance()==1 && lep_0_iso_FCTight_FixedRad->EvalInstance()==1) );
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
bool LepHadObservable::initializeSelf(){
  
  if (!this->fSample->getTag("~isData", _isData)) {
    ERROR("tag isData missing");
    return false;
  }

  if (isData())  
    this->x_run_number = new TTreeFormula("run_number", "run_number", this->fTree);
  else {
    this->x_run_number = new TTreeFormula("NOMINAL_pileup_random_run_number", "NOMINAL_pileup_random_run_number", this->fTree);
    this->mc_channel_number = new TTreeFormula("mc_channel_number", "mc_channel_number", this->fTree);
  }

  this->n_bjets = new TTreeFormula( "n_bjets", "n_bjets", this->fTree);
  this->n_muons = new TTreeFormula( "n_muons", "n_muons", this->fTree);
  this->n_electrons = new TTreeFormula( "n_electrons", "n_electrons", this->fTree);
  
  this->lep_0 = new TTreeFormula( "lep_0", "lep_0", this->fTree);
  this->lep_0_pt = new TTreeFormula( "lep_0_pt", "lep_0_p4.Pt()", this->fTree);
  this->lep_0_eta = new TTreeFormula( "lep_0_eta", "lep_0_p4.Eta()", this->fTree);
  this->lep_0_phi = new TTreeFormula( "lep_0_phi", "lep_0_p4.Phi()", this->fTree);
  this->lep_0_iso_Gradient = new TTreeFormula( "lep_0_iso_Gradient", "lep_0_iso_Gradient", this->fTree);
  this->lep_0_iso_FCTightTrackOnly = new TTreeFormula( "lep_0_iso_FCTightTrackOnly", "lep_0_iso_FCTightTrackOnly", this->fTree);
  this->lep_0_iso_FCTight_FixedRad = new TTreeFormula( "lep_0_iso_FCTight_FixedRad", "lep_0_iso_FCTight_FixedRad", this->fTree);
 
  this->tau_0_n_charged_tracks = new TTreeFormula( "tau_0_n_charged_tracks", "tau_0_n_charged_tracks", this->fTree); 
  this->tau_0_pt = new TTreeFormula( "tau_0_pt", "tau_0_p4.Pt()", this->fTree);
  this->tau_0_eta = new TTreeFormula( "tau_0_eta", "tau_0_p4.Eta()", this->fTree);
  this->tau_0_phi = new TTreeFormula( "tau_0_phi", "tau_0_p4.Phi()", this->fTree);
  this->tau_0_jet_bdt_medium = new TTreeFormula( "tau_0_jet_bdt_medium", "tau_0_jet_bdt_medium", this->fTree);
  
  this->lephad_dphi = new TTreeFormula( "lephad_dphi", "lephad_dphi", this->fTree);

  this->met_reco_et = new TTreeFormula( "met_reco_et", "met_reco_p4.Pt()", this->fTree);
  this->met_reco_etx = new TTreeFormula( "met_reco_etx", "met_reco_p4.Px()", this->fTree);
  this->met_reco_ety = new TTreeFormula( "met_reco_ety", "met_reco_p4.Py()", this->fTree);

  this->lephad_mt_lep0_met = new TTreeFormula( "lephad_mt_lep0_met", "lephad_mt_lep0_met", this->fTree);
  this->lephad_mt_lep1_met = new TTreeFormula( "lephad_mt_lep1_met", "lephad_mt_lep1_met", this->fTree);
  this->lephad_met_lep0_cos_dphi = new TTreeFormula( "lephad_met_lep0_cos_dphi", "lephad_met_lep0_cos_dphi", this->fTree);
  this->lephad_met_lep1_cos_dphi = new TTreeFormula( "lephad_met_lep1_cos_dphi", "lephad_met_lep1_cos_dphi", this->fTree);

  return true;
}

//______________________________________________________________________________________________

bool LepHadObservable::finalizeSelf(){
  delete this->x_run_number;
  delete this->mc_channel_number;
    
  delete this->n_bjets;  
  delete this->n_muons;
  delete this->n_electrons;
  
  delete this->lep_0;
  delete this->lep_0_pt;
  delete this->lep_0_eta;
  delete this->lep_0_phi;
  delete this->lep_0_iso_Gradient;
  delete this->lep_0_iso_FCTightTrackOnly;
  delete this->lep_0_iso_FCTight_FixedRad;
  
  delete this->tau_0_n_charged_tracks;
  delete this->tau_0_pt;
  delete this->tau_0_eta;
  delete this->tau_0_phi;
  delete this->tau_0_jet_bdt_medium;
  
  delete this->lephad_dphi;
  
  delete this->met_reco_et;
  delete this->met_reco_etx;
  delete this->met_reco_ety;
  
  delete this->lephad_mt_lep0_met;
  delete this->lephad_mt_lep1_met;
  delete this->lephad_met_lep0_cos_dphi;
  delete this->lephad_met_lep1_cos_dphi;
  
  return true;
}
