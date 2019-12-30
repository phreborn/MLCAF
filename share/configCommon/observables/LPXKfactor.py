import QFramework
import ROOT
from BSMtautauCAF import LPXKfactor

def addObservables(config):
    variation = config.getTagStringDefault("lpxvar","nominal")
    myObs = LPXKfactor("LPXKfactor_"+variation)
    if not QFramework.TQTreeObservable.addObservable(myObs, "LPXKfactor_"+variation):
        INFO("failed to add LPXKfactor Observable!")
        return False
    return True
