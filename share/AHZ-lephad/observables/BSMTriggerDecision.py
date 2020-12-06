import QFramework
from BSMtautauCAF import BSMTriggerDecision

def addObservables(config):
    myObs = BSMTriggerDecision("BSMTriggerDecision")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
