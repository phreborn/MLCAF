//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __PU_weight_ll_v05__
#define __PU_weight_ll_v05__
#include "QFramework/TQTreeObservable.h"

#include "TTreeFormula.h"
#include "TH2F.h"

class PU_weight_ll_v05 : public TQTreeObservable {
protected:
  // put here any data members your class might need
public:
  virtual double getValue() const override;
  virtual TObjArray* getBranchNames() const override;
protected:
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;
protected:
  TString fExpression = "";
  TTreeFormula* PU_weight = NULL;
  TTreeFormula* RRN = NULL;
  TTreeFormula* sherpa_weight = NULL;
  TTreeFormula* n_truth_jets = NULL;
  TTreeFormula* true_parent_pdgId = NULL;
  TTreeFormula* true_parent_pt = NULL;
  int m_systematic=0;
  TString PU_weight_name="";
  TString RRN_name = "";
  bool m_isSherpa;
  bool m_isMG;
  TH2F * m_MG_histo;
  bool doRRN=false;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  PU_weight_ll_v05();
  PU_weight_ll_v05(const TString& expression, int systematic=0);
  virtual ~PU_weight_ll_v05();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(PU_weight_ll_v05, 1);


};
#endif
