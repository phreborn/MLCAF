import QFramework
import ROOT
from BSMtautauCAF import TauReweight

def addObservables(config):
    variation = config.getTagStringDefault("materialvar","nominal")
    myObs = TauReweight("TauReweight_"+variation)
    if not QFramework.TQTreeObservable.addObservable(myObs, "TauReweight_"+variation):
        INFO("failed to add TauReweight Observable!")
        return False
    return True
