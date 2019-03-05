import QFramework
import ROOT
from BSMtautauCAF import ptReweight

def addObservables(config):
    variation = config.getTagStringDefault("fakevar","nominal")
    myptReweight= ptReweight("ptreweight_"+variation)
    if not QFramework.TQTreeObservable.addObservable(myptReweight,"ptreweight_"+variation):
        INFO("failed to add myptReweight observable")
        return False
    #print(myptReweight.getExpression())
    return True
