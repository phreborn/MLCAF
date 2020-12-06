import QFramework
from BSMtautauCAF import TopTheorySys

def addObservables(config):
    myObs = TopTheorySys("TopTheorySys")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
