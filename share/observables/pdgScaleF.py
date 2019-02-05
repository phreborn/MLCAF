from QFramework import *
from ROOT import *

def addObservables(config):
    for name in [
    "", 
    ] : 
        mypdgScaleF= pdgScaleF("pdgscalef"+name)
        if not TQTreeObservable.addObservable(mypdgScaleF):
            INFO("failed to add mypdgScaleF observable")
            return False
        print(mypdgScaleF.getExpression()) 

    return True
