from QFramework import *
from ROOT import *

def addObservables(config):
    for name in [
    "", 
    ] : 
        mytopCor= topCor("topcor"+name)
        if not TQTreeObservable.addObservable(mytopCor):
            INFO("failed to add mytopCor observable")
            return False
        print(mytopCor.getExpression()) 

    return True
