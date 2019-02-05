from QFramework import *
from ROOT import *

def addObservables():
    myTriggerSF = TriggerSF("TriggerSF")
    if not TQTreeObservable.addObservable(myTriggerSF):
        INFO("failed to add myTriggerSF observable")
        return False
    return True
