//this file looks like plain C, but it's actually -*- c++ -*-
// added by Ulrike <ulrike.schnoor@cern.ch>
#ifndef __MJJLEPLEP__
#define __MJJLEPLEP__
#include "QFramework/TQTreeObservable.h"

#include "TLorentzVector.h"
#include "TTreeFormula.h"

class Mjjleplep : public TQTreeObservable {
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

  TTreeFormula* jet_0_pt = NULL;
  TTreeFormula* jet_0_eta = NULL;
  TTreeFormula* jet_0_phi = NULL;
  TTreeFormula* jet_0_m = NULL;

  TTreeFormula* jet_1_pt = NULL;
  TTreeFormula* jet_1_eta = NULL;
  TTreeFormula* jet_1_phi = NULL;
  TTreeFormula* jet_1_m = NULL;

  TLorentzVector* jet0 = NULL;
  TLorentzVector* jet1 = NULL;


public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  Mjjleplep();
  Mjjleplep(const TString& expression);
  virtual ~Mjjleplep();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(Mjjleplep, 1);


};
#endif
