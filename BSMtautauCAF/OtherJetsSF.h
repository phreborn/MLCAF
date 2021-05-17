//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __OtherJetsSF__
#define __OtherJetsSF__

#include "BSMtautauCAF/LepHadObservable.h"

class OtherJetsSF : public LepHadObservable {

public:
  ClassDef(OtherJetsSF, 1);
  
  OtherJetsSF();
  OtherJetsSF(const TString& expression);
  virtual ~OtherJetsSF() = default;
  
  virtual double getValue() const override;
  virtual TObjArray* getBranchNames() const override;

protected:
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;

  TString fExpression = "";
  TString fSysName = "";

  std::map<TString, TH1F*> m_SF_hist;
};

#endif
