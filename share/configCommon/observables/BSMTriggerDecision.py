import QFramework
import ROOT
from BSMtautauCAF import BSMTriggerDecision

def addObservables(config):
    myObs = BSMTriggerDecision("BSMTriggerDecision")
    if not QFramework.TQTreeObservable.addObservable(myObs,"BSMTriggerDecision"):
        INFO("failed to add BSMTriggerDecision Observable!")
        return False
    return True
