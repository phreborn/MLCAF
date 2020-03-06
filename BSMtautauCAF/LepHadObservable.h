//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __LEPHADOBSERVABLE__
#define __LEPHADOBSERVABLE__
#include "QFramework/TQTreeObservable.h"

#include "TTreeFormula.h"
#include "TMath.h"

class LepHadObservable : public TQTreeObservable {
  
  public:
    
    LepHadObservable();
    LepHadObservable(const TString& expression);
    ~LepHadObservable();
    
    virtual TObjArray* getBranchNames() const override;
    virtual bool hasExpression() const override;
    virtual const TString& getExpression() const override;
    virtual void setExpression(const TString& expr) override;

    bool isData() const;
    bool isMC() const;
  
    bool is2015() const;
    bool is2016() const;
    bool is2017() const;
    bool is2018() const;
    
    bool isSLT() const;
 
    bool isMuon() const;
    bool isElectron() const;
    bool isTauID() const;
    bool isLepISO() const;
  
    bool isHighPt() const;

  protected:
    
    virtual bool initializeSelf() override;
    virtual bool finalizeSelf() override;
    
    TString fExpression = "";

    // limit is the number of the last run of that year:
    const long LIMIT_2015 = 284484;
    const long LIMIT_2016 = 311563;
    const long LIMIT_2017 = 341649;
    const long LIMIT_2018 = 364292;

    bool _isData = false;
    bool _isMC = false;

    TTreeFormula* x_run_number = nullptr;
    TTreeFormula* mc_channel_number = nullptr;
    
    TTreeFormula* n_bjets = nullptr;
    TTreeFormula* n_electrons = nullptr;
    TTreeFormula* n_muons = nullptr;
    
    TTreeFormula* lep_0 = nullptr;
    TTreeFormula* lep_0_pt = nullptr;
    TTreeFormula* lep_0_eta = nullptr;
    TTreeFormula* lep_0_phi = nullptr;
    TTreeFormula* lep_0_iso_Gradient = nullptr;
    TTreeFormula* lep_0_iso_FCTightTrackOnly = nullptr;
    TTreeFormula* lep_0_iso_FCTight_FixedRad = nullptr;
    
    TTreeFormula* tau_0_n_charged_tracks = nullptr;
    TTreeFormula* tau_0_pt = nullptr;
    TTreeFormula* tau_0_eta = nullptr;
    TTreeFormula* tau_0_phi = nullptr;
    TTreeFormula* tau_0_jet_bdt_medium = nullptr;

    TTreeFormula* lephad_dphi = nullptr;
    
    TTreeFormula* met_reco_et = nullptr;
    TTreeFormula* met_reco_etx = nullptr;
    TTreeFormula* met_reco_ety = nullptr;
    TTreeFormula* met_reco_phi = nullptr;
    
    TTreeFormula* lephad_met_lep0_cos_dphi = nullptr;
    TTreeFormula* lephad_met_lep1_cos_dphi = nullptr;
    TTreeFormula* lephad_mt_lep0_met = nullptr;
    TTreeFormula* lephad_mt_lep1_met = nullptr;
};
#endif
