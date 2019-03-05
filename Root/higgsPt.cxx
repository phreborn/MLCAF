#include "BSMtautauCAF/higgsPt.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(higgsPt)

//______________________________________________________________________________________________

higgsPt::higgsPt(){
  // default constructor
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

higgsPt::~higgsPt(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* higgsPt::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();
  bnames->SetOwner(false);
  bnames->Add(new TObjString("tau_0_pt"));
  bnames->Add(new TObjString("lep_0_pt"));
  bnames->Add(new TObjString("tau_0_phi"));
  bnames->Add(new TObjString("lep_0_phi"));
  bnames->Add(new TObjString("met_reco_ety"));
  bnames->Add(new TObjString("met_reco_etx"));

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  return bnames;
}

//______________________________________________________________________________________________

double higgsPt::getValue() const {
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

  float f_lep_0_pt                = this->lep_0_pt->EvalInstance();
  float f_tau_0_pt                = this->tau_0_pt->EvalInstance();
  float f_lep_0_phi               = this->lep_0_phi->EvalInstance();
  float f_tau_0_phi               = this->tau_0_phi->EvalInstance();
  float f_met_reco_ety            = this->met_reco_ety->EvalInstance();
  float f_met_reco_etx            = this->met_reco_etx->EvalInstance();



  // higgs pt is the modulus of a vector sum of lep, tau and met
  float px = f_lep_0_pt*std::cos(f_lep_0_phi) + f_tau_0_pt*std::cos(f_tau_0_phi) + f_met_reco_etx;
  float py = f_lep_0_pt*std::sin(f_lep_0_phi) + f_tau_0_pt*std::sin(f_tau_0_phi) + f_met_reco_ety;
  float lephad_higgs_pt = std::sqrt( px*px + py*py );

  DEBUGclass("returning");
  return lephad_higgs_pt;
}
//______________________________________________________________________________________________

bool higgsPt::initializeSelf(){
  // initialize this observable on a sample/tree
  DEBUGclass("initializing");
  LepHadObservable::initializeSelf();
  // since this function is only called once per sample, we can
  // perform any checks that seem necessary
  if(!this->fTree){
    DEBUGclass("no tree, terminating");
    return false;
  }

  // if you want to use a TTreeFormula, can may construct it here
  /* example block for TTreeFormula method:
  this->fFormula = new TTreeFormula("branch1 + branch2",this->fTree);
  */

  // if you want to use the TTree::SetBranchAddress method, you can
  // call TTree::SetBranchAddress here
  // please note that this method is highly discouraged.
  // if a branch you access via this method is used by any other
  // observable, you will 'steal' the branch address from that
  // observable, leading to the other observable returning wrong
  // results
  /* example block for TTree::SetBranchAddress method:
  this->fTree->SetBranchAddress("branch1",&(this->fBranch1));
  this->fTree->SetBranchAddress("branch2",&(this->fBranch2));
  */

  return true;
}

//______________________________________________________________________________________________

bool higgsPt::finalizeSelf(){
  // finalize this observable on a sample/tree
  DEBUGclass("finalizing");
  // here, you should undo anything that you did while initializing
  /* example block for TTreeFormula method:
  delete this->fFormula;
  this->fFormula = NULL;
  */

  return true;
}
//______________________________________________________________________________________________

higgsPt::higgsPt(const TString& name):
LepHadObservable(name)
{
  // constructor with name argument
  DEBUGclass("constructor called with '%s'",name.Data());
}
