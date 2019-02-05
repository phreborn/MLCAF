//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __NSelecLep_ll_v05__
#define __NSelecLep_ll_v05__
#include "QFramework/TQTreeObservable.h"
#include "Htautau2015/EventSelection_leplep_default.h"
#include "Htautau2015/EventSelection_leplep_fake.h"

#include "TTreeFormula.h"

class NSelecLep_ll_v05 : public TQTreeObservable {
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

  TTreeFormula* leptons = NULL;
  EventSelection_leplep_default * EVS;
  EventSelection_leplep_fake * EVS_fake;

  bool isEE = false;
  bool isMM = false;
  bool isEM = false;
  bool isME = false;

  bool useFakeSelec = false;


public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  NSelecLep_ll_v05();
  NSelecLep_ll_v05(const TString& expression, const TString& channel);
  virtual ~NSelecLep_ll_v05();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(NSelecLep_ll_v05, 1);


};
#endif
