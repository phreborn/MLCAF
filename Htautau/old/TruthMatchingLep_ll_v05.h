//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __TruthMatchingLep_ll_v05__
#define __TruthMatchingLep_ll_v05__
#include "QFramework/TQTreeObservable.h"
#include "Htautau2015/EventSelection_leplep_default.h"
#include "Htautau2015/EventSelection_leplep_fake.h"


#include "TTreeFormula.h"

class TruthMatchingLep_ll_v05 : public TQTreeObservable {
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

  TTreeFormula* leptons_matched_lep = NULL;
  TTreeFormula* leptons_matched_lep_pdgId = NULL;
  TTreeFormula* leptons_matched_lep_mother_pdgId = NULL;
  TTreeFormula* leptons_matched_lep_origin = NULL;
  TTreeFormula* leptons_matched_lep_type = NULL;

  EventSelection_leplep_default * EVS;
  EventSelection_leplep_fake * EVS_fake;

  bool useFakeSelec = false;

  int lepIndex = -1;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  TruthMatchingLep_ll_v05();
  TruthMatchingLep_ll_v05(const TString& expression, const int& lepton);
  virtual ~TruthMatchingLep_ll_v05();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(TruthMatchingLep_ll_v05, 1);


};
#endif
