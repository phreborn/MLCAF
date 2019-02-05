#include "Htautau2015/ScaleFactor_ll_v05.h"
#include <limits>

// uncomment the following line to enable debug printouts
//#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
#include "Htautau2015/EventSelection_leplep_default.h"
#include "Htautau2015/EventSelection_leplep_fake.h"

ClassImp(ScaleFactor_ll_v05)

//______________________________________________________________________________________________

ScaleFactor_ll_v05::ScaleFactor_ll_v05(){
  // default constructor
 
  this->setExpression(this->GetName() );
  
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

ScaleFactor_ll_v05::~ScaleFactor_ll_v05(){
  // default destructor
  DEBUGclass("destructor called");
} 


//______________________________________________________________________________________________

TObjArray* ScaleFactor_ll_v05::getBranchNames() const {
  // retrieve the list of branch names 
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));
  
  bnames->Add(new TObjString("leptons")); 
  bnames->Add(new TObjString("leptons_id_loose"));
  bnames->Add(new TObjString("leptons_id_medium"));
  bnames->Add(new TObjString("leptons_id_tight"));
  bnames->Add(new TObjString("leptons_iso_wp"));

  bnames->Add(new TObjString(muon_ID_effSF_name));
  bnames->Add(new TObjString(muon_ISO_effSF_name));
  bnames->Add(new TObjString(el_Track_effSF_name));
  bnames->Add(new TObjString(el_ID_effSF_name));
  bnames->Add(new TObjString(el_ISO_effSF_name));

  /// ---- to be removed

  // for muons:
  //    ID
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_RecoLoose"));   
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_RecoMedium"));   
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_RecoTight"));   
  //    ISO
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_IsoLoose"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_IsoTight"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_IsoGradientLoose"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_IsoGradient"));

  // for electrons:
  //    ID
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_offline_LooseAndBLayerLLH_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_offline_MediumLLH_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_offline_TightLLH_2015_13TeV_rel20p0_25ns_v04"));
  //    TRACK
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_offline_RecoTrk_2015_13TeV_rel20p0_25ns_v04"));
  //    ISO
  //       for loose ID
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04"));
  //       for medium ID
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04"));
  //       for tight ID
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04"));

  /// end ---- to be removed


  
  return bnames;
}

//______________________________________________________________________________________________

double ScaleFactor_ll_v05::getValue() const {
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

  int idx = 0;

  leptons->GetNdata();
  leptons_id_loose->GetNdata();
  leptons_id_medium->GetNdata();
  leptons_id_tight->GetNdata();
  leptons_iso_wp->GetNdata();
  

  /// ---- to be removed
  leptons_NOMINAL_effSF_RecoLoose->GetNdata();
  leptons_NOMINAL_effSF_RecoMedium->GetNdata();
  leptons_NOMINAL_effSF_RecoTight->GetNdata();
  leptons_NOMINAL_effSF_IsoLoose->GetNdata();
  leptons_NOMINAL_effSF_IsoTight->GetNdata();
  leptons_NOMINAL_effSF_IsoGradientLoose->GetNdata();
  leptons_NOMINAL_effSF_IsoGradient->GetNdata();

  leptons_NOMINAL_effSF_offline_LooseAndBLayerLLH_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  leptons_NOMINAL_effSF_offline_MediumLLH_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  leptons_NOMINAL_effSF_offline_TightLLH_2015_13TeV_rel20p0_25ns_v04->GetNdata();
 
  leptons_NOMINAL_effSF_offline_RecoTrk_2015_13TeV_rel20p0_25ns_v04->GetNdata();

  leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  /// end ---- to be removed

  double SF = 1.;


  int lep = this->leptons->EvalInstance(idx);
  int lep_id_loose  = this->leptons_id_loose->EvalInstance(idx);
  int lep_id_medium = this->leptons_id_medium->EvalInstance(idx);
  int lep_id_tight  = this->leptons_id_tight->EvalInstance(idx);
  int lep_iso_wp        = this->leptons_iso_wp->EvalInstance(idx);
  

  if (lep==1) {
      muon_ID_effSF->GetNdata();
      muon_ISO_effSF->GetNdata();
      SF *= muon_ID_effSF->EvalInstance(idx);
      SF *= muon_ISO_effSF->EvalInstance(idx);
  } else if (lep==2) {
      el_ID_effSF->GetNdata();
      el_ISO_effSF->GetNdata();
      el_Track_effSF->GetNdata();
      SF *= el_ID_effSF->EvalInstance(idx);
      SF *= el_ISO_effSF->EvalInstance(idx);
      SF *= el_Track_effSF->EvalInstance(idx);
  }
  /// ---- to be removed

  // muons:
  double lep_effSF_RecoLoose  = this->leptons_NOMINAL_effSF_RecoLoose->EvalInstance(idx);
  double lep_effSF_RecoMedium = this->leptons_NOMINAL_effSF_RecoMedium->EvalInstance(idx);
  double lep_effSF_RecoTight  = this->leptons_NOMINAL_effSF_RecoTight->EvalInstance(idx);

  double lep_effSF_IsoLoose   = this->leptons_NOMINAL_effSF_IsoLoose->EvalInstance(idx);
  double lep_effSF_IsoTight   = this->leptons_NOMINAL_effSF_IsoTight->EvalInstance(idx);
  double lep_effSF_IsoGradientLoose   = this->leptons_NOMINAL_effSF_IsoGradientLoose->EvalInstance(idx);
  double lep_effSF_IsoGradient   = this->leptons_NOMINAL_effSF_IsoGradient->EvalInstance(idx);
  
  // electrons:
  double lep_effSF_offline_Loose    = this->leptons_NOMINAL_effSF_offline_LooseAndBLayerLLH_2015_13TeV_rel20p0_25ns_v04->EvalInstance(idx);
  double lep_effSF_offline_Medium   = this->leptons_NOMINAL_effSF_offline_MediumLLH_2015_13TeV_rel20p0_25ns_v04->EvalInstance(idx);  
  double lep_effSF_offline_Tight    = this->leptons_NOMINAL_effSF_offline_TightLLH_2015_13TeV_rel20p0_25ns_v04->EvalInstance(idx);
  
  double lep_effSF_Loose_isolLoose  = this->leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->EvalInstance(idx);
  double lep_effSF_Loose_isolTight = this->leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04->EvalInstance(idx);
  double lep_effSF_Loose_isolGradLoose = this->leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04->EvalInstance(idx);
  double lep_effSF_Loose_isolGrad = this->leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04->EvalInstance(idx);

  double lep_effSF_Medium_isolLoose = this->leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->EvalInstance(idx);
  double lep_effSF_Medium_isolTight = this->leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04->EvalInstance(idx);
  double lep_effSF_Medium_isolGradLoose = this->leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04->EvalInstance(idx);
  double lep_effSF_Medium_isolGrad= this->leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04->EvalInstance(idx);

  double lep_effSF_Tight_isolLoose  = this->leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->EvalInstance(idx);
  double lep_effSF_Tight_isolTight = this->leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04->EvalInstance(idx);
  double lep_effSF_Tight_isolGradLoose = this->leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04->EvalInstance(idx);
  double lep_effSF_Tight_isolGrad= this->leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04->EvalInstance(idx);

  double lep_effSF_offline_RecoTrk  = this->leptons_NOMINAL_effSF_offline_RecoTrk_2015_13TeV_rel20p0_25ns_v04->EvalInstance(idx);



//  //muons:
//  if (lep == 1){
//    if(lep_looseID){
//      SF *=lep_effSF_RecoLoose;
//    }
//    else if(lep_mediumID){
//      SF *=lep_effSF_RecoMedium;
//    }
//    else if(lep_tightID){
//      SF *=lep_effSF_RecoTight;
//    }
//    if(lep_looseISO){
//      SF *= lep_effSF_IsoLoose;
//    }
//    else if(lep_tightISO){
//      SF *= lep_effSF_IsoTight;
//    }
//    else if(lep_gradlooseISO){
//      SF *= lep_effSF_IsoGradientLoose;
//    }
//    else if(lep_gradISO){
//      SF *= lep_effSF_IsoGradient;
//    }
//  }
//  //electrons:
//  else if (lep == 2){
//    SF *= lep_effSF_offline_RecoTrk;
//    if(lep_looseID){
//      SF *= lep_effSF_offline_Loose;
//      if(lep_looseISO){
//	SF *= lep_effSF_Loose_isolLoose;
//      }
//      else if(lep_tightISO){
//        SF *= lep_effSF_Loose_isolTight;
//      }
//      else if(lep_gradlooseISO){
//	SF *= lep_effSF_Loose_isolGradLoose;
//      }
//      else if(lep_gradISO){
//	SF *= lep_effSF_Loose_isolGrad;
//      }
//    }
//    else if(lep_mediumID){
//      SF *= lep_effSF_offline_Medium;
//      if(lep_looseISO){
//        SF *= lep_effSF_Medium_isolLoose;
//      }
//      else if(lep_tightISO){
//        SF *= lep_effSF_Medium_isolTight;
//      }
//      else if(lep_gradlooseISO){
//	SF *= lep_effSF_Medium_isolGradLoose;
//      }
//      else if(lep_gradISO){
//	SF *= lep_effSF_Medium_isolGrad;
//      }
//    }
//    else if(lep_tightID){
//      SF *= lep_effSF_offline_Tight;
//      if(lep_looseISO){
//        SF *= lep_effSF_Tight_isolLoose;
//      }
//      else if(lep_tightISO){
//        SF *= lep_effSF_Tight_isolTight;
//      }
//      else if(lep_gradlooseISO){
//	SF *= lep_effSF_Tight_isolGradLoose;
//      }
//      else if(lep_gradISO){
//	SF *= lep_effSF_Tight_isolGrad;
//      }
//    }
//  }
//  else {
//    DEBUGclass("Scalefactor: No matching reco found for LeptonSF; returning 0");
//    std::cout << "In ScaleFactor: Problem with leptons ID!! returning 0" << std::endl;
//    return 0.;
//  }

  /// end ---- to be removed

  double SF_new = 1.;
  if(useFakeSelec){
    SF_new=EVS_fake->getScaleFactor();
  }
  else {
    SF_new=EVS->getScaleFactor();
  }

  DEBUGclass("returning");

  //std::cout <<"returning SF " << SF_new <<std::endl;

  return SF_new;
}
//______________________________________________________________________________________________

ScaleFactor_ll_v05::ScaleFactor_ll_v05(const TString& expression):
TQTreeObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  if(expression.Contains("fake")){
    useFakeSelec = true;
  }

  isowp_e    = 1;
  idwp_e     = 1;
  isowp_m    = 1;
  if (isowp_m == -1) isowp_m=isowp_e;
  idwp_m    = 1;
  if (idwp_m == -1) idwp_m=idwp_e;
  lepIndex = 0;


  switch (idwp_e) {
      case 1: el_looseID  = true;break;
      case 2: el_mediumID = true;break;
      case 3: el_tightID  = true;break;
      default:
              std::cout << "WARNING in ScaleFactor: no valid ID for lepton found!" << std::endl;
  }

  switch (isowp_e) {
      case 10:    el_looseISO     = true; break;
      case 100:   el_tightISO     = true; break;
      case 1000:  el_gradlooseISO = true; break;
      case 10000: el_gradISO      = true; break;
      default:
              std::cout << "WARNING in ScaleFactor: no valid Iso for lepton found! Assuming no Isolation!" << std::endl;
  }

  switch (idwp_m) {
      case 1: mu_looseID  = true;break;
      case 2: mu_mediumID = true;break;
      case 3: mu_tightID  = true;break;
      default:
              std::cout << "WARNING in ScaleFactor: no valid ID for lepton found!" << std::endl;
  }

  switch (isowp_m) {
      case 10:    mu_looseISO     = true; break;
      case 100:   mu_tightISO     = true; break;
      case 1000:  mu_gradlooseISO = true; break;
      case 10000: mu_gradISO      = true; break;
      default:
              std::cout << "WARNING in ScaleFactor: no valid Iso for lepton found! Assuming no Isolation!" << std::endl;
  }

}

//______________________________________________________________________________________________

const TString& ScaleFactor_ll_v05::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool ScaleFactor_ll_v05::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void ScaleFactor_ll_v05::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool ScaleFactor_ll_v05::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void ScaleFactor_ll_v05::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString ScaleFactor_ll_v05::getActiveExpression() const {
  // retrieve the expression associated with this incarnation
  
  return this->getExpression();
}

//______________________________________________________________________________________________

bool ScaleFactor_ll_v05::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  // this->bla = new TTreeFormula( "name", "formula", this->fTree);

  EVS = new EventSelection_leplep_default();
  EVS_fake = new EventSelection_leplep_fake();

  this->leptons = new TTreeFormula( "leptoms", "leptons", this->fTree);
  this->leptons_id_loose = new TTreeFormula( "leptons_id_loose", "leptons_id_loose", this->fTree);
  this->leptons_id_medium = new TTreeFormula( "leptons_id_medium", "leptons_id_medium", this->fTree);
  this->leptons_id_tight = new TTreeFormula( "leptons_id_tight", "leptons_id_tight", this->fTree);
  this->leptons_iso_wp = new TTreeFormula( "leptons_iso_wp", "leptons_iso_wp", this->fTree);
  
  if (mu_looseID){
      muon_ID_effSF_name     = "leptons_NOMINAL_effSF_RecoLoose";
  }
  else if (mu_mediumID){
      muon_ID_effSF_name     = "leptons_NOMINAL_effSF_RecoMedium";
  }
  else if (mu_tightID){
      muon_ID_effSF_name     = "leptons_NOMINAL_effSF_RecoTight";
  }
  this->muon_ID_effSF = new TTreeFormula("muon_ID_effSF", muon_ID_effSF_name, this->fTree);

  if ( mu_looseISO) {
      muon_ISO_effSF_name          = "leptons_NOMINAL_effSF_IsoLoose";
  }
  else if ( mu_tightISO) {
      muon_ISO_effSF_name          = "leptons_NOMINAL_effSF_IsoTight";
  }
  else if ( mu_gradlooseISO) {
      muon_ISO_effSF_name          = "leptons_NOMINAL_effSF_IsoGradientLoose";
  }
  else if ( mu_gradISO) {
      muon_ISO_effSF_name          = "leptons_NOMINAL_effSF_IsoGradient";
  }
  this->muon_ISO_effSF = new TTreeFormula("muon_ISO_effSF",muon_ISO_effSF_name, this->fTree);
   
  el_Track_effSF_name="leptons_NOMINAL_effSF_offline_RecoTrk_2015_13TeV_rel20p0_25ns_v04";
  this->el_Track_effSF = new TTreeFormula("el_Track_effSF",el_Track_effSF_name,this->fTree);

  if ( el_looseID ) {
      el_ID_effSF_name                            = "leptons_NOMINAL_effSF_offline_LooseAndBLayerLLH_2015_13TeV_rel20p0_25ns_v04";
      if (el_looseISO) el_ISO_effSF_name          = "leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04";
      else if (el_tightISO) el_ISO_effSF_name     = "leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04";
      else if (el_gradlooseISO) el_ISO_effSF_name = "leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04";
      else if (el_gradISO) el_ISO_effSF_name      = "leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04";
  }
  else if ( el_mediumID ) {
      el_ID_effSF_name                            = "leptons_NOMINAL_effSF_offline_MediumLLH_2015_13TeV_rel20p0_25ns_v04";
      if (el_looseISO) el_ISO_effSF_name          = "leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04";
      else if (el_tightISO) el_ISO_effSF_name     = "leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04";
      else if (el_gradlooseISO) el_ISO_effSF_name = "leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04";
      else if (el_gradISO) el_ISO_effSF_name      = "leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04";
  }
  else if ( el_tightID ) {
      el_ID_effSF_name                            = "leptons_NOMINAL_effSF_offline_TightLLH_2015_13TeV_rel20p0_25ns_v04";
      if (el_looseISO) el_ISO_effSF_name          = "leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04";
      else if (el_tightISO) el_ISO_effSF_name     = "leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04";
      else if (el_gradlooseISO) el_ISO_effSF_name = "leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04";
      else if (el_gradISO) el_ISO_effSF_name      = "leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04";
  }
  this->el_ID_effSF  = new TTreeFormula("el_ID_effSF",el_ID_effSF_name,this->fTree);
  this->el_ISO_effSF = new TTreeFormula("el_ISO_effSF",el_ISO_effSF_name,this->fTree);

  /// ---- to be removed

  this->leptons_NOMINAL_effSF_RecoLoose                                                                         = new TTreeFormula("leptons_NOMINAL_effSF_RecoLoose", "leptons_NOMINAL_effSF_RecoLoose", this->fTree);
  this->leptons_NOMINAL_effSF_RecoMedium                                                                        = new TTreeFormula("leptons_NOMINAL_effSF_RecoMedium", "leptons_NOMINAL_effSF_RecoMedium", this->fTree);
  this->leptons_NOMINAL_effSF_RecoTight                                                                         = new TTreeFormula("leptons_NOMINAL_effSF_RecoTight", "leptons_NOMINAL_effSF_RecoTight", this->fTree);
  this->leptons_NOMINAL_effSF_IsoLoose                                                                          = new TTreeFormula("leptons_NOMINAL_effSF_IsoLoose", "leptons_NOMINAL_effSF_IsoLoose", this->fTree);
  this->leptons_NOMINAL_effSF_IsoTight                                                                          = new TTreeFormula("leptons_NOMINAL_effSF_IsoTight", "leptons_NOMINAL_effSF_IsoTight", this->fTree);
  this->leptons_NOMINAL_effSF_IsoGradientLoose                                                                  = new TTreeFormula("leptons_NOMINAL_effSF_IsoGradientLoose", "leptons_NOMINAL_effSF_IsoGradientLoose", this->fTree);
  this->leptons_NOMINAL_effSF_IsoGradient                                                                       = new TTreeFormula("leptons_NOMINAL_effSF_IsoGradient", "leptons_NOMINAL_effSF_IsoGradient", this->fTree);

  this->leptons_NOMINAL_effSF_offline_LooseAndBLayerLLH_2015_13TeV_rel20p0_25ns_v04                             = new TTreeFormula("leptons_NOMINAL_effSF_offline_LooseAndBLayerLLH_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_offline_LooseAndBLayerLLH_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_offline_MediumLLH_2015_13TeV_rel20p0_25ns_v04                                     = new TTreeFormula("leptons_NOMINAL_effSF_offline_MediumLLH_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_offline_MediumLLH_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_offline_TightLLH_2015_13TeV_rel20p0_25ns_v04                                      = new TTreeFormula("leptons_NOMINAL_effSF_offline_TightLLH_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_offline_TightLLH_2015_13TeV_rel20p0_25ns_v04", this->fTree);

  this->leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04         = new TTreeFormula("leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04         = new TTreeFormula("leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04 = new TTreeFormula("leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04      = new TTreeFormula("leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04", this->fTree);

  this->leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04                 = new TTreeFormula("leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04                 = new TTreeFormula("leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04         = new TTreeFormula("leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04              = new TTreeFormula("leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04", this->fTree);

  this->leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04                  = new TTreeFormula("leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04                  = new TTreeFormula("leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04          = new TTreeFormula("leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04               = new TTreeFormula("leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04", this->fTree);

  this->leptons_NOMINAL_effSF_offline_RecoTrk_2015_13TeV_rel20p0_25ns_v04                                       = new TTreeFormula("leptons_NOMINAL_effSF_offline_RecoTrk_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_offline_RecoTrk_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  /// end ---- to be removed


  return true;
}
 
//______________________________________________________________________________________________

bool ScaleFactor_ll_v05::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete EVS;
  delete EVS_fake;
  delete this->leptons;
  delete this->leptons_id_loose;
  delete this->leptons_id_medium;
  delete this->leptons_id_tight;
  delete this->leptons_iso_wp;

  /// ---- to be removed
  delete this->leptons_NOMINAL_effSF_RecoLoose;
  delete this->leptons_NOMINAL_effSF_RecoMedium;
  delete this->leptons_NOMINAL_effSF_RecoTight;
  delete this->leptons_NOMINAL_effSF_IsoLoose;
  delete this->leptons_NOMINAL_effSF_IsoTight;
  delete this->leptons_NOMINAL_effSF_IsoGradientLoose;
  delete this->leptons_NOMINAL_effSF_IsoGradient;
  delete this->leptons_NOMINAL_effSF_offline_LooseAndBLayerLLH_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_offline_MediumLLH_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_offline_TightLLH_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_Isolation_LooseAndBLayerLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_Isolation_MediumLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolTight_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolGradientLoose_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_Isolation_TightLLH_d0z0_v8_isolGradient_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_offline_RecoTrk_2015_13TeV_rel20p0_25ns_v04;
  /// end ---- to be removed

  delete this->muon_ID_effSF;
  delete this->muon_ISO_effSF;

  delete this->el_ID_effSF;
  delete this->el_ISO_effSF;
  delete this->el_Track_effSF;

  return true;
}
