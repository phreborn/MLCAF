//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __TAUREWEIGHT__
#define __TAUREWEIGHT__

#include "BSMtautauCAF/LepHadObservable.h"
#include "TGraphAsymmErrors.h"

class TauReweight : public LepHadObservable {
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

  std::map<TString, TF1*> m_SF_fun;
  std::map<TString, TGraphAsymmErrors*> m_SF_graph;

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  TauReweight();
  TauReweight(const TString& expression);
  virtual ~TauReweight();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  ClassDef(TauReweight, 1);


};
#endif
