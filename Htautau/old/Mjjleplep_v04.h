//this file looks like plain C, but it's actually -*- c++ -*-
// added by Ulrike <ulrike.schnoor@cern.ch>
#ifndef __Mjjleplep_v04__
#define __Mjjleplep_v04__
#include "QFramework/TQTreeObservable.h"
#include "Htautau2015/OverlapRemovalAlg_leplep.h"

#include "TLorentzVector.h"
#include "TTreeFormula.h"

class Mjjleplep_v04 : public TQTreeObservable {
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

  TTreeFormula* jets_pt = NULL;
  TTreeFormula* jets_eta = NULL;
  TTreeFormula* jets_phi = NULL;
  TTreeFormula* jets_m = NULL;

  TLorentzVector* jet0 = NULL;
  TLorentzVector* jet1 = NULL;

  OverlapRemovalAlg_leplep * OVR;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  Mjjleplep_v04();
  Mjjleplep_v04(const TString& expression);
  virtual ~Mjjleplep_v04();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(Mjjleplep_v04, 1);


};
#endif
