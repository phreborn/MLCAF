//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __btagEffSys__
#define __btagEffSys__
#include "QFramework/TQTreeObservable.h"

#include "TTreeFormula.h"

class btagEffSys : public TQTreeObservable {
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
  
  Float_t btagSys_NOMINAL_sf;
  Float_t btagSys_NOMINAL_ineff_sf;

  Float_t btagSys_Eigen_B_0_1down_sf ;
  Float_t btagSys_Eigen_B_0_1down_ineff_sf ;
  Float_t btagSys_Eigen_B_0_1up_sf ;
  Float_t btagSys_Eigen_B_0_1up_ineff_sf ;
  Float_t btagSys_Eigen_B_1_1down_sf ;
  Float_t btagSys_Eigen_B_1_1down_ineff_sf ;
  Float_t btagSys_Eigen_B_1_1up_sf ;
  Float_t btagSys_Eigen_B_1_1up_ineff_sf ;
  Float_t btagSys_Eigen_B_2_1down_sf ;
  Float_t btagSys_Eigen_B_2_1down_ineff_sf ;
  Float_t btagSys_Eigen_B_2_1up_sf ;
  Float_t btagSys_Eigen_B_2_1up_ineff_sf ;
  Float_t btagSys_Eigen_B_3_1down_sf ;
  Float_t btagSys_Eigen_B_3_1down_ineff_sf ;
  Float_t btagSys_Eigen_B_3_1up_sf ;
  Float_t btagSys_Eigen_B_3_1up_ineff_sf ;
  Float_t btagSys_Eigen_B_4_1down_sf ;
  Float_t btagSys_Eigen_B_4_1down_ineff_sf ;
  Float_t btagSys_Eigen_B_4_1up_sf ;
  Float_t btagSys_Eigen_B_4_1up_ineff_sf ;
  Float_t btagSys_Eigen_C_0_1down_sf ;
  Float_t btagSys_Eigen_C_0_1down_ineff_sf ;
  Float_t btagSys_Eigen_C_0_1up_sf ;
  Float_t btagSys_Eigen_C_0_1up_ineff_sf ;
  Float_t btagSys_Eigen_C_1_1down_sf ;
  Float_t btagSys_Eigen_C_1_1down_ineff_sf ;
  Float_t btagSys_Eigen_C_1_1up_sf ;
  Float_t btagSys_Eigen_C_1_1up_ineff_sf ;
  Float_t btagSys_Eigen_C_2_1down_sf ;
  Float_t btagSys_Eigen_C_2_1down_ineff_sf ;
  Float_t btagSys_Eigen_C_2_1up_sf ;
  Float_t btagSys_Eigen_C_2_1up_ineff_sf ;
  Float_t btagSys_Eigen_C_3_1down_sf ;
  Float_t btagSys_Eigen_C_3_1down_ineff_sf ;
  Float_t btagSys_Eigen_C_3_1up_sf ;
  Float_t btagSys_Eigen_C_3_1up_ineff_sf ;
  Float_t btagSys_Eigen_Light_0_1down_sf ;
  Float_t btagSys_Eigen_Light_0_1down_ineff_sf ;
  Float_t btagSys_Eigen_Light_0_1up_sf ;
  Float_t btagSys_Eigen_Light_0_1up_ineff_sf ;
  Float_t btagSys_Eigen_Light_1_1down_sf ;
  Float_t btagSys_Eigen_Light_1_1down_ineff_sf ;
  Float_t btagSys_Eigen_Light_1_1up_sf ;
  Float_t btagSys_Eigen_Light_1_1up_ineff_sf ;
  Float_t btagSys_Eigen_Light_10_1down_sf ;
  Float_t btagSys_Eigen_Light_10_1down_ineff_sf ;
  Float_t btagSys_Eigen_Light_10_1up_sf ;
  Float_t btagSys_Eigen_Light_10_1up_ineff_sf ;
  Float_t btagSys_Eigen_Light_11_1down_sf ;
  Float_t btagSys_Eigen_Light_11_1down_ineff_sf ;
  Float_t btagSys_Eigen_Light_11_1up_sf ;
  Float_t btagSys_Eigen_Light_11_1up_ineff_sf ;
  Float_t btagSys_Eigen_Light_12_1down_sf ;
  Float_t btagSys_Eigen_Light_12_1down_ineff_sf ;
  Float_t btagSys_Eigen_Light_12_1up_sf ;
  Float_t btagSys_Eigen_Light_12_1up_ineff_sf ;
  Float_t btagSys_Eigen_Light_13_1down_sf ;
  Float_t btagSys_Eigen_Light_13_1down_ineff_sf ;
  Float_t btagSys_Eigen_Light_13_1up_sf ;
  Float_t btagSys_Eigen_Light_13_1up_ineff_sf ;
  Float_t btagSys_Eigen_Light_2_1down_sf ;
  Float_t btagSys_Eigen_Light_2_1down_ineff_sf ;
  Float_t btagSys_Eigen_Light_2_1up_sf ;
  Float_t btagSys_Eigen_Light_2_1up_ineff_sf ;
  Float_t btagSys_Eigen_Light_3_1down_sf ;
  Float_t btagSys_Eigen_Light_3_1down_ineff_sf ;
  Float_t btagSys_Eigen_Light_3_1up_sf ;
  Float_t btagSys_Eigen_Light_3_1up_ineff_sf ;
  Float_t btagSys_Eigen_Light_4_1down_sf ;
  Float_t btagSys_Eigen_Light_4_1down_ineff_sf ;
  Float_t btagSys_Eigen_Light_4_1up_sf ;
  Float_t btagSys_Eigen_Light_4_1up_ineff_sf ;
  Float_t btagSys_Eigen_Light_5_1down_sf ;
  Float_t btagSys_Eigen_Light_5_1down_ineff_sf ;
  Float_t btagSys_Eigen_Light_5_1up_sf ;
  Float_t btagSys_Eigen_Light_5_1up_ineff_sf ;
  Float_t btagSys_Eigen_Light_6_1down_sf ;
  Float_t btagSys_Eigen_Light_6_1down_ineff_sf ;
  Float_t btagSys_Eigen_Light_6_1up_sf ;
  Float_t btagSys_Eigen_Light_6_1up_ineff_sf ;
  Float_t btagSys_Eigen_Light_7_1down_sf ;
  Float_t btagSys_Eigen_Light_7_1down_ineff_sf ;
  Float_t btagSys_Eigen_Light_7_1up_sf ;
  Float_t btagSys_Eigen_Light_7_1up_ineff_sf ;
  Float_t btagSys_Eigen_Light_8_1down_sf ;
  Float_t btagSys_Eigen_Light_8_1down_ineff_sf ;
  Float_t btagSys_Eigen_Light_8_1up_sf ;
  Float_t btagSys_Eigen_Light_8_1up_ineff_sf ;
  Float_t btagSys_Eigen_Light_9_1down_sf ;
  Float_t btagSys_Eigen_Light_9_1down_ineff_sf ;
  Float_t btagSys_Eigen_Light_9_1up_sf ;
  Float_t btagSys_Eigen_Light_9_1up_ineff_sf ;
  Float_t btagSys_extrapolation_1down_sf ;
  Float_t btagSys_extrapolation_1down_ineff_sf ;
  Float_t btagSys_extrapolation_1up_sf ;
  Float_t btagSys_extrapolation_1up_ineff_sf ;
  Float_t btagSys_extrapolation_charm_down_sf ;
  Float_t btagSys_extrapolation_charm_down_ineff_sf ;
  Float_t btagSys_extrapolation_charm_up_sf ;
  Float_t btagSys_extrapolation_charm_up_ineff_sf ;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  btagEffSys();
  btagEffSys(const TString& expression);
  virtual ~btagEffSys();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(btagEffSys, 1);


};
#endif
