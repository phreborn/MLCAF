from QFramework import *
from ROOT import *

def addObservables(config):

    mydRljm = DeltaRFakeLepJetmin_ll_v05("dRljm")
    if not TQTreeObservable.addObservable(mydRljm):
        INFO("failed to add mydRljm observable")
        return False

    mydRljm_fake = DeltaRFakeLepJetmin_ll_v05("dRljm_fake")
    if not TQTreeObservable.addObservable(mydRljm_fake):
        INFO("failed to add mydRljm_fake observable")
        return False
    
    return True


