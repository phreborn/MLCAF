from QFramework import *
from ROOT import *

def addObservables(config):

    myTriggerMC_v05 = Trigger_ll_v05("Trigger_MC_v05")
    if not TQTreeObservable.addObservable(myTriggerMC_v05):
        INFO("failed to add myTriggerMC_v05 observable")
        return False

    myTriggerData_v05 = Trigger_ll_v05("Trigger_Data_v05")
    if not TQTreeObservable.addObservable(myTriggerData_v05):
        INFO("failed to add myTriggerData_v05 observable")
        return False
    
    myTriggerType = Trigger_ll_v05("TriggerType")
    if not TQTreeObservable.addObservable(myTriggerType):
        INFO("failed to add myTriggerType observable")
        return False

    myTriggerMC_v05_fake = Trigger_ll_v05("Trigger_MC_v05_fake")
    if not TQTreeObservable.addObservable(myTriggerMC_v05_fake):
        INFO("failed to add myTriggerMC_v05_fake observable")
        return False

    myTriggerData_v05_fake = Trigger_ll_v05("Trigger_Data_v05_fake")
    if not TQTreeObservable.addObservable(myTriggerData_v05_fake):
        INFO("failed to add myTriggerData_v05_fake observable")
        return False

    myTriggerType_fake = Trigger_ll_v05("TriggerType_fake")
    if not TQTreeObservable.addObservable(myTriggerType_fake):
        INFO("failed to add myTriggerType_fake observable")
        return False

    return True


