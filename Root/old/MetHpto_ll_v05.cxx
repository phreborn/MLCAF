#include "Htautau2015/MetHpto_ll_v05.h"
#include <limits>

// uncomment the following line to enable debug printouts
//#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
#include "Htautau2015/EventSelection_leplep_default.h"
#include "TVector3.h"

ClassImp(MetHpto_ll_v05)

//______________________________________________________________________________________________

MetHpto_ll_v05::MetHpto_ll_v05(){
  // default constructor
 
  this->setExpression(this->GetName() );
  
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

MetHpto_ll_v05::~MetHpto_ll_v05(){
  // default destructor
  DEBUGclass("destructor called");
} 


//______________________________________________________________________________________________

TObjArray* MetHpto_ll_v05::getBranchNames() const {
  // retrieve the list of branch names 
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));
  

  bnames->Add(new TObjString("leptons_pt"));
  bnames->Add(new TObjString("leptons_eta"));
  bnames->Add(new TObjString("leptons_phi"));
  bnames->Add(new TObjString("jets_pt"));
  bnames->Add(new TObjString("jets_eta"));
  bnames->Add(new TObjString("jets_phi"));
  
  return bnames;
}

//______________________________________________________________________________________________

double MetHpto_ll_v05::getValue() const {
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

  double retval = -1;
  double sumpx  = 0;
  double sumpy  = 0;

  leptons_pt->GetNdata();
  leptons_eta->GetNdata();
  leptons_phi->GetNdata();
  jets_pt->GetNdata();
  jets_eta->GetNdata();
  jets_phi->GetNdata();

  int idxlep0 = -1;
  int idxlep1 = -1;

  TVector3 lep0, lep1;
  lep0.Clear(); lep1.Clear();

  idxlep0 = EVS->getLeptonIdx(0);
  idxlep1 = EVS->getLeptonIdx(1);

  if(idxlep0 >=0 && idxlep1>=0){
    lep0.SetPtEtaPhi(leptons_pt->EvalInstance(idxlep0), leptons_eta->EvalInstance(idxlep0), leptons_phi->EvalInstance(idxlep0));
    lep1.SetPtEtaPhi(leptons_pt->EvalInstance(idxlep1), leptons_eta->EvalInstance(idxlep1), leptons_phi->EvalInstance(idxlep1));
  }
  //else {
  //  std::cout<< "WARNING in MetHpto:: Have negative lep indices!!" << std::endl;
  //}
  sumpx = -lep0.Px()-lep1.Px();
  sumpy = -lep0.Py()-lep1.Py();
  
  int nSelecJets = -1;
  nSelecJets = EVS->getNJet();
  //std::cout << "Have n selected jets: " << nSelecJets << std::endl;
  for(uint i=0; i<nSelecJets; i++){
    int idxjet = EVS->getJetIdx(i);
    //std::cout << "idx for jet "<< i << ": " << idxjet << std::endl; 
    TVector3 jet; jet.Clear();
    jet.SetPtEtaPhi(jets_pt->EvalInstance(idxjet), jets_eta->EvalInstance(idxjet), jets_phi->EvalInstance(idxjet));
    //std::cout << "pt: " << jet.Pt() << std::endl;
    if(jet.Pt()>25*1000.){
      //std::cout << "use this jet for hpto calculation" << std::endl;
      sumpx -= jet.Px();
      sumpy -= jet.Py();
    }
  }


  retval = sqrt(sumpx*sumpx+sumpy*sumpy);
  //std::cout << "retavl = " << retval << std::endl;

  DEBUGclass("returning");

  return retval;
}
//______________________________________________________________________________________________

MetHpto_ll_v05::MetHpto_ll_v05(const TString& expression):
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

const TString& MetHpto_ll_v05::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool MetHpto_ll_v05::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void MetHpto_ll_v05::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool MetHpto_ll_v05::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void MetHpto_ll_v05::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString MetHpto_ll_v05::getActiveExpression() const {
  // retrieve the expression associated with this incarnation
  
  return this->getExpression();
}

//______________________________________________________________________________________________

bool MetHpto_ll_v05::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  // this->bla = new TTreeFormula( "name", "formula", this->fTree);
  
  this->leptons_pt = new TTreeFormula( "leptons_pt", "leptons_pt", this->fTree);
  this->leptons_eta = new TTreeFormula( "leptons_eta", "leptons_eta", this->fTree);
  this->leptons_phi = new TTreeFormula( "leptons_phi", "leptons_phi", this->fTree);
  this->jets_pt = new TTreeFormula( "jets_pt", "jets_pt", this->fTree);
  this->jets_eta = new TTreeFormula( "jets_eta", "jets_eta", this->fTree);
  this->jets_phi = new TTreeFormula( "jets_phi", "jets_phi", this->fTree);

  EVS = new EventSelection_leplep_default();

  return true;
}
 
//______________________________________________________________________________________________

bool MetHpto_ll_v05::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();
  
  delete this->leptons_pt;  
  delete this->leptons_eta;  
  delete this->leptons_phi;  
  delete this->jets_pt;  
  delete this->jets_eta;  
  delete this->jets_phi;  
  delete EVS;


  return true;
}
