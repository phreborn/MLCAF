from QFramework import *
from ROOT import *

def addObservables(config):

    myTriggerWeight = TriggerWeight_ll("TriggerWeight")

    if not TQTreeObservable.addObservable(myTriggerWeight):
        INFO("failed to add myTriggerWeight observable")
        return False
    
    return True


