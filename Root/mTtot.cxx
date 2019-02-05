#include "Htautau/mTtot.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(mTtot)

//______________________________________________________________________________________________

mTtot::mTtot(){
  // default constructor
  this->setExpression(this->GetName() );
  DEBUGclass("default constructor called");
}
//______________________________________________________________________________________________

mTtot::mTtot(const TString& expression) : LepHadObservable(expression)
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

mTtot::~mTtot(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* mTtot::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();
  bnames->SetOwner(false);
  bnames->Add(new TObjString("tau_0_pt"));
  bnames->Add(new TObjString("lep_0_pt"));
  bnames->Add(new TObjString("lephad_mt_lep0_met"));
  bnames->Add(new TObjString("lephad_mt_lep1_met"));
  bnames->Add(new TObjString("lephad_dphi"));


  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  return bnames;
}

//______________________________________________________________________________________________

double mTtot::getValue() const {
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

  float f_lephad_mt_lep0_met      = this->lephad_mt_lep0_met->EvalInstance();
  float f_lephad_mt_lep1_met      = this->lephad_mt_lep1_met->EvalInstance();
  float f_lep_0_pt                = this->lep_0_pt->EvalInstance();
  float f_tau_0_pt                = this->tau_0_pt->EvalInstance();
  float f_lephad_dphi             = this->lephad_dphi->EvalInstance();

  float retval = std::sqrt(f_lephad_mt_lep0_met*f_lephad_mt_lep0_met + f_lephad_mt_lep1_met*f_lephad_mt_lep1_met + 2.*f_lep_0_pt*f_tau_0_pt*(1-cos(f_lephad_dphi)) );

  DEBUGclass("returning");
  return retval;
}
//______________________________________________________________________________________________

bool mTtot::initializeSelf(){
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
  this->tau_0_pt = new TTreeFormula( "tau_0_pt", "tau_0_p4.Pt()", this->fTree);
  this->lep_0_pt = new TTreeFormula( "lep_0_pt", "lep_0_p4.Pt()", this->fTree);
  this->lephad_mt_lep0_met = new TTreeFormula( "lephad_mt_lep0_met", "lephad_mt_lep0_met", this->fTree);
  this->lephad_mt_lep1_met = new TTreeFormula( "lephad_mt_lep1_met", "lephad_mt_lep1_met", this->fTree);
  this->lephad_dphi = new TTreeFormula( "lephad_dphi", "lephad_dphi", this->fTree);


}

//______________________________________________________________________________________________

bool mTtot::finalizeSelf(){
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

const TString& mTtot::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool mTtot::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void mTtot::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
