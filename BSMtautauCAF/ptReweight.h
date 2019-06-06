//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __PTREWEIGHT__
#define __PTREWEIGHT__
#include "QFramework/TQTreeObservable.h"

#include "BSMtautauCAF/LepHadObservable.h"
#include "TH2F.h"

class ptReweight : public LepHadObservable {
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

  TString fSysName = "";

  bool _isData = false;
  TDirectory* m_histoDir = 0;

  const long LIMIT_2016 = 311563;
  const long LIMIT_2017 = 341649;
  const long LIMIT_2018 = 364292;

  TH1 *h_weight = 0;

  // nominal pt parametrization
  // 2015/16
  TH1F * h_ff15_wfr_ehad_1p_0tag = 0;
  TH1F * h_ff15_wfr_ehad_3p_0tag = 0;
  TH1F * h_ff15_wfr_ehad_1p_0tag_up   = 0;
  TH1F * h_ff15_wfr_ehad_3p_0tag_up   = 0;
  TH1F * h_ff15_wfr_ehad_1p_0tag_down = 0;
  TH1F * h_ff15_wfr_ehad_3p_0tag_down = 0;

  TH1F * h_ff15_wfr_muhad_1p_0tag = 0;
  TH1F * h_ff15_wfr_muhad_3p_0tag = 0;
  TH1F * h_ff15_wfr_muhad_1p_0tag_up   = 0;
  TH1F * h_ff15_wfr_muhad_3p_0tag_up   = 0;
  TH1F * h_ff15_wfr_muhad_1p_0tag_down = 0;
  TH1F * h_ff15_wfr_muhad_3p_0tag_down = 0;

  TH1F * h_ff15_wfr_ehad_1p_1tag = 0;
  TH1F * h_ff15_wfr_ehad_3p_1tag = 0;
  TH1F * h_ff15_wfr_ehad_1p_1tag_up   = 0;
  TH1F * h_ff15_wfr_ehad_3p_1tag_up   = 0;
  TH1F * h_ff15_wfr_ehad_1p_1tag_down = 0;
  TH1F * h_ff15_wfr_ehad_3p_1tag_down = 0;

  TH1F * h_ff15_wfr_muhad_1p_1tag = 0;
  TH1F * h_ff15_wfr_muhad_3p_1tag = 0;
  TH1F * h_ff15_wfr_muhad_1p_1tag_up   = 0;
  TH1F * h_ff15_wfr_muhad_3p_1tag_up   = 0;
  TH1F * h_ff15_wfr_muhad_1p_1tag_down = 0;
  TH1F * h_ff15_wfr_muhad_3p_1tag_down = 0;

  // 2017
  TH1F * h_ff17_wfr_ehad_1p_0tag = 0;
  TH1F * h_ff17_wfr_ehad_3p_0tag = 0;
  TH1F * h_ff17_wfr_ehad_1p_0tag_up   = 0;
  TH1F * h_ff17_wfr_ehad_3p_0tag_up   = 0;
  TH1F * h_ff17_wfr_ehad_1p_0tag_down = 0;
  TH1F * h_ff17_wfr_ehad_3p_0tag_down = 0;

  TH1F * h_ff17_wfr_ehad_1p_1tag = 0;
  TH1F * h_ff17_wfr_ehad_3p_1tag = 0;
  TH1F * h_ff17_wfr_ehad_1p_1tag_up   = 0;
  TH1F * h_ff17_wfr_ehad_3p_1tag_up   = 0;
  TH1F * h_ff17_wfr_ehad_1p_1tag_down = 0;
  TH1F * h_ff17_wfr_ehad_3p_1tag_down = 0;

  TH1F * h_ff17_wfr_muhad_1p_0tag = 0;
  TH1F * h_ff17_wfr_muhad_3p_0tag = 0;
  TH1F * h_ff17_wfr_muhad_1p_0tag_up   = 0;
  TH1F * h_ff17_wfr_muhad_3p_0tag_up   = 0;
  TH1F * h_ff17_wfr_muhad_1p_0tag_down = 0;
  TH1F * h_ff17_wfr_muhad_3p_0tag_down = 0;

  TH1F * h_ff17_wfr_muhad_1p_1tag = 0;
  TH1F * h_ff17_wfr_muhad_3p_1tag = 0;
  TH1F * h_ff17_wfr_muhad_1p_1tag_up   = 0;
  TH1F * h_ff17_wfr_muhad_3p_1tag_up   = 0;
  TH1F * h_ff17_wfr_muhad_1p_1tag_down = 0;
  TH1F * h_ff17_wfr_muhad_3p_1tag_down = 0;

  // 2018
  TH1F * h_ff18_wfr_ehad_1p_0tag = 0;
  TH1F * h_ff18_wfr_ehad_3p_0tag = 0;
  TH1F * h_ff18_wfr_ehad_1p_0tag_up   = 0;
  TH1F * h_ff18_wfr_ehad_3p_0tag_up   = 0;
  TH1F * h_ff18_wfr_ehad_1p_0tag_down = 0;
  TH1F * h_ff18_wfr_ehad_3p_0tag_down = 0;

  TH1F * h_ff18_wfr_ehad_1p_1tag = 0;
  TH1F * h_ff18_wfr_ehad_3p_1tag = 0;
  TH1F * h_ff18_wfr_ehad_1p_1tag_up   = 0;
  TH1F * h_ff18_wfr_ehad_3p_1tag_up   = 0;
  TH1F * h_ff18_wfr_ehad_1p_1tag_down = 0;
  TH1F * h_ff18_wfr_ehad_3p_1tag_down = 0;

  TH1F * h_ff18_wfr_muhad_1p_0tag = 0;
  TH1F * h_ff18_wfr_muhad_3p_0tag = 0;
  TH1F * h_ff18_wfr_muhad_1p_0tag_up   = 0;
  TH1F * h_ff18_wfr_muhad_3p_0tag_up   = 0;
  TH1F * h_ff18_wfr_muhad_1p_0tag_down = 0;
  TH1F * h_ff18_wfr_muhad_3p_0tag_down = 0;

  TH1F * h_ff18_wfr_muhad_1p_1tag = 0;
  TH1F * h_ff18_wfr_muhad_3p_1tag = 0;
  TH1F * h_ff18_wfr_muhad_1p_1tag_up   = 0;
  TH1F * h_ff18_wfr_muhad_3p_1tag_up   = 0;
  TH1F * h_ff18_wfr_muhad_1p_1tag_down = 0;
  TH1F * h_ff18_wfr_muhad_3p_1tag_down = 0;

  // all years
  TH1F * h_fffull_wfr_ehad_1p_0tag = 0;
  TH1F * h_fffull_wfr_ehad_3p_0tag = 0;
  TH1F * h_fffull_wfr_ehad_1p_0tag_up   = 0;
  TH1F * h_fffull_wfr_ehad_3p_0tag_up   = 0;
  TH1F * h_fffull_wfr_ehad_1p_0tag_down = 0;
  TH1F * h_fffull_wfr_ehad_3p_0tag_down = 0;

  TH1F * h_fffull_wfr_ehad_1p_1tag = 0;
  TH1F * h_fffull_wfr_ehad_3p_1tag = 0;
  TH1F * h_fffull_wfr_ehad_1p_1tag_up   = 0;
  TH1F * h_fffull_wfr_ehad_3p_1tag_up   = 0;
  TH1F * h_fffull_wfr_ehad_1p_1tag_down = 0;
  TH1F * h_fffull_wfr_ehad_3p_1tag_down = 0;

  TH1F * h_fffull_wfr_muhad_1p_0tag = 0;
  TH1F * h_fffull_wfr_muhad_3p_0tag = 0;
  TH1F * h_fffull_wfr_muhad_1p_0tag_up   = 0;
  TH1F * h_fffull_wfr_muhad_3p_0tag_up   = 0;
  TH1F * h_fffull_wfr_muhad_1p_0tag_down = 0;
  TH1F * h_fffull_wfr_muhad_3p_0tag_down = 0;

  TH1F * h_fffull_wfr_muhad_1p_1tag = 0;
  TH1F * h_fffull_wfr_muhad_3p_1tag = 0;
  TH1F * h_fffull_wfr_muhad_1p_1tag_up   = 0;
  TH1F * h_fffull_wfr_muhad_3p_1tag_up   = 0;
  TH1F * h_fffull_wfr_muhad_1p_1tag_down = 0;
  TH1F * h_fffull_wfr_muhad_3p_1tag_down = 0;

  // pt * dphi parametrization
  // 2015/16
  TH1F * h_ff15_wfr_ehad_1p_dphi1_0tag = 0;
  TH1F * h_ff15_wfr_ehad_1p_dphi1_0tag_up   = 0;
  TH1F * h_ff15_wfr_ehad_1p_dphi1_0tag_down = 0;

  TH1F * h_ff15_wfr_ehad_1p_dphi2_0tag = 0;
  TH1F * h_ff15_wfr_ehad_1p_dphi2_0tag_up   = 0;
  TH1F * h_ff15_wfr_ehad_1p_dphi2_0tag_down = 0;

  TH1F * h_ff15_wfr_ehad_1p_dphi3_0tag = 0;
  TH1F * h_ff15_wfr_ehad_1p_dphi3_0tag_up   = 0;
  TH1F * h_ff15_wfr_ehad_1p_dphi3_0tag_down = 0;

  TH1F * h_ff15_wfr_ehad_1p_dphi4_0tag = 0;
  TH1F * h_ff15_wfr_ehad_1p_dphi4_0tag_up   = 0;
  TH1F * h_ff15_wfr_ehad_1p_dphi4_0tag_down = 0;

  TH1F * h_ff15_wfr_ehad_3p_dphi1_0tag = 0;
  TH1F * h_ff15_wfr_ehad_3p_dphi1_0tag_up   = 0;
  TH1F * h_ff15_wfr_ehad_3p_dphi1_0tag_down = 0;

  TH1F * h_ff15_wfr_ehad_3p_dphi2_0tag = 0;
  TH1F * h_ff15_wfr_ehad_3p_dphi2_0tag_up   = 0;
  TH1F * h_ff15_wfr_ehad_3p_dphi2_0tag_down = 0;

  TH1F * h_ff15_wfr_ehad_3p_dphi3_0tag = 0;
  TH1F * h_ff15_wfr_ehad_3p_dphi3_0tag_up   = 0;
  TH1F * h_ff15_wfr_ehad_3p_dphi3_0tag_down = 0;

  TH1F * h_ff15_wfr_ehad_3p_dphi4_0tag = 0;
  TH1F * h_ff15_wfr_ehad_3p_dphi4_0tag_up   = 0;
  TH1F * h_ff15_wfr_ehad_3p_dphi4_0tag_down = 0;

  TH1F * h_ff15_wfr_muhad_1p_dphi1_0tag = 0;
  TH1F * h_ff15_wfr_muhad_1p_dphi1_0tag_up   = 0;
  TH1F * h_ff15_wfr_muhad_1p_dphi1_0tag_down = 0;

  TH1F * h_ff15_wfr_muhad_1p_dphi2_0tag = 0;
  TH1F * h_ff15_wfr_muhad_1p_dphi2_0tag_up   = 0;
  TH1F * h_ff15_wfr_muhad_1p_dphi2_0tag_down = 0;

  TH1F * h_ff15_wfr_muhad_1p_dphi3_0tag = 0;
  TH1F * h_ff15_wfr_muhad_1p_dphi3_0tag_up   = 0;
  TH1F * h_ff15_wfr_muhad_1p_dphi3_0tag_down = 0;

  TH1F * h_ff15_wfr_muhad_1p_dphi4_0tag = 0;
  TH1F * h_ff15_wfr_muhad_1p_dphi4_0tag_up   = 0;
  TH1F * h_ff15_wfr_muhad_1p_dphi4_0tag_down = 0;

  TH1F * h_ff15_wfr_muhad_3p_dphi1_0tag = 0;
  TH1F * h_ff15_wfr_muhad_3p_dphi1_0tag_up   = 0;
  TH1F * h_ff15_wfr_muhad_3p_dphi1_0tag_down = 0;

  TH1F * h_ff15_wfr_muhad_3p_dphi2_0tag = 0;
  TH1F * h_ff15_wfr_muhad_3p_dphi2_0tag_up   = 0;
  TH1F * h_ff15_wfr_muhad_3p_dphi2_0tag_down = 0;

  TH1F * h_ff15_wfr_muhad_3p_dphi3_0tag = 0;
  TH1F * h_ff15_wfr_muhad_3p_dphi3_0tag_up   = 0;
  TH1F * h_ff15_wfr_muhad_3p_dphi3_0tag_down = 0;

  TH1F * h_ff15_wfr_muhad_3p_dphi4_0tag = 0;
  TH1F * h_ff15_wfr_muhad_3p_dphi4_0tag_up   = 0;
  TH1F * h_ff15_wfr_muhad_3p_dphi4_0tag_down = 0;

  // 2017
  TH1F * h_ff17_wfr_ehad_1p_dphi1_0tag = 0;
  TH1F * h_ff17_wfr_ehad_1p_dphi1_0tag_up   = 0;
  TH1F * h_ff17_wfr_ehad_1p_dphi1_0tag_down = 0;

  TH1F * h_ff17_wfr_ehad_1p_dphi2_0tag = 0;
  TH1F * h_ff17_wfr_ehad_1p_dphi2_0tag_up   = 0;
  TH1F * h_ff17_wfr_ehad_1p_dphi2_0tag_down = 0;

  TH1F * h_ff17_wfr_ehad_1p_dphi3_0tag = 0;
  TH1F * h_ff17_wfr_ehad_1p_dphi3_0tag_up   = 0;
  TH1F * h_ff17_wfr_ehad_1p_dphi3_0tag_down = 0;

  TH1F * h_ff17_wfr_ehad_1p_dphi4_0tag = 0;
  TH1F * h_ff17_wfr_ehad_1p_dphi4_0tag_up   = 0;
  TH1F * h_ff17_wfr_ehad_1p_dphi4_0tag_down = 0;

  TH1F * h_ff17_wfr_ehad_3p_dphi1_0tag = 0;
  TH1F * h_ff17_wfr_ehad_3p_dphi1_0tag_up   = 0;
  TH1F * h_ff17_wfr_ehad_3p_dphi1_0tag_down = 0;

  TH1F * h_ff17_wfr_ehad_3p_dphi2_0tag = 0;
  TH1F * h_ff17_wfr_ehad_3p_dphi2_0tag_up   = 0;
  TH1F * h_ff17_wfr_ehad_3p_dphi2_0tag_down = 0;

  TH1F * h_ff17_wfr_ehad_3p_dphi3_0tag = 0;
  TH1F * h_ff17_wfr_ehad_3p_dphi3_0tag_up   = 0;
  TH1F * h_ff17_wfr_ehad_3p_dphi3_0tag_down = 0;

  TH1F * h_ff17_wfr_ehad_3p_dphi4_0tag = 0;
  TH1F * h_ff17_wfr_ehad_3p_dphi4_0tag_up   = 0;
  TH1F * h_ff17_wfr_ehad_3p_dphi4_0tag_down = 0;

  TH1F * h_ff17_wfr_muhad_1p_dphi1_0tag = 0;
  TH1F * h_ff17_wfr_muhad_1p_dphi1_0tag_up   = 0;
  TH1F * h_ff17_wfr_muhad_1p_dphi1_0tag_down = 0;

  TH1F * h_ff17_wfr_muhad_1p_dphi2_0tag = 0;
  TH1F * h_ff17_wfr_muhad_1p_dphi2_0tag_up   = 0;
  TH1F * h_ff17_wfr_muhad_1p_dphi2_0tag_down = 0;

  TH1F * h_ff17_wfr_muhad_1p_dphi3_0tag = 0;
  TH1F * h_ff17_wfr_muhad_1p_dphi3_0tag_up   = 0;
  TH1F * h_ff17_wfr_muhad_1p_dphi3_0tag_down = 0;

  TH1F * h_ff17_wfr_muhad_1p_dphi4_0tag = 0;
  TH1F * h_ff17_wfr_muhad_1p_dphi4_0tag_up   = 0;
  TH1F * h_ff17_wfr_muhad_1p_dphi4_0tag_down = 0;

  TH1F * h_ff17_wfr_muhad_3p_dphi1_0tag = 0;
  TH1F * h_ff17_wfr_muhad_3p_dphi1_0tag_up   = 0;
  TH1F * h_ff17_wfr_muhad_3p_dphi1_0tag_down = 0;

  TH1F * h_ff17_wfr_muhad_3p_dphi2_0tag = 0;
  TH1F * h_ff17_wfr_muhad_3p_dphi2_0tag_up   = 0;
  TH1F * h_ff17_wfr_muhad_3p_dphi2_0tag_down = 0;

  TH1F * h_ff17_wfr_muhad_3p_dphi3_0tag = 0;
  TH1F * h_ff17_wfr_muhad_3p_dphi3_0tag_up   = 0;
  TH1F * h_ff17_wfr_muhad_3p_dphi3_0tag_down = 0;

  TH1F * h_ff17_wfr_muhad_3p_dphi4_0tag = 0;
  TH1F * h_ff17_wfr_muhad_3p_dphi4_0tag_up   = 0;
  TH1F * h_ff17_wfr_muhad_3p_dphi4_0tag_down = 0;

  // 2018
  TH1F * h_ff18_wfr_ehad_1p_dphi1_0tag = 0;
  TH1F * h_ff18_wfr_ehad_1p_dphi1_0tag_up   = 0;
  TH1F * h_ff18_wfr_ehad_1p_dphi1_0tag_down = 0;

  TH1F * h_ff18_wfr_ehad_1p_dphi2_0tag = 0;
  TH1F * h_ff18_wfr_ehad_1p_dphi2_0tag_up   = 0;
  TH1F * h_ff18_wfr_ehad_1p_dphi2_0tag_down = 0;

  TH1F * h_ff18_wfr_ehad_1p_dphi3_0tag = 0;
  TH1F * h_ff18_wfr_ehad_1p_dphi3_0tag_up   = 0;
  TH1F * h_ff18_wfr_ehad_1p_dphi3_0tag_down = 0;

  TH1F * h_ff18_wfr_ehad_1p_dphi4_0tag = 0;
  TH1F * h_ff18_wfr_ehad_1p_dphi4_0tag_up   = 0;
  TH1F * h_ff18_wfr_ehad_1p_dphi4_0tag_down = 0;

  TH1F * h_ff18_wfr_ehad_3p_dphi1_0tag = 0;
  TH1F * h_ff18_wfr_ehad_3p_dphi1_0tag_up   = 0;
  TH1F * h_ff18_wfr_ehad_3p_dphi1_0tag_down = 0;

  TH1F * h_ff18_wfr_ehad_3p_dphi2_0tag = 0;
  TH1F * h_ff18_wfr_ehad_3p_dphi2_0tag_up   = 0;
  TH1F * h_ff18_wfr_ehad_3p_dphi2_0tag_down = 0;

  TH1F * h_ff18_wfr_ehad_3p_dphi3_0tag = 0;
  TH1F * h_ff18_wfr_ehad_3p_dphi3_0tag_up   = 0;
  TH1F * h_ff18_wfr_ehad_3p_dphi3_0tag_down = 0;

  TH1F * h_ff18_wfr_ehad_3p_dphi4_0tag = 0;
  TH1F * h_ff18_wfr_ehad_3p_dphi4_0tag_up   = 0;
  TH1F * h_ff18_wfr_ehad_3p_dphi4_0tag_down = 0;

  TH1F * h_ff18_wfr_muhad_1p_dphi1_0tag = 0;
  TH1F * h_ff18_wfr_muhad_1p_dphi1_0tag_up   = 0;
  TH1F * h_ff18_wfr_muhad_1p_dphi1_0tag_down = 0;

  TH1F * h_ff18_wfr_muhad_1p_dphi2_0tag = 0;
  TH1F * h_ff18_wfr_muhad_1p_dphi2_0tag_up   = 0;
  TH1F * h_ff18_wfr_muhad_1p_dphi2_0tag_down = 0;

  TH1F * h_ff18_wfr_muhad_1p_dphi3_0tag = 0;
  TH1F * h_ff18_wfr_muhad_1p_dphi3_0tag_up   = 0;
  TH1F * h_ff18_wfr_muhad_1p_dphi3_0tag_down = 0;

  TH1F * h_ff18_wfr_muhad_1p_dphi4_0tag = 0;
  TH1F * h_ff18_wfr_muhad_1p_dphi4_0tag_up   = 0;
  TH1F * h_ff18_wfr_muhad_1p_dphi4_0tag_down = 0;

  TH1F * h_ff18_wfr_muhad_3p_dphi1_0tag = 0;
  TH1F * h_ff18_wfr_muhad_3p_dphi1_0tag_up   = 0;
  TH1F * h_ff18_wfr_muhad_3p_dphi1_0tag_down = 0;

  TH1F * h_ff18_wfr_muhad_3p_dphi2_0tag = 0;
  TH1F * h_ff18_wfr_muhad_3p_dphi2_0tag_up   = 0;
  TH1F * h_ff18_wfr_muhad_3p_dphi2_0tag_down = 0;

  TH1F * h_ff18_wfr_muhad_3p_dphi3_0tag = 0;
  TH1F * h_ff18_wfr_muhad_3p_dphi3_0tag_up   = 0;
  TH1F * h_ff18_wfr_muhad_3p_dphi3_0tag_down = 0;

  TH1F * h_ff18_wfr_muhad_3p_dphi4_0tag = 0;
  TH1F * h_ff18_wfr_muhad_3p_dphi4_0tag_up   = 0;
  TH1F * h_ff18_wfr_muhad_3p_dphi4_0tag_down = 0;

  // all years
  TH1F * h_fffull_wfr_ehad_1p_dphi1_0tag = 0;
  TH1F * h_fffull_wfr_ehad_1p_dphi1_0tag_up   = 0;
  TH1F * h_fffull_wfr_ehad_1p_dphi1_0tag_down = 0;

  TH1F * h_fffull_wfr_ehad_1p_dphi2_0tag = 0;
  TH1F * h_fffull_wfr_ehad_1p_dphi2_0tag_up   = 0;
  TH1F * h_fffull_wfr_ehad_1p_dphi2_0tag_down = 0;

  TH1F * h_fffull_wfr_ehad_1p_dphi3_0tag = 0;
  TH1F * h_fffull_wfr_ehad_1p_dphi3_0tag_up   = 0;
  TH1F * h_fffull_wfr_ehad_1p_dphi3_0tag_down = 0;

  TH1F * h_fffull_wfr_ehad_1p_dphi4_0tag = 0;
  TH1F * h_fffull_wfr_ehad_1p_dphi4_0tag_up   = 0;
  TH1F * h_fffull_wfr_ehad_1p_dphi4_0tag_down = 0;

  TH1F * h_fffull_wfr_ehad_3p_dphi1_0tag = 0;
  TH1F * h_fffull_wfr_ehad_3p_dphi1_0tag_up   = 0;
  TH1F * h_fffull_wfr_ehad_3p_dphi1_0tag_down = 0;

  TH1F * h_fffull_wfr_ehad_3p_dphi2_0tag = 0;
  TH1F * h_fffull_wfr_ehad_3p_dphi2_0tag_up   = 0;
  TH1F * h_fffull_wfr_ehad_3p_dphi2_0tag_down = 0;

  TH1F * h_fffull_wfr_ehad_3p_dphi3_0tag = 0;
  TH1F * h_fffull_wfr_ehad_3p_dphi3_0tag_up   = 0;
  TH1F * h_fffull_wfr_ehad_3p_dphi3_0tag_down = 0;

  TH1F * h_fffull_wfr_ehad_3p_dphi4_0tag = 0;
  TH1F * h_fffull_wfr_ehad_3p_dphi4_0tag_up   = 0;
  TH1F * h_fffull_wfr_ehad_3p_dphi4_0tag_down = 0;

  TH1F * h_fffull_wfr_muhad_1p_dphi1_0tag = 0;
  TH1F * h_fffull_wfr_muhad_1p_dphi1_0tag_up   = 0;
  TH1F * h_fffull_wfr_muhad_1p_dphi1_0tag_down = 0;

  TH1F * h_fffull_wfr_muhad_1p_dphi2_0tag = 0;
  TH1F * h_fffull_wfr_muhad_1p_dphi2_0tag_up   = 0;
  TH1F * h_fffull_wfr_muhad_1p_dphi2_0tag_down = 0;

  TH1F * h_fffull_wfr_muhad_1p_dphi3_0tag = 0;
  TH1F * h_fffull_wfr_muhad_1p_dphi3_0tag_up   = 0;
  TH1F * h_fffull_wfr_muhad_1p_dphi3_0tag_down = 0;

  TH1F * h_fffull_wfr_muhad_1p_dphi4_0tag = 0;
  TH1F * h_fffull_wfr_muhad_1p_dphi4_0tag_up   = 0;
  TH1F * h_fffull_wfr_muhad_1p_dphi4_0tag_down = 0;

  TH1F * h_fffull_wfr_muhad_3p_dphi1_0tag = 0;
  TH1F * h_fffull_wfr_muhad_3p_dphi1_0tag_up   = 0;
  TH1F * h_fffull_wfr_muhad_3p_dphi1_0tag_down = 0;

  TH1F * h_fffull_wfr_muhad_3p_dphi2_0tag = 0;
  TH1F * h_fffull_wfr_muhad_3p_dphi2_0tag_up   = 0;
  TH1F * h_fffull_wfr_muhad_3p_dphi2_0tag_down = 0;

  TH1F * h_fffull_wfr_muhad_3p_dphi3_0tag = 0;
  TH1F * h_fffull_wfr_muhad_3p_dphi3_0tag_up   = 0;
  TH1F * h_fffull_wfr_muhad_3p_dphi3_0tag_down = 0;

  TH1F * h_fffull_wfr_muhad_3p_dphi4_0tag = 0;
  TH1F * h_fffull_wfr_muhad_3p_dphi4_0tag_up   = 0;
  TH1F * h_fffull_wfr_muhad_3p_dphi4_0tag_down = 0;

  // dphi correction
  TH1F * h_ff_wfr_1p_1tag_cor = 0;
  TH1F * h_ff_wfr_3p_1tag_cor = 0;
  TH1F * h_ff_wfr_1p_1tag_cor_up   = 0;
  TH1F * h_ff_wfr_3p_1tag_cor_up   = 0;
  TH1F * h_ff_wfr_1p_1tag_cor_down = 0;
  TH1F * h_ff_wfr_3p_1tag_cor_down = 0;

  TH1F * h_2015ff_mj_1p_0tag  = 0;
  TH1F * h_2015ff_mj_3p_0tag  = 0;

  TH1F * h_2015ff_mj_1p_0tag_up  = 0;
  TH1F * h_2015ff_mj_3p_0tag_up  = 0;

  TH1F * h_2015ff_mj_1p_0tag_do  = 0;
  TH1F * h_2015ff_mj_3p_0tag_do  = 0;

  TH1F * h_2015ff_mj_1p_1tag  = 0;
  TH1F * h_2015ff_mj_3p_1tag  = 0;

  TH1F * h_2015ff_mj_1p_1tag_up  = 0;
  TH1F * h_2015ff_mj_3p_1tag_up  = 0;

  TH1F * h_2015ff_mj_1p_1tag_do  = 0;
  TH1F * h_2015ff_mj_3p_1tag_do  = 0;

  TH1F * h_ff_mj_1p_0tag  = 0;
  TH1F * h_ff_mj_3p_0tag  = 0;

  TH1F * h_ff_mj_1p_0tag_up  = 0;
  TH1F * h_ff_mj_3p_0tag_up  = 0;

  TH1F * h_ff_mj_1p_0tag_do  = 0;
  TH1F * h_ff_mj_3p_0tag_do  = 0;

  TH1F * h_ff_mj_1p_1tag  = 0;
  TH1F * h_ff_mj_3p_1tag  = 0;

  TH1F * h_ff_mj_1p_1tag_up  = 0;
  TH1F * h_ff_mj_3p_1tag_up  = 0;

  TH1F * h_ff_mj_1p_1tag_do  = 0;
  TH1F * h_ff_mj_3p_1tag_do  = 0;

  //** rqcd vs taupt : Allison
  TH1F * h_rqcd_el_bveto    = 0;
  TH1F * h_rqcd_el_bveto_up = 0;
  TH1F * h_rqcd_el_bveto_do = 0;
  TH1F * h_rqcd_mu_bveto    = 0;
  //TH1D * h_rqcd_mu_bveto_fixed    = 0;
  TH1F * h_rqcd_mu_bveto_up = 0;
  TH1F * h_rqcd_mu_bveto_do = 0;
  TH1F * h_rqcd_el_btag     = 0;
  TH1F * h_rqcd_el_btag_up  = 0;
  TH1F * h_rqcd_el_btag_do  = 0;
  TH1F * h_rqcd_mu_btag     = 0;
  TH1F * h_rqcd_mu_btag_up  = 0;
  TH1F * h_rqcd_mu_btag_do  = 0;

  TH1F * h_dphi_cor  = 0;
  TH1F * h_dphi_cor_up  = 0;
  TH1F * h_dphi_cor_do  = 0;

  TH1F * h_dphiW25 = 0;
  TH1F * h_dphiW30 = 0;
  TH1F * h_dphiW40 = 0;
  TH1F * h_dphiW60 = 0;

  std::vector<TFile*> fileList;


public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  ptReweight();
  ptReweight(const TString& expression);
  virtual ~ptReweight();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(ptReweight, 1);


};
#endif
