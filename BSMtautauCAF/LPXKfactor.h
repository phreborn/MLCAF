//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __LPXKFACTOR__
#define __LPXKFACTOR__

#include "BSMtautauCAF/LepHadObservable.h"
#include "TGraphAsymmErrors.h"

class LPXKfactor : public LepHadObservable {

  public:
    ClassDef(LPXKfactor, 1);

    LPXKfactor();
    LPXKfactor(const TString& expression);
    ~LPXKfactor();

    virtual bool hasExpression() const override;
    virtual const TString& getExpression() const override;
    virtual void setExpression(const TString& expr) override;
    virtual double getValue() const override;
    virtual TObjArray* getBranchNames() const override;

  protected:
    virtual bool initializeSelf() override;
    virtual bool finalizeSelf() override;
    TString fExpression = "";
    TString fSysName = "";
    TDirectory* m_histoDir = 0;

    std::map<int, int> m_DSID_bin;
    std::map<TString, TGraphAsymmErrors*> m_SF_graph;

};
#endif
