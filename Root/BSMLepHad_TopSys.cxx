#include "Htautau/BSMLepHad_TopSys.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
#include "TFile.h"
#include <map>

ClassImp(BSMLepHad_TopSys)

//______________________________________________________________________________________________

BSMLepHad_TopSys::BSMLepHad_TopSys(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

BSMLepHad_TopSys::~BSMLepHad_TopSys(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* BSMLepHad_TopSys::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("lep_0_pt"));
  bnames->Add(new TObjString("tau_0_pt"));
  bnames->Add(new TObjString("lephad_mt_lep0_met"));
  bnames->Add(new TObjString("lephad_mt_lep1_met"));
  bnames->Add(new TObjString("lephad_dphi"));


  return bnames;
}

//______________________________________________________________________________________________

double BSMLepHad_TopSys::getValue() const {
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

  //std::cout<<" In getValue "<<std::endl;

  double f_lep_0_pt       = this->lep_0_pt->EvalInstance();
  double f_tau_0_pt       = this->tau_0_pt->EvalInstance();
  double f_lepmet_mt1     = this->lephad_mt_lep0_met->EvalInstance();
  double f_lepmet_mt2     = this->lephad_mt_lep1_met->EvalInstance();
  double f_lephad_dphi    = this->lephad_dphi->EvalInstance();

  double mttot = std::sqrt(f_lepmet_mt1*f_lepmet_mt1 + f_lepmet_mt2*f_lepmet_mt2 + 2.*f_lep_0_pt*f_tau_0_pt*(1-cos(f_lephad_dphi)) );

  double cor_Rad  = 1.11 - 0.0007 * mttot;
  double cor_ShUe = 1.18 - 0.0015 * mttot + 1.5 * 0.000001 * mttot * mttot;
  if(mttot>500) {
   cor_ShUe = 1.18 - 0.0015 * 500 + 1.5 * 0.000001 * 500 * 500;
  }

  double retval(1);

  if( fSysName.Contains("TTBAR_Radiation_1up") ) {
    retval = cor_Rad;
  }
  if( fSysName.Contains("TTBAR_Radiation_1down") ) {
    retval = -1*(cor_Rad - 1) + 1;
  }

  if( fSysName.Contains("TTBAR_ShowerUE_1up") ) {
    retval = cor_ShUe;
  }
  if( fSysName.Contains("TTBAR_ShowerUE_1down") ) {
    retval = -1*(cor_ShUe - 1) + 1;
  }

  DEBUGclass("returning");
  //return 0;
  return retval;
}
//______________________________________________________________________________________________

BSMLepHad_TopSys::BSMLepHad_TopSys(const TString& expression):
LepHadObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  fSysName = expression;
}

//______________________________________________________________________________________________

const TString& BSMLepHad_TopSys::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool BSMLepHad_TopSys::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void BSMLepHad_TopSys::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool BSMLepHad_TopSys::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void BSMLepHad_TopSys::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString BSMLepHad_TopSys::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool BSMLepHad_TopSys::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  this->lephad_dphi        = new TTreeFormula( "lephad_dphi",              "lephad_dphi",              this->fTree);
  this->tau_0_pt           = new TTreeFormula( "tau_0_pt",           "tau_0_p4.Pt()",           this->fTree);
  this->lep_0_pt           = new TTreeFormula( "lep_0_pt",           "lep_0_p4.Pt()",           this->fTree);
  this->lephad_mt_lep0_met = new TTreeFormula( "lephad_mt_lep0_met", "lephad_mt_lep0_met", this->fTree);
  this->lephad_mt_lep1_met = new TTreeFormula( "lephad_mt_lep1_met", "lephad_mt_lep1_met", this->fTree);

  return true;
}

//______________________________________________________________________________________________

bool BSMLepHad_TopSys::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete this->lephad_dphi;
  delete this->tau_0_pt;
  delete this->lep_0_pt;
  delete this->lephad_mt_lep0_met;
  delete this->lephad_mt_lep1_met;

  return true;
}
