import QFramework
import ROOT
from BSMtautauCAF import QCDReweight

def addObservables(config):
    variation = config.getTagStringDefault("isovar","nominal")
    myObs = QCDReweight("QCDReweight_"+variation)
    if not QFramework.TQTreeObservable.addObservable(myObs,"QCDReweight_"+variation):
        INFO("failed to add QCDReweight Observable!")
        return False
    return True
