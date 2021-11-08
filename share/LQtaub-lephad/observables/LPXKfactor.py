import QFramework
from BSMtautauCAF import LPXKfactor

def addObservables(config):
    myObs = LPXKfactor("LPXKfactor")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
