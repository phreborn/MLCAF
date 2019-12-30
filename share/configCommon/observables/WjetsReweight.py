import QFramework
import ROOT
from BSMtautauCAF import WjetsReweight

def addObservables(config):
    variation = config.getTagStringDefault("fakevar","nominal")
    myObs = WjetsReweight("WjetsReweight_"+variation)
    if not QFramework.TQTreeObservable.addObservable(myObs,"WjetsReweight_"+variation):
        INFO("failed to add WjetsReweight Observable!")
        return False
    return True
