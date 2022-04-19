//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __TTBarPDFDoWeight__
#define __TTBarPDFDoWeight__

#include "BSMtautauCAF/LepHadObservable.h"

class TTBarPDFDoWeight : public LepHadObservable {

public:
  ClassDef(TTBarPDFDoWeight, 1);

  TTBarPDFDoWeight();
  TTBarPDFDoWeight(const TString& expression);
  virtual ~TTBarPDFDoWeight() = default;

  virtual TObjArray* getBranchNames() const override;
  virtual double getValue() const override;

protected:
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;

  TTreeFormula* pdf_weight_0 = nullptr;
  TTreeFormula* pdf_weight_1 = nullptr;
  TTreeFormula* pdf_weight_2 = nullptr;
  TTreeFormula* pdf_weight_3 = nullptr;
  TTreeFormula* pdf_weight_4 = nullptr;
  TTreeFormula* pdf_weight_5 = nullptr;
  TTreeFormula* pdf_weight_6 = nullptr;
  TTreeFormula* pdf_weight_7 = nullptr;
  TTreeFormula* pdf_weight_8 = nullptr;
  TTreeFormula* pdf_weight_9 = nullptr;
  TTreeFormula* pdf_weight_10 = nullptr;
  TTreeFormula* pdf_weight_11 = nullptr;
  TTreeFormula* pdf_weight_12 = nullptr;
  TTreeFormula* pdf_weight_13 = nullptr;
  TTreeFormula* pdf_weight_14 = nullptr;
  TTreeFormula* pdf_weight_15 = nullptr;
  TTreeFormula* pdf_weight_16 = nullptr;
  TTreeFormula* pdf_weight_17 = nullptr;
  TTreeFormula* pdf_weight_18 = nullptr;
  TTreeFormula* pdf_weight_19 = nullptr;
  TTreeFormula* pdf_weight_20 = nullptr;
  TTreeFormula* pdf_weight_21 = nullptr;
  TTreeFormula* pdf_weight_22 = nullptr;
  TTreeFormula* pdf_weight_23 = nullptr;
  TTreeFormula* pdf_weight_24 = nullptr;
  TTreeFormula* pdf_weight_25 = nullptr;
  TTreeFormula* pdf_weight_26 = nullptr;
  TTreeFormula* pdf_weight_27 = nullptr;
  TTreeFormula* pdf_weight_28 = nullptr;
  TTreeFormula* pdf_weight_29 = nullptr;
  TTreeFormula* pdf_weight_30 = nullptr;

  TString fExpression = "";
  TString fSysName = "";
};

#endif
