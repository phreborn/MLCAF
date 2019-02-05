//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __FakesMM__
#define __FakesMM__
#include "QFramework/TQTreeObservable.h"

#include "TTreeFormula.h"
#include "TH1F.h"
#include "TFile.h"

class FakesMM : public TQTreeObservable {
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

  TTreeFormula* lep_0 = NULL;
  TTreeFormula* lep_1 = NULL;
  TTreeFormula* lep_0_pt = NULL;
  TTreeFormula* lep_1_pt = NULL;
  TTreeFormula* lep_0_id_tight = NULL;
  TTreeFormula* lep_1_id_loose = NULL;
  TTreeFormula* lep_1_id_tight = NULL;

  TFile* FileEff_real_elec = NULL;
  TFile* FileEff_real_muon = NULL;
  TFile* FileEff_fake_elec = NULL;
  TFile* FileEff_fake_muon = NULL;
  
  TH1F* h_eff_real_elec = NULL;
  TH1F* h_eff_real_muon = NULL;
  TH1F* h_eff_fake_elec = NULL;
  TH1F* h_eff_fake_muon = NULL;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  FakesMM();
  FakesMM(const TString& expression);
  virtual ~FakesMM();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(FakesMM, 1);


};
#endif
