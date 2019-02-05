#include "Htautau2015/SF_MVX_ll_v05.h"
#include <limits>

// uncomment the following line to enable debug printouts
//#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
#include "Htautau2015/EventSelection_leplep_default.h"

ClassImp(SF_MVX_ll_v05)

//______________________________________________________________________________________________

SF_MVX_ll_v05::SF_MVX_ll_v05(){
  // default constructor
 
  this->setExpression(this->GetName() );

  std::cout << "default constructor called" << std::endl;
  
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

SF_MVX_ll_v05::~SF_MVX_ll_v05(){
  // default destructor
  DEBUGclass("destructor called");
} 


//______________________________________________________________________________________________

TObjArray* SF_MVX_ll_v05::getBranchNames() const {
  // retrieve the list of branch names 
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString(jets_effSF_MVX_name));
  bnames->Add(new TObjString(jets_ineffSF_MVX_name));
  bnames->Add(new TObjString("jets_pt"));
  bnames->Add(new TObjString("jets_eta"));
  bnames->Add(new TObjString("jets_mvx_tagged"));

  return bnames;
}

//______________________________________________________________________________________________

double SF_MVX_ll_v05::getValue() const {
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
  jets_effSF_MVX->GetNdata();
  jets_ineffSF_MVX->GetNdata();
  jets_pt->GetNdata();
  jets_eta->GetNdata();
  jets_mvx_tagged->GetNdata();

  double SF_MVX = 1.;
  double SF_MVX_nom = 1.;

  int nJets= 0;
  nJets = EVS->getNJet();

  for(int i=0; i<nJets; i++){
    int idx=EVS->getJetIdx(i);
    double pt = jets_pt->EvalInstance(idx);
    double eta = jets_eta->EvalInstance(idx);
    double tagged = jets_mvx_tagged->EvalInstance(idx);
    if(pt >= 25*1000. && fabs(eta) <= 2.5 && tagged != 0){
      SF_MVX_nom *= this->jets_effSF_MVX->EvalInstance(idx);
    }
    else {
      SF_MVX_nom *= this->jets_ineffSF_MVX->EvalInstance(idx);
    }
  }

  // check here for nom, sys up, sys down
  SF_MVX *= SF_MVX_nom;

  DEBUGclass("returning");

  return SF_MVX;
}
//______________________________________________________________________________________________

SF_MVX_ll_v05::SF_MVX_ll_v05(const TString& expression, int systematic):
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

const TString& SF_MVX_ll_v05::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool SF_MVX_ll_v05::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void SF_MVX_ll_v05::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool SF_MVX_ll_v05::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void SF_MVX_ll_v05::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString SF_MVX_ll_v05::getActiveExpression() const {
  // retrieve the expression associated with this incarnation
  
  return this->getExpression();
}

//______________________________________________________________________________________________

bool SF_MVX_ll_v05::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  // this->bla = new TTreeFormula( "name", "formula", this->fTree);
  switch (m_systematic) {
      case 0: 
          jets_effSF_MVX_name="jets_NOMINAL_effSF_MVX";
          jets_ineffSF_MVX_name="jets_NOMINAL_ineffSF_MVX";
          break;
      case 1:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_B_0_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_B_0_1down_ineffSF_MVX";
          break;
      case 2:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_B_0_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_B_0_1up_ineffSF_MVX";
          break;
      case 3:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_B_1_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_B_1_1down_ineffSF_MVX";
          break;
      case 4:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_B_1_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_B_1_1up_ineffSF_MVX";
          break;
      case 5:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_B_2_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_B_2_1down_ineffSF_MVX";
          break;
      case 6:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_B_2_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_B_2_1up_ineffSF_MVX";
          break;
      case 7:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_B_3_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_B_3_1down_ineffSF_MVX";
          break;
      case 8:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_B_3_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_B_3_1up_ineffSF_MVX";
          break;
      case 9:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_B_4_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_B_4_1down_ineffSF_MVX";
          break;
      case 10:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_B_4_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_B_4_1up_ineffSF_MVX";
          break;
      case 11:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_C_0_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_C_0_1down_ineffSF_MVX";
          break;
      case 12:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_C_0_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_C_0_1up_ineffSF_MVX";
          break;
      case 13:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_C_1_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_C_1_1down_ineffSF_MVX";
          break;
      case 14:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_C_1_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_C_1_1up_ineffSF_MVX";
          break;
      case 15:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_C_2_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_C_2_1down_ineffSF_MVX";
          break;
      case 16:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_C_2_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_C_2_1up_ineffSF_MVX";
          break;
      case 17:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_C_3_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_C_3_1down_ineffSF_MVX";
          break;
      case 18:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_C_3_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_C_3_1up_ineffSF_MVX";
          break;
      case 19:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_0_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_0_1down_ineffSF_MVX";
          break;
      case 20:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_0_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_0_1up_ineffSF_MVX";
          break;
      case 21:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_1_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_1_1down_ineffSF_MVX";
          break;
      case 22:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_1_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_1_1up_ineffSF_MVX";
          break;
      case 23:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_10_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_10_1down_ineffSF_MVX";
          break;
      case 24:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_10_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_10_1up_ineffSF_MVX";
          break;
      case 25:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_11_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_11_1down_ineffSF_MVX";
          break;
      case 26:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_11_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_11_1up_ineffSF_MVX";
          break;
      case 27:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_12_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_12_1down_ineffSF_MVX";
          break;
      case 28:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_12_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_12_1up_ineffSF_MVX";
          break;
      case 29:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_13_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_13_1down_ineffSF_MVX";
          break;
      case 30:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_13_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_13_1up_ineffSF_MVX";
          break;
      case 31:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_2_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_2_1down_ineffSF_MVX";
          break;
      case 32:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_2_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_2_1up_ineffSF_MVX";
          break;
      case 33:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_3_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_3_1down_ineffSF_MVX";
          break;
      case 34:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_3_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_3_1up_ineffSF_MVX";
          break;
      case 35:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_4_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_4_1down_ineffSF_MVX";
          break;
      case 36:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_4_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_4_1up_ineffSF_MVX";
          break;
      case 37:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_5_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_5_1down_ineffSF_MVX";
          break;
      case 38:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_5_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_5_1up_ineffSF_MVX";
          break;
      case 39:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_6_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_6_1down_ineffSF_MVX";
          break;
      case 40:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_6_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_6_1up_ineffSF_MVX";
          break;
      case 41:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_7_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_7_1down_ineffSF_MVX";
          break;
      case 42:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_7_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_7_1up_ineffSF_MVX";
          break;
      case 43:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_8_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_8_1down_ineffSF_MVX";
          break;
      case 44:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_8_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_8_1up_ineffSF_MVX";
          break;
      case 45:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_9_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_9_1down_ineffSF_MVX";
          break;
      case 46:
          jets_effSF_MVX_name="jets_FT_EFF_Eigen_Light_9_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_Eigen_Light_9_1up_ineffSF_MVX";
          break;
      case 47:
          jets_effSF_MVX_name="jets_FT_EFF_extrapolation_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_extrapolation_1down_ineffSF_MVX";
          break;
      case 48:
          jets_effSF_MVX_name="jets_FT_EFF_extrapolation_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_extrapolation_1up_ineffSF_MVX";
          break;
      case 49:
          jets_effSF_MVX_name="jets_FT_EFF_extrapolation_from_charm_1down_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_extrapolation_from_charm_1down_ineffSF_MVX";
          break;
      case 50:
          jets_effSF_MVX_name="jets_FT_EFF_extrapolation_from_charm_1up_effSF_MVX";
          jets_ineffSF_MVX_name="jets_FT_EFF_extrapolation_from_charm_1up_ineffSF_MVX";
  }
  this->jets_effSF_MVX   = new TTreeFormula("jets_effSF_MVX"     , jets_effSF_MVX_name , this->fTree);
  this->jets_ineffSF_MVX = new TTreeFormula("jets_ineffSF_MVX"   , jets_ineffSF_MVX_name, this->fTree);
  this->jets_pt = new TTreeFormula("jets_pt"   , "jets_pt", this->fTree);
  this->jets_eta = new TTreeFormula("jets_eta"   , "jets_eta", this->fTree);
  this->jets_mvx_tagged = new TTreeFormula("jets_mvx_tagged"   , "jets_mvx_tagged", this->fTree);

  EVS = new EventSelection_leplep_default();

  return true;
}
 
//______________________________________________________________________________________________

bool SF_MVX_ll_v05::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete this->jets_effSF_MVX;
  delete this->jets_ineffSF_MVX;
  delete this->jets_pt;
  delete this->jets_eta;
  delete this->jets_mvx_tagged;

  delete EVS;

  return true;
}
