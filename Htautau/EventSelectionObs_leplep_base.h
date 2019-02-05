//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __EventSelectionObs_leplep_base__
#define __EventSelectionObs_leplep_base__
#include "QFramework/TQTreeObservable.h"

#include "TLorentzVector.h"
#include "TTreeFormula.h"
#include <vector>
#include "Htautau/EventSelection_leplep_base.h"

template < class selection >
class EventSelectionObs_leplep_base : public TQTreeObservable {
protected:
  // put here any data members your class might need

public:
  virtual double getValue() const override;
  virtual TObjArray* getBranchNames() const override;


protected:
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;
protected:

  selection * ovl;
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

  bool leptonSelectMode = false;
  bool leptonSelectMode_Lep0Tight = false;
  bool leptonSelectMode_Lep1Tight = false;
  bool leptonPt0Mode = false;
  bool leptonPt1Mode = false;
  bool leptonEta0Mode = false;
  bool leptonEta1Mode = false;

  bool lep0MatchMode=false;
  bool lep1MatchMode=false;

  bool lep0jetdRMode=false;
  bool lep1jetdRMode=false;

  int jetIndex    = -1;
  int elIndex     = -1;
  int muIndex     = -1;
  int tauIndex    = -1;
  int leptonIndex = -1;

  bool triggerWeightMode=false;
  bool leptonWeightMode=false;
  bool isTriggeredMCMode=false;
  bool isTriggeredDataMode=false;
  bool isTriggerTypeMode=false;

  bool SpecialtriggerWeightMode=false;
  bool isSpecialTriggeredMCMode=false;
  bool isSpecialTriggeredDataMode=false;
  bool isSpecialTriggerTypeMode=false;

  bool leptonMVisMode=false;
  bool leptonMtMode=false;
  bool leptonMMCmaxwMode=false;
  bool leptonMMCmlmMode=false;
  bool leptonMMCmlnu3pMode=false;
  bool leptonSumPtMode=false;
  bool leptonDphiLLMode=false;
  bool leptonDphiL0METMode=false;
  bool leptonDphiL1METMode=false;
  bool leptonDEtaLLmode=false;
  bool leptonMLLmode=false;
  bool leptonMCollASymMode=false;
  bool leptonSignMode=false;
  bool leptonXCollAppMode=false;

  bool jetPt0Mode=false;
  bool jetJVTWeightMode=false;
  bool jetMVXWeightMode=false;
  bool jetBtagMode=false;

  bool metHptoMode=false;

  bool runnumberMode=false;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  EventSelectionObs_leplep_base();
  EventSelectionObs_leplep_base(const TString& expression);
  virtual ~EventSelectionObs_leplep_base();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;


};
#endif
