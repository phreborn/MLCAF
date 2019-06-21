import QFramework
import ROOT
from BSMtautauCAF import TopReweight

def addObservables(config):
    variation = config.getTagStringDefault("topvar","nominal")
    myObs = TopReweight("TopReweight_"+variation)
    if not QFramework.TQTreeObservable.addObservable(myObs,"TopReweight_"+variation):
        INFO("failed to add TopReweight Observable!")
        return False
    return True
