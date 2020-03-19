import QFramework
from BSMtautauCAF import MTtot

def addObservables(config):
    myObs = MTtot("MTtot")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
