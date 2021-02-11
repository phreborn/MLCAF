//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __TopSF__
#define __TopSF__

#include "BSMtautauCAF/LepHadObservable.h"

class TopSF : public LepHadObservable {

public:
  ClassDef(TopSF, 1);

  TopSF();
  TopSF(const TString& expression);
  virtual ~TopSF() = default;

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
