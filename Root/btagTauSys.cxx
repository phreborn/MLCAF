#include "Htautau/btagTauSys.h"
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

ClassImp(btagTauSys)

//______________________________________________________________________________________________

btagTauSys::btagTauSys(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

btagTauSys::~btagTauSys(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* btagTauSys::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("bjet_sf_MVX_FT_EFF_extrapolation from charm_1down_sf"));
  bnames->Add(new TObjString("bjet_sf_MVX_FT_EFF_extrapolation from charm_1down_ineff_sf"));
  bnames->Add(new TObjString("bjet_sf_MVX_FT_EFF_extrapolation from charm_1up_sf"));
  bnames->Add(new TObjString("bjet_sf_MVX_FT_EFF_extrapolation from charm_1up_ineff_sf"));

  return bnames;
}

//______________________________________________________________________________________________

double btagTauSys::getValue() const {
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

  float retval = 0;
  std::cout<<"  retval : " << retval << std::endl;
  std::cout<<"  charmExSys_down_sf: "       << charmExSys_down_sf       <<std::endl;
  std::cout<<"  charmExSys_down_ineff_sf: " << charmExSys_down_ineff_sf <<std::endl;
  std::cout<<"  charmExSys_up_sf: "         << charmExSys_up_sf         <<std::endl;
  std::cout<<"  charmExSys_up_ineff_sf: "   << charmExSys_up_ineff_sf   <<std::endl;

  DEBUGclass("returning");
  //return 0;
  return retval;
}
//______________________________________________________________________________________________

btagTauSys::btagTauSys(const TString& expression):
TQTreeObservable(expression)
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

const TString& btagTauSys::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool btagTauSys::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void btagTauSys::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool btagTauSys::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void btagTauSys::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString btagTauSys::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool btagTauSys::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))) {
    return false;
  }

  //this->btagCharmSyscharm_1down_sf       = new TTreeFormula( "bjet_sf_MVX_FT_EFF_extrapolation from charm_1down_sf",       "bjet_sf_MVX_FT_EFF_extrapolation from charm_1down_sf",        this->fTree);
  //this->btagCharmSyscharm_1down_ineff_sf = new TTreeFormula( "bjet_sf_MVX_FT_EFF_extrapolation from charm_1down_ineff_sf", "bjet_sf_MVX_FT_EFF_extrapolation from charm_1down_ineff_sf",  this->fTree);
  //this->btagCharmSyscharm_1up_sf         = new TTreeFormula( "bjet_sf_MVX_FT_EFF_extrapolation from charm_1up_sf",         "bjet_sf_MVX_FT_EFF_extrapolation from charm_1up_sf",          this->fTree);
  //this->btagCharmSyscharm_1up_ineff_sf   = new TTreeFormula( "bjet_sf_MVX_FT_EFF_extrapolation from charm_1up_ineff_sf",   "bjet_sf_MVX_FT_EFF_extrapolation from charm_1up_ineff_sf",    this->fTree);

  fTree->Print();
  std::cout<<" add: "<< fTree->SetBranchAddress( "bjet_sf_MVX_FT_EFF_extrapolation from charm_1down_sf",       &charmExSys_down_sf)        <<std::endl;
  std::cout<<" add: "<< fTree->SetBranchAddress( "bjet_sf_MVX_FT_EFF_extrapolation from charm_1down_ineff_sf", &charmExSys_down_ineff_sf ) <<std::endl;
  std::cout<<" add: "<< fTree->SetBranchAddress( "bjet_sf_MVX_FT_EFF_extrapolation from charm_1up_sf",         &charmExSys_up_sf )         <<std::endl;
  std::cout<<" add: "<< fTree->SetBranchAddress( "bjet_sf_MVX_FT_EFF_extrapolation from charm_1up_ineff_sf",   &charmExSys_up_ineff_sf )   <<std::endl;

  return true;
}

//______________________________________________________________________________________________

bool btagTauSys::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  //delete this->btagCharmSyscharm_1down_sf      ;
  //delete this->btagCharmSyscharm_1down_ineff_sf;
  //delete this->btagCharmSyscharm_1up_sf        ;
  //delete this->btagCharmSyscharm_1up_ineff_sf  ;

  return true;
}
