from ROOT import *
from QFramework import *
import EventSelectionObs_leplep_common

def addObservables(config):
    selection=EventSelectionObs_leplep_tight
    if "fakes" in str(config.getTagStringDefault("restrictedPath","")):
        INFO("running over fakes, using fakes EventSelection")
        selection=EventSelectionObs_leplep_fake
    observables=EventSelectionObs_leplep_common.generateCommonObservables("","_tight");
    for obs in observables:
      thisobs=selection(obs)
      if not TQTreeObservable.addObservable(thisobs):
        INFO("failed to add "+obs+" observable")
        return False
    return True
    #for nEl in  xrange(4):
    #  ElIdx=EventSelectionObs_leplep_tight("ElIdx_"+str(nEl)+"_tight")
    #  if not TQTreeObservable.addObservable(ElIdx):
    #    INFO("failed to add ElIdx_"+str(nEl)+" observable")
    #    return False
    #for nMu in  xrange(4):
    #  MuIdx=EventSelectionObs_leplep_tight("MuIdx_"+str(nMu)+"_tight")
    #  if not TQTreeObservable.addObservable(MuIdx):
    #    INFO("failed to add MuIdx_"+str(nMu)+" observable")
    #    return False
    #for nJet in  xrange(5):
    #  JetIdx=EventSelectionObs_leplep_tight("JetIdx_"+str(nJet)+"_tight")
    #  if not TQTreeObservable.addObservable(JetIdx):
    #    INFO("failed to add JetIdx_"+str(nJet)+" observable")
    #    return False
    #for nLepton in  xrange(8):
    #  LeptonIdx=EventSelectionObs_leplep_tight("LeptonIdx_"+str(nLepton)+"_tight")
    #  if not TQTreeObservable.addObservable(LeptonIdx):
    #    INFO("failed to add LeptonIdx_"+str(nLepton)+" observable")
    #    return False
    #for nTau in  xrange(8):
    #  TauIdx=EventSelectionObs_leplep_tight("TauIdx_"+str(nTau)+"_tight")
    #  if not TQTreeObservable.addObservable(TauIdx):
    #    INFO("failed to add TauIdx_"+str(nTau)+" observable")
    #    return False
    #ElN=EventSelectionObs_leplep_tight("ElN"+"_tight")
    #if not TQTreeObservable.addObservable(ElN):
    #  INFO("failed to add ElN observable")
    #  return False
    #MuN=EventSelectionObs_leplep_tight("MuN"+"_tight")
    #if not TQTreeObservable.addObservable(MuN):
    #  INFO("failed to add MuN observable")
    #  return False
    #JetN=EventSelectionObs_leplep_tight("JetN"+"_tight")
    #if not TQTreeObservable.addObservable(JetN):
    #  INFO("failed to add JetN observable")
    #  return False
    #LeptonN=EventSelectionObs_leplep_tight("LeptonN"+"_tight")
    #if not TQTreeObservable.addObservable(LeptonN):
    #  INFO("failed to add LeptonN observable")
    #  return False
    #Lep0Pt=EventSelectionObs_leplep_tight("Lep0Pt"+"_tight")
    #if not TQTreeObservable.addObservable(Lep0Pt):
    #  INFO("failed to add Lep0Pt observable")
    #  return False
    #Lep1Pt=EventSelectionObs_leplep_tight("Lep1Pt"+"_tight")
    #if not TQTreeObservable.addObservable(Lep1Pt):
    #  INFO("failed to add Lep1Pt observable")
    #  return False
    #Lep0Eta=EventSelectionObs_leplep_tight("Lep0Eta"+"_tight")
    #if not TQTreeObservable.addObservable(Lep0Eta):
    #  INFO("failed to add Lep0Eta observable")
    #  return False
    #Lep1Eta=EventSelectionObs_leplep_tight("Lep1Eta"+"_tight")
    #if not TQTreeObservable.addObservable(Lep1Eta):
    #  INFO("failed to add Lep1Eta observable")
    #  return False
    #TauN=EventSelectionObs_leplep_tight("TauN"+"_tight")
    #if not TQTreeObservable.addObservable(TauN):
    #  INFO("failed to add TauN observable")
    #  return False
    #TriggerWeight=EventSelectionObs_leplep_tight("TriggerWeight"+"_tight")
    #if not TQTreeObservable.addObservable(TriggerWeight):
    #  INFO("failed to add TriggerWeight observable")
    #  return False
    #LeptonWeight=EventSelectionObs_leplep_tight("LeptonWeight"+"_tight")
    #if not TQTreeObservable.addObservable(LeptonWeight):
    #  INFO("failed to add LeptonWeight observable")
    #  return False
    #TriggeredMC=EventSelectionObs_leplep_tight("TriggeredMC"+"_tight")
    #if not TQTreeObservable.addObservable(TriggeredMC):
    #  INFO("failed to add TriggeredMC observable")
    #  return False
    #TriggeredData=EventSelectionObs_leplep_tight("TriggeredData"+"_tight")
    #if not TQTreeObservable.addObservable(TriggeredData):
    #  INFO("failed to add TriggeredData observable")
    #  return False
    #TriggerType_new=EventSelectionObs_leplep_tight("TriggerType_new"+"_tight")
    #if not TQTreeObservable.addObservable(TriggerType_new):
    #  INFO("failed to add TriggerType_new observable")
    #  return False
    #MVis_new=EventSelectionObs_leplep_tight("MVis_new"+"_tight")
    #if not TQTreeObservable.addObservable(MVis_new):
    #  INFO("failed to add MVis_new observable")
    #  return False
    #Mt_new=EventSelectionObs_leplep_tight("Mt_new"+"_tight")
    #if not TQTreeObservable.addObservable(Mt_new):
    #  INFO("failed to add Mt_new observable")
    #  return False
    #SumPtLep_new=EventSelectionObs_leplep_tight("SumPtLep_new"+"_tight")
    #if not TQTreeObservable.addObservable(SumPtLep_new):
    #  INFO("failed to add SumPtLep_new observable")
    #  return False
    #DphiLL_new=EventSelectionObs_leplep_tight("DphiLL_new"+"_tight")
    #if not TQTreeObservable.addObservable(DphiLL_new):
    #  INFO("failed to add DphiLL_new observable")
    #  return False
    #LepLepSign=EventSelectionObs_leplep_tight("LepLepSign"+"_tight")
    #if not TQTreeObservable.addObservable(LepLepSign):
    #  INFO("failed to add LepLepSign observable")
    #  return False
    #LepXCollApp=EventSelectionObs_leplep_tight("LepXCollApp"+"_tight")
    #if not TQTreeObservable.addObservable(LepXCollApp):
    #  INFO("failed to add LepXCollApp observable")
    #  return False
    #LepMColl=EventSelectionObs_leplep_tight("LepMColl"+"_tight")
    #if not TQTreeObservable.addObservable(LepMColl):
    #  INFO("failed to add LepMColl observable")
    #  return False
    #Jet0Pt=EventSelectionObs_leplep_tight("Jet0Pt"+"_tight")
    #if not TQTreeObservable.addObservable(Jet0Pt):
    #  INFO("failed to add Jet0Pt_new observable")
    #  return False
    #JVTWeight=EventSelectionObs_leplep_tight("JVTWeight"+"_tight")
    #if not TQTreeObservable.addObservable(JVTWeight):
    #  INFO("failed to add JVTWeight observable")
    #  return False
    #MVXWeight=EventSelectionObs_leplep_tight("MVXWeight"+"_tight")
    #if not TQTreeObservable.addObservable(MVXWeight):
    #  INFO("failed to add MVXWeight observable")
    #  return False
    #Btag=EventSelectionObs_leplep_tight("Btag"+"_tight")
    #if not TQTreeObservable.addObservable(Btag):
    #  INFO("failed to add bTag observable")
    #  return False
    #SelectLep=EventSelectionObs_leplep_tight("SelectLep"+"_tight")
    #if not TQTreeObservable.addObservable(SelectLep):
    #  INFO("failed to add SelectLep observable")
    #  return False
    #MetHPTO=EventSelectionObs_leplep_tight("MetHPTO_et"+"_tight")
    #if not TQTreeObservable.addObservable(MetHPTO):
    #  INFO("failed to add MetHPTO observable")
    #  return False
    #MetHPTO_ex=EventSelectionObs_leplep_tight("MetHPTO_ex"+"_tight")
    #if not TQTreeObservable.addObservable(MetHPTO_ex):
    #    INFO("failed to add MetHPTO_ex observable")
    #    return False
    #MetHPTO_ey=EventSelectionObs_leplep_tight("MetHPTO_ey"+"_tight")
    #if not TQTreeObservable.addObservable(MetHPTO_ey):
    #    INFO("failed to add MetHPTO_ey observable")
    #    return False
    #MetHPTO_phi=EventSelectionObs_leplep_tight("MetHPTO_phi"+"_tight")
    #if not TQTreeObservable.addObservable(MetHPTO_phi):
    #    INFO("failed to add MetHPTO_phi observable")
    #    return False
    #MetHPTO_x0=EventSelectionObs_leplep_tight("MetHPTO_x0"+"_tight")
    #if not TQTreeObservable.addObservable(MetHPTO_x0):
    #    INFO("failed to add MetHPTO_x0 observable")
    #    return False
    #MetHPTO_x1=EventSelectionObs_leplep_tight("MetHPTO_x1"+"_tight")
    #if not TQTreeObservable.addObservable(MetHPTO_x1):
    #    INFO("failed to add MetHPTO_x1 observable")
    #    return False
    #MetHPTO_MColl=EventSelectionObs_leplep_tight("MetHPTO_MColl"+"_tight")
    #if not TQTreeObservable.addObservable(MetHPTO_MColl):
    #    INFO("failed to add MetHPTO_MColl observable")
    #    return False
    #HiggsPt=EventSelectionObs_leplep_tight("HiggsPt"+"_tight")
    #if not TQTreeObservable.addObservable(HiggsPt):
    #    INFO("failed to add HiggsPt observable")
    #    return False
    #BVeto=EventSelectionObs_leplep_tight("BVeto_new"+"_tight")
    #if not TQTreeObservable.addObservable(BVeto):
    #    INFO("failed to add BVeto observable")
    #    return False
    #Lep0Match=EventSelectionObs_leplep_tight("Lep0Match"+"_tight")
    #if not TQTreeObservable.addObservable(Lep0Match):
    #  INFO("failed to add Lep0Match observable")
    #  return False
    #Lep1Match=EventSelectionObs_leplep_tight("Lep1Match"+"_tight")
    #if not TQTreeObservable.addObservable(Lep1Match):
    #  INFO("failed to add Lep1Match observable")
    #  return False
    #SelectLep_Lep0Tight=EventSelectionObs_leplep_tight("SelectLep_Lep0Tight"+"_tight")
    #if not TQTreeObservable.addObservable(SelectLep_Lep0Tight):
    #    INFO("failed to add SelectLep_Lep0Tight observable")
    #    return False
    #SelectLep_Lep1Tight=EventSelectionObs_leplep_tight("SelectLep_Lep1Tight"+"_tight")
    #if not TQTreeObservable.addObservable(SelectLep_Lep1Tight):
    #    INFO("failed to add SelectLep_Lep1Tight observable")
    #    return False
    #dRminLep0Jet=EventSelectionObs_leplep_tight("dRminLep0Jet"+"_tight")
    #if not TQTreeObservable.addObservable(dRminLep0Jet):
    #    INFO("failed to add dRminLep0Jet observable")
    #    return False
    #dRminLep1Jet=EventSelectionObs_leplep_tight("dRminLep1Jet"+"_tight")
    #if not TQTreeObservable.addObservable(dRminLep1Jet):
    #    INFO("failed to add dRminLep1Jet observable")
    #    return False
    #VBFcat=EventSelectionObs_leplep_tight("VBFcat"+"_tight")
    #if not TQTreeObservable.addObservable(VBFcat):
    #    INFO("failed to add VBFcat observable")
    #    return False
    #Boostedcat=EventSelectionObs_leplep_tight("Boostedcat"+"_tight")
    #if not TQTreeObservable.addObservable(Boostedcat):
    #    INFO("failed to add Boostedcat observable")
    #    return False
    #MMC_maxw=EventSelectionObs_leplep_tight("MMC_maxw"+"_tight")
    #if not TQTreeObservable.addObservable(MMC_maxw):
    #    INFO("failed to add MMC_maxw observable")
    #    return False
    #MMC_mlm=EventSelectionObs_leplep_tight("MMC_mlm"+"_tight")
    #if not TQTreeObservable.addObservable(MMC_mlm):
    #    INFO("failed to add MMC_mlm observable")
    #    return False
    #MMC_mlnu3p=EventSelectionObs_leplep_tight("MMC_mlnu3p"+"_tight")
    #if not TQTreeObservable.addObservable(MMC_mlnu3p):
    #    INFO("failed to add MMC_mlnu3p observable")
    #    return False
    #
    #return True
