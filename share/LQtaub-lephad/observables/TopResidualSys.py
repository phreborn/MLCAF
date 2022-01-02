import QFramework
from BSMtautauCAF import TopResidualSys

def addObservables(config):
    myObs = TopResidualSys("TopResidualSys")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
