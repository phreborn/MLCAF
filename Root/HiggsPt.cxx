#include "BSMtautauCAF/HiggsPt.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(HiggsPt)

//______________________________________________________________________________________________

HiggsPt::HiggsPt(const TString& expression):
LepHadObservable(expression)
{
  // constructor with name argument
  DEBUGclass("constructor called with '%s'",name.Data());
  
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);
}
//______________________________________________________________________________________________

HiggsPt::HiggsPt(){
  // default constructor
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

HiggsPt::~HiggsPt(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* HiggsPt::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();
  
  return bnames;
}

//______________________________________________________________________________________________

double HiggsPt::getValue() const {
  
  float f_lep_0_pt                = this->lep_0_pt->EvalInstance();
  float f_tau_0_pt                = this->tau_0_pt->EvalInstance();
  float f_lep_0_phi               = this->lep_0_phi->EvalInstance();
  float f_tau_0_phi               = this->tau_0_phi->EvalInstance();
  float f_met_reco_etx            = this->met_reco_etx->EvalInstance();
  float f_met_reco_ety            = this->met_reco_ety->EvalInstance();

  // higgs pt is the modulus of a vector sum of lep, tau and met
  float px = f_lep_0_pt*std::cos(f_lep_0_phi) + f_tau_0_pt*std::cos(f_tau_0_phi) + f_met_reco_etx;
  float py = f_lep_0_pt*std::sin(f_lep_0_phi) + f_tau_0_pt*std::sin(f_tau_0_phi) + f_met_reco_ety;
  float lephad_higgs_pt = std::sqrt( px*px + py*py );

  return lephad_higgs_pt;
}
//______________________________________________________________________________________________

bool HiggsPt::initializeSelf(){
  if (! LepHadObservable::initializeSelf()) return false;
  return true;
}

//______________________________________________________________________________________________

bool HiggsPt::finalizeSelf(){
  if (! LepHadObservable::finalizeSelf()) return false;
  return true;
}
