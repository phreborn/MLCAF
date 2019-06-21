//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __QCDREWEIGHT__
#define __QCDREWEIGHT__

#include "BSMtautauCAF/LepHadObservable.h"

class QCDReweight : public LepHadObservable {
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

  std::map<TString, TH1F*> m_SF_hist;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  QCDReweight();
  QCDReweight(const TString& expression);
  virtual ~QCDReweight();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(QCDReweight, 1);


};
#endif
