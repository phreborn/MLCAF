//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __LPXKFACTOR__
#define __LPXKFACTOR__

#include "BSMtautauCAF/LepHadObservable.h"
#include "TGraphAsymmErrors.h"

class LPXKfactor : public LepHadObservable {
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

  TTreeFormula* mc_channel_number = NULL;

  std::map<int, int> m_DSID_bin;

  std::map<TString, TGraphAsymmErrors*> m_SF_graph;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  LPXKfactor();
  LPXKfactor(const TString& expression);
  virtual ~LPXKfactor();
public:


  ClassDef(LPXKfactor, 1);


};
#endif
