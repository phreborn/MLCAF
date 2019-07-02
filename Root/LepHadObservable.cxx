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

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("tau_0_pt"));
  bnames->Add(new TObjString("lep_0_pt"));
  bnames->Add(new TObjString("tau_0_phi"));
  bnames->Add(new TObjString("lep_0_phi"));
  bnames->Add(new TObjString("lephad_mt_lep0_met"));
  bnames->Add(new TObjString("lephad_mt_lep1_met"));
  bnames->Add(new TObjString("lephad_dphi"));
  bnames->Add(new TObjString("met_reco_ety"));
  bnames->Add(new TObjString("met_reco_etx"));
  bnames->Add(new TObjString("n_muons"));
  bnames->Add(new TObjString("n_electrons"));
  bnames->Add(new TObjString("lep_0"));
  bnames->Add(new TObjString("lep_0_iso_Gradient"));
  bnames->Add(new TObjString("lep_0_iso_FCTightTrackOnly"));
  bnames->Add(new TObjString("lep_0_iso_FCTight_FixedRad"));

  if (isData()) {
    bnames->Add(new TObjString("run_number"));
  } else {
    //bnames->Add(new TObjString("PRW_DATASF_1up_pileup_random_run_number"));
    //bnames->Add(new TObjString("PRW_DATASF_1down_pileup_random_run_number"));
    bnames->Add(new TObjString("NOMINAL_pileup_random_run_number"));
  }

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

bool LepHadObservable::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void LepHadObservable::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString LepHadObservable::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________
bool LepHadObservable::isSherpa() const {
  return false;//_isSherpa;
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
bool LepHadObservable::isFake() const {
  return false;//_isFake;
}

//______________________________________________________________________________________________
bool LepHadObservable::is2015() const {
 // if (!_use2015) { return false; }

  long xrn = x_run_number->EvalInstance();
  return xrn <= LIMIT_2015 && xrn > 0;
}

//______________________________________________________________________________________________
bool LepHadObservable::is2016() const {
  //if (!_use2016) { return false; }

  long xrn = x_run_number->EvalInstance();
  return xrn > LIMIT_2015 && xrn <= LIMIT_2016;
}

//______________________________________________________________________________________________
bool LepHadObservable::is2017() const {
  //if (!_use2017) { return false; }

  long xrn = x_run_number->EvalInstance();
  return xrn > LIMIT_2016 && xrn <= LIMIT_2017;
}

//______________________________________________________________________________________________
bool LepHadObservable::is2018() const {
  //if (!_use2018) { return false; }

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
bool LepHadObservable::isTLT() const {
 // if (!_useTLT) { return false; }

  //if (!(tau_0_pt->EvalInstance() > 30.
  //    && jet_0_pt->EvalInstance() > 70.
  //    && fabs(jet_0_eta->EvalInstance()) < 3.2)) {
  //  return false;
  //}
//
  //if (isMuon()) {
  //  if (is2015()) {
  //    return (lep_0_pt->EvalInstance() > 14.7 && lep_0_pt->EvalInstance() < 21.);
  //  } else if (is2016()) {
  //    return (lep_0_pt->EvalInstance() > 14.7 && lep_0_pt->EvalInstance() < 25.2);
  //  }
  //} else if (isElectron()) {
  //  return (lep_0_pt->EvalInstance() > 18. && lep_0_pt->EvalInstance() < 25.);
  //}

  // at the moment in BSM H-tautau LepHad analysis it's never tau lepton trigger:
  return false;
}

bool LepHadObservable::isTauID() const {
  return tau_0_jet_bdt_medium->EvalInstance()==1;

}

bool LepHadObservable::isLepISO() const {
//  return ((lep_0->EvalInstance()==2 && lep_0_iso_Gradient->EvalInstance()==1)
//            || (lep_0->EvalInstance()==1 && ( (lep_0_pt->EvalInstance()<50. && lep_0_iso_FCTightTrackOnly->EvalInstance()==1) || (lep_0_pt->EvalInstance()>=50. && lep_0_iso_FCTight->EvalInstance()==1) )));
  return ( (lep_0->EvalInstance()==2 && lep_0_iso_Gradient->EvalInstance()==1)
            || (lep_0->EvalInstance()==1 && lep_0_iso_FCTight_FixedRad->EvalInstance()==1) );

}

//______________________________________________________________________________________________
bool LepHadObservable::isSLT() const {
  //if (!_useSLT) { return false; }
/*
  if (isMuon()) {
    if (is2015()) {
      return lep_0_pt->EvalInstance() > 21.;
    } else if (is2016()) {
      return lep_0_pt->EvalInstance() > 25.2;
    }
  } else if (isElectron()) {
    return lep_0_pt->EvalInstance() > 25.;
  }
*/

  // at the moment in BSM H-tautau LepHad analysis it's always single lepton trigger:
  return true;
}

//______________________________________________________________________________________________
bool LepHadObservable::isHighPt() const {

  if(lep_0_pt->EvalInstance() > 55) return true;
  else return false;

}

//______________________________________________________________________________________________
bool LepHadObservable::isHighPt2() const {

  if(lep_0_pt->EvalInstance() >= 50.) return true;
  else return false;

}

//______________________________________________________________________________________________
bool LepHadObservable::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }
/*
  if (!this->fSample->getTag("~isFailID", _isFake)) {
    ERROR("tag isFailID missing");
    return false;
  }*/
  if (!this->fSample->getTag("~isData", _isData)) {
    ERROR("tag isData missing");
    return false;
  }
/*
  if (!this->fSample->getTag("~isSherpa", _isSherpa)) {
    ERROR("tag isSherpa missing");
    return false;
  }

  if (!this->fSample->getTag("~use2016", _use2016)) {
    WARN("tag use2016 missing, will use 2016 by default.");
  }

  if (!this->fSample->getTag("~use2015", _use2015)) {
    WARN("tag use2015 missing, will use 2015 by default.");
  }

  if (!this->fSample->getTag("~useSLT", _useSLT)) {
    WARN("tag useSLT missing, will use SLT by default.");
  }

  if (!this->fSample->getTag("~useTLT", _useTLT)) {
    WARN("tag useTLT missing, will use TLT by default.");
  }
*/
  //if (!this->fSample->getTag("~weightvariation", _weightvariation)) {
  //  ERROR("tag weightvariation missing.");
  //  return false;
  //}
/*
  _pileup_low = _weightvariation == "pu_prw_low";
  _pileup_high = _weightvariation == "pu_prw_high";
  _pileup = _pileup_low || _pileup_high;
*/
  // if (isData()) {
  //   INFO("this is data");
  // } else {
  //   INFO("this is MC");
  // }

  // if (isFake()) {
  //   INFO("this is fake");
  // } else {
  //   INFO("this is non-fake");
  // }


  this->tau_0_pt = new TTreeFormula( "tau_0_pt", "tau_0_p4.Pt()", this->fTree);
  this->tau_0_jet_bdt_medium = new TTreeFormula( "tau_0_jet_bdt_medium", "tau_0_jet_bdt_medium", this->fTree);
  //this->jet_0_pt = new TTreeFormula( "jet_0_pt", "jet_0_pt", this->fTree);
  //this->jet_0_eta = new TTreeFormula( "jet_0_eta", "jet_0_eta", this->fTree);
  this->lep_0_pt = new TTreeFormula( "lep_0_pt", "lep_0_p4.Pt()", this->fTree);


  this->tau_0_phi = new TTreeFormula( "tau_0_phi", "tau_0_p4.Phi()", this->fTree);
  this->lep_0_phi = new TTreeFormula( "lep_0_phi", "lep_0_p4.Phi()", this->fTree);
  this->met_reco_ety = new TTreeFormula( "met_reco_ety", "met_reco_p4.Px()", this->fTree);
  this->met_reco_etx = new TTreeFormula( "met_reco_etx", "met_reco_p4.Py()", this->fTree);

  this->lephad_mt_lep0_met = new TTreeFormula( "lephad_mt_lep0_met", "lephad_mt_lep0_met", this->fTree);
  this->lephad_mt_lep1_met = new TTreeFormula( "lephad_mt_lep1_met", "lephad_mt_lep1_met", this->fTree);
  this->lephad_dphi = new TTreeFormula( "lephad_dphi", "lephad_dphi", this->fTree);

  this->n_muons = new TTreeFormula( "n_muons", "n_muons", this->fTree);
  this->n_electrons = new TTreeFormula( "n_electrons", "n_electrons", this->fTree);
  this->lep_0 = new TTreeFormula( "lep_0", "lep_0", this->fTree);
  this->lep_0_iso_Gradient = new TTreeFormula( "lep_0_iso_Gradient", "lep_0_iso_Gradient", this->fTree);
  this->lep_0_iso_FCTightTrackOnly = new TTreeFormula( "lep_0_iso_FCTightTrackOnly", "lep_0_iso_FCTightTrackOnly", this->fTree);
  this->lep_0_iso_FCTight_FixedRad = new TTreeFormula( "lep_0_iso_FCTight_FixedRad", "lep_0_iso_FCTight_FixedRad", this->fTree);

  if (this->fTree->FindLeaf("NOMINAL_pileup_random_run_number")) this->x_run_number = new TTreeFormula("NOMINAL_pileup_random_run_number", "NOMINAL_pileup_random_run_number", this->fTree);
  else                                                           this->x_run_number = new TTreeFormula("run_number", "run_number", this->fTree);
  //} else {
  //// if (_pileup_high) {
  ////   this->x_run_number = new TTreeFormula("PRW_DATASF_1up_pileup_random_run_number", "PRW_DATASF_1up_pileup_random_run_number", this->fTree);
  //// } else if (_pileup_low) {
  ////   this->x_run_number = new TTreeFormula("PRW_DATASF_1down_pileup_random_run_number", "PRW_DATASF_1down_pileup_random_run_number", this->fTree);
  //// } else {
  //    this->x_run_number = new TTreeFormula("NOMINAL_pileup_random_run_number", "NOMINAL_pileup_random_run_number", this->fTree);
//
  //}

  return true;
}

//______________________________________________________________________________________________

bool LepHadObservable::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete this->n_muons;
  delete this->n_electrons;
  delete this->lep_0;
  delete this->lep_0_iso_Gradient;
  delete this->lep_0_iso_FCTightTrackOnly;
  delete this->lep_0_iso_FCTight_FixedRad;
  delete this->lephad_mt_lep0_met;
  delete this->lephad_mt_lep1_met;
  delete this->lephad_dphi;
  delete this->tau_0_jet_bdt_medium;
  delete this->tau_0_pt;
  delete this->lep_0_pt;
  delete this->tau_0_phi;
  delete this->lep_0_phi;
  delete this->met_reco_etx;
  delete this->met_reco_ety;
  delete this->x_run_number;

  return true;
}
