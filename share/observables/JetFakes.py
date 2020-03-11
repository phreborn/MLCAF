import QFramework
import ROOT
from BSMtautauCAF import JetFakes

def addObservables(config):
    variation = config.getTagStringDefault("fakevar","nominal")
    myObs= JetFakes("JetFakes_"+variation)
    if not QFramework.TQTreeObservable.addObservable(myObs,"JetFakes_"+variation):
        INFO("failed to add myJetFakes observable")
        return False
    #print(myJetFakes.getExpression())
    return True
