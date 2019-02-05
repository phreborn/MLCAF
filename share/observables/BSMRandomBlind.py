from QFramework import *
from ROOT import *

def addObservables(config):
    for name in ["" ] :
        myBSMRandomBlind= BSMRandomBlind("bsmrandomblind"+name)
        if not TQTreeObservable.addObservable(myBSMRandomBlind):
            INFO("failed to add myBSMRandomBlind observable")
            return False
        print(myBSMRandomBlind.getExpression()) 

    return True
