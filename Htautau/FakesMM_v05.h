//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __FakesMM_v05__
#define __FakesMM_v05__
#include "QFramework/TQTreeObservable.h"
#include "Htautau/EventSelection_leplep_fake.h"

#include "TTreeFormula.h"
#include "TH1F.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"

class FakesMM_v05 : public TQTreeObservable {
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

  int m_systematic = 0;
  int m_flag = 1;
  TString m_filePath = "";

  EventSelection_leplep_fake * EVS_fake;

  TTreeFormula* leptons = NULL;
  TTreeFormula* leptons_pt = NULL;

  TFile* infile;

  TGraphAsymmErrors* g_real_elec_SL0T_pt0;
  TGraphAsymmErrors* g_real_elec_SL0T_pt1;
  TGraphAsymmErrors* g_real_elec_SL0T_eta;
  TGraphAsymmErrors* g_real_elec_SL1T_pt0;
  TGraphAsymmErrors* g_real_elec_SL1T_pt1;
  TGraphAsymmErrors* g_real_elec_SL1T_eta;
  TGraphAsymmErrors* g_real_elec_DLT_pt0;
  TGraphAsymmErrors* g_real_elec_DLT_pt1;
  TGraphAsymmErrors* g_real_elec_DLT_eta;

  TGraphAsymmErrors* g_real_muon_SL0T_pt0;
  TGraphAsymmErrors* g_real_muon_SL0T_pt1;
  TGraphAsymmErrors* g_real_muon_SL0T_eta;
  TGraphAsymmErrors* g_real_muon_SL1T_pt0;
  TGraphAsymmErrors* g_real_muon_SL1T_pt1;
  TGraphAsymmErrors* g_real_muon_SL1T_eta;
  TGraphAsymmErrors* g_real_muon_DLT_pt0;
  TGraphAsymmErrors* g_real_muon_DLT_pt1;
  TGraphAsymmErrors* g_real_muon_DLT_eta;

  TGraphAsymmErrors* g_fake_elec_SL0T_pt0;
  TGraphAsymmErrors* g_fake_elec_SL0T_pt1;
  TGraphAsymmErrors* g_fake_elec_SL0T_eta;
  TGraphAsymmErrors* g_fake_elec_SL1T_pt0;
  TGraphAsymmErrors* g_fake_elec_SL1T_pt1;
  TGraphAsymmErrors* g_fake_elec_SL1T_eta;
  TGraphAsymmErrors* g_fake_elec_DLT_pt0;
  TGraphAsymmErrors* g_fake_elec_DLT_pt1;
  TGraphAsymmErrors* g_fake_elec_DLT_eta;

  TGraphAsymmErrors* g_fake_muon_SL0T_pt0;
  TGraphAsymmErrors* g_fake_muon_SL0T_pt1;
  TGraphAsymmErrors* g_fake_muon_SL0T_eta;
  TGraphAsymmErrors* g_fake_muon_SL1T_pt0;
  TGraphAsymmErrors* g_fake_muon_SL1T_pt1;
  TGraphAsymmErrors* g_fake_muon_SL1T_eta;
  TGraphAsymmErrors* g_fake_muon_DLT_pt0;
  TGraphAsymmErrors* g_fake_muon_DLT_pt1;
  TGraphAsymmErrors* g_fake_muon_DLT_eta;



public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  FakesMM_v05();
  FakesMM_v05(const TString& expression, const TString& filePath, int systematic, int flag);
  virtual ~FakesMM_v05();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();
  double getEff(double val, TGraphAsymmErrors* graph, int m_systematic, TString whateff) const;

  virtual TString getActiveExpression() const override;


  ClassDef(FakesMM_v05, 1);


};
#endif
