#include "Htautau2015/TriggerWeight_ll_v05.h"
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

ClassImp(TriggerWeight_ll_v05)

//______________________________________________________________________________________________

TriggerWeight_ll_v05::TriggerWeight_ll_v05(){
  // default constructor
 
  this->setExpression(this->GetName() );

  std::cout << "default constructor called" << std::endl;
  
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

TriggerWeight_ll_v05::~TriggerWeight_ll_v05(){
  // default destructor
  DEBUGclass("destructor called");
} 


//______________________________________________________________________________________________

TObjArray* TriggerWeight_ll_v05::getBranchNames() const {
  // retrieve the list of branch names 
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));
  
  bnames->Add(new TObjString("leptons"));
  bnames->Add(new TObjString("leptons_pt"));
  bnames->Add(new TObjString("leptons_id_loose"));
  bnames->Add(new TObjString("leptons_id_medium"));
  bnames->Add(new TObjString("leptons_id_tight"));
  bnames->Add(new TObjString("leptons_iso_wp"));
  //Trigger:
  bnames->Add(new TObjString("leptons_HLT_e24_lhmedium_L1EM18VH"));
  bnames->Add(new TObjString("leptons_HLT_e60_lhmedium"));
  bnames->Add(new TObjString("leptons_HLT_e120_lhloose"));
  bnames->Add(new TObjString("leptons_HLT_mu20_iloose_L1MU15"));
  bnames->Add(new TObjString("leptons_HLT_mu50"));
  bnames->Add(new TObjString("HLT_e17_loose_mu14"));
  bnames->Add(new TObjString("HLT_mu18_mu8noL1"));
  // Scalefactors:
  bnames->Add(new TObjString("leptons_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE"));
  bnames->Add(new TObjString("leptons_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE"));
  bnames->Add(new TObjString("leptons_NOMINAL_HLT_mu18_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE"));
  bnames->Add(new TObjString("leptons_NOMINAL_HLT_mu18_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE"));
  bnames->Add(new TObjString("leptons_NOMINAL_HLT_mu8noL1_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE"));
  bnames->Add(new TObjString("leptons_NOMINAL_HLT_mu8noL1_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE"));
  bnames->Add(new TObjString("leptons_NOMINAL_HLT_mu14_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE"));
  bnames->Add(new TObjString("leptons_NOMINAL_HLT_mu14_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_e17_lhloose_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_e17_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04"));
  bnames->Add(new TObjString("leptons_NOMINAL_effSF_e17_lhloose_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04"));


  
  
  return bnames;
}

//______________________________________________________________________________________________

double TriggerWeight_ll_v05::getValue() const {
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

  int idx0=-1;
  int idx1=-1;
  //idx0=OVR->getLeptonIdx(0);
  //idx1=OVR->getLeptonIdx(1);
  
  //leptons->GetNdata();
  //leptons_pt->GetNdata();
  //leptons_id_loose->GetNdata();
  //leptons_id_medium->GetNdata();
  //leptons_id_tight->GetNdata();
  //leptons_iso_wp->GetNdata();
  //
  //leptons_HLT_e24_lhmedium_L1EM18VH->GetNdata();
  //leptons_HLT_e60_lhmedium->GetNdata();
  //leptons_HLT_e120_lhloose->GetNdata();
  //leptons_HLT_mu20_iloose_L1MU15->GetNdata();
  //leptons_HLT_mu50->GetNdata();
  //
  //// NOTE: scale factors are available for different ISO WP, however at the moment only noISO and looseISO are included here
  //
  //int lep_0           = this->leptons->EvalInstance(idx0);
  //int lep_1           = this->leptons->EvalInstance(idx1);
  //int lep_0_pt        = this->leptons_pt->EvalInstance(idx0);
  //int lep_1_pt        = this->leptons_pt->EvalInstance(idx1);
  //int lep_0_id_loose  = this->leptons_id_loose->EvalInstance(idx0);
  //int lep_1_id_loose  = this->leptons_id_loose->EvalInstance(idx1);
  //int lep_0_id_medium = this->leptons_id_medium->EvalInstance(idx0);
  //int lep_1_id_medium = this->leptons_id_medium->EvalInstance(idx1);
  //int lep_0_id_tight  = this->leptons_id_tight->EvalInstance(idx0);
  //int lep_1_id_tight  = this->leptons_id_tight->EvalInstance(idx1);
  //int lep_0_iso_wp        = this->leptons_iso_wp->EvalInstance(idx0);
  //int lep_1_iso_wp        = this->leptons_iso_wp->EvalInstance(idx1);
  //
  //bool lep_0_noISO    = false;
  //bool lep_0_looseISO = false;
  //bool lep_1_noISO    = false;
  //bool lep_1_looseISO = false;
  //
  //// for gradient iso:
  //int loose_wp = 10000;
  //
  //if ((lep_0_iso_wp % (10*loose_wp)) >= loose_wp){ lep_0_looseISO = true; }
  //else lep_0_noISO = true;
  //if ((lep_1_iso_wp % (10*loose_wp)) >= loose_wp){ lep_1_looseISO = true; }
  //else lep_0_noISO = true;
  //
  //if (lep_0_noISO || lep_1_noISO){
  //  std::cout<< "WARNING in TriggerWeight : Found leptons with no ISO requirement!!" << std::endl;
  //  //std::cout<< "lep0: " << lep_0_noISO << " lep1: " << lep_1_noISO << std::endl;
  //}
  //
  ///////////////
  //// Trigger //
  //////////////
  //
  //int lep_0_HLT_e24_lhmedium_L1EM18VH = this->leptons_HLT_e24_lhmedium_L1EM18VH ->EvalInstance(0);
  //int lep_0_HLT_e60_lhmedium          = this->leptons_HLT_e60_lhmedium ->EvalInstance(0);
  //int lep_0_HLT_e120_lhloose          = this->leptons_HLT_e120_lhloose ->EvalInstance(0);
  //int lep_0_HLT_mu20_iloose_L1MU15    = this->leptons_HLT_mu20_iloose_L1MU15 ->EvalInstance(0);
  //int lep_0_HLT_mu50                  = this->leptons_HLT_mu50 ->EvalInstance(0);
  //
  //int lep_1_HLT_e24_lhmedium_L1EM18VH = this->leptons_HLT_e24_lhmedium_L1EM18VH ->EvalInstance(1);
  //int lep_1_HLT_e60_lhmedium          = this->leptons_HLT_e60_lhmedium ->EvalInstance(1);
  //int lep_1_HLT_e120_lhloose          = this->leptons_HLT_e120_lhloose ->EvalInstance(1);
  //int lep_1_HLT_mu20_iloose_L1MU15    = this->leptons_HLT_mu20_iloose_L1MU15 ->EvalInstance(1);
  //int lep_1_HLT_mu50                  = this->leptons_HLT_mu50 ->EvalInstance(1);
  //
  //int HLT_e17_loose_mu14         = this->HLT_e17_loose_mu14 ->EvalInstance();
  //int HLT_mu18_mu8noL1           = this->HLT_mu18_mu8noL1 ->EvalInstance();
  //int HLT_2e12_lhloose_L12EM10VH = this->HLT_2e12_lhloose_L12EM10VH ->EvalInstance();
  //
  ///////////////////
  //// Trigger SF //
  //////////////////
  //// muons:
  //// single mu trigger for medID, looseISO
  //leptons_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE->GetNdata();
  //float lep_0_mu20ORmu50_medID_looseISO = this->leptons_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE ->EvalInstance(0);
  //float lep_1_mu20ORmu50_medID_looseISO = this->leptons_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE ->EvalInstance(1);
  //// single mu trigger for tightID, looseISO
  //leptons_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE->GetNdata();
  //float lep_0_mu20ORmu50_tightID_looseISO = this->leptons_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE ->EvalInstance(0);
  //float lep_1_mu20ORmu50_tightID_looseISO = this->leptons_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE ->EvalInstance(1);
  //// mu18 for medID, looseISO
  //leptons_NOMINAL_HLT_mu18_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE->GetNdata();
  //float lep_0_mu18_medID_looseISO = this->leptons_NOMINAL_HLT_mu18_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE->EvalInstance(0);
  //float lep_1_mu18_medID_looseISO = this->leptons_NOMINAL_HLT_mu18_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE->EvalInstance(1);
  //// mu18 for tightID, looseISO                                             
  //leptons_NOMINAL_HLT_mu18_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE->GetNdata();
  //float lep_0_mu18_tightID_looseISO = this->leptons_NOMINAL_HLT_mu18_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE->EvalInstance(0);
  //float lep_1_mu18_tightID_looseISO = this->leptons_NOMINAL_HLT_mu18_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE->EvalInstance(1);
  //// mu8noL1 for medID, looseISO
  //leptons_NOMINAL_HLT_mu8noL1_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE->GetNdata();
  //float lep_0_mu8noL1_medID_looseISO = this->leptons_NOMINAL_HLT_mu8noL1_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE->EvalInstance(0);
  //float lep_1_mu8noL1_medID_looseISO = this->leptons_NOMINAL_HLT_mu8noL1_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE->EvalInstance(1);
  //// mu8noL1 for tightID, looseISO
  //leptons_NOMINAL_HLT_mu8noL1_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE->GetNdata();
  //float lep_0_mu8noL1_tightID_looseISO = this->leptons_NOMINAL_HLT_mu8noL1_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE->EvalInstance(0);
  //float lep_1_mu8noL1_tightID_looseISO = this->leptons_NOMINAL_HLT_mu8noL1_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE->EvalInstance(1);
  //// mu14 for medID, looseISO
  //leptons_NOMINAL_HLT_mu14_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE->GetNdata();
  //float lep_0_mu14_medID_looseISO = this->leptons_NOMINAL_HLT_mu14_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE->EvalInstance(0);
  //float lep_1_mu14_medID_looseISO = this->leptons_NOMINAL_HLT_mu14_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE->EvalInstance(1);
  //// mu14 for tightID, looseISO
  //leptons_NOMINAL_HLT_mu14_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE->GetNdata();
  //float lep_0_mu14_tightID_looseISO = this->leptons_NOMINAL_HLT_mu14_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE->EvalInstance(0);
  //float lep_1_mu14_tightID_looseISO = this->leptons_NOMINAL_HLT_mu14_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE->EvalInstance(1);
  //
  //// electrons: TO DO: looseID, noISO einbauen
  //// single e for looseID, noISO
  //leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  //float lep_0_e24ORe60ORe120_looseID_noISO = this->leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->EvalInstance(0);
  //float lep_1_e24ORe60ORe120_looseID_noISO = this->leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->EvalInstance(1);
  //// single e for medID, noISO
  //leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  //float lep_0_e24ORe60ORe120_medID_noISO = this->leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->EvalInstance(0);
  //float lep_1_e24ORe60ORe120_medID_noISO = this->leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->EvalInstance(1);
  //// single e for medID, looseISO
  //leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  //float lep_0_e24ORe60ORe120_medID_looseISO = this->leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->EvalInstance(0);
  //float lep_1_e24ORe60ORe120_medID_looseISO = this->leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->EvalInstance(1);
  //// single e for tightID, noISO
  //leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  //float lep_0_e24ORe60ORe120_tightID_noISO = this->leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->EvalInstance(0);
  //float lep_1_e24ORe60ORe120_tightID_noISO = this->leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->EvalInstance(1);
  //// single for tightID, looseISO
  //leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  //float lep_0_e24ORe60ORe120_tightID_looseISO = this->leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->EvalInstance(0);
  //float lep_1_e24ORe60ORe120_tightID_looseISO = this->leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->EvalInstance(1);
  //// e12 for looseID, no ISO
  //leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  //float lep_0_e12_looseID_noISO = this->leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->EvalInstance(0);
  //float lep_1_e12_looseID_noISO = this->leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->EvalInstance(1);
  //// e12 for medID, noISO
  //leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  //float lep_0_e12_medID_noISO = this->leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->EvalInstance(0);
  //float lep_1_e12_medID_noISO = this->leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->EvalInstance(1);
  //// e12 for medID, looseISO
  //leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  //float lep_0_e12_medID_looseISO = this->leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->EvalInstance(0);
  //float lep_1_e12_medID_looseISO = this->leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->EvalInstance(1);
  //// e12 for tightID, noISO
  //leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  //float lep_0_e12_tightID_noISO = this->leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->EvalInstance(0);
  //float lep_1_e12_tightID_noISO = this->leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->EvalInstance(1);
  //// e12 for tightID, looseISO
  //leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  //float lep_0_e12_tightID_looseISO = this->leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->EvalInstance(0);
  //float lep_1_e12_tightID_looseISO = this->leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->EvalInstance(1);
  //// e17 for looseID, noISO
  //leptons_NOMINAL_effSF_e17_lhloose_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  //float lep_0_e17_looseID_noISO = this->leptons_NOMINAL_effSF_e17_lhloose_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->EvalInstance(0);
  //float lep_1_e17_looseID_noISO = this->leptons_NOMINAL_effSF_e17_lhloose_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->EvalInstance(1);
  //// e17 medID, noISO
  //leptons_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  //float lep_0_e17_medID_noISO = this->leptons_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->EvalInstance(0);
  //float lep_1_e17_medID_noISO = this->leptons_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->EvalInstance(1);
  //// e17 for medID, looseISO
  //leptons_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  //float lep_0_e17_medID_looseISO = this->leptons_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->EvalInstance(0);
  //float lep_1_e17_medID_looseISO = this->leptons_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->EvalInstance(1);
  //// e17 for tightID, noISO
  //leptons_NOMINAL_effSF_e17_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  //float lep_0_e17_tightID_noISO = this->leptons_NOMINAL_effSF_e17_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->EvalInstance(0);
  //float lep_1_e17_tightID_noISO = this->leptons_NOMINAL_effSF_e17_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04->EvalInstance(1);
  //// e17 for tightID, looseISO
  //leptons_NOMINAL_effSF_e17_lhloose_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->GetNdata();
  //float lep_0_e17_tightID_looseISO = this->leptons_NOMINAL_effSF_e17_lhloose_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->EvalInstance(0);
  //float lep_1_e17_tightID_looseISO = this->leptons_NOMINAL_effSF_e17_lhloose_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04->EvalInstance(1);
  //
  //float TriggerWeight = 1.;
  //
  //if (lep_0 == 1 && lep_1 == 1){ //mm
  //  if (lep_0_pt >= 22*1000 && (lep_0_HLT_mu20_iloose_L1MU15==1 || lep_0_HLT_mu50==1)){
  //    if (lep_0_id_medium == 1 && lep_0_id_tight == 0){
  //	TriggerWeight *= lep_0_mu20ORmu50_medID_looseISO;
  //    }
  //    if (lep_0_id_tight == 1){
  //	TriggerWeight *= lep_0_mu20ORmu50_tightID_looseISO;
  //    }
  //  }
  //  else if (lep_0_pt/1000 < 22  && lep_0_pt/1000 >=20 && lep_1_pt/1000 >=10 && HLT_mu18_mu8noL1==1){
  //    // assume: lead lep fired mu18, sublead leptons fired mu8
  //    if(lep_0_id_medium == 1 && lep_0_id_tight == 0){
  //	TriggerWeight *= lep_0_mu18_medID_looseISO;
  //    }
  //    if (lep_1_id_medium == 1 && lep_1_id_tight == 0){
  //	TriggerWeight *= lep_1_mu8noL1_medID_looseISO;
  //    }
  //    if (lep_0_id_tight == 1){
  //	TriggerWeight *= lep_0_mu18_tightID_looseISO; 
  //    }
  //    if(lep_1_id_tight == 1){
  //	TriggerWeight *= lep_1_mu8noL1_tightID_looseISO;
  //    }
  //  }
  //}
  //else if (lep_0 == 2 && lep_1 == 2){ // ee
  //  if (lep_0_pt >= 26*1000 && (lep_0_HLT_e24_lhmedium_L1EM18VH==1 || lep_0_HLT_e60_lhmedium==1 || lep_0_HLT_e120_lhloose==1)){
  //    if(lep_0_id_medium == 1 && lep_0_id_tight == 0){
  //	if(lep_0_looseISO){
  //	  TriggerWeight *= lep_0_e24ORe60ORe120_medID_looseISO;
  //	}
  //	else {
  //	  TriggerWeight *= lep_0_e24ORe60ORe120_medID_noISO;
  //	}
  //    }
  //    if(lep_0_id_tight == 1){
  //	if(lep_0_looseISO){
  //	  TriggerWeight *= lep_0_e24ORe60ORe120_tightID_looseISO;
  //	}
  //	else {
  //	  TriggerWeight *= lep_0_e24ORe60ORe120_tightID_noISO;
  //	}
  //    }
  //  }
  //  else if (lep_0_pt< 26000 && lep_0_pt >= 15000 && lep_1_pt >= 15000 && HLT_2e12_lhloose_L12EM10VH==1){
  //    if(lep_0_id_medium == 1 && lep_0_id_tight == 0){
  //	if(lep_0_looseISO){
  //	  TriggerWeight *= lep_0_e12_medID_looseISO; 
  //	}
  //	else {
  //	  TriggerWeight *= lep_0_e12_medID_noISO; 
  //	}
  //    }
  //    if(lep_1_id_medium == 1 && lep_1_id_tight == 0){
  //	if(lep_1_looseISO){
  //	  TriggerWeight *=lep_1_e12_medID_looseISO;
  //	}
  //	else {
  //	  TriggerWeight *=lep_1_e12_medID_noISO;
  //	}
  //    }
  //    if(lep_0_id_tight == 1){
  //	if(lep_0_looseISO){
  //	  TriggerWeight *= lep_0_e12_tightID_looseISO;
  //	}
  //	else {
  //	  TriggerWeight *= lep_0_e12_tightID_noISO;
  //	}
  //    }
  //    if(lep_1_id_tight == 1){
  //	if(lep_1_looseISO){
  //	  TriggerWeight *= lep_1_e12_tightID_looseISO;
  //	}
  //	else {
  //	  TriggerWeight *= lep_1_e12_tightID_noISO;
  //	}
  //    }
  //  }
  //}
  //else if (lep_0 == 1 && lep_1 == 2){ //me
  //  if(lep_1_pt < 26 * 1000 && lep_0_pt >= 22 * 1000 && (lep_0_HLT_mu20_iloose_L1MU15==1 || lep_0_HLT_mu50==1)){
  //    if(lep_0_id_medium == 1 && lep_0_id_tight == 0){
  //	TriggerWeight *= lep_0_mu20ORmu50_medID_looseISO;
  //    }
  //    if(lep_0_id_tight == 1){
  //	TriggerWeight *= lep_0_mu20ORmu50_tightID_looseISO;
  //    }
  //  }
  //  else if (lep_1_pt >= 26 * 1000 && (lep_1_HLT_e24_lhmedium_L1EM18VH==1 || lep_1_HLT_e60_lhmedium==1 || lep_1_HLT_e120_lhloose==1)) {
  //    if(lep_1_id_medium == 1 && lep_1_id_tight == 0){
  //	if(lep_1_looseISO){
  //	  TriggerWeight *= lep_1_e24ORe60ORe120_medID_looseISO;
  //	}
  //	else {
  //	  TriggerWeight *= lep_1_e24ORe60ORe120_medID_noISO;
  //	}
  //    }
  //    if(lep_1_id_tight == 1){
  //	if(lep_1_looseISO){
  //	  TriggerWeight *= lep_1_e24ORe60ORe120_tightID_looseISO;
  //	}
  //	else {
  //	  TriggerWeight *= lep_1_e24ORe60ORe120_tightID_noISO;
  //	}
  //    }
  //  }
  //  else if (lep_1_pt < 26 * 1000 && lep_1_pt >= 19 * 1000 && lep_0_pt < 22 * 1000 && lep_0_pt >= 16 * 1000 && HLT_e17_loose_mu14==1 ){
  //    if(lep_1_id_medium == 1 && lep_1_id_tight == 0){
  //	if(lep_1_looseISO){
  //	  TriggerWeight *= lep_1_e17_medID_looseISO; 
  //	}
  //	else {
  //	  TriggerWeight *= lep_1_e17_medID_noISO; 
  //	}
  //    }
  //    if (lep_0_id_medium == 1 && lep_0_id_tight == 0){
  //	TriggerWeight *= lep_0_mu14_medID_looseISO;
  //    }
  //    if(lep_1_id_tight == 1){
  //	if(lep_0_looseISO){
  //	  TriggerWeight *= lep_1_e17_tightID_looseISO;
  //	}
  //	else {
  //	  TriggerWeight *= lep_1_e17_tightID_noISO;
  //	}
  //    }
  //    if (lep_0_id_tight == 1){
  //      TriggerWeight *= lep_0_mu14_tightID_looseISO;
  //    } 
  //  }
  //}
  //else if (lep_0 == 2 && lep_1 == 1) { // em
  //  if (lep_0_pt >= 26 * 1000 && (lep_0_HLT_e24_lhmedium_L1EM18VH==1 || lep_0_HLT_e60_lhmedium==1 || lep_0_HLT_e120_lhloose==1)){
  //    if(lep_0_id_medium == 1 && lep_0_id_tight == 0){
  //	if(lep_0_looseISO){
  //	  TriggerWeight *= lep_0_e24ORe60ORe120_medID_looseISO; 
  //	}
  //	else {
  //	  TriggerWeight *= lep_0_e24ORe60ORe120_medID_noISO; 
  //	}
  //    }
  //    if(lep_0_id_tight == 1){
  //	if(lep_0_looseISO){
  //	  TriggerWeight *= lep_0_e24ORe60ORe120_tightID_looseISO;
  //	}
  //	else {
  //	  TriggerWeight *= lep_0_e24ORe60ORe120_tightID_noISO;
  //	}
  //    }
  //  }
  //  else if (lep_0_pt < 26 * 1000 && lep_1_pt >=22 * 1000 && (lep_1_HLT_mu20_iloose_L1MU15==1 || lep_1_HLT_mu50==1)){
  //    if(lep_1_id_medium == 1 && lep_1_id_tight == 0){
  //	TriggerWeight *= lep_1_mu20ORmu50_medID_looseISO;
  //    }
  //    if(lep_1_id_tight == 1){
  //	TriggerWeight *= lep_1_mu20ORmu50_tightID_looseISO;
  //    }
  //  }
  //  else if (lep_0_pt < 26 * 1000 && lep_0_pt >= 19 * 1000 && lep_1_pt < 22 * 1000 && lep_1_pt >= 16 * 1000 && HLT_e17_loose_mu14==1){
  //    if(lep_0_id_medium == 1 && lep_0_id_tight == 0){
  //	if(lep_0_looseISO){
  //	  TriggerWeight *= lep_0_e17_medID_looseISO;
  //	}
  //	else {
  //	  TriggerWeight *= lep_0_e17_medID_noISO;
  //	}
  //    }
  //    if(lep_1_id_medium == 1 && lep_1_id_tight == 0){
  //	TriggerWeight *= lep_1_mu14_medID_looseISO;
  //    }
  //    if(lep_0_id_tight == 1){
  //	if(lep_0_looseISO){
  //	  TriggerWeight *= lep_0_e17_tightID_looseISO;
  //	}
  //	else {
  //	  TriggerWeight *= lep_0_e17_tightID_noISO;
  //	}
  //    }
  //    if(lep_1_id_tight == 1){
  //	TriggerWeight *= lep_1_mu14_tightID_looseISO;
  //    }
  //  }
  //}

  //std::cout << "In TriggerWeight:: Calling EVS fct!" << std::endl;
  double TriggerWeight = 1.;
  if(useFakeSelec){
    TriggerWeight = EVS_fake->getTriggerWeight();
  }
  else {
    TriggerWeight = EVS->getTriggerWeight();
  }

  DEBUGclass("In TriggerWeight: trigger weight = "+TriggerWeight);

  DEBUGclass("returning");
  
  //std::cout << "TriggerWeight old " << TriggerWeight << std::endl;

  //std::cout << "In TriggerWeight:: Returning!" << std::endl;

  return TriggerWeight;
}
//______________________________________________________________________________________________

TriggerWeight_ll_v05::TriggerWeight_ll_v05(const TString& expression):
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

}

//______________________________________________________________________________________________

const TString& TriggerWeight_ll_v05::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool TriggerWeight_ll_v05::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void TriggerWeight_ll_v05::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool TriggerWeight_ll_v05::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void TriggerWeight_ll_v05::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString TriggerWeight_ll_v05::getActiveExpression() const {
  // retrieve the expression associated with this incarnation
  
  return this->getExpression();
}

//______________________________________________________________________________________________

bool TriggerWeight_ll_v05::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  // this->bla = new TTreeFormula( "name", "formula", this->fTree);
  //this-> = new TTreeFormula( "", "", this->fTree);
  
  EVS = new EventSelection_leplep_default();
  EVS_fake = new EventSelection_leplep_fake();

  this->leptons    = new TTreeFormula( "leptons", "leptons", this->fTree);
  this->leptons_pt = new TTreeFormula( "leptons_pt", "leptons_pt", this->fTree);
  this->leptons_id_loose = new TTreeFormula( "leptons_id_loose", "leptons_id_loose", this->fTree);
  this->leptons_id_medium = new TTreeFormula( "leptons_id_medium", "leptons_id_medium", this->fTree);
  this->leptons_id_tight = new TTreeFormula( "leptons_id_tight", "leptons_id_tight", this->fTree);
  this->leptons_iso_wp = new TTreeFormula( "leptons_iso_wp", "leptons_iso_wp", this->fTree);

  this->leptons_HLT_e24_lhmedium_L1EM18VH = new TTreeFormula( "leptons_HLT_e24_lhmedium_L1EM18VH", "leptons_HLT_e24_lhmedium_L1EM18VH", this->fTree);
  this->leptons_HLT_e60_lhmedium = new TTreeFormula( "leptons_HLT_e60_lhmedium", "leptons_HLT_e60_lhmedium", this->fTree);
  this->leptons_HLT_e120_lhloose = new TTreeFormula( "leptons_HLT_e120_lhloose", "leptons_HLT_e120_lhloose", this->fTree);
  this->leptons_HLT_mu20_iloose_L1MU15 = new TTreeFormula( "leptons_HLT_mu20_iloose_L1MU15", "leptons_HLT_mu20_iloose_L1MU15", this->fTree);
  this->leptons_HLT_mu50 = new TTreeFormula( "leptons_HLT_mu50", "leptons_HLT_mu50", this->fTree);

  this->HLT_e17_loose_mu14 = new TTreeFormula( "HLT_e17_loose_mu14", "HLT_e17_loose_mu14", this->fTree);
  this->HLT_mu18_mu8noL1 = new TTreeFormula( "HLT_mu18_mu8noL1", "HLT_mu18_mu8noL1", this->fTree);
  this->HLT_2e12_lhloose_L12EM10VH = new TTreeFormula( "HLT_2e12_lhloose_L12EM10VH", "HLT_2e12_lhloose_L12EM10VH", this->fTree);

  this->leptons_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE = new TTreeFormula( "leptons_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE", "leptons_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE", this->fTree);
  this->leptons_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE = new TTreeFormula( "leptons_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE", "leptons_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE", this->fTree);
  this->leptons_NOMINAL_HLT_mu18_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE = new TTreeFormula( "leptons_NOMINAL_HLT_mu18_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE", "leptons_NOMINAL_HLT_mu18_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE", this->fTree);
  this->leptons_NOMINAL_HLT_mu18_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE = new TTreeFormula( "leptons_NOMINAL_HLT_mu18_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE", "leptons_NOMINAL_HLT_mu18_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE", this->fTree);
  this->leptons_NOMINAL_HLT_mu8noL1_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE = new TTreeFormula( "leptons_NOMINAL_HLT_mu8noL1_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE", "leptons_NOMINAL_HLT_mu8noL1_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE", this->fTree);
  this->leptons_NOMINAL_HLT_mu8noL1_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE = new TTreeFormula( "leptons_NOMINAL_HLT_mu8noL1_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE", "leptons_NOMINAL_HLT_mu8noL1_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE", this->fTree);
  this->leptons_NOMINAL_HLT_mu14_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE = new TTreeFormula( "leptons_NOMINAL_HLT_mu14_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE", "leptons_NOMINAL_HLT_mu14_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE", this->fTree);
  this->leptons_NOMINAL_HLT_mu14_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE = new TTreeFormula( "leptons_NOMINAL_HLT_mu14_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE", "leptons_NOMINAL_HLT_mu14_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE", this->fTree);
  this->leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04 = new TTreeFormula( "leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04 = new TTreeFormula( "leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04 = new TTreeFormula( "leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04 = new TTreeFormula( "leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04 = new TTreeFormula( "leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04 = new TTreeFormula( "leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04 = new TTreeFormula( "leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04 = new TTreeFormula( "leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04 = new TTreeFormula( "leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04 = new TTreeFormula( "leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_e17_lhloose_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04 = new TTreeFormula( "leptons_NOMINAL_effSF_e17_lhloose_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_e17_lhloose_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04 = new TTreeFormula( "leptons_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04 = new TTreeFormula( "leptons_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_e17_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04 = new TTreeFormula( "leptons_NOMINAL_effSF_e17_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_e17_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04", this->fTree);
  this->leptons_NOMINAL_effSF_e17_lhloose_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04 = new TTreeFormula( "leptons_NOMINAL_effSF_e17_lhloose_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04", "leptons_NOMINAL_effSF_e17_lhloose_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04", this->fTree);

  
  return true;
}
 
//______________________________________________________________________________________________

bool TriggerWeight_ll_v05::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();
  
  delete EVS;
  delete EVS_fake;

  delete this->leptons;
  delete this->leptons_pt;
  delete this->leptons_id_loose;
  delete this->leptons_id_medium;
  delete this->leptons_id_tight;
  delete this->leptons_iso_wp;
  delete this->leptons_HLT_e24_lhmedium_L1EM18VH;
  delete this->leptons_HLT_e60_lhmedium;
  delete this->leptons_HLT_e120_lhloose;
  delete this->leptons_HLT_mu20_iloose_L1MU15;
  delete this->leptons_HLT_mu50;
  delete this->HLT_e17_loose_mu14;
  delete this->HLT_mu18_mu8noL1;
  delete this->HLT_2e12_lhloose_L12EM10VH;
  delete this->leptons_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE;
  delete this->leptons_NOMINAL_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE;
  delete this->leptons_NOMINAL_HLT_mu18_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE;
  delete this->leptons_NOMINAL_HLT_mu18_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE;
  delete this->leptons_NOMINAL_HLT_mu8noL1_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE;
  delete this->leptons_NOMINAL_HLT_mu8noL1_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE;
  delete this->leptons_NOMINAL_HLT_mu14_MU_TRIG_QUAL_MEDIUM_MU_TRIG_ISO_NONE;
  delete this->leptons_NOMINAL_HLT_mu14_MU_TRIG_QUAL_TIGHT_MU_TRIG_ISO_NONE;
  delete this->leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_e12_lhloose_L1EM10VH_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_e17_lhloose_LooseAndBLayerLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_e17_lhloose_MediumLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_e17_lhloose_TightLLH_d0z0_v8_2015_13TeV_rel20p0_25ns_v04;
  delete this->leptons_NOMINAL_effSF_e17_lhloose_TightLLH_d0z0_v8_isolLoose_2015_13TeV_rel20p0_25ns_v04;
  
  

  return true;
}
