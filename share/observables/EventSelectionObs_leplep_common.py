def generateCommonObservables(prefix="",postfix=""):
    observables=[]
    for nEl in  xrange(4):
       observables.append("ElIdx_"+str(nEl))
    for nMu in  xrange(4):
       observables.append("MuIdx_"+str(nMu))
    for nJet in  xrange(5):
       observables.append("JetIdx_"+str(nJet))
    for nLepton in  xrange(8):
       observables.append("LeptonIdx_"+str(nLepton))
    for nTau in  xrange(2):
       observables.append("TauIdx_"+str(nTau))
    observables+=["ElN","MuN","JetN","LeptonN","TauN"]
    observables+=["Lep0Pt","Lep1Pt","Lep0Eta","Lep1Eta"]
    observables+=["TriggerWeight","LeptonWeight","TriggeredMC","TriggeredData", "TriggerType_new"]
    observables+=["MVis_new","Mt_new","SumPtLep_new","DphiLL_new","DphiL0MET","DphiL1MET","DEtaLL","MLL","MCollASym"]
    observables+=["LepLepSign","LepXCollApp","LepMColl","LepX0Coll","LepX1Coll"]
    observables+=["Jet0Pt","Jet1Pt","JVTWeight","MVXWeight","Btag","DEtaJetJet"]
    observables+=["SelectLep","Lep0Match","Lep1Match"]
    observables+=["MetHPTO_et","MetHPTO_ex","MetHPTO_ey","MetHPTO_phi","MetHPTO_x0","MetHPTO_x1","MetHPTO_MColl"]
    observables+=["HiggsPt","LeptonCentrality","CentralJetVeto"]
    observables+=["VBFcat","VBFZttCRcat","Boostedcat","BoostedZttCRcat" ]
    observables+=["MMC_maxw","MMC_mlm","MMC_mlnu3p"]
    observables+=["SelectLep_Lep0Tight","SelectLep_Lep1Tight"]
    observables+=["dRminLep0Jet","dRminLep1Jet"]
    observables+=["Jet_NPt25","Jet_N2p4Eta25Pt","MtLep0","MtLep1"]
    observables+=["DphiLep0MET","DphiLep1MET"]
    observables+=["d0Lep0","d0Lep1"]
    observables+=["d0SigLep0","d0SigLep1"]
    observables+=["DphiLL"]
    observables+=["MJetJet"]
    observables+=["PtLep0MET","PtLep1MET"]
    observables+=["PtLL","PtTauTau","PtCollPt"]
    observables+=["RunNumber"]
    observables=[ prefix+e+postfix for e in observables ]
    return observables
