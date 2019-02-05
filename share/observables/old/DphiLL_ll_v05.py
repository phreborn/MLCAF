from QFramework import *
from ROOT import *

def addObservables(config):

    myDphiLL = DphiLL_ll_v05("DphiLL")

    if not TQTreeObservable.addObservable(myDphiLL):
        INFO("failed to add myDphiLL observable")
        return False
    
    return True


