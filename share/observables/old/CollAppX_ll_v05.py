from QFramework import *
from ROOT import *

def addObservables(config):

    myCollAppX = CollAppX_ll_v05("CollApp_x0x1")

    if not TQTreeObservable.addObservable(myCollAppX):
        INFO("failed to add myCollAppX observable")
        return False
    
    return True


