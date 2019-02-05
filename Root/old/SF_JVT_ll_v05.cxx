#include "Htautau2015/SF_JVT_ll_v05.h"
#include <limits>

// uncomment the following line to enable debug printouts
//#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
#include "Htautau2015/EventSelection_leplep_default.h"

ClassImp(SF_JVT_ll_v05)

//______________________________________________________________________________________________

SF_JVT_ll_v05::SF_JVT_ll_v05(){
  // default constructor
 
  this->setExpression(this->GetName() );

  std::cout << "default constructor called" << std::endl;
  
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

SF_JVT_ll_v05::~SF_JVT_ll_v05(){
  // default destructor
  DEBUGclass("destructor called");
} 


//______________________________________________________________________________________________

TObjArray* SF_JVT_ll_v05::getBranchNames() const {
  // retrieve the list of branch names 
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));
  
  bnames->Add(new TObjString(jets_effSF_JVT_name));
  
  return bnames;
}

//______________________________________________________________________________________________

double SF_JVT_ll_v05::getValue() const {
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
  double SF_JVT_nom= 1.;

  jets_effSF_JVT->GetNdata();
  int NJets = EVS->getNJet();

  //std::cout << "I have n selected jets: " << NJets << std::endl;

  for (uint i=0; i<NJets; i++){
    int idx = EVS->getJetIdx(i);
    //std::cout << "i: " << i << " idx: " << idx << std::endl;
    double SF_tmp  = this->jets_effSF_JVT->EvalInstance(idx);
    //std::cout << "SF: " << SF_JVT_nom << std::endl;
    SF_JVT_nom *=SF_tmp;
  }

  double SF_JVT = 1.;
  // check here for nom, sys up, sys down
  SF_JVT *= SF_JVT_nom;

  DEBUGclass("returning");

  return SF_JVT;
}
//______________________________________________________________________________________________

SF_JVT_ll_v05::SF_JVT_ll_v05(const TString& expression, int systematic):
TQTreeObservable(expression),m_systematic(systematic)
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

const TString& SF_JVT_ll_v05::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool SF_JVT_ll_v05::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void SF_JVT_ll_v05::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool SF_JVT_ll_v05::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void SF_JVT_ll_v05::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString SF_JVT_ll_v05::getActiveExpression() const {
  // retrieve the expression associated with this incarnation
  
  return this->getExpression();
}

//______________________________________________________________________________________________

bool SF_JVT_ll_v05::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  // this->bla = new TTreeFormula( "name", "formula", this->fTree);

  EVS = new EventSelection_leplep_default();


  if (m_systematic ==0 ) { 
      jets_effSF_JVT_name="jets_NOMINAL_effSF_JVT";
  }
  else if (m_systematic <0) {
      jets_effSF_JVT_name="jets_JvtEfficiencyDown_effSF_JVT";
      DEBUGclass("JET SF down");
  }
  else if (m_systematic >0) {
      jets_effSF_JVT_name="jets_JvtEfficiencyUp_effSF_JVT";
  }


  //std::cout << "JVT name: " << jets_effSF_JVT_name << std::endl;
  
  this->jets_effSF_JVT = new TTreeFormula( "jets_effSF_JVT", jets_effSF_JVT_name, this->fTree);
  DEBUGclass("JET SF "+jets_effSF_JVT_name);
   
  return true;
}
 
//______________________________________________________________________________________________

bool SF_JVT_ll_v05::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete EVS;
  delete this->jets_effSF_JVT;

  return true;
}
