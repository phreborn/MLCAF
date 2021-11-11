//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __MCFAKESSYS__
#define __MCFAKESSYS__

#include "BSMtautauCAF/LepHadObservable.h"

class MCFakesSYS : public LepHadObservable {

public:
  ClassDef(MCFakesSYS, 1);

  MCFakesSYS();
  MCFakesSYS(const TString& expression);
  virtual ~MCFakesSYS() = default;

  virtual TObjArray* getBranchNames() const override;
  virtual double getValue() const override;

protected:
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;

  const TH1F* getFakeFactorHist() const;

  TString fExpression = "";
  TString fSysName = "";

  std::map<TString, TH1F*> m_FF_hist;
};

#endif
