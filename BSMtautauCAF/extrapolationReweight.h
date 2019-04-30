//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __EXTRAPOLATIONREWEIGHT__
#define __EXTRAPOLATIONREWEIGHT__
#include "QFramework/TQTreeObservable.h"

#include "BSMtautauCAF/LepHadObservable.h"
#include "TH2F.h"

class extrapolationReweight : public LepHadObservable {
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

  const long LIMIT_2016 = 311481;
  const long LIMIT_2017 = 340453;


  TH1 *h_weight ;

  // nominal pt parametrization
  // 2015/16
  TH1F * h_ff15_vr_ehad_1p_0tag = 0;
  TH1F * h_ff15_vr_ehad_3p_0tag = 0;
  TH1F * h_ff15_vr_ehad_1p_0tag_up   = 0;
  TH1F * h_ff15_vr_ehad_3p_0tag_up   = 0;
  TH1F * h_ff15_vr_ehad_1p_0tag_down = 0;
  TH1F * h_ff15_vr_ehad_3p_0tag_down = 0;

  TH1F * h_ff15_vr_ehad_1p_1tag = 0;
  TH1F * h_ff15_vr_ehad_3p_1tag = 0;
  TH1F * h_ff15_vr_ehad_1p_1tag_up   = 0;
  TH1F * h_ff15_vr_ehad_3p_1tag_up   = 0;
  TH1F * h_ff15_vr_ehad_1p_1tag_down = 0;
  TH1F * h_ff15_vr_ehad_3p_1tag_down = 0;

  TH1F * h_ff15_vr_muhad_1p_0tag = 0;
  TH1F * h_ff15_vr_muhad_3p_0tag = 0;
  TH1F * h_ff15_vr_muhad_1p_0tag_up   = 0;
  TH1F * h_ff15_vr_muhad_3p_0tag_up   = 0;
  TH1F * h_ff15_vr_muhad_1p_0tag_down = 0;
  TH1F * h_ff15_vr_muhad_3p_0tag_down = 0;

  TH1F * h_ff15_vr_muhad_1p_1tag = 0;
  TH1F * h_ff15_vr_muhad_3p_1tag = 0;
  TH1F * h_ff15_vr_muhad_1p_1tag_up   = 0;
  TH1F * h_ff15_vr_muhad_3p_1tag_up   = 0;
  TH1F * h_ff15_vr_muhad_1p_1tag_down = 0;
  TH1F * h_ff15_vr_muhad_3p_1tag_down = 0;

  // 2017
  TH1F * h_ff17_vr_ehad_1p_0tag = 0;
  TH1F * h_ff17_vr_ehad_3p_0tag = 0;
  TH1F * h_ff17_vr_ehad_1p_0tag_up   = 0;
  TH1F * h_ff17_vr_ehad_3p_0tag_up   = 0;
  TH1F * h_ff17_vr_ehad_1p_0tag_down = 0;
  TH1F * h_ff17_vr_ehad_3p_0tag_down = 0;

  TH1F * h_ff17_vr_ehad_1p_1tag = 0;
  TH1F * h_ff17_vr_ehad_3p_1tag = 0;
  TH1F * h_ff17_vr_ehad_1p_1tag_up   = 0;
  TH1F * h_ff17_vr_ehad_3p_1tag_up   = 0;
  TH1F * h_ff17_vr_ehad_1p_1tag_down = 0;
  TH1F * h_ff17_vr_ehad_3p_1tag_down = 0;

  TH1F * h_ff17_vr_muhad_1p_0tag = 0;
  TH1F * h_ff17_vr_muhad_3p_0tag = 0;
  TH1F * h_ff17_vr_muhad_1p_0tag_up   = 0;
  TH1F * h_ff17_vr_muhad_3p_0tag_up   = 0;
  TH1F * h_ff17_vr_muhad_1p_0tag_down = 0;
  TH1F * h_ff17_vr_muhad_3p_0tag_down = 0;

  TH1F * h_ff17_vr_muhad_1p_1tag = 0;
  TH1F * h_ff17_vr_muhad_3p_1tag = 0;
  TH1F * h_ff17_vr_muhad_1p_1tag_up   = 0;
  TH1F * h_ff17_vr_muhad_3p_1tag_up   = 0;
  TH1F * h_ff17_vr_muhad_1p_1tag_down = 0;
  TH1F * h_ff17_vr_muhad_3p_1tag_down = 0;


  // pt * dphi parametrization
  // 2015/16
  TH1F * h_ff15_vr_1p_dphi1_0tag = 0;
  TH1F * h_ff15_vr_1p_dphi1_0tag_up   = 0;
  TH1F * h_ff15_vr_1p_dphi1_0tag_down = 0;

  TH1F * h_ff15_vr_1p_dphi2_0tag = 0;
  TH1F * h_ff15_vr_1p_dphi2_0tag_up   = 0;
  TH1F * h_ff15_vr_1p_dphi2_0tag_down = 0;

  TH1F * h_ff15_vr_1p_dphi3_0tag = 0;
  TH1F * h_ff15_vr_1p_dphi3_0tag_up   = 0;
  TH1F * h_ff15_vr_1p_dphi3_0tag_down = 0;

  TH1F * h_ff15_vr_3p_dphi1_0tag = 0;
  TH1F * h_ff15_vr_3p_dphi1_0tag_up   = 0;
  TH1F * h_ff15_vr_3p_dphi1_0tag_down = 0;

  TH1F * h_ff15_vr_3p_dphi2_0tag = 0;
  TH1F * h_ff15_vr_3p_dphi2_0tag_up   = 0;
  TH1F * h_ff15_vr_3p_dphi2_0tag_down = 0;

  TH1F * h_ff15_vr_3p_dphi3_0tag = 0;
  TH1F * h_ff15_vr_3p_dphi3_0tag_up   = 0;
  TH1F * h_ff15_vr_3p_dphi3_0tag_down = 0;

  // 2017
  TH1F * h_ff17_vr_1p_dphi1_0tag = 0;
  TH1F * h_ff17_vr_1p_dphi1_0tag_up   = 0;
  TH1F * h_ff17_vr_1p_dphi1_0tag_down = 0;

  TH1F * h_ff17_vr_1p_dphi2_0tag = 0;
  TH1F * h_ff17_vr_1p_dphi2_0tag_up   = 0;
  TH1F * h_ff17_vr_1p_dphi2_0tag_down = 0;

  TH1F * h_ff17_vr_1p_dphi3_0tag = 0;
  TH1F * h_ff17_vr_1p_dphi3_0tag_up   = 0;
  TH1F * h_ff17_vr_1p_dphi3_0tag_down = 0;

  TH1F * h_ff17_vr_3p_dphi1_0tag = 0;
  TH1F * h_ff17_vr_3p_dphi1_0tag_up   = 0;
  TH1F * h_ff17_vr_3p_dphi1_0tag_down = 0;

  TH1F * h_ff17_vr_3p_dphi2_0tag = 0;
  TH1F * h_ff17_vr_3p_dphi2_0tag_up   = 0;
  TH1F * h_ff17_vr_3p_dphi2_0tag_down = 0;

  TH1F * h_ff17_vr_3p_dphi3_0tag = 0;
  TH1F * h_ff17_vr_3p_dphi3_0tag_up   = 0;
  TH1F * h_ff17_vr_3p_dphi3_0tag_down = 0;



  std::vector<TFile*> fileList;


public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  extrapolationReweight();
  extrapolationReweight(const TString& expression);
  virtual ~extrapolationReweight();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(extrapolationReweight, 1);


};
#endif
