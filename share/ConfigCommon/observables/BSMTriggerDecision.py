import QFramework
import ROOT
from Htautau import BSMTriggerDecision

def addObservables(config):
#    myBSMTriggerDecision= BSMTriggerDecision("bsmtriggerdecision")
#    variation = config.getTagStringDefault("variation","nominal")
#    if not TQTreeObservable.addObservable(myBSMTriggerDecision):
#        INFO("failed to add myVptRedecision observable")
#        return False
#    INFO("using decisions for variation '{:s}'".format(variation))
#    print(myBSMTriggerDecision.getExpression())
#    return True
#
    for name in [""]:
        myBSMTriggerDecision = BSMTriggerDecision("bsmtriggerdecision"+name)
        if not QFramework.TQTreeObservable.addObservable(myBSMTriggerDecision,"BSMTriggerDecision"):
            INFO("failed to add myBSMTriggerDecision observable")
            return False
#        print(myBSMTriggerDecision.getExpression())

   # for name in ["data"] :
   #     myBSMTriggerDecision= BSMTriggerDecision("bsmtriggerdecision"+name)
   #     if not TQTreeObservable.addObservable(myBSMTriggerDecision):
   #         INFO("failed to add myBSMTriggerDecision observable")
   #         return False
   #     print(myBSMTriggerDecision.getExpression())

    return True
