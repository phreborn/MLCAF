//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __TOPREWEIGHT__
#define __TOPREWEIGHT__

#include "BSMtautauCAF/LepHadObservable.h"

class TopReweight : public LepHadObservable {
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

  TopReweight();
  TopReweight(const TString& expression);
  virtual ~TopReweight();
public:


  ClassDef(TopReweight, 1);


};
#endif
