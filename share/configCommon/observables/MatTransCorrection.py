import QFramework
import ROOT
from BSMtautauCAF import MatTransCorrection

def addObservables(config):
    variation = config.getTagStringDefault("materialvar","nominal")
    myObs = MatTransCorrection("MatTransCorrection_"+variation)
    if not QFramework.TQTreeObservable.addObservable(myObs, "MatTransCorrection_"+variation):
        INFO("failed to add MatTransCorrection Observable!")
        return False
    return True
