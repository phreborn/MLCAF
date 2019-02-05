from QFramework import *
from ROOT import *

def addObservables(config):

    myTriggerMC = Trigger_ll("Trigger_MC")
    if not TQTreeObservable.addObservable(myTriggerMC):
        INFO("failed to add myTriggerMC observable")
        return False

    myTriggerData = Trigger_ll("Trigger_Data")
    if not TQTreeObservable.addObservable(myTriggerData):
        INFO("failed to add myTriggerData observable")
        return False
    
    return True


