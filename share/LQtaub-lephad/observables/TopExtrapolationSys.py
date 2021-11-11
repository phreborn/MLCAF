import QFramework
from BSMtautauCAF import TopExtrapolationSys

def addObservables(config):
    myObs = TopExtrapolationSys("TopExtrapolationSys")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
