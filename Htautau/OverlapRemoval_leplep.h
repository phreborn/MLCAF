//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __OverlapRemoval_leplep__
#define __OverlapRemoval_leplep__
#include "QFramework/TQTreeObservable.h"

#include "TLorentzVector.h"
#include "TTreeFormula.h"
#include <vector>
#include "Htautau/OverlapRemovalAlg_leplep.h"

class OverlapRemoval_leplep : public TQTreeObservable {
protected:
  // put here any data members your class might need

public:
  virtual double getValue() const override;
  virtual TObjArray* getBranchNames() const override;


protected:
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;
protected:

  OverlapRemovalAlg_leplep * ovl;
  long event_number;
  long run_number;
  bool debug;


  TString fExpression = "";

  TTreeFormula *m_event_number;
  TTreeFormula *m_run_number;

  bool jetIndexMode    = false;
  bool elIndexMode     = false;
  bool muIndexMode     = false;
  bool tauIndexMode    = false;
  bool leptonIndexMode = false;

  bool jetNMode    = false;
  bool elNMode     = false;
  bool muNMode     = false;
  bool tauNMode    = false;
  bool leptonNMode = false;

  int jetIndex    = -1;
  int elIndex     = -1;
  int muIndex     = -1;
  int tauIndex    = -1;
  int leptonIndex = -1;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  OverlapRemoval_leplep();
  OverlapRemoval_leplep(const TString& expression);
  virtual ~OverlapRemoval_leplep();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(OverlapRemoval_leplep, 1);


};
#endif
