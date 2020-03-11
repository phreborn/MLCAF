import QFramework
import ROOT
from BSMtautauCAF import ScaleFactor

def addObservables(config):
    variation = config.getTagStringDefault("weightvar","nominal")
    myObs = ScaleFactor("ScaleFactor_"+variation)
    if not QFramework.TQTreeObservable.addObservable(myObs, "ScaleFactor_"+variation):
        INFO("failed to add " + name + " Observable!")
        return False
    return True
