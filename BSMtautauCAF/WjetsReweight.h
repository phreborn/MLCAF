//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __WjetsREWEIGHT__
#define __WjetsREWEIGHT__

#include "BSMtautauCAF/LepHadObservable.h"

class WjetsReweight : public LepHadObservable {
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

  std::map<TString, TH1F*> m_SF_hist;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  WjetsReweight();
  WjetsReweight(const TString& expression);
  virtual ~WjetsReweight();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(WjetsReweight, 1);


};
#endif
