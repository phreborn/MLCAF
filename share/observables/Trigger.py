from QFramework import *
from ROOT import *

def addObservables():
    myTriggerMC = Trigger("TriggerMC")
    if not TQTreeObservable.addObservable(myTriggerMC):
        INFO("failed to add myTriggerMC observable")
        return False

    myTriggerData = Trigger("TriggerData")
    if not TQTreeObservable.addObservable(myTriggerData):
        INFO("failed to add myTriggerData observable")
        return False

    return True
