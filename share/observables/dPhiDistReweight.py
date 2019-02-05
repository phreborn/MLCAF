from QFramework import *
from ROOT import *

def addObservables(config):
    for name in [
    "", 
    ] : 
        mydPhiDistReweight= dPhiDistReweight("dphidistreweight"+name)
        if not TQTreeObservable.addObservable(mydPhiDistReweight):
            INFO("failed to add mydPhiDistReweight observable")
            return False
        print(mydPhiDistReweight.getExpression()) 

    return True
