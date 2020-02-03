import QFramework
import ROOT
from BSMtautauCAF import LeptonFakes

def addObservables(config):
    variation = config.getTagStringDefault("isovar","nominal")
    myObs = LeptonFakes("LeptonFakes_"+variation)
    if not QFramework.TQTreeObservable.addObservable(myObs,"LeptonFakes_"+variation):
        INFO("failed to add LeptonFakes Observable!")
        return False
    return True
