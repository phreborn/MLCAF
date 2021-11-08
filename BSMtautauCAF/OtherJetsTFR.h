//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __OtherJetsTFR__
#define __OtherJetsTFR__

#include "BSMtautauCAF/LepHadObservable.h"

class OtherJetsTFR : public LepHadObservable {

public:
  ClassDef(OtherJetsTFR, 1);

  OtherJetsTFR();
  OtherJetsTFR(const TString& expression);
  virtual ~OtherJetsTFR() = default;

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
