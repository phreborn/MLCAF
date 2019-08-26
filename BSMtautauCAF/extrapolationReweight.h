//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __EXTRAPOLATIONREWEIGHT__
#define __EXTRAPOLATIONREWEIGHT__

#include "BSMtautauCAF/LepHadObservable.h"

class extrapolationReweight : public LepHadObservable {
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

  extrapolationReweight();
  extrapolationReweight(const TString& expression);
  virtual ~extrapolationReweight();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(extrapolationReweight, 1);


};
#endif
