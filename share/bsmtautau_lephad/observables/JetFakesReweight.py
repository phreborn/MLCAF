import QFramework
import ROOT
from BSMtautauCAF import JetFakesReweight

def addObservables(config):
    variation = config.getTagStringDefault("fakevar","nominal")
    myObs = JetFakesReweight("JetFakesReweight_"+variation)
    if not QFramework.TQTreeObservable.addObservable(myObs,"JetFakesReweight_"+variation):
        INFO("failed to add JetFakesReweight Observable!")
        return False
    return True
