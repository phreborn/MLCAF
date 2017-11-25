//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __HWWEVENTWEIGHT__
#define __HWWEVENTWEIGHT__
#include "CAFxAODUtils/TQEventObservable.h"

#ifndef __CINT__
#define XAOD_STANDALONE 1
// put here any EDM includes you might need, e.g.
#include "PileupReweighting/PileupReweightingTool.h"
#include "xAODParticleEvent/CompositeParticleContainer.h"
#include "AsgTools/ToolHandle.h"
#include "AthContainers/AuxElement.h"
//#include "NNLOReweighter/NNLOReweighter.h"
using namespace xAOD;
#else
// put here forward declares for the classes you might need, e.g.
// class CompositeParticle;
// class CompositeParticleContainer;
#endif

class HWWEventWeight : public TQEventObservable {
protected:
  // put here data members you wish to retrieve
  // be careful to declare them as follows:
  // mutable ClassName const * varname = 0
  // the "mutable" keyword ensures that this member can be changed also by const functions
  // the "const" keyword ensures that const containers can be retrieved
  // for example, use
public:
  virtual double getValue() const override;
  virtual bool initializeSelf() override;

  enum VariationType {
    NoVar,
    EleReco,
    EleID,
    EleIso,
    EleTrig,
    MuonReco,
    MuonID,
    MuonIso,
    MuonTTVA,
    MuonTrig,
    Btag,
		BtagTrackJet,
    PU,
    JVT,
    FJVT,
    TTbarNNLO,
    ggFQCDscale
//    ggFQCDscale12,
//    ggFQCDscalemu
  };
  enum BtagType {
		CaloJet,
		TrackJet
  };

  void setVariation(VariationType type, const TString& name);
  unsigned int m_RunNumber;

protected:
  TString fExpression = "";
  TString fExpressionInternal = "";
  // Pile-up re-weighting
  mutable ToolHandle<CP::IPileupReweightingTool> m_prwTool_mc15a; //!
  mutable ToolHandle<CP::IPileupReweightingTool> m_prwTool_mc15b; //!
  bool m_wasInitialized = false; //!
  std::string m_prwVarName = "PileupWeight";
  
  bool m_doMCWeight=false;
  bool m_doMCWeightOnly=false;
  bool m_useBtagWeight = false;
	bool m_useBtagTrackJetWeight = false;
  bool m_doPRW=false;
  bool m_usePRWTool=false;
  bool m_useLepWeight=false;
  bool m_useElectronIDWeight=false;
  bool m_useElectronIsoWeight=false;
  bool m_useElectronTrigWeight=false;
  bool m_useMuonIsoWeight=false;
  bool m_useMuonTTVAWeight=false;
  bool m_useMuonTrigWeight=false;
  bool m_useJVTWeight=false;
  bool m_useForwardJVTWeight=false;
  bool m_useMuonTrigEffWeight=false;
  bool m_useElectronTrigEffWeight=false;
  bool m_useTTbarNNLOWeight=false;
  bool m_useGGFScaleWeight=false;

  std::string m_eleSFName;
  std::string m_muonSFName;
  std::string m_muonSFNameLow;
  std::string m_bTagSFName;
  std::string m_bTagTrackJetSFName;
  std::string m_eleIDSFName;
  std::string m_eleIDSFNameLow;
  std::string m_eleIsoSFName;
  std::string m_eleIsoSFNameLow;
  std::string m_eleTrigSFName;
  std::string m_eleTrigSFNameLow;
  std::string m_eleTrigSFName_D4;
  std::string m_eleTrigSFNameLow_D4;
  std::string m_muonIsoSFName;
  std::string m_muonTTVASFName;
  std::string m_muonTrigSFName;
  std::string m_muonTrigSFNameLow;
  std::string m_muonTrigSFName_D4;
  std::string m_muonTrigSFNameLow_D4;
  std::string m_jetJVTSFName;
  std::string m_jetForwardJVTSFName;
  std::string m_muonTrigEffName;
  std::string m_muonTrigEffNameLow;
  std::string m_muonTrigEffName_D4;
  std::string m_muonTrigEffNameLow_D4;
  std::string m_eleTrigEffName;
  std::string m_eleTrigEffNameLow;
  std::string m_eleTrigEffName_D4;
  std::string m_eleTrigEffNameLow_D4;
  std::string m_ttbarNNLOSFName;
  
  bool m_isMuonEvent;
  bool m_isDFEvent;
  bool m_isVHEvent;
  bool m_isDiLeptonTrigger;
  int m_indexWeight;
  TString m_candName = "";
  bool m_overwriteEventName;
  mutable Long64_t fCachedEntry; //!
  mutable double fCachedValue; //!

  // Accessors for lepton efficiency weights
  SG::AuxElement::Accessor<float>* m_eleSFDecor=0;//!
  SG::AuxElement::Accessor<float>* m_muonSFDecor=0;//!
  SG::AuxElement::Accessor<float>* m_muonSFDecorLowPt=0;//!
  SG::AuxElement::Accessor<float>* m_eleIDSFDecor=0;//!
  SG::AuxElement::Accessor<float>* m_eleIDSFDecorLowPt=0;//!
  SG::AuxElement::Accessor<float>* m_eleIsoSFDecor=0;//!
  SG::AuxElement::Accessor<float>* m_eleIsoSFDecorLowPt=0;//!
  SG::AuxElement::Accessor<float>* m_muonIsoSFDecor=0;//!
  SG::AuxElement::Accessor<float>* m_muonTTVASFDecor=0;//!
  SG::AuxElement::Accessor<float>* m_eleTrigSFDecor=0;//!
  SG::AuxElement::Accessor<float>* m_eleTrigSFDecorLowPt=0;//!
  SG::AuxElement::Accessor<float>* m_muonTrigSFDecor=0;//!
  SG::AuxElement::Accessor<float>* m_muonTrigSFDecorLowPt=0;//!
  SG::AuxElement::Accessor<float>* m_ttbarNNLOSFDecor=0;//!

  SG::AuxElement::Accessor<char>* m_TrigMatchDecorELE1=0;//!
  SG::AuxElement::Accessor<char>* m_TrigMatchDecorELE2=0;//!
  SG::AuxElement::Accessor<char>* m_TrigMatchDecorELE3=0;//!
  SG::AuxElement::Accessor<char>* m_TrigMatchDecorMUON1=0;//!
  SG::AuxElement::Accessor<char>* m_TrigMatchDecorMUON2=0;//!

  SG::AuxElement::Accessor<float>* m_muonTrigEffDecor=0;//!
  SG::AuxElement::Accessor<float>* m_muonTrigEffDecorLowPt=0;//!
  SG::AuxElement::Accessor<float>* m_eleTrigEffDecor=0;//!
  SG::AuxElement::Accessor<float>* m_eleTrigEffDecorLowPt=0;//!

  // Accessors for jet efficiency weights
  SG::AuxElement::Accessor<float>* m_btagSFDecor=0;//!
	SG::AuxElement::Accessor<float>* m_btagTrackJetSFDecor=0;//!
  SG::AuxElement::Accessor<float>* m_jetJVTSFDecor=0;//!
  SG::AuxElement::Accessor<float>* m_jetForwardJVTSFDecor=0;//!

  // Methods to properly retrieve the respective weights
  double getLeptonWeight(const xAOD::IParticle* p) const ;
  double getElectronIDWeight(const xAOD::IParticle* p) const ;
  double getElectronIsoWeight(const xAOD::IParticle* p) const ;
  double getElectronTrigWeight(const xAOD::IParticle* p) const ;
  double getMuonIsoWeight(const xAOD::IParticle* p) const ;
  double getMuonTTVAWeight(const xAOD::IParticle* p) const ;
  double getMuonTrigWeight(const xAOD::CompositeParticle* compPart) const ;
  double getBtagWeight(const xAOD::IParticle* p) const ;
  double getJVTWeight(const xAOD::IParticle* p) const ;
  double getForwardJVTWeight(const xAOD::IParticle* p) const ;
  double getBtagTrackJetWeight() const ;
  double getTTbarNNLOWeight(const xAOD::EventInfo* e) const ;

  int    getRunNumber(const xAOD::EventInfo *evtInfo) const;
  double getTriggerSF_DF_singLep(const xAOD::CompositeParticle* compPart) const;
  double getTriggerSF_VH_singLep(const xAOD::CompositeParticle* compPart) const;
  double getTriggerSF_singLep(const xAOD::CompositeParticle* compPart) const;

  VariationType m_variationType = NoVar;
  TString m_variationName = "Nominal";
  bool m_useOtherJets;
  
  std::string m_confFileMC15a;
  std::string m_confFileMC15b;
  std::string m_lCalcFile;
  double m_dataScaleFactor;

  void preparePRW();
  void prepareLepWeight();
  void prepareElectronIDWeight();
  void prepareElectronIsoWeight();
  void prepareElectronTrigWeight();
  void prepareMuonIsoWeight();
  void prepareMuonTTVAWeight();
  void prepareMuonTrigWeight();
  void prepareBtagWeight();
  void prepareJVTWeight();
  void prepareForwardJVTWeight();
  void prepareMuonTrigEffWeight();
  void prepareElectronTrigEffWeight();
  void prepareTTbarNNLOWeight();
  
public:

  // Methods to configure the observable from outside
  void doMCWeight(bool doMCWeight);
  void doMCWeightOnly(bool doMCWeightOnly);
  void doPRWWeight(const std::string& confFileMC15a, const std::string& confFileMC15b, const std::string& lCalcFile, const double& dataScaleFactor = 1.0);
  void doPRWWeight(std::string prwVarName = "PileupWeight");
  void doLepWeight(const std::string& eleSFName = "effiSFRecoTrk", const std::string& muonSFName = "effiSFMedium", const std::string& muonSFNameLow = "effiSFTight");
  void doElectronIDWeight(const std::string& eleIDSFName = "effiSFMediumLH", const std::string& eleIDSFNameLow = "effiSFTightLH");
  void doElectronIsoWeight(const std::string& eleIsoSFName = "effiSFIsoGradient_wrtMediumLH", const std::string& eleIsoSFNameLow = "effiSFIsoGradient_wrtTightLH");
  void doElectronTrigWeight(const std::string& eleTrigSFName = "effiSFTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_MediumLHIsoGradient", const std::string& eleTrigSFNameLow = "effiSFTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_TightLHIsoGradient");
  void doMuonIsoWeight(const std::string& muonIsoSFName = "effiSFIsoGradient");
  void doMuonTTVAWeight(const std::string& muonTTVASFName = "effiSFTTVA");
  void doMuonTrigWeight(const std::string& muonTrigSFName = "effiSFTrig_wrtMedium_HLT_mu20_iloose_L1MU15_OR_HLT_mu50", const std::string& muonTrigSFNameLow = "effiSFTrig_wrtTight_HLT_mu20_iloose_L1MU15_OR_HLT_mu50");
  void doBtagWeight(const bool& useOtherJets=true, const std::string& btagSFName = "effiSF",
										BtagType type = CaloJet);
  void doJVTWeight(const std::string& jetJVTSFName = "effiSFJVT");
  void doForwardJVTWeight(const std::string& jetJVTSFName = "effiSFForwardJVT");
  void doAllWeights(const std::string& confFileMC15a, const std::string& confFileMC15b, const std::string& lCalcFile, const double& dataScaleFactor = 1.0);
  void doMuonTrigEffWeight(const std::string& muonTrigEffName = "effiTrig_wrtMedium_HLT_mu20_iloose_L1MU15_OR_HLT_mu50",
                           const std::string& muonTrigEffNameLow = "effiTrig_wrtTight_HLT_mu20_iloose_L1MU15_OR_HLT_mu50",
                           const std::string& muonTrigSFName = "effiSFTrig_wrtMedium_HLT_mu20_iloose_L1MU15_OR_HLT_mu50",
                           const std::string& muonTrigSFNameLow = "effiSFTrig_wrtTight_HLT_mu20_iloose_L1MU15_OR_HLT_mu50",
			   const std::string& muonTrigEffName_D4 = "effiTrig_wrtMedium_HLT_mu20_iloose_L1MU15_OR_HLT_mu50",
                           const std::string& muonTrigEffNameLow_D4 = "effiTrig_wrtTight_HLT_mu20_iloose_L1MU15_OR_HLT_mu50",
                           const std::string& muonTrigSFName_D4 = "effiSFTrig_wrtMedium_HLT_mu20_iloose_L1MU15_OR_HLT_mu50",
                           const std::string& muonTrigSFNameLow_D4 = "effiSFTrig_wrtTight_HLT_mu20_iloose_L1MU15_OR_HLT_mu50");
  /*  void doElectronTrigEffWeight(const std::string& eleTrigEffName = "effiTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_MediumLHIsoGradient",
                               const std::string& eleTrigEffNameLow = "effiTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_TightLHIsoGradient",
                               const std::string& eleTrigSFName = "effiSFTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_MediumLHIsoGradient",
                               const std::string& eleTrigSFNameLow = "effiSFTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_TightLHIsoGradient");
  */
  void doElectronTrigEffWeight(const std::string& eleTrigEffName = "effiTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_MediumLHIsoGradient",
                               const std::string& eleTrigEffNameLow = "effiTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_TightLHIsoGradient",
                               const std::string& eleTrigSFName = "effiSFTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_MediumLHIsoGradient",
                               const std::string& eleTrigSFNameLow = "effiSFTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_TightLHIsoGradient",
			       const std::string& eleTrigEffName_D4 = "effiTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_MediumLHIsoGradient",
                               const std::string& eleTrigEffNameLow_D4 = "effiTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_TightLHIsoGradient",
                               const std::string& eleTrigSFName_D4 = "effiSFTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_MediumLHIsoGradient",
                               const std::string& eleTrigSFNameLow_D4 = "effiSFTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_TightLHIsoGradient");

  void doTTbarNNLOWeight(const std::string& ttbarNNLOSFName = "ttbarNNLORW");
  void useDiLeptonTrigger(bool useIt) { m_isDiLeptonTrigger=useIt; };

  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expression) override;

  HWWEventWeight();
  HWWEventWeight(const TString& expression);
  virtual ~HWWEventWeight();
  
  ClassDefOverride(HWWEventWeight,1);
};

#endif
