from QFramework import *
from ROOT import *

def addObservables(config):

    myMt = Mt_ll_v05("Mt")
    if not TQTreeObservable.addObservable(myMt):
        INFO("failed to add myMt observable")
        return False

    myMt_fake = Mt_ll_v05("Mt_fake")
    if not TQTreeObservable.addObservable(myMt_fake):
        INFO("failed to add myMt_fake observable")
        return False
    
    return True


