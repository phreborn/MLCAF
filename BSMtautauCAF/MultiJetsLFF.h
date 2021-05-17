//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __MultiJetsLFF__
#define __MultiJetsLFF__

#include "BSMtautauCAF/LepHadObservable.h"

class MultiJetsLFF : public LepHadObservable {

public:
  ClassDef(MultiJetsLFF, 1);

  MultiJetsLFF();
  MultiJetsLFF(const TString& expression);
  virtual ~MultiJetsLFF() = default;

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
