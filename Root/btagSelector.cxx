#include "Htautau/btagSelector.h"
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

ClassImp(btagSelector)

//______________________________________________________________________________________________

btagSelector::btagSelector(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

btagSelector::~btagSelector(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* btagSelector::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("jetPt"));
  bnames->Add(new TObjString("jetMv2c20"));

  return bnames;
}

//______________________________________________________________________________________________

double btagSelector::getValue() const {
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
  //std::cout<<"  retval : " << retval << std::endl;
  //std::cout<<"  jetPt    : "  <<  vjetPt    ->size() <<std::endl;
  //std::cout<<"  jetMv2c20: "  <<  vjetMv2c20->size() <<std::endl;

  for(int ijet=0; ijet<vjetPt->size(); ijet++) {

    if( (*vjetMv2c20)[ijet]>-0.0436)  retval = 1;

  }

  // b-tag information
  // name weight cut   b-jet  efficiency [%]  purity [%]  c RR   tau RR  light RR
  // FixedCutBEff_30   0.9540   30.17         99.87      686.23  4609.15 52788.25
  // FixedCutBEff_50   0.7535   50.26         99.11      61.25   318.80  6683.46
  // FixedCutBEff_60   0.4496   60.27         97.83      21.32   94.04   1704.54
  // FixedCutBEff_70  -0.0436   70.26         94.86      8.03    26.59   405.37
  // FixedCutBEff_77  -0.4434   77.25         90.90      4.51    9.84    125.93
  // FixedCutBEff_80  -0.5911   80.24         88.45      3.62    6.77    71.70
  // FixedCutBEff_85  -0.7887   85.22         82.75      2.60    3.83    27.16
  // FixedCutBEff_90  -0.9185   90.17         72.89      1.95    2.14    9.27

  DEBUGclass("returning");
  //return 0;
  return retval;
}
//______________________________________________________________________________________________

btagSelector::btagSelector(const TString& expression):
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

const TString& btagSelector::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool btagSelector::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void btagSelector::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool btagSelector::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void btagSelector::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString btagSelector::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool btagSelector::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))) {
    return false;
  }

  fTree->SetBranchAddress( "jetPt",     &vjetPt     );
  fTree->SetBranchAddress( "jetMv2c20", &vjetMv2c20 );

  return true;
}

//______________________________________________________________________________________________

bool btagSelector::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  return true;
}
