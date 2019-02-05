from QFramework import *
from ROOT import *

def addObservables(config):
    for name in ["effUp" ] :
        myBtagTauSys= btagTauSys("BtagTauSys"+name)
        if not TQTreeObservable.addObservable(myBtagTauSys):
            INFO("failed to add myBtagTauSys observable")
            return False
        print(myBtagTauSys.getExpression()) 

    for name in ["effDo"] : 
        myBtagTauSys= btagTauSys("BtagTauSys"+name)
        if not TQTreeObservable.addObservable(myBtagTauSys):
            INFO("failed to add myBtagTauSys observable")
            return False
        print(myBtagTauSys.getExpression()) 

    for name in ["ineffUp" ] :
        myBtagTauSys= btagTauSys("BtagTauSys"+name)
        if not TQTreeObservable.addObservable(myBtagTauSys):
            INFO("failed to add myBtagTauSys observable")
            return False
        print(myBtagTauSys.getExpression()) 

    for name in ["ineffDo"] : 
        myBtagTauSys= btagTauSys("BtagTauSys"+name)
        if not TQTreeObservable.addObservable(myBtagTauSys):
            INFO("failed to add myBtagTauSys observable")
            return False
        print(myBtagTauSys.getExpression()) 

    return True
