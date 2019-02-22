import QFramework
import ROOT
from BSMtautauCAF import ScaleFactor

def addObservables(config):
    weightSystematic = config.getTagStringDefault("weightvar","nominal")
    names = ["ScaleFactor"]
    names += ["ScaleFactor_%s" % weightSystematic]
    for name in names:
        myObs = ScaleFactor(name)
        if not QFramework.TQTreeObservable.addObservable(myObs,name):
            INFO("failed to add " + name + " Observable!")
            return False
    return True
