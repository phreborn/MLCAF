//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __PTREWEIGHT__
#define __PTREWEIGHT__

#include "BSMtautauCAF/LepHadObservable.h"

class ptReweight : public LepHadObservable {
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
  TDirectory* m_histoDir = 0;

  std::map<TString, TH1F*> m_FF_hist;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  ptReweight();
  ptReweight(const TString& expression);
  virtual ~ptReweight();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(ptReweight, 1);


};
#endif
