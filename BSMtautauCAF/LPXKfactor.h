//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __LPXKFACTORNEW__
#define __LPXKFACTORNEW__

#include "BSMtautauCAF/LepHadObservable.h"
#include "TGraphAsymmErrors.h"

#include <tuple>
#include <bitset>
#include <vector>
#include "TTreeFormula.h"
#include "TH2.h"

class LPXKfactor : public LepHadObservable {

  public:
    ClassDef(LPXKfactor, 1);

    LPXKfactor();
    LPXKfactor(const TString& expression);
    ~LPXKfactor();

    virtual double getValue() const override;
    virtual TObjArray* getBranchNames() const override;

  protected:
    virtual bool initializeSelf() override;
    virtual bool finalizeSelf() override;
    
    void addScaleFactor(Condition requirement, TString branch);
    void addScaleFactor(Condition requirement, Condition veto, TString branch);
    Condition registerVariation(TString name);
    
    TString fExpression = "";
    TString fSysName = "";

    std::vector< std::pair<TString, Condition> > m_variations;
    std::vector< std::tuple<Condition, Condition, TString, TTreeFormula*> > m_branches;
    Condition m_variation;
    
    const Condition none  = 0;
    const Condition nominal = 1<<0;
    unsigned int m_nextBitPosition = 1; // position to register new variations
    Condition m_staticConditionsMask; // bit including all the variations
    
};
#endif
