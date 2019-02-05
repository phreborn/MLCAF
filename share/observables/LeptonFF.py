from QFramework import *
from ROOT import *

def addObservables(config):
    for name in [
    "", 
    ] : 
        myLeptonFF= LeptonFF("leptonff"+name)
        if not TQTreeObservable.addObservable(myLeptonFF):
            INFO("failed to add myLeptonFF observable")
            return False
        print(myLeptonFF.getExpression()) 

    return True
