import QFramework
import ROOT
from BSMtautauCAF import extrapolationReweight

def addObservables(config):
    variation = config.getTagStringDefault("extraposf","nominal")
    myextrapolationReweight= extrapolationReweight("extraporeweight_"+variation)
    if not QFramework.TQTreeObservable.addObservable(myextrapolationReweight,"extraporeweight_"+variation):
        INFO("failed to add myextrapolationReweight observable")
        return False
    #print(myextrapolationReweight.getExpression())
    return True
