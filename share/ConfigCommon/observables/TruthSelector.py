from QFramework import *
from ROOT import *

def addObservables(config):
    for name in ["" ] :
        myTruthSelector= TruthSelector("TruthSelector"+name)
        if not TQTreeObservable.addObservable(myTruthSelector):
            INFO("failed to add myTruthSelector observable")
            return False
#        print(myTruthSelector.getExpression()) 

    return True
