import QFramework
import ROOT
from BSMtautauCAF import ExtrapolationSys

def addObservables(config):
    variation = config.getTagStringDefault("fakevar","nominal")
    myObs= ExtrapolationSys("ExtrapolationSys_"+variation)
    if not QFramework.TQTreeObservable.addObservable(myObs,"ExtrapolationSys_"+variation):
        INFO("failed to add myExtrapolationSys observable")
        return False
    #print(myExtrapolationSys.getExpression())
    return True
