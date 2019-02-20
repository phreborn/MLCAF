import QFramework
import ROOT
from BSMtautauCAF import isoReweight

def addObservables(config):
    variation = config.getTagStringDefault("isovar","nominal")
    myObs = isoReweight("isoreweight_"+variation)
    if not QFramework.TQTreeObservable.addObservable(myObs,"isoreweight_"+variation):
        INFO("failed to add isoReweight Observable!")
        return False
    return True
