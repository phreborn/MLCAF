//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __ISOREWEIGHT__
#define __ISOREWEIGHT__

#include "BSMtautauCAF/LepHadObservable.h"

class isoReweight : public LepHadObservable {
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


  TH1 *h_weight ;
  // 2015+2016
  TH1F* h_ff15_lfr_ehad_0tag = 0;
  TH1F* h_ff15_lfr_ehad_0tag_up = 0;
  TH1F* h_ff15_lfr_ehad_0tag_down = 0;

  TH1F* h_ff15_lfr_ehad_1tag = 0;
  TH1F* h_ff15_lfr_ehad_1tag_up = 0;
  TH1F* h_ff15_lfr_ehad_1tag_down = 0;

  TH1F* h_ff15_lfr_muhad_0tag_lowpt = 0;
  TH1F* h_ff15_lfr_muhad_0tag_lowpt_up = 0;
  TH1F* h_ff15_lfr_muhad_0tag_lowpt_down = 0;

  TH1F* h_ff15_lfr_muhad_0tag_highpt = 0;
  TH1F* h_ff15_lfr_muhad_0tag_highpt_up = 0;
  TH1F* h_ff15_lfr_muhad_0tag_highpt_down = 0;

  TH1F* h_ff15_lfr_muhad_1tag_lowpt = 0;
  TH1F* h_ff15_lfr_muhad_1tag_lowpt_up = 0;
  TH1F* h_ff15_lfr_muhad_1tag_lowpt_down = 0;

  TH1F* h_ff15_lfr_muhad_1tag_highpt = 0;
  TH1F* h_ff15_lfr_muhad_1tag_highpt_up = 0;
  TH1F* h_ff15_lfr_muhad_1tag_highpt_down = 0;


  TH1F* h_ff15_lfr_ehad_0tag_pt = 0;
  TH1F* h_ff15_lfr_ehad_0tag_pt_up = 0;
  TH1F* h_ff15_lfr_ehad_0tag_pt_down = 0;

  TH1F* h_ff15_lfr_ehad_1tag_pt = 0;
  TH1F* h_ff15_lfr_ehad_1tag_pt_up = 0;
  TH1F* h_ff15_lfr_ehad_1tag_pt_down = 0;

  TH1F* h_ff15_lfr_muhad_0tag_pt = 0;
  TH1F* h_ff15_lfr_muhad_0tag_pt_up = 0;
  TH1F* h_ff15_lfr_muhad_0tag_pt_down = 0;

  TH1F* h_ff15_lfr_muhad_1tag_pt = 0;
  TH1F* h_ff15_lfr_muhad_1tag_pt_up = 0;
  TH1F* h_ff15_lfr_muhad_1tag_pt_down = 0;


  TH1F* h_dphi15corr_lfr_ehad_0tag = 0;
  TH1F* h_dphi15corr_lfr_ehad_0tag_up = 0;
  TH1F* h_dphi15corr_lfr_ehad_0tag_down = 0;

  TH1F* h_dphi15corr_lfr_muhad_0tag = 0;
  TH1F* h_dphi15corr_lfr_muhad_0tag_up = 0;
  TH1F* h_dphi15corr_lfr_muhad_0tag_down = 0;

  TH1F* h_dphi15corr_lfr_ehad_1tag = 0;
  TH1F* h_dphi15corr_lfr_ehad_1tag_up = 0;
  TH1F* h_dphi15corr_lfr_ehad_1tag_down = 0;

  TH1F* h_dphi15corr_lfr_muhad_1tag = 0;
  TH1F* h_dphi15corr_lfr_muhad_1tag_up = 0;
  TH1F* h_dphi15corr_lfr_muhad_1tag_down = 0;

  float ave_ele_bveto_eta, ave_ele_btag_eta;

  TH1F* h_ff15_lfr_ehad_dphi1_0tag_pt = 0;
  TH1F* h_ff15_lfr_ehad_dphi1_0tag_pt_up = 0;
  TH1F* h_ff15_lfr_ehad_dphi1_0tag_pt_down = 0;
  TH1F* h_ff15_lfr_ehad_dphi2_0tag_pt = 0;
  TH1F* h_ff15_lfr_ehad_dphi2_0tag_pt_up = 0;
  TH1F* h_ff15_lfr_ehad_dphi2_0tag_pt_down = 0;
  TH1F* h_ff15_lfr_ehad_dphi3_0tag_pt = 0;
  TH1F* h_ff15_lfr_ehad_dphi3_0tag_pt_up = 0;
  TH1F* h_ff15_lfr_ehad_dphi3_0tag_pt_down = 0;
  TH1F* h_ff15_lfr_ehad_dphi4_0tag_pt = 0;
  TH1F* h_ff15_lfr_ehad_dphi4_0tag_pt_up = 0;
  TH1F* h_ff15_lfr_ehad_dphi4_0tag_pt_down = 0;

  TH1F* h_ff15_lfr_ehad_dphi1_1tag_pt = 0;
  TH1F* h_ff15_lfr_ehad_dphi1_1tag_pt_up = 0;
  TH1F* h_ff15_lfr_ehad_dphi1_1tag_pt_down = 0;
  TH1F* h_ff15_lfr_ehad_dphi2_1tag_pt = 0;
  TH1F* h_ff15_lfr_ehad_dphi2_1tag_pt_up = 0;
  TH1F* h_ff15_lfr_ehad_dphi2_1tag_pt_down = 0;
  TH1F* h_ff15_lfr_ehad_dphi3_1tag_pt = 0;
  TH1F* h_ff15_lfr_ehad_dphi3_1tag_pt_up = 0;
  TH1F* h_ff15_lfr_ehad_dphi3_1tag_pt_down = 0;
  TH1F* h_ff15_lfr_ehad_dphi4_1tag_pt = 0;
  TH1F* h_ff15_lfr_ehad_dphi4_1tag_pt_up = 0;
  TH1F* h_ff15_lfr_ehad_dphi4_1tag_pt_down = 0;


  TH1F* h_ff15_lfr_muhad_dphi1_0tag_pt = 0;
  TH1F* h_ff15_lfr_muhad_dphi1_0tag_pt_up = 0;
  TH1F* h_ff15_lfr_muhad_dphi1_0tag_pt_down = 0;
  TH1F* h_ff15_lfr_muhad_dphi2_0tag_pt = 0;
  TH1F* h_ff15_lfr_muhad_dphi2_0tag_pt_up = 0;
  TH1F* h_ff15_lfr_muhad_dphi2_0tag_pt_down = 0;
  TH1F* h_ff15_lfr_muhad_dphi3_0tag_pt = 0;
  TH1F* h_ff15_lfr_muhad_dphi3_0tag_pt_up = 0;
  TH1F* h_ff15_lfr_muhad_dphi3_0tag_pt_down = 0;
  TH1F* h_ff15_lfr_muhad_dphi4_0tag_pt = 0;
  TH1F* h_ff15_lfr_muhad_dphi4_0tag_pt_up = 0;
  TH1F* h_ff15_lfr_muhad_dphi4_0tag_pt_down = 0;

  TH1F* h_ff15_lfr_muhad_dphi1_1tag_pt = 0;
  TH1F* h_ff15_lfr_muhad_dphi1_1tag_pt_up = 0;
  TH1F* h_ff15_lfr_muhad_dphi1_1tag_pt_down = 0;
  TH1F* h_ff15_lfr_muhad_dphi2_1tag_pt = 0;
  TH1F* h_ff15_lfr_muhad_dphi2_1tag_pt_up = 0;
  TH1F* h_ff15_lfr_muhad_dphi2_1tag_pt_down = 0;
  TH1F* h_ff15_lfr_muhad_dphi3_1tag_pt = 0;
  TH1F* h_ff15_lfr_muhad_dphi3_1tag_pt_up = 0;
  TH1F* h_ff15_lfr_muhad_dphi3_1tag_pt_down = 0;
  TH1F* h_ff15_lfr_muhad_dphi4_1tag_pt = 0;
  TH1F* h_ff15_lfr_muhad_dphi4_1tag_pt_up = 0;
  TH1F* h_ff15_lfr_muhad_dphi4_1tag_pt_down = 0;

  // 2017
  TH1F* h_ff17_lfr_ehad_0tag = 0;
  TH1F* h_ff17_lfr_ehad_0tag_up = 0;
  TH1F* h_ff17_lfr_ehad_0tag_down = 0;

  TH1F* h_ff17_lfr_ehad_1tag = 0;
  TH1F* h_ff17_lfr_ehad_1tag_up = 0;
  TH1F* h_ff17_lfr_ehad_1tag_down = 0;

  TH1F* h_ff17_lfr_muhad_0tag_lowpt = 0;
  TH1F* h_ff17_lfr_muhad_0tag_lowpt_up = 0;
  TH1F* h_ff17_lfr_muhad_0tag_lowpt_down = 0;

  TH1F* h_ff17_lfr_muhad_0tag_highpt = 0;
  TH1F* h_ff17_lfr_muhad_0tag_highpt_up = 0;
  TH1F* h_ff17_lfr_muhad_0tag_highpt_down = 0;

  TH1F* h_ff17_lfr_muhad_1tag_lowpt = 0;
  TH1F* h_ff17_lfr_muhad_1tag_lowpt_up = 0;
  TH1F* h_ff17_lfr_muhad_1tag_lowpt_down = 0;

  TH1F* h_ff17_lfr_muhad_1tag_highpt = 0;
  TH1F* h_ff17_lfr_muhad_1tag_highpt_up = 0;
  TH1F* h_ff17_lfr_muhad_1tag_highpt_down = 0;


  TH1F* h_ff17_lfr_ehad_0tag_pt = 0;
  TH1F* h_ff17_lfr_ehad_0tag_pt_up = 0;
  TH1F* h_ff17_lfr_ehad_0tag_pt_down = 0;

  TH1F* h_ff17_lfr_ehad_1tag_pt = 0;
  TH1F* h_ff17_lfr_ehad_1tag_pt_up = 0;
  TH1F* h_ff17_lfr_ehad_1tag_pt_down = 0;

  TH1F* h_ff17_lfr_muhad_0tag_pt = 0;
  TH1F* h_ff17_lfr_muhad_0tag_pt_up = 0;
  TH1F* h_ff17_lfr_muhad_0tag_pt_down = 0;

  TH1F* h_ff17_lfr_muhad_1tag_pt = 0;
  TH1F* h_ff17_lfr_muhad_1tag_pt_up = 0;
  TH1F* h_ff17_lfr_muhad_1tag_pt_down = 0;


  TH1F* h_dphi17corr_lfr_ehad_0tag = 0;
  TH1F* h_dphi17corr_lfr_ehad_0tag_up = 0;
  TH1F* h_dphi17corr_lfr_ehad_0tag_down = 0;

  TH1F* h_dphi17corr_lfr_muhad_0tag = 0;
  TH1F* h_dphi17corr_lfr_muhad_0tag_up = 0;
  TH1F* h_dphi17corr_lfr_muhad_0tag_down = 0;

  TH1F* h_dphi17corr_lfr_ehad_1tag = 0;
  TH1F* h_dphi17corr_lfr_ehad_1tag_up = 0;
  TH1F* h_dphi17corr_lfr_ehad_1tag_down = 0;

  TH1F* h_dphi17corr_lfr_muhad_1tag = 0;
  TH1F* h_dphi17corr_lfr_muhad_1tag_up = 0;
  TH1F* h_dphi17corr_lfr_muhad_1tag_down = 0;

  TH1F* h_ff17_lfr_ehad_dphi1_0tag_pt = 0;
  TH1F* h_ff17_lfr_ehad_dphi1_0tag_pt_up = 0;
  TH1F* h_ff17_lfr_ehad_dphi1_0tag_pt_down = 0;
  TH1F* h_ff17_lfr_ehad_dphi2_0tag_pt = 0;
  TH1F* h_ff17_lfr_ehad_dphi2_0tag_pt_up = 0;
  TH1F* h_ff17_lfr_ehad_dphi2_0tag_pt_down = 0;
  TH1F* h_ff17_lfr_ehad_dphi3_0tag_pt = 0;
  TH1F* h_ff17_lfr_ehad_dphi3_0tag_pt_up = 0;
  TH1F* h_ff17_lfr_ehad_dphi3_0tag_pt_down = 0;
  TH1F* h_ff17_lfr_ehad_dphi4_0tag_pt = 0;
  TH1F* h_ff17_lfr_ehad_dphi4_0tag_pt_up = 0;
  TH1F* h_ff17_lfr_ehad_dphi4_0tag_pt_down = 0;

  TH1F* h_ff17_lfr_ehad_dphi1_1tag_pt = 0;
  TH1F* h_ff17_lfr_ehad_dphi1_1tag_pt_up = 0;
  TH1F* h_ff17_lfr_ehad_dphi1_1tag_pt_down = 0;
  TH1F* h_ff17_lfr_ehad_dphi2_1tag_pt = 0;
  TH1F* h_ff17_lfr_ehad_dphi2_1tag_pt_up = 0;
  TH1F* h_ff17_lfr_ehad_dphi2_1tag_pt_down = 0;
  TH1F* h_ff17_lfr_ehad_dphi3_1tag_pt = 0;
  TH1F* h_ff17_lfr_ehad_dphi3_1tag_pt_up = 0;
  TH1F* h_ff17_lfr_ehad_dphi3_1tag_pt_down = 0;
  TH1F* h_ff17_lfr_ehad_dphi4_1tag_pt = 0;
  TH1F* h_ff17_lfr_ehad_dphi4_1tag_pt_up = 0;
  TH1F* h_ff17_lfr_ehad_dphi4_1tag_pt_down = 0;


  TH1F* h_ff17_lfr_muhad_dphi1_0tag_pt = 0;
  TH1F* h_ff17_lfr_muhad_dphi1_0tag_pt_up = 0;
  TH1F* h_ff17_lfr_muhad_dphi1_0tag_pt_down = 0;
  TH1F* h_ff17_lfr_muhad_dphi2_0tag_pt = 0;
  TH1F* h_ff17_lfr_muhad_dphi2_0tag_pt_up = 0;
  TH1F* h_ff17_lfr_muhad_dphi2_0tag_pt_down = 0;
  TH1F* h_ff17_lfr_muhad_dphi3_0tag_pt = 0;
  TH1F* h_ff17_lfr_muhad_dphi3_0tag_pt_up = 0;
  TH1F* h_ff17_lfr_muhad_dphi3_0tag_pt_down = 0;
  TH1F* h_ff17_lfr_muhad_dphi4_0tag_pt = 0;
  TH1F* h_ff17_lfr_muhad_dphi4_0tag_pt_up = 0;
  TH1F* h_ff17_lfr_muhad_dphi4_0tag_pt_down = 0;

  TH1F* h_ff17_lfr_muhad_dphi1_1tag_pt = 0;
  TH1F* h_ff17_lfr_muhad_dphi1_1tag_pt_up = 0;
  TH1F* h_ff17_lfr_muhad_dphi1_1tag_pt_down = 0;
  TH1F* h_ff17_lfr_muhad_dphi2_1tag_pt = 0;
  TH1F* h_ff17_lfr_muhad_dphi2_1tag_pt_up = 0;
  TH1F* h_ff17_lfr_muhad_dphi2_1tag_pt_down = 0;
  TH1F* h_ff17_lfr_muhad_dphi3_1tag_pt = 0;
  TH1F* h_ff17_lfr_muhad_dphi3_1tag_pt_up = 0;
  TH1F* h_ff17_lfr_muhad_dphi3_1tag_pt_down = 0;
  TH1F* h_ff17_lfr_muhad_dphi4_1tag_pt = 0;
  TH1F* h_ff17_lfr_muhad_dphi4_1tag_pt_up = 0;
  TH1F* h_ff17_lfr_muhad_dphi4_1tag_pt_down = 0;

  // 2018
  TH1F* h_ff18_lfr_ehad_0tag = 0;
  TH1F* h_ff18_lfr_ehad_0tag_up = 0;
  TH1F* h_ff18_lfr_ehad_0tag_down = 0;

  TH1F* h_ff18_lfr_ehad_1tag = 0;
  TH1F* h_ff18_lfr_ehad_1tag_up = 0;
  TH1F* h_ff18_lfr_ehad_1tag_down = 0;

  TH1F* h_ff18_lfr_muhad_0tag_lowpt = 0;
  TH1F* h_ff18_lfr_muhad_0tag_lowpt_up = 0;
  TH1F* h_ff18_lfr_muhad_0tag_lowpt_down = 0;

  TH1F* h_ff18_lfr_muhad_0tag_highpt = 0;
  TH1F* h_ff18_lfr_muhad_0tag_highpt_up = 0;
  TH1F* h_ff18_lfr_muhad_0tag_highpt_down = 0;

  TH1F* h_ff18_lfr_muhad_1tag_lowpt = 0;
  TH1F* h_ff18_lfr_muhad_1tag_lowpt_up = 0;
  TH1F* h_ff18_lfr_muhad_1tag_lowpt_down = 0;

  TH1F* h_ff18_lfr_muhad_1tag_highpt = 0;
  TH1F* h_ff18_lfr_muhad_1tag_highpt_up = 0;
  TH1F* h_ff18_lfr_muhad_1tag_highpt_down = 0;


  TH1F* h_ff18_lfr_ehad_0tag_pt = 0;
  TH1F* h_ff18_lfr_ehad_0tag_pt_up = 0;
  TH1F* h_ff18_lfr_ehad_0tag_pt_down = 0;

  TH1F* h_ff18_lfr_ehad_1tag_pt = 0;
  TH1F* h_ff18_lfr_ehad_1tag_pt_up = 0;
  TH1F* h_ff18_lfr_ehad_1tag_pt_down = 0;

  TH1F* h_ff18_lfr_muhad_0tag_pt = 0;
  TH1F* h_ff18_lfr_muhad_0tag_pt_up = 0;
  TH1F* h_ff18_lfr_muhad_0tag_pt_down = 0;

  TH1F* h_ff18_lfr_muhad_1tag_pt = 0;
  TH1F* h_ff18_lfr_muhad_1tag_pt_up = 0;
  TH1F* h_ff18_lfr_muhad_1tag_pt_down = 0;


  TH1F* h_dphi18corr_lfr_ehad_0tag = 0;
  TH1F* h_dphi18corr_lfr_ehad_0tag_up = 0;
  TH1F* h_dphi18corr_lfr_ehad_0tag_down = 0;

  TH1F* h_dphi18corr_lfr_muhad_0tag = 0;
  TH1F* h_dphi18corr_lfr_muhad_0tag_up = 0;
  TH1F* h_dphi18corr_lfr_muhad_0tag_down = 0;

  TH1F* h_dphi18corr_lfr_ehad_1tag = 0;
  TH1F* h_dphi18corr_lfr_ehad_1tag_up = 0;
  TH1F* h_dphi18corr_lfr_ehad_1tag_down = 0;

  TH1F* h_dphi18corr_lfr_muhad_1tag = 0;
  TH1F* h_dphi18corr_lfr_muhad_1tag_up = 0;
  TH1F* h_dphi18corr_lfr_muhad_1tag_down = 0;

  TH1F* h_ff18_lfr_ehad_dphi1_0tag_pt = 0;
  TH1F* h_ff18_lfr_ehad_dphi1_0tag_pt_up = 0;
  TH1F* h_ff18_lfr_ehad_dphi1_0tag_pt_down = 0;
  TH1F* h_ff18_lfr_ehad_dphi2_0tag_pt = 0;
  TH1F* h_ff18_lfr_ehad_dphi2_0tag_pt_up = 0;
  TH1F* h_ff18_lfr_ehad_dphi2_0tag_pt_down = 0;
  TH1F* h_ff18_lfr_ehad_dphi3_0tag_pt = 0;
  TH1F* h_ff18_lfr_ehad_dphi3_0tag_pt_up = 0;
  TH1F* h_ff18_lfr_ehad_dphi3_0tag_pt_down = 0;
  TH1F* h_ff18_lfr_ehad_dphi4_0tag_pt = 0;
  TH1F* h_ff18_lfr_ehad_dphi4_0tag_pt_up = 0;
  TH1F* h_ff18_lfr_ehad_dphi4_0tag_pt_down = 0;

  TH1F* h_ff18_lfr_ehad_dphi1_1tag_pt = 0;
  TH1F* h_ff18_lfr_ehad_dphi1_1tag_pt_up = 0;
  TH1F* h_ff18_lfr_ehad_dphi1_1tag_pt_down = 0;
  TH1F* h_ff18_lfr_ehad_dphi2_1tag_pt = 0;
  TH1F* h_ff18_lfr_ehad_dphi2_1tag_pt_up = 0;
  TH1F* h_ff18_lfr_ehad_dphi2_1tag_pt_down = 0;
  TH1F* h_ff18_lfr_ehad_dphi3_1tag_pt = 0;
  TH1F* h_ff18_lfr_ehad_dphi3_1tag_pt_up = 0;
  TH1F* h_ff18_lfr_ehad_dphi3_1tag_pt_down = 0;
  TH1F* h_ff18_lfr_ehad_dphi4_1tag_pt = 0;
  TH1F* h_ff18_lfr_ehad_dphi4_1tag_pt_up = 0;
  TH1F* h_ff18_lfr_ehad_dphi4_1tag_pt_down = 0;


  TH1F* h_ff18_lfr_muhad_dphi1_0tag_pt = 0;
  TH1F* h_ff18_lfr_muhad_dphi1_0tag_pt_up = 0;
  TH1F* h_ff18_lfr_muhad_dphi1_0tag_pt_down = 0;
  TH1F* h_ff18_lfr_muhad_dphi2_0tag_pt = 0;
  TH1F* h_ff18_lfr_muhad_dphi2_0tag_pt_up = 0;
  TH1F* h_ff18_lfr_muhad_dphi2_0tag_pt_down = 0;
  TH1F* h_ff18_lfr_muhad_dphi3_0tag_pt = 0;
  TH1F* h_ff18_lfr_muhad_dphi3_0tag_pt_up = 0;
  TH1F* h_ff18_lfr_muhad_dphi3_0tag_pt_down = 0;
  TH1F* h_ff18_lfr_muhad_dphi4_0tag_pt = 0;
  TH1F* h_ff18_lfr_muhad_dphi4_0tag_pt_up = 0;
  TH1F* h_ff18_lfr_muhad_dphi4_0tag_pt_down = 0;

  TH1F* h_ff18_lfr_muhad_dphi1_1tag_pt = 0;
  TH1F* h_ff18_lfr_muhad_dphi1_1tag_pt_up = 0;
  TH1F* h_ff18_lfr_muhad_dphi1_1tag_pt_down = 0;
  TH1F* h_ff18_lfr_muhad_dphi2_1tag_pt = 0;
  TH1F* h_ff18_lfr_muhad_dphi2_1tag_pt_up = 0;
  TH1F* h_ff18_lfr_muhad_dphi2_1tag_pt_down = 0;
  TH1F* h_ff18_lfr_muhad_dphi3_1tag_pt = 0;
  TH1F* h_ff18_lfr_muhad_dphi3_1tag_pt_up = 0;
  TH1F* h_ff18_lfr_muhad_dphi3_1tag_pt_down = 0;
  TH1F* h_ff18_lfr_muhad_dphi4_1tag_pt = 0;
  TH1F* h_ff18_lfr_muhad_dphi4_1tag_pt_up = 0;
  TH1F* h_ff18_lfr_muhad_dphi4_1tag_pt_down = 0;

  std::vector<TFile*> fileList;


public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  isoReweight();
  isoReweight(const TString& expression);
  virtual ~isoReweight();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(isoReweight, 1);


};
#endif
