//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __ZjetsSF__
#define __ZjetsSF__

#include "BSMtautauCAF/LepHadObservable.h"

class ZjetsSF : public LepHadObservable {

public:
  ClassDef(ZjetsSF, 1);

  ZjetsSF();
  ZjetsSF(const TString& expression);
  virtual ~ZjetsSF() = default;

  virtual TObjArray* getBranchNames() const override;
  virtual double getValue() const override;

protected:
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;

  auto getFakeFactorHist() const;

  TString fExpression = "";
  TString fSysName = "";

  std::map<TString, TH1F*> m_FF_hist;
};

#endif
