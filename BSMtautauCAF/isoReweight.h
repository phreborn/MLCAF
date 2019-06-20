//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __ISOREWEIGHT__
#define __ISOREWEIGHT__

#include "BSMtautauCAF/LepHadObservable.h"

class isoReweight : public LepHadObservable {
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

  const long LIMIT_2016 = 311563;
  const long LIMIT_2017 = 341649;
  const long LIMIT_2018 = 364292;

  std::map<TString, TH1F*> m_FF_hist;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  isoReweight();
  isoReweight(const TString& expression);
  virtual ~isoReweight();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(isoReweight, 1);


};
#endif
