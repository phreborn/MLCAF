from QFramework import *
from ROOT import *

def addObservables(config):

    myMVis = MVis_ll_v05("MVis")
    if not TQTreeObservable.addObservable(myMVis):
        INFO("failed to add myMVis observable")
        return False

    myMVis_fake = MVis_ll_v05("MVis_fake")
    if not TQTreeObservable.addObservable(myMVis_fake):
        INFO("failed to add myMVis_fake observable")
        return False
    
    return True


