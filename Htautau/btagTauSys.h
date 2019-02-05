//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __btagTauSys__
#define __btagTauSys__
#include "QFramework/TQTreeObservable.h"

#include "TTreeFormula.h"

class btagTauSys : public TQTreeObservable {
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

  //TTreeFormula* btagCharmSyscharm_1down_sf       = NULL;
  //TTreeFormula* btagCharmSyscharm_1down_ineff_sf = NULL;
  //TTreeFormula* btagCharmSyscharm_1up_sf         = NULL;
  //TTreeFormula* btagCharmSyscharm_1up_ineff_sf   = NULL;
  
  Float_t charmExSys_down_sf;      
  Float_t charmExSys_down_ineff_sf;
  Float_t charmExSys_up_sf;        
  Float_t charmExSys_up_ineff_sf;  

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  btagTauSys();
  btagTauSys(const TString& expression);
  virtual ~btagTauSys();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(btagTauSys, 1);


};
#endif
