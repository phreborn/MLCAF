#include "Htautau/mcWeight.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(mcWeight)

//______________________________________________________________________________________________

mcWeight::mcWeight(){
  // default constructor
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

mcWeight::~mcWeight(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* mcWeight::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();
  bnames->SetOwner(false);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));
  bnames->Add(new TObjString("weight_mc"));
  bnames->Add(new TObjString("NOMINAL_pileup_combined_weight"));
  return bnames;
}

//______________________________________________________________________________________________

double mcWeight::getValue() const {
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
  double    temp_weight_mc = 1., temp_puweight = 1.;
  if(this->weight_mc)   temp_weight_mc = this->weight_mc->EvalInstance();
  if(this->NOMINAL_pileup_combined_weight)   temp_puweight = this->NOMINAL_pileup_combined_weight->EvalInstance();
  DEBUGclass("returning");
  return temp_weight_mc*temp_puweight;
}
//______________________________________________________________________________________________

bool mcWeight::initializeSelf(){
  // initialize this observable on a sample/tree
  DEBUGclass("initializing");

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
  if(this->fTree->FindLeaf("weight_mc")) this->weight_mc = new TTreeFormula( "weight_mc",    "weight_mc",    this->fTree);
  if(this->fTree->FindLeaf("NOMINAL_pileup_combined_weight")) this->NOMINAL_pileup_combined_weight = new TTreeFormula( "NOMINAL_pileup_combined_weight",    "NOMINAL_pileup_combined_weight",    this->fTree);
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

bool mcWeight::finalizeSelf(){
  // finalize this observable on a sample/tree
  DEBUGclass("finalizing");
  // here, you should undo anything that you did while initializing
  /* example block for TTreeFormula method:
  delete this->fFormula;
  this->fFormula = NULL;
  */
  if(this->weight_mc) delete this->weight_mc;
  this->weight_mc = NULL;
  if(this->NOMINAL_pileup_combined_weight) delete this->NOMINAL_pileup_combined_weight;
  this->NOMINAL_pileup_combined_weight = NULL;
  return true;
}
//______________________________________________________________________________________________

mcWeight::mcWeight(const TString& name):
TQTreeObservable(name)
{
  // constructor with name argument
  DEBUGclass("constructor called with '%s'",name.Data());
}
