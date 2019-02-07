import QFramework
import ROOT
from Htautau import BSMTriggerDecision

def addObservables(config):
    #variation = config.getTagStringDefault("variation","nominal")
    #INFO("using decisions for variation '{:s}'".format(variation))
    #for name in ["data"]:
    for name in [""]:
        myObs = BSMTriggerDecision("bsmtriggerdecision"+name)
        if not QFramework.TQTreeObservable.addObservable(myObs,"BSMTriggerDecision"):
            INFO("failed to add BSMTriggerDecision Observable!")
            return False
    return True
