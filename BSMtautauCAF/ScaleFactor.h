//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __SCALEFACTORAUTO__
#define __SCALEFACTORAUTO__
#include "BSMtautauCAF/LepHadObservable.h"

#include <tuple>
#include <bitset>
#include <vector>
#include "TTreeFormula.h"
#include "TH2.h"


typedef std::bitset<256> Condition;

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
  
    TString fExpression = "";

    std::vector< std::pair<TString, Condition> > variations;
    Condition variation;

    std::vector< std::tuple<Condition, Condition, TString, TTreeFormula*> > branches;

    virtual void addScaleFactor(Condition requirement, TString branch);
    virtual void addScaleFactor(Condition requirement, Condition veto, TString branch);

    const Condition none  = 0;
    const Condition y2015 = 1<<0;
    const Condition y2016 = 1<<1;
    const Condition y2017 = 1<<2;
    const Condition y2018 = 1<<3;
    const Condition slt   = 1<<4;
    const Condition tauid = 1<<5;
    const Condition lepiso = 1<<6;
    const Condition muon  = 1<<7;
    const Condition electron  = 1<<8;
    const Condition sherpa    = 1<<9;
    const Condition highpt    = 1<<10;
    const Condition highpt2    = 1<<11;
    const Condition isZ       = 1<<12;

    const Condition nominal = 1<<13;

    virtual Condition registerVariation(TString name);
    unsigned int nextBitPosition = 14;

    // This variable contains all flags, which do not change until
    // initializeSelf is called again. It can therefore be used to determine
    // which branches need to be registered.
    Condition staticConditionsMask;
};
#endif
