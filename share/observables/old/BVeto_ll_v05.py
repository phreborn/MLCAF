from QFramework import *
from ROOT import *

def addObservables(config):

    myBVeto = BVeto_ll_v05("BVeto")

    if not TQTreeObservable.addObservable(myBVeto):
        INFO("failed to add myBVeto observable")
        return False
    
    return True


