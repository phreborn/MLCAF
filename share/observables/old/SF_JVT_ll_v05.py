from QFramework import *
from ROOT import *

def addObservables(config):
    syst=0
    systematic=str(config.getTagStringDefault("systematic",""))
    if systematic == "JET_EFF_JVT_up": 
        syst=1
        INFO("JET_EFF_JVT_up "+str(syst))
    elif systematic == "JET_EFF_JVT_down": 
        syst=-1
        INFO("JET_EFF_JVT_down "+str(syst))
    mySFJVT = SF_JVT_ll_v05("SF_JVT",syst)
    if not TQTreeObservable.addObservable(mySFJVT):
        INFO("failed to add mySFJVT observable")
        return False
    return True
