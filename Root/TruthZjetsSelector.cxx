#include "BSMtautauCAF/TruthZjetsSelector.h"
#include <limits>
#include "TObjString.h"

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(TruthZjetsSelector)



TruthZjetsSelector::TruthZjetsSelector(){
  this->setExpression(this->GetName());
}



TObjArray* TruthZjetsSelector::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  TObjArray* bnames = LepHadObservable::getBranchNames();

  //bnames->Add(new TObjString("selected_jet_0_origin"));
  //bnames->Add(new TObjString("selected_jet_1_origin"));
  bnames->Add(new TObjString("jet_origin_b_count"));
  bnames->Add(new TObjString("jet_origin_c_count"));

  return bnames;
}



double TruthZjetsSelector::getValue() const {

  if (isData()) return 1.0;
  //if ( !isZ2BJET() && !isZ1BJET() && !isZ1CJET() && !isZ1LJET() ) return 1.0;
  if ( !isZHF() && !isZLF() ) return 1.0;

  double retval = -9999;

  //int temp_selected_jet_0_origin = this->selected_jet_0_origin->EvalInstance();
  //int temp_selected_jet_1_origin = this->selected_jet_1_origin->EvalInstance();
  int temp_jet_origin_b_count = this->jet_origin_b_count->EvalInstance();
  int temp_jet_origin_c_count = this->jet_origin_c_count->EvalInstance();

  bool isZHF = temp_jet_origin_b_count >= 1 || temp_jet_origin_c_count >= 1;
  bool isZLF = temp_jet_origin_b_count == 0 && temp_jet_origin_c_count == 0;

  if (isZHF) {
    retval = 30;
  }
  else if (isZLF) { 
    retval = 40;
  }
  else {
    retval = -30;
  }  


  /*
  bool isZ2BJET = (temp_selected_jet_0_origin ==5 && temp_selected_jet_1_origin ==5) || (temp_selected_jet_0_origin ==5 && temp_selected_jet_1_origin ==4) || (temp_selected_jet_0_origin ==4 && temp_selected_jet_1_origin ==5) || (temp_selected_jet_0_origin ==4 && temp_selected_jet_1_origin ==4);
  bool isZ1BJET = (temp_selected_jet_0_origin ==5 && temp_selected_jet_1_origin !=5 && temp_selected_jet_1_origin !=4) || (temp_selected_jet_1_origin ==5 && temp_selected_jet_0_origin !=5 && temp_selected_jet_0_origin !=4);
  bool isZ1CJET = (temp_selected_jet_0_origin ==4 && temp_selected_jet_1_origin !=5 && temp_selected_jet_1_origin !=4) || (temp_selected_jet_1_origin ==4 && temp_selected_jet_0_origin !=5 && temp_selected_jet_0_origin !=4);
  bool isZ1LJET = (temp_selected_jet_0_origin !=5 && temp_selected_jet_0_origin !=4 && temp_selected_jet_1_origin !=5 && temp_selected_jet_1_origin !=4);

  if(isZ2BJET) {
    retval = 30;  //bb bc cc
  }
  else if(isZ1BJET) {
    retval = 40;  //b bl
  }
  else if(isZ1CJET) {
    retval = 60;  //c cl
  }
  else if(isZ1LJET) {
    retval = 80;  //l ll
  }
  else {
    retval = -30;
  }
  */

  return retval;
}



TruthZjetsSelector::TruthZjetsSelector(const TString& expression):
LepHadObservable(expression) {
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);
}



const TString& TruthZjetsSelector::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}



bool TruthZjetsSelector::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}



void TruthZjetsSelector::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}



bool TruthZjetsSelector::initializeSelf(){
  if (!LepHadObservable::initializeSelf()) return false;

  //if (!isData() && (isZ2BJET() || isZ1BJET() || isZ1CJET() || isZ1LJET()) ) {
  if (!isData() && (isZHF() || isZLF()) ) {
    //this->selected_jet_0_origin = new TTreeFormula("selected_jet_0_origin", "selected_jet_0_origin", this->fTree);
    //this->selected_jet_1_origin = new TTreeFormula("selected_jet_1_origin", "selected_jet_1_origin", this->fTree);
    this->jet_origin_b_count = new TTreeFormula("jet_origin_b_count", "jet_origin_b_count", this->fTree);
    this->jet_origin_c_count = new TTreeFormula("jet_origin_c_count", "jet_origin_c_count", this->fTree);
  }
  return true;
}



bool TruthZjetsSelector::finalizeSelf(){
  if (! LepHadObservable::finalizeSelf()) return false;

  //if (!isData()&& (isZ2BJET() || isZ1BJET() || isZ1CJET() || isZ1LJET())) {
  if (!isData()&& (isZHF() || isZLF())) {
    //delete this->selected_jet_0_origin;
    //delete this->selected_jet_1_origin;
    delete this->jet_origin_b_count;
    delete this->jet_origin_c_count;
  }

  return true;
}

