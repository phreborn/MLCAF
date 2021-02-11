//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __MCOtherJetsTFF__
#define __MCOtherJetsTFF__

#include "BSMtautauCAF/LepHadObservable.h"

class MCOtherJetsTFF : public LepHadObservable {

public:
  ClassDef(MCOtherJetsTFF, 1);

  MCOtherJetsTFF();
  MCOtherJetsTFF(const TString& expression);
  virtual ~MCOtherJetsTFF() = default;

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
