from ROOT import *
from QFramework import *
def addObservables():
    for nEl in  xrange(4):
      ElIdx=OverlapRemoval_leplep("ElIdx_"+str(nEl))
      if not TQTreeObservable.addObservable(ElIdx):
        INFO("failed to add ElIdx_"+str(nEl)+" observable")
        return False
    for nMu in  xrange(4):
      MuIdx=OverlapRemoval_leplep("MuIdx_"+str(nMu))
      if not TQTreeObservable.addObservable(MuIdx):
        INFO("failed to add MuIdx_"+str(nMu)+" observable")
        return False
    for nJet in  xrange(5):
      JetIdx=OverlapRemoval_leplep("JetIdx_"+str(nJet))
      if not TQTreeObservable.addObservable(JetIdx):
        INFO("failed to add JetIdx_"+str(nJet)+" observable")
        return False
    for nLepton in  xrange(8):
      LeptonIdx=OverlapRemoval_leplep("LeptonIdx_"+str(nLepton))
      if not TQTreeObservable.addObservable(LeptonIdx):
        INFO("failed to add LeptonIdx_"+str(nLepton)+" observable")
        return False
    for nTau in  xrange(8):
      TauIdx=OverlapRemoval_leplep("TauIdx_"+str(nTau))
      if not TQTreeObservable.addObservable(TauIdx):
        INFO("failed to add TauIdx_"+str(nTau)+" observable")
        return False
    ElN=OverlapRemoval_leplep("ElN")
    if not TQTreeObservable.addObservable(ElN):
      INFO("failed to add ElN observable")
      return False
    MuN=OverlapRemoval_leplep("MuN")
    if not TQTreeObservable.addObservable(MuN):
      INFO("failed to add MuN observable")
      return False
    JetN=OverlapRemoval_leplep("JetN")
    if not TQTreeObservable.addObservable(JetN):
      INFO("failed to add JetN observable")
      return False
    LeptonN=OverlapRemoval_leplep("LeptonN")
    if not TQTreeObservable.addObservable(LeptonN):
      INFO("failed to add LeptonN observable")
      return False
    TauN=OverlapRemoval_leplep("TauN")
    if not TQTreeObservable.addObservable(TauN):
      INFO("failed to add TauN observable")
      return False
    return True
