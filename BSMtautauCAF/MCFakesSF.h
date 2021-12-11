//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __MCFAKESSF__
#define __MCFAKESSF__

#include "BSMtautauCAF/LepHadObservable.h"

class MCFakesSF : public LepHadObservable {

public:
  ClassDef(MCFakesSF, 1);

  MCFakesSF();
  MCFakesSF(const TString& expression);
  virtual ~MCFakesSF() = default;

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
