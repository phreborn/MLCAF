//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __OtherJetsTFF__
#define __OtherJetsTFF__

#include "BSMtautauCAF/LepHadObservable.h"

class OtherJetsTFF : public LepHadObservable {

public:
  ClassDef(OtherJetsTFF, 1);

  OtherJetsTFF();
  OtherJetsTFF(const TString& expression);
  virtual ~OtherJetsTFF() = default;

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
