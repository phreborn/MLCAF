from QFramework import *
from ROOT import *

def addObservables(config):

    myTruthMatchingLep0_v05 = TruthMatchingLep_ll_v05("TruthMatchLep0_v05", 0)

    if not TQTreeObservable.addObservable(myTruthMatchingLep0_v05):
        INFO("failed to add myTruthMatchingLep0_v05 observable")
        return False

    myTruthMatchingLep1_v05 = TruthMatchingLep_ll_v05("TruthMatchLep1_v05", 1)
    if not TQTreeObservable.addObservable(myTruthMatchingLep1_v05):
        INFO("failed to add myTruthMatchingLep1_v05 observable")
        return False

    myTruthMatchingLep1_v05_fake = TruthMatchingLep_ll_v05("TruthMatchLep1_v05_fake", 1)
    if not TQTreeObservable.addObservable(myTruthMatchingLep1_v05_fake):
        INFO("failed to add myTruthMatchingLep1_v05_fake observable")
        return False

    return True
