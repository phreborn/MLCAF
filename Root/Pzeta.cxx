#include "Htautau/Pzeta.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
#include "TVector3.h"

ClassImp(Pzeta)

//______________________________________________________________________________________________

Pzeta::Pzeta(){
  // default constructor
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

Pzeta::~Pzeta(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* Pzeta::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();
  bnames->SetOwner(false);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("met_reco_phi"));
  bnames->Add(new TObjString("lep_0_phi"));
  bnames->Add(new TObjString("lep_0_iso_Gradient"));
  bnames->Add(new TObjString("tau_0_phi"));

  return bnames;
}

//______________________________________________________________________________________________

double Pzeta::getValue() const {
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
  float f_lep_0_phi                = this->lep_0_phi->EvalInstance();
  float f_lep_0_pt                 = this->lep_0_pt->EvalInstance();
  float f_tau_0_phi                = this->tau_0_phi->EvalInstance();
  float f_tau_0_pt                 = this->tau_0_pt->EvalInstance();
  float f_met_reco_phi             = this->met_reco_phi->EvalInstance();
  float f_met_reco_et              = this->met_reco_et->EvalInstance();
  int   f_lep_0_iso_Gradient       = this->lep_0_iso_Gradient->EvalInstance();


  float zeta_phi   = p_z_phi_custom(f_lep_0_phi, f_tau_0_phi, 0.);
  float P_zeta_vis = p_z_vis(zeta_phi, f_lep_0_pt, f_lep_0_phi, f_tau_0_pt, f_tau_0_phi);
  float P_zeta=0;

  P_zeta = p_z(zeta_phi, f_lep_0_pt, f_lep_0_phi, f_tau_0_pt, f_tau_0_phi, f_met_reco_et, f_met_reco_phi);



  DEBUGclass("returning");
  return P_zeta - 3. * P_zeta_vis;
}
//______________________________________________________________________________________________


float Pzeta::p_z_phi_custom(float lep_phi, float tau_phi, float frac) const{
   double var;
   TVector3 Vlep(1., 1., 1.);
   TVector3 Vtau(1., 1., 1.);
   TVector3 temp1(1., 1., 1.);
   TVector3 temp2(1., 1., 1.);

   Vlep.SetPhi(lep_phi);
   Vtau.SetPhi(tau_phi);

   // Find difference of angles:
   double dphi = Vlep.DeltaPhi(Vtau);

   // Add to correct direction of lepton axis
   temp1.SetPhi(lep_phi + frac*fabs(dphi));
   temp2.SetPhi(lep_phi - frac*fabs(dphi));

   double dphi1 = Vtau.DeltaPhi(temp1);
   double dphi2 = Vtau.DeltaPhi(temp2);

   // Switch direction from lep axis if negative fraction
   if (frac>0.){
      if (fabs(dphi1)<fabs(dphi2)) var = temp1.Phi();
      else var = temp2.Phi();}
   else{
      if (fabs(dphi1)>fabs(dphi2)) var = temp1.Phi();
      else var = temp2.Phi();}

   return var;
}

// To calculate the P_zeta_vis variable. Provide phi of zeta axis (calculated above), lepton transverse momentum and phi, and tau transverse momentum and phi.

float Pzeta::p_z_vis(float p_z_phi, float lep_pt, float lep_phi, float tau_pt, float tau_phi)const{
   float var;
   var = lep_pt * cos(lep_phi - p_z_phi) + tau_pt * cos(tau_phi - p_z_phi);
   return var;
}

// To calculate the P_zeta variable. Provide same variables as to the P_zeta_vis function, in addition with the MET and phi of the MET.

float Pzeta::p_z(float p_z_phi, float lep_pt, float lep_phi, float tau_pt, float tau_phi, float met_et, float met_phi)const{
   float var;
   var = lep_pt * cos(lep_phi - p_z_phi) + tau_pt * cos(tau_phi - p_z_phi) + met_et * cos(met_phi - p_z_phi);
   return var;
}


bool Pzeta::initializeSelf(){
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


  this->lep_0_phi                 = new TTreeFormula( "lep_0_phi",     "lep_0_p4.Phi()",      this->fTree);
  this->lep_0_pt                  = new TTreeFormula( "lep_0_pt",     "lep_0_p4.Pt()",      this->fTree);
  this->tau_0_phi                 = new TTreeFormula( "tau_0_phi",     "tau_0_p4.Phi()",      this->fTree);
  this->tau_0_pt                  = new TTreeFormula( "tau_0_pt",       "tau_0_p4.Pt()",      this->fTree);
  this->met_reco_phi              = new TTreeFormula( "met_reco_phi",     "met_reco_p4.Phi()",      this->fTree);
  this->met_reco_et               = new TTreeFormula( "met_reco_et",     "met_reco_p4.Et()",      this->fTree);
  this->lep_0_iso_Gradient        = new TTreeFormula( "lep_0_iso_Gradient",     "lep_0_iso_Gradient",      this->fTree);
  return true;
}

//______________________________________________________________________________________________

bool Pzeta::finalizeSelf(){
  // finalize this observable on a sample/tree
  DEBUGclass("finalizing");
  // here, you should undo anything that you did while initializing
  /* example block for TTreeFormula method:
  delete this->fFormula;
  this->fFormula = NULL;
  */

  delete this->lep_0_phi;
  delete this->lep_0_pt;
  delete this->tau_0_phi;
  delete this->tau_0_pt;
  delete this->met_reco_phi;
  delete this->met_reco_et;
  delete this->lep_0_iso_Gradient;

  return true;
}
//______________________________________________________________________________________________

Pzeta::Pzeta(const TString& name):
LepHadObservable(name)
{
  // constructor with name argument
  DEBUGclass("constructor called with '%s'",name.Data());
}
