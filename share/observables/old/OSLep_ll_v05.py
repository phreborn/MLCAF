from QFramework import *
from ROOT import *

def addObservables(config):

    myOSLep = OSLep_ll_v05("OSLep")
    if not TQTreeObservable.addObservable(myOSLep):
        INFO("failed to add myOSLep observable")
        return False

    myOSLep_fake = OSLep_ll_v05("OSLep_fake")
    if not TQTreeObservable.addObservable(myOSLep_fake):
        INFO("failed to add myOSLep_fake observable")
        return False
    
    return True


