import QFramework
from BSMtautauCAF import ScaleFactor

def addObservables(config):
    myObs = ScaleFactor("ScaleFactor")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
