import QFramework
import ROOT
from BSMtautauCAF import LeptonFakesReweight

def addObservables(config):
    variation = config.getTagStringDefault("isovar","nominal")
    myObs = LeptonFakesReweight("LeptonFakesReweight_"+variation)
    if not QFramework.TQTreeObservable.addObservable(myObs,"LeptonFakesReweight_"+variation):
        INFO("failed to add LeptonFakesReweight Observable!")
        return False
    return True
