from ROOT import *
from QFramework import *
import EventSelectionObs_leplep_common

def addObservables():
    #selection=EventSelectionObs_leplep_fake
    #if "fakes" in str(config.getTagStringDefault("restrictedPath","")):
    #    INFO("running over fakes, using fakes EventSelection")
    #    selection=EventSelectionObs_leplep_fake
    #observables=EventSelectionObs_leplep_common.generateCommonObservables();
    #for obs in observables:
    #  thisobs=selection(obs)
    #  if not TQTreeObservable.addObservable(thisobs):
    #    INFO("failed to add "+obs+" observable")
    #    return False
    #return True

    for nEl in  xrange(4):
      ElIdx=EventSelectionObs_leplep_fake("ElIdx_"+str(nEl)+"_fake")
      if not TQTreeObservable.addObservable(ElIdx):
        INFO("failed to add ElIdx_"+str(nEl)+" observable")
        return False
    for nMu in  xrange(4):
      MuIdx=EventSelectionObs_leplep_fake("MuIdx_"+str(nMu)+"_fake")
      if not TQTreeObservable.addObservable(MuIdx):
        INFO("failed to add MuIdx_"+str(nMu)+" observable")
        return False
    for nJet in  xrange(5):
      JetIdx=EventSelectionObs_leplep_fake("JetIdx_"+str(nJet)+"_fake")
      if not TQTreeObservable.addObservable(JetIdx):
        INFO("failed to add JetIdx_"+str(nJet)+" observable")
        return False
    for nLepton in  xrange(8):
      LeptonIdx=EventSelectionObs_leplep_fake("LeptonIdx_"+str(nLepton)+"_fake")
      if not TQTreeObservable.addObservable(LeptonIdx):
        INFO("failed to add LeptonIdx_"+str(nLepton)+" observable")
        return False
    for nTau in  xrange(8):
      TauIdx=EventSelectionObs_leplep_fake("TauIdx_"+str(nTau)+"_fake")
      if not TQTreeObservable.addObservable(TauIdx):
        INFO("failed to add TauIdx_"+str(nTau)+" observable")
        return False
    ElN=EventSelectionObs_leplep_fake("ElN"+"_fake")
    if not TQTreeObservable.addObservable(ElN):
      INFO("failed to add ElN observable")
      return False
    MuN=EventSelectionObs_leplep_fake("MuN"+"_fake")
    if not TQTreeObservable.addObservable(MuN):
      INFO("failed to add MuN observable")
      return False
    JetN=EventSelectionObs_leplep_fake("JetN"+"_fake")
    if not TQTreeObservable.addObservable(JetN):
      INFO("failed to add JetN observable")
      return False
    LeptonN=EventSelectionObs_leplep_fake("LeptonN"+"_fake")
    if not TQTreeObservable.addObservable(LeptonN):
      INFO("failed to add LeptonN observable")
      return False
    Lep0Pt=EventSelectionObs_leplep_fake("Lep0Pt"+"_fake")
    if not TQTreeObservable.addObservable(Lep0Pt):
      INFO("failed to add Lep0Pt observable")
      return False
    Lep1Pt=EventSelectionObs_leplep_fake("Lep1Pt"+"_fake")
    if not TQTreeObservable.addObservable(Lep1Pt):
      INFO("failed to add Lep1Pt observable")
      return False
    Lep0Eta=EventSelectionObs_leplep_fake("Lep0Eta"+"_fake")
    if not TQTreeObservable.addObservable(Lep0Eta):
      INFO("failed to add Lep0Eta observable")
      return False
    Lep1Eta=EventSelectionObs_leplep_fake("Lep1Eta"+"_fake")
    if not TQTreeObservable.addObservable(Lep1Eta):
      INFO("failed to add Lep1Eta observable")
      return False
    TauN=EventSelectionObs_leplep_fake("TauN"+"_fake")
    if not TQTreeObservable.addObservable(TauN):
      INFO("failed to add TauN observable")
      return False
    TriggerWeight=EventSelectionObs_leplep_fake("TriggerWeight"+"_fake")
    if not TQTreeObservable.addObservable(TriggerWeight):
      INFO("failed to add TriggerWeight observable")
      return False
    LeptonWeight=EventSelectionObs_leplep_fake("LeptonWeight"+"_fake")
    if not TQTreeObservable.addObservable(LeptonWeight):
      INFO("failed to add LeptonWeight observable")
      return False
    TriggeredMC=EventSelectionObs_leplep_fake("TriggeredMC"+"_fake")
    if not TQTreeObservable.addObservable(TriggeredMC):
      INFO("failed to add TriggeredMC observable")
      return False
    TriggeredData=EventSelectionObs_leplep_fake("TriggeredData"+"_fake")
    if not TQTreeObservable.addObservable(TriggeredData):
      INFO("failed to add TriggeredData observable")
      return False
    TriggerType_new=EventSelectionObs_leplep_fake("TriggerType_new"+"_fake")
    if not TQTreeObservable.addObservable(TriggerType_new):
      INFO("failed to add TriggerType_new observable")
      return False
    #specialTriggerWeight=EventSelectionObs_leplep_fake("specialTriggerWeight"+"_fake")
    #if not TQTreeObservable.addObservable(specialTriggerWeight):
    #  INFO("failed to add specialTriggerWeight observable")
    #  return False
    #specialTriggeredMC=EventSelectionObs_leplep_fake("specialTriggeredMC"+"_fake")
    #if not TQTreeObservable.addObservable(specialTriggeredMC):
    #  INFO("failed to add specialTriggeredMC observable")
    #  return False
    #specialTriggeredData=EventSelectionObs_leplep_fake("specialTriggeredData"+"_fake")
    #if not TQTreeObservable.addObservable(specialTriggeredData):
    #  INFO("failed to add specialTriggeredData observable")
    #  return False
    #specialTriggerType_new=EventSelectionObs_leplep_fake("specialTriggerType_new"+"_fake")
    #if not TQTreeObservable.addObservable(specialTriggerType_new):
    #  INFO("failed to add specialTriggerType_new observable")
    #  return False
    MVis_new=EventSelectionObs_leplep_fake("MVis_new"+"_fake")
    if not TQTreeObservable.addObservable(MVis_new):
      INFO("failed to add MVis_new observable")
      return False
    Mt_new=EventSelectionObs_leplep_fake("Mt_new"+"_fake")
    if not TQTreeObservable.addObservable(Mt_new):
      INFO("failed to add Mt_new observable")
      return False
    SumPtLep_new=EventSelectionObs_leplep_fake("SumPtLep_new"+"_fake")
    if not TQTreeObservable.addObservable(SumPtLep_new):
      INFO("failed to add SumPtLep_new observable")
      return False
    DphiLL_new=EventSelectionObs_leplep_fake("DphiLL_new"+"_fake")
    if not TQTreeObservable.addObservable(DphiLL_new):
      INFO("failed to add DphiLL_new observable")
      return False
    #DphiL0MET=EventSelectionObs_leplep_fake("DphiL0MET"+"_fake")
    #if not TQTreeObservable.addObservable(DphiL0MET):
    #  INFO("failed to add DphiL0MET observable")
    #  return False
    #DphiL1=EventSelectionObs_leplep_fake("DphiL1MET"+"_fake")
    #if not TQTreeObservable.addObservable(DphiL1MET):
    #  INFO("failed to add DphiL1MET observable")
    #  return False
    #DEtaLL=EventSelectionObs_leplep_default("DEtaLL"+"_fake")
    #if not TQTreeObservable.addObservable(DEtaLL):
    #    INFO("failed to add DEtaLL observable")
    #    return False
    #MLL=EventSelectionObs_leplep_default("MLL"+"_fake")
    #if not TQTreeObservable.addObservable(MLL):
    #    INFO("failed to add MLL observable")
    #    return False    
    LepLepSign=EventSelectionObs_leplep_fake("LepLepSign"+"_fake")
    if not TQTreeObservable.addObservable(LepLepSign):
      INFO("failed to add LepLepSign observable")
      return False
    LepXCollApp=EventSelectionObs_leplep_fake("LepXCollApp"+"_fake")
    if not TQTreeObservable.addObservable(LepXCollApp):
      INFO("failed to add LepXCollApp observable")
      return False
    LepMColl=EventSelectionObs_leplep_fake("LepMColl"+"_fake")
    if not TQTreeObservable.addObservable(LepMColl):
      INFO("failed to add LepMColl observable")
      return False
    Jet0Pt=EventSelectionObs_leplep_fake("Jet0Pt"+"_fake")
    if not TQTreeObservable.addObservable(Jet0Pt):
      INFO("failed to add Jet0Pt_new observable")
      return False
    JVTWeight=EventSelectionObs_leplep_fake("JVTWeight"+"_fake")
    if not TQTreeObservable.addObservable(JVTWeight):
      INFO("failed to add JVTWeight observable")
      return False
    MVXWeight=EventSelectionObs_leplep_fake("MVXWeight"+"_fake")
    if not TQTreeObservable.addObservable(MVXWeight):
      INFO("failed to add MVXWeight observable")
      return False
    Btag=EventSelectionObs_leplep_fake("Btag"+"_fake")
    if not TQTreeObservable.addObservable(Btag):
      INFO("failed to add bTag observable")
      return False
    SelectLep=EventSelectionObs_leplep_fake("SelectLep"+"_fake")
    if not TQTreeObservable.addObservable(SelectLep):
      INFO("failed to add SelectLep observable")
      return False
    MetHPTO=EventSelectionObs_leplep_fake("MetHPTO_et"+"_fake")
    if not TQTreeObservable.addObservable(MetHPTO):
      INFO("failed to add MetHPTO observable")
      return False
    MetHPTO_ex=EventSelectionObs_leplep_fake("MetHPTO_ex"+"_fake")
    if not TQTreeObservable.addObservable(MetHPTO_ex):
        INFO("failed to add MetHPTO_ex observable")
        return False
    MetHPTO_ey=EventSelectionObs_leplep_fake("MetHPTO_ey"+"_fake")
    if not TQTreeObservable.addObservable(MetHPTO_ey):
        INFO("failed to add MetHPTO_ey observable")
        return False
    MetHPTO_phi=EventSelectionObs_leplep_fake("MetHPTO_phi"+"_fake")
    if not TQTreeObservable.addObservable(MetHPTO_phi):
        INFO("failed to add MetHPTO_phi observable")
        return False
    MetHPTO_x0=EventSelectionObs_leplep_fake("MetHPTO_x0"+"_fake")
    if not TQTreeObservable.addObservable(MetHPTO_x0):
        INFO("failed to add MetHPTO_x0 observable")
        return False
    MetHPTO_x1=EventSelectionObs_leplep_fake("MetHPTO_x1"+"_fake")
    if not TQTreeObservable.addObservable(MetHPTO_x1):
        INFO("failed to add MetHPTO_x1 observable")
        return False
    MetHPTO_MColl=EventSelectionObs_leplep_fake("MetHPTO_MColl"+"_fake")
    if not TQTreeObservable.addObservable(MetHPTO_MColl):
        INFO("failed to add MetHPTO_MColl observable"+"_fake")
        return False
    HiggsPt=EventSelectionObs_leplep_fake("HiggsPt"+"_fake")
    if not TQTreeObservable.addObservable(HiggsPt):
        INFO("failed to add HiggsPt observable")
        return False
    Lep0Match=EventSelectionObs_leplep_fake("Lep0Match"+"_fake")
    if not TQTreeObservable.addObservable(Lep0Match):
      INFO("failed to add Lep0Match observable")
      return False
    Lep1Match=EventSelectionObs_leplep_fake("Lep1Match"+"_fake")
    if not TQTreeObservable.addObservable(Lep1Match):
      INFO("failed to add Lep1Match observable")
      return False
    SelectLep_Lep0Tight=EventSelectionObs_leplep_fake("SelectLep_Lep0Tight"+"_fake")
    if not TQTreeObservable.addObservable(SelectLep_Lep0Tight):
        INFO("failed to add SelectLep_Lep0Tight observable")
        return False
    SelectLep_Lep1Tight=EventSelectionObs_leplep_fake("SelectLep_Lep1Tight"+"_fake")
    if not TQTreeObservable.addObservable(SelectLep_Lep1Tight):
        INFO("failed to add SelectLep_Lep1Tight observable")
        return False
    dRminLep0Jet=EventSelectionObs_leplep_fake("dRminLep0Jet"+"_fake")
    if not TQTreeObservable.addObservable(dRminLep0Jet):
        INFO("failed to add dRminLep0Jet observable")
        return False
    dRminLep1Jet=EventSelectionObs_leplep_fake("dRminLep1Jet"+"_fake")
    if not TQTreeObservable.addObservable(dRminLep1Jet):
        INFO("failed to add dRminLep1Jet observable")
        return False
    VBFcat=EventSelectionObs_leplep_fake("VBFcat"+"_fake")
    if not TQTreeObservable.addObservable(VBFcat):
        INFO("failed to add VBFcat observable")
        return False
    Boostedcat=EventSelectionObs_leplep_fake("Boostedcat"+"_fake")
    if not TQTreeObservable.addObservable(Boostedcat):
        INFO("failed to add Boostedcat observable")
        return False
    MMC_maxw=EventSelectionObs_leplep_fake("MMC_maxw"+"_fake")
    if not TQTreeObservable.addObservable(MMC_maxw):
        INFO("failed to add MMC_maxw observable")
        return False
    MMC_mlm=EventSelectionObs_leplep_fake("MMC_mlm"+"_fake")
    if not TQTreeObservable.addObservable(MMC_mlm):
        INFO("failed to add MMC_mlm observable")
        return False
    MMC_mlnu3p=EventSelectionObs_leplep_fake("MMC_mlnu3p"+"_fake")
    if not TQTreeObservable.addObservable(MMC_mlnu3p):
        INFO("failed to add MMC_mlnu3p observable")
        return False
    RunNumber=EventSelectionObs_leplep_fake("RunNumber"+"_fake")
    if not TQTreeObservable.addObservable(RunNumber):
        INFO("failed to add RunNumber observable")
        return False
    
    return True
