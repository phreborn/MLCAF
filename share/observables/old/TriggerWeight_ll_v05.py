from QFramework import *
from ROOT import *

def addObservables(config):

    myTriggerWeight_v05 = TriggerWeight_ll_v05("TriggerWeight_v05")

    if not TQTreeObservable.addObservable(myTriggerWeight_v05):
        INFO("failed to add myTriggerWeight_v05 observable")
        return False

    myTriggerWeight_v05_fake = TriggerWeight_ll_v05("TriggerWeight_v05_fake")

    if not TQTreeObservable.addObservable(myTriggerWeight_v05_fake):
        INFO("failed to add myTriggerWeight_v05_fake observable")
        return False
    
    return True


