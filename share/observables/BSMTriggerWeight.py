from QFramework import *
from ROOT import *

def addObservables(config):
    for name in ["" ] : 
    #for name in ["", "MuTrigSysStatUp", "MuTrigSysStatDo", "MuTrigSysSystUp", "MuTrigSysSystDo", "ElTrigSysStatUp", "ElTrigSysStatUp" ] : 
        myBSMTriggerWeight= BSMTriggerWeight("bsmtriggerweight"+name)
        if not TQTreeObservable.addObservable(myBSMTriggerWeight):
            INFO("failed to add myVptReweight observable")
            return False
        print(myBSMTriggerWeight.getExpression()) 

    for name in ["MuTrigSysStatUp" ] : 
        myBSMTriggerWeight= BSMTriggerWeight("bsmtriggerweight"+name)
        if not TQTreeObservable.addObservable(myBSMTriggerWeight):
            INFO("failed to add myVptReweight observable")
            return False
        print(myBSMTriggerWeight.getExpression()) 

    for name in ["MuTrigSysStatDo" ] : 
        myBSMTriggerWeight= BSMTriggerWeight("bsmtriggerweight"+name)
        if not TQTreeObservable.addObservable(myBSMTriggerWeight):
            INFO("failed to add myVptReweight observable")
            return False
        print(myBSMTriggerWeight.getExpression()) 

    for name in ["MuTrigSysSystUp" ] : 
        myBSMTriggerWeight= BSMTriggerWeight("bsmtriggerweight"+name)
        if not TQTreeObservable.addObservable(myBSMTriggerWeight):
            INFO("failed to add myVptReweight observable")
            return False
        print(myBSMTriggerWeight.getExpression()) 

    for name in ["MuTrigSysSystDo" ] : 
        myBSMTriggerWeight= BSMTriggerWeight("bsmtriggerweight"+name)
        if not TQTreeObservable.addObservable(myBSMTriggerWeight):
            INFO("failed to add myVptReweight observable")
            return False
        print(myBSMTriggerWeight.getExpression()) 

    for name in ["ElTrigSysUp" ] : 
        myBSMTriggerWeight= BSMTriggerWeight("bsmtriggerweight"+name)
        if not TQTreeObservable.addObservable(myBSMTriggerWeight):
            INFO("failed to add myVptReweight observable")
            return False
        print(myBSMTriggerWeight.getExpression()) 

    for name in ["ElTrigSysDo" ] : 
        myBSMTriggerWeight= BSMTriggerWeight("bsmtriggerweight"+name)
        if not TQTreeObservable.addObservable(myBSMTriggerWeight):
            INFO("failed to add myVptReweight observable")
            return False
        print(myBSMTriggerWeight.getExpression()) 

    return True
