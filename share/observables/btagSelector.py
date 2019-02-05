from QFramework import *
from ROOT import *

def addObservables(config):
    for name in ["" ] :
        myBtagSelector= btagSelector("BtagSelector"+name)
        if not TQTreeObservable.addObservable(myBtagSelector):
            INFO("failed to add myBtagSelector observable")
            return False
        print(myBtagSelector.getExpression()) 

    return True
