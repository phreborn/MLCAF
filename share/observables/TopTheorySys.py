import QFramework
import ROOT
from BSMtautauCAF import TopTheorySys

def addObservables(config):
    variation = config.getTagStringDefault("topvar","nominal")
    myObs= TopTheorySys("TopTheorySys_"+variation)
    if not QFramework.TQTreeObservable.addObservable(myObs,"TopTheorySys_"+variation):
        INFO("failed to add myTopTheorySys observable")
        return False
    return True
