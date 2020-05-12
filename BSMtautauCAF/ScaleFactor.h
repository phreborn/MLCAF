//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __SCALEFACTORAUTO__
#define __SCALEFACTORAUTO__
#include "BSMtautauCAF/LepHadObservable.h"

#include <tuple>
#include <bitset>
#include <vector>
#include "TTreeFormula.h"
#include "TH2.h"


typedef std::bitset<128> Condition;

class ScaleFactor : public LepHadObservable {

  public:
    ClassDef(ScaleFactor, 1);
    
    ScaleFactor();
    ScaleFactor(const TString& expression);
    ~ScaleFactor();
  
    virtual double getValue() const override;
    virtual TObjArray* getBranchNames() const override;

  
  protected:
    virtual bool initializeSelf() override;
    virtual bool finalizeSelf() override;
 
    TString getTauIDWPName(const TString&) const;

    TString fSysName = "";

    std::vector< std::pair<TString, Condition> > variations;
    Condition variation;

    std::vector< std::tuple<Condition, Condition, TString, TTreeFormula*> > branches;

    virtual void addScaleFactor(Condition requirement, TString branch);
    virtual void addScaleFactor(Condition requirement, Condition veto, TString branch);

    const Condition none  = 0;
    
    const Condition y2015 =     1<<0;
    const Condition muon  =     1<<1;
    const Condition electron =  1<<2;
    const Condition highpt  =   1<<3;
    const Condition tauid =     1<<4;
    const Condition lepiso =    1<<5;
    const Condition nominal =   1<<6;

    virtual Condition registerVariation(TString name);
    // position to register new variations
    unsigned int nextBitPosition =7;

    // stores bit of all the variations (including nominal)
    Condition staticConditionsMask;
};
#endif
