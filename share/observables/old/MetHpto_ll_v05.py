from QFramework import *
from ROOT import *

def addObservables(config):

    myMetHpto = MetHpto_ll_v05("MetHpto")

    if not TQTreeObservable.addObservable(myMetHpto):
        INFO("failed to add myMetHpto observable")
        return False
    
    return True


