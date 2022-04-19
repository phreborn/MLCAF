#include "BSMtautauCAF/TTBarPDFUpWeight.h"
#include <limits>

#include "QFramework/TQLibrary.h"
#include "TFile.h"
#include "TMath.h"
#include <map>

ClassImp(TTBarPDFUpWeight)



TTBarPDFUpWeight::TTBarPDFUpWeight() {
  this->setExpression(this->GetName() );
  DEBUGclass("default constructor called");
}



TTBarPDFUpWeight::TTBarPDFUpWeight(const TString& expression) : LepHadObservable(expression) {
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);
  
  INFOclass("Loading file...");
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("ApplyPDFHiWeight", false) ) return;

  TString signalProcess = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("SignalProcess", signalProcess) ){
    ERRORclass("AnaChannel not set !!!");
  }
}



TObjArray* TTBarPDFUpWeight::getBranchNames() const {
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();
 
  int n = 30;
  TString pdf_weight = "pmg_truth_weight_pdf_signal_weight_";
  for ( int i = 0; i < 31; i++) {
    bnames->Add(new TObjString(pdf_weight + i));
  }

  return bnames;
}



bool TTBarPDFUpWeight::initializeSelf() {
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagBoolDefault("ApplyPDFHiWeight", false) ) return true;
  if (! LepHadObservable::initializeSelf()) return false;
  fSysName = this->fSample->replaceInTextRecursive("$(variation)","~");
 
  this->pdf_weight_0 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_0", "pmg_truth_weight_pdf_signal_weight_0", this->fTree);
  this->pdf_weight_1 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_1", "pmg_truth_weight_pdf_signal_weight_1", this->fTree);
  this->pdf_weight_2 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_2", "pmg_truth_weight_pdf_signal_weight_2", this->fTree);
  this->pdf_weight_3 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_3", "pmg_truth_weight_pdf_signal_weight_3", this->fTree);
  this->pdf_weight_4 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_4", "pmg_truth_weight_pdf_signal_weight_4", this->fTree);
  this->pdf_weight_5 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_5", "pmg_truth_weight_pdf_signal_weight_5", this->fTree);
  this->pdf_weight_6 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_6", "pmg_truth_weight_pdf_signal_weight_6", this->fTree);
  this->pdf_weight_7 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_7", "pmg_truth_weight_pdf_signal_weight_7", this->fTree);
  this->pdf_weight_8 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_8", "pmg_truth_weight_pdf_signal_weight_8", this->fTree);
  this->pdf_weight_9 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_9", "pmg_truth_weight_pdf_signal_weight_9", this->fTree);
  this->pdf_weight_10 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_10", "pmg_truth_weight_pdf_signal_weight_10", this->fTree);
  this->pdf_weight_11 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_11", "pmg_truth_weight_pdf_signal_weight_11", this->fTree);
  this->pdf_weight_12 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_12", "pmg_truth_weight_pdf_signal_weight_12", this->fTree);
  this->pdf_weight_13 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_13", "pmg_truth_weight_pdf_signal_weight_13", this->fTree);
  this->pdf_weight_14 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_14", "pmg_truth_weight_pdf_signal_weight_14", this->fTree);
  this->pdf_weight_15 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_15", "pmg_truth_weight_pdf_signal_weight_15", this->fTree);
  this->pdf_weight_16 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_16", "pmg_truth_weight_pdf_signal_weight_16", this->fTree);
  this->pdf_weight_17 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_17", "pmg_truth_weight_pdf_signal_weight_17", this->fTree);
  this->pdf_weight_18 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_18", "pmg_truth_weight_pdf_signal_weight_18", this->fTree);
  this->pdf_weight_19 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_19", "pmg_truth_weight_pdf_signal_weight_19", this->fTree);
  this->pdf_weight_20 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_20", "pmg_truth_weight_pdf_signal_weight_20", this->fTree);
  this->pdf_weight_21 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_21", "pmg_truth_weight_pdf_signal_weight_21", this->fTree);
  this->pdf_weight_22 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_22", "pmg_truth_weight_pdf_signal_weight_22", this->fTree);
  this->pdf_weight_23 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_23", "pmg_truth_weight_pdf_signal_weight_23", this->fTree);
  this->pdf_weight_24 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_24", "pmg_truth_weight_pdf_signal_weight_24", this->fTree);
  this->pdf_weight_25 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_25", "pmg_truth_weight_pdf_signal_weight_25", this->fTree);
  this->pdf_weight_26 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_26", "pmg_truth_weight_pdf_signal_weight_26", this->fTree);
  this->pdf_weight_27 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_27", "pmg_truth_weight_pdf_signal_weight_27", this->fTree);
  this->pdf_weight_28 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_28", "pmg_truth_weight_pdf_signal_weight_28", this->fTree);
  this->pdf_weight_29 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_29", "pmg_truth_weight_pdf_signal_weight_29", this->fTree);
  this->pdf_weight_30 = new TTreeFormula( "pmg_truth_weight_pdf_signal_weight_30", "pmg_truth_weight_pdf_signal_weight_30", this->fTree);

  return true;
}



bool TTBarPDFUpWeight::finalizeSelf() {
  if (! LepHadObservable::finalizeSelf()) return false;

  delete this->pdf_weight_0;
  delete this->pdf_weight_1;
  delete this->pdf_weight_2;
  delete this->pdf_weight_3;
  delete this->pdf_weight_4;
  delete this->pdf_weight_5;
  delete this->pdf_weight_6;
  delete this->pdf_weight_7;
  delete this->pdf_weight_8;
  delete this->pdf_weight_9;
  delete this->pdf_weight_10;
  delete this->pdf_weight_11;
  delete this->pdf_weight_12;
  delete this->pdf_weight_13;
  delete this->pdf_weight_14;
  delete this->pdf_weight_15;
  delete this->pdf_weight_16;
  delete this->pdf_weight_17;
  delete this->pdf_weight_18;
  delete this->pdf_weight_19;
  delete this->pdf_weight_20;
  delete this->pdf_weight_21;
  delete this->pdf_weight_22;
  delete this->pdf_weight_23;
  delete this->pdf_weight_24;
  delete this->pdf_weight_25;
  delete this->pdf_weight_26;
  delete this->pdf_weight_27;
  delete this->pdf_weight_28;
  delete this->pdf_weight_29;
  delete this->pdf_weight_30;

  return true;
}




double TTBarPDFUpWeight::getValue() const {
  // Check whether we want to apply the fake factor
  bool apply = false;
  if (! TQTaggable::getGlobalTaggable("aliases")->getTagBool("ApplyPDFHiWeight", apply)) {
    ERRORclass("Can not get ApplyPDFHiWeight tag");
  }
  if (!apply) return 1.0;

  if (isData()) return 1.0;
  if ( !isTTBar() ) return 1.0;
  
  TString signalProcess = "";
  if ( ! TQTaggable::getGlobalTaggable("aliases")->getTagString("SignalProcess", signalProcess) ){
    ERRORclass("AnaChannel not set !!!");
  }

  float pdf_weight_0 = this->pdf_weight_0->EvalInstance();
  float pdf_weight_1 = this->pdf_weight_1->EvalInstance();
  float pdf_weight_2 = this->pdf_weight_2->EvalInstance();
  float pdf_weight_3 = this->pdf_weight_3->EvalInstance();
  float pdf_weight_4 = this->pdf_weight_4->EvalInstance();
  float pdf_weight_5 = this->pdf_weight_5->EvalInstance();
  float pdf_weight_6 = this->pdf_weight_6->EvalInstance();
  float pdf_weight_7 = this->pdf_weight_7->EvalInstance();
  float pdf_weight_8 = this->pdf_weight_8->EvalInstance();
  float pdf_weight_9 = this->pdf_weight_9->EvalInstance();
  float pdf_weight_10 = this->pdf_weight_10->EvalInstance();
  float pdf_weight_11 = this->pdf_weight_11->EvalInstance();
  float pdf_weight_12 = this->pdf_weight_12->EvalInstance();
  float pdf_weight_13 = this->pdf_weight_13->EvalInstance();
  float pdf_weight_14 = this->pdf_weight_14->EvalInstance();
  float pdf_weight_15 = this->pdf_weight_15->EvalInstance();
  float pdf_weight_16 = this->pdf_weight_16->EvalInstance();
  float pdf_weight_17 = this->pdf_weight_17->EvalInstance();
  float pdf_weight_18 = this->pdf_weight_18->EvalInstance();
  float pdf_weight_19 = this->pdf_weight_19->EvalInstance();
  float pdf_weight_20 = this->pdf_weight_20->EvalInstance();
  float pdf_weight_21 = this->pdf_weight_21->EvalInstance();
  float pdf_weight_22 = this->pdf_weight_22->EvalInstance();
  float pdf_weight_23 = this->pdf_weight_23->EvalInstance();
  float pdf_weight_24 = this->pdf_weight_24->EvalInstance();
  float pdf_weight_25 = this->pdf_weight_25->EvalInstance();
  float pdf_weight_26 = this->pdf_weight_26->EvalInstance();
  float pdf_weight_27 = this->pdf_weight_27->EvalInstance();
  float pdf_weight_28 = this->pdf_weight_28->EvalInstance();
  float pdf_weight_29 = this->pdf_weight_29->EvalInstance();
  float pdf_weight_30 = this->pdf_weight_30->EvalInstance();

  double pdfWeighSum = 0.0;
  double nPDFs = 30.0;
  pdfWeighSum = std::pow(pdf_weight_1-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_2-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_3-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_4-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_5-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_6-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_7-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_8-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_9-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_10-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_11-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_12-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_13-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_14-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_15-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_16-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_17-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_18-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_19-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_20-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_21-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_22-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_23-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_24-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_25-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_26-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_27-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_28-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_29-pdf_weight_0, 2.0);
  pdfWeighSum += std::pow(pdf_weight_30-pdf_weight_0, 2.0);

  double pdfDev = std::sqrt(pdfWeighSum/(nPDFs-1.0));
  // TTBar PDF up weight
  double retval = 1.0 + pdfDev/pdf_weight_0;
  std::cout << retval << std::endl;   
  return retval;

}
