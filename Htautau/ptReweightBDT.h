//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __PTREWEIGHTBDT__
#define __PTREWEIGHTBDT__
#include "QFramework/TQTreeObservable.h"
#include "Htautau/LepHadObservable.h"

class ptReweightBDT : public LepHadObservable {
protected:
  // put here any data members your class might need

public:
  virtual double getValue() const override;
  virtual TObjArray* getBranchNames() const override;

protected:
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;
  void printError(const TString& name="");
  TString fSysName = "";
  TDirectory* m_histoDir = 0;

  TH1F* h_ff_wcr[2][2][5][4];
  TH1F* h_ff_wcr_up[2][2][5][4];
  TH1F* h_ff_wcr_down[2][2][5][4];
  bool checkFF(int prongs,int tags,int bdt,int dphi)const;
  std::string resolveFileName(int prongs,int tags,int bdt,int dphi)const;
  std::string resolveHistName(int prongs,int tags,int bdt,int dphi)const;

  ///////////////////////
  //
  //	B-VETO 1-PRONG
  //
  TH1F * h_ff_wcr_1p_0tag_bdt1 		= 0;
  TH1F * h_ff_wcr_1p_0tag_bdt1_up   = 0;
  TH1F * h_ff_wcr_1p_0tag_bdt1_down = 0;

  TH1F * h_ff_wcr_1p_0tag_bdt2 		= 0;
  TH1F * h_ff_wcr_1p_0tag_bdt2_up   = 0;
  TH1F * h_ff_wcr_1p_0tag_bdt2_down = 0;

  TH1F * h_ff_wcr_1p_0tag_bdt3 		= 0;
  TH1F * h_ff_wcr_1p_0tag_bdt3_up   = 0;
  TH1F * h_ff_wcr_1p_0tag_bdt3_down = 0;

  TH1F * h_ff_wcr_1p_0tag_bdt4 		= 0;
  TH1F * h_ff_wcr_1p_0tag_bdt4_up   = 0;
  TH1F * h_ff_wcr_1p_0tag_bdt4_down = 0;

  ///////////////////////
  //
  //	B-VETO 3-PRONG
  //
  TH1F * h_ff_wcr_3p_0tag_bdt1 		= 0;
  TH1F * h_ff_wcr_3p_0tag_bdt1_up   = 0;
  TH1F * h_ff_wcr_3p_0tag_bdt1_down = 0;

  TH1F * h_ff_wcr_3p_0tag_bdt2 		= 0;
  TH1F * h_ff_wcr_3p_0tag_bdt2_up   = 0;
  TH1F * h_ff_wcr_3p_0tag_bdt2_down = 0;

  TH1F * h_ff_wcr_3p_0tag_bdt3 		= 0;
  TH1F * h_ff_wcr_3p_0tag_bdt3_up   = 0;
  TH1F * h_ff_wcr_3p_0tag_bdt3_down = 0;


  ///////////////////////
  //
  //	B-TAG 1-PRONG
  //
  TH1F * h_ff_wcr_1p_1tag_bdt1 		= 0;
  TH1F * h_ff_wcr_1p_1tag_bdt1_up   = 0;
  TH1F * h_ff_wcr_1p_1tag_bdt1_down = 0;

  TH1F * h_ff_wcr_1p_1tag_bdt2 		= 0;
  TH1F * h_ff_wcr_1p_1tag_bdt2_up   = 0;
  TH1F * h_ff_wcr_1p_1tag_bdt2_down = 0;

  TH1F * h_ff_wcr_1p_1tag_bdt3 		= 0;
  TH1F * h_ff_wcr_1p_1tag_bdt3_up   = 0;
  TH1F * h_ff_wcr_1p_1tag_bdt3_down = 0;

  TH1F * h_ff_wcr_1p_1tag_bdt4 		= 0;
  TH1F * h_ff_wcr_1p_1tag_bdt4_up   = 0;
  TH1F * h_ff_wcr_1p_1tag_bdt4_down = 0;

  ///////////////////////
  //
  //	B-TAG 3-PRONG
  //
  TH1F * h_ff_wcr_3p_1tag_bdt1 		= 0;
  TH1F * h_ff_wcr_3p_1tag_bdt1_up   = 0;
  TH1F * h_ff_wcr_3p_1tag_bdt1_down = 0;

  TH1F * h_ff_wcr_3p_1tag_bdt2 		= 0;
  TH1F * h_ff_wcr_3p_1tag_bdt2_up   = 0;
  TH1F * h_ff_wcr_3p_1tag_bdt2_down = 0;

  TH1F * h_ff_wcr_3p_1tag_bdt3 		= 0;
  TH1F * h_ff_wcr_3p_1tag_bdt3_up   = 0;
  TH1F * h_ff_wcr_3p_1tag_bdt3_down = 0;


  ///////////////////////
  //
  //	DPHI CORRECTIONS
  //
  TH1F * h_corr_wcr_1p_0tag_bdt1 = 0;
  TH1F * h_corr_wcr_1p_0tag_bdt2 = 0;
  TH1F * h_corr_wcr_1p_0tag_bdt3 = 0;
  TH1F * h_corr_wcr_1p_0tag_bdt4 = 0;
  TH1F * h_corr_wcr_3p_0tag_bdt123 = 0;

public:
  ptReweightBDT();
  ptReweightBDT(const TString& name);
  virtual ~ptReweightBDT();
  ClassDefOverride(ptReweightBDT, 1);


};
#endif
