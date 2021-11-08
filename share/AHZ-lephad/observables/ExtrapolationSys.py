import QFramework
from BSMtautauCAF import ExtrapolationSys

def addObservables(config):
    myObs = ExtrapolationSys("ExtrapolationSys")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
